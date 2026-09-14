#include <std_include.hpp>
#include <fstream>
#include "loader/component_loader.hpp"

#include "command.hpp"
#include "filesystem.hpp"
#include "scripting.hpp"
#include "console/console.hpp"

#include "game/game.hpp"

#include <utils/hook.hpp>
#include <utils/io.hpp>
#include <utils/memory.hpp>
#include <utils/nt.hpp>
#include <utils/string.hpp>

// Loose-file string table overrides.
//
// A CSV placed at the asset path inside one of the loose file search paths
// (for example %LOCALAPPDATA%\s2x\data\mp\botDivisionTable.csv or
// <game>\s2x\mp\botDivisionTable.csv) replaces the packaged string table
// asset of the same name. Tables that do not exist in any fastfile can be
// added the same way.
namespace stringtable_override
{
	namespace
	{
		constexpr std::size_t max_file_size = 8u * 1024u * 1024u;
		constexpr std::size_t max_rows = 65535;
		constexpr std::size_t max_columns = 1024;
		// Rows x columns after ragged-row padding. The dimension limits alone
		// allow 67 million cells from a 65 KB file of commas and newlines.
		constexpr std::size_t max_table_cells = 1u << 20;
		constexpr std::size_t hash_sample_cells = 64;

		utils::hook::detour db_find_x_asset_header_hook;

		// Override tables are never freed. The engine may cache StringTable and
		// cell pointers across levels, so replaced tables are leaked instead.
		utils::memory::allocator table_allocator;
		constexpr char empty_cell[] = "";

		using hash_function = int(*)(const char*);

		int hash_lowercase(const char* text)
		{
			auto hash = 0u;
			for (; *text; ++text)
			{
				hash = static_cast<unsigned int>(std::tolower(static_cast<unsigned char>(*text))) + 31u * hash;
			}

			return static_cast<int>(hash);
		}

		int hash_exact(const char* text)
		{
			auto hash = 0u;
			for (; *text; ++text)
			{
				hash = static_cast<unsigned char>(*text) + 31u * hash;
			}

			return static_cast<int>(hash);
		}

		int hash_none(const char*)
		{
			return 0;
		}

		struct hash_candidate
		{
			const char* label;
			hash_function function;
		};

		constexpr hash_candidate hash_candidates[] =
		{
			{"lowercase * 31", hash_lowercase},
			{"case-sensitive * 31", hash_exact},
			{"none", hash_none},
		};

		std::mutex hash_mutex;
		hash_function verified_hash{};
		std::atomic_bool overrides_disabled{false};
		std::atomic_bool unverified_hash_reported{false};

		struct cache_entry
		{
			game::StringTable* table{};
			std::string real_path{};
			std::filesystem::file_time_type write_time{};
			// The asset name as requested, so invalidation can re-resolve the
			// winning search path rather than only re-stat the old one.
			std::string name{};
		};

		std::mutex cache_mutex;
		std::unordered_map<std::string, cache_entry> cache;

		bool is_safe_asset_name(const std::string_view name)
		{
			return !name.empty()
				&& name.find("..") == std::string_view::npos
				&& name.find(':') == std::string_view::npos
				&& name.front() != '/'
				&& name.front() != '\\';
		}

		// The engine compares cell hashes before strings during row lookups
		// (tablelookup and friends). Confirm our formula against a packaged
		// table before handing out any override.
		void verify_hash_formula(const game::StringTable* stock)
		{
			if (!stock || !stock->values || stock->rowCount <= 0 || stock->columnCount <= 0)
			{
				return;
			}

			std::lock_guard _(hash_mutex);
			if (verified_hash || overrides_disabled)
			{
				return;
			}

			const auto total_cells = static_cast<std::size_t>(stock->rowCount) * static_cast<std::size_t>(stock->columnCount);

			for (const auto& candidate : hash_candidates)
			{
				auto sampled = 0u;
				auto matches = true;

				for (std::size_t i = 0; i < total_cells && sampled < hash_sample_cells && matches; ++i)
				{
					const auto& cell = stock->values[i];
					if (!cell.string || !*cell.string)
					{
						continue;
					}

					++sampled;
					matches = candidate.function(cell.string) == cell.hash;
				}

				if (sampled == 0)
				{
					// Nothing to compare against yet; try again with the next table.
					return;
				}

				if (matches)
				{
					verified_hash = candidate.function;
					console::info("[stringtable] cell hash formula '%s' verified against '%s'\n",
						candidate.label, stock->name ? stock->name : "?");
					return;
				}
			}

			overrides_disabled = true;
			console::warn("[stringtable] no known cell hash formula matches '%s'; loose string table overrides are disabled\n",
				stock->name ? stock->name : "?");
		}

		hash_function get_hash_function()
		{
			std::lock_guard _(hash_mutex);
			if (verified_hash)
			{
				return verified_hash;
			}

			if (!unverified_hash_reported.exchange(true))
			{
				console::warn("[stringtable] no packaged table was seen yet; using the default cell hash formula unverified\n");
			}

			return hash_lowercase;
		}

		struct csv_data
		{
			std::vector<std::vector<std::string>> rows{};
			std::size_t columns{};
		};

		enum class csv_parse_result
		{
			ok,
			too_many_cells,
			unterminated_quote,
		};

		// Rows are separated by '\n' ('\r' is ignored), cells by ','. A cell
		// that starts with a double quote is parsed RFC 4180 style so dumped
		// tables round-trip; anything else is taken verbatim, like the packaged
		// tables. A trailing newline does not create a row; blank lines do, so
		// row indices match editor line numbers. A quoted cell that never closes
		// is rejected rather than silently swallowing the rest of the file.
		csv_parse_result parse_csv(const std::string& text, csv_data& out)
		{
			std::vector<std::string> row{};
			std::string cell{};
			auto at_cell_start = true;

			const auto end_cell = [&]
			{
				row.emplace_back(std::move(cell));
				cell.clear();
				at_cell_start = true;
			};

			const auto end_row = [&]
			{
				end_cell();
				out.columns = std::max(out.columns, row.size());
				out.rows.emplace_back(std::move(row));
				row.clear();
			};

			const auto size = text.size();
			for (std::size_t i = 0; i < size;)
			{
				const auto character = text[i];

				if (at_cell_start && character == '"')
				{
					auto closed = false;
					++i;
					while (i < size)
					{
						if (text[i] == '"')
						{
							if (i + 1 < size && text[i + 1] == '"')
							{
								cell += '"';
								i += 2;
								continue;
							}

							++i;
							closed = true;
							break;
						}

						cell += text[i++];
					}

					if (!closed)
					{
						return csv_parse_result::unterminated_quote;
					}

					at_cell_start = false;
					continue;
				}

				if (character == ',')
				{
					end_cell();
				}
				else if (character == '\n')
				{
					end_row();
				}
				else if (character != '\r')
				{
					cell += character;
					at_cell_start = false;
				}

				++i;

				// The row being built counts too: a line of a million commas must
				// fail at the 1,025th cell, not after building a million strings.
				if (out.rows.size() > max_rows || out.columns > max_columns || row.size() > max_columns)
				{
					return csv_parse_result::too_many_cells;
				}
			}

			// A final row without a trailing newline still counts, including one
			// whose last cell is a quoted empty string (""): the quote consumed
			// the cell start even though no text was produced.
			if (!cell.empty() || !row.empty() || !at_cell_start)
			{
				end_row();
			}

			return out.rows.size() <= max_rows && out.columns <= max_columns
				? csv_parse_result::ok
				: csv_parse_result::too_many_cells;
		}

		// Nullptr when the padded table would exceed the cell budget or the
		// allocation fails; nothing is published in that case.
		game::StringTable* build_table(const std::string& name, const csv_data& csv)
		{
			const auto row_count = csv.rows.size();
			const auto column_count = std::max<std::size_t>(csv.columns, 1);
			if (row_count == 0 || column_count > max_table_cells / row_count)
			{
				return nullptr;
			}

			const auto rows = static_cast<int>(row_count);
			const auto columns = static_cast<int>(column_count);
			const auto hash = get_hash_function();

			auto* values = table_allocator.allocate_array<game::StringTableCell>(row_count * column_count);
			auto* table = values ? table_allocator.allocate<game::StringTable>() : nullptr;
			if (!table)
			{
				return nullptr;
			}

			table->name = table_allocator.duplicate_string(name);
			table->rowCount = rows;
			table->columnCount = columns;
			table->values = values;

			for (auto row = 0; row < rows; ++row)
			{
				const auto& cells = csv.rows[row];
				for (auto column = 0; column < columns; ++column)
				{
					auto& cell = table->values[row * columns + column];
					const auto has_value = column < static_cast<int>(cells.size()) && !cells[column].empty();

					cell.string = has_value ? table_allocator.duplicate_string(cells[column]) : empty_cell;
					cell.hash = hash(cell.string);
				}
			}

			return table;
		}

		// Reads a loose file only after checking its size on the open stream, so
		// an oversized file is rejected before any buffer is allocated.
		bool read_bounded(const std::string& path, std::string& data, bool& oversized)
		{
			oversized = false;
			std::ifstream stream(std::filesystem::path{path}, std::ios::binary);
			if (!stream.is_open())
			{
				return false;
			}

			stream.seekg(0, std::ios::end);
			const auto size = stream.tellg();
			if (size < 0)
			{
				return false;
			}

			if (static_cast<std::uintmax_t>(size) > max_file_size)
			{
				oversized = true;
				return false;
			}

			stream.seekg(0, std::ios::beg);
			data.resize(static_cast<std::size_t>(size));
			stream.read(data.data(), size);
			return static_cast<std::streamsize>(stream.gcount()) == size;
		}

		game::StringTable* find_override(const std::string& name)
		{
			if (!is_safe_asset_name(name))
			{
				return nullptr;
			}

			const auto key = utils::string::to_lower(name);

			{
				std::lock_guard _(cache_mutex);
				const auto entry = cache.find(key);
				if (entry != cache.end())
				{
					return entry->second.table;
				}
			}

			// Disk access happens without the cache lock held.
			cache_entry entry{};
			entry.name = name;
			std::string data{};
			auto oversized = false;

			if (filesystem::find_file(name, &entry.real_path) && !read_bounded(entry.real_path, data, oversized))
			{
				if (oversized)
				{
					console::error("[stringtable] '%s' exceeds %zu bytes; using the packaged table\n",
						entry.real_path.data(), max_file_size);
				}
				else
				{
					console::error("[stringtable] '%s' could not be read; using the packaged table\n",
						entry.real_path.data());
				}
			}
			else if (!entry.real_path.empty())
			{
				{
					csv_data csv{};
					const auto result = parse_csv(data, csv);
					if (result == csv_parse_result::ok && (entry.table = build_table(name, csv)) == nullptr)
					{
						console::error("[stringtable] '%s' pads to more than %zu cells; using the packaged table\n",
							entry.real_path.data(), max_table_cells);
					}
					else if (result == csv_parse_result::ok)
					{
						std::error_code error{};
						entry.write_time = std::filesystem::last_write_time(entry.real_path, error);

						console::info("[stringtable] loaded '%s' from '%s' (%d rows x %d columns)\n",
							name.data(), entry.real_path.data(), entry.table->rowCount, entry.table->columnCount);
					}
					else if (result == csv_parse_result::unterminated_quote)
					{
						console::error("[stringtable] '%s' has an unterminated quoted cell on row %zu; using the packaged table\n",
							entry.real_path.data(), csv.rows.size() + 1);
					}
					else
					{
						console::error("[stringtable] '%s' has too many rows or columns; using the packaged table\n",
							entry.real_path.data());
					}
				}
			}

			std::lock_guard _(cache_mutex);
			return cache.try_emplace(key, std::move(entry)).first->second.table;
		}

		game::XAssetHeader db_find_x_asset_header_stub(const game::XAssetType type, const char* name,
			const int allow_create_default)
		{
			if (type != game::ASSET_TYPE_STRINGTABLE || !name || !*name || overrides_disabled)
			{
				return db_find_x_asset_header_hook.invoke<game::XAssetHeader>(type, name, allow_create_default);
			}

			{
				std::unique_lock lock(hash_mutex);
				const auto verified = verified_hash != nullptr;
				lock.unlock();

				if (!verified)
				{
					const auto stock = db_find_x_asset_header_hook.invoke<game::XAssetHeader>(type, name, 0);
					verify_hash_formula(stock.stringTable);

					if (overrides_disabled)
					{
						return stock.stringTable
							? stock
							: db_find_x_asset_header_hook.invoke<game::XAssetHeader>(type, name, allow_create_default);
					}
				}
			}

			if (auto* table = find_override(name))
			{
				game::XAssetHeader header{};
				header.stringTable = table;
				return header;
			}

			return db_find_x_asset_header_hook.invoke<game::XAssetHeader>(type, name, allow_create_default);
		}

		// Called on level shutdown so edited or newly added files are picked up
		// by the next map load without restarting the game.
		void invalidate_changed_entries()
		{
			std::lock_guard _(cache_mutex);

			for (auto entry = cache.begin(); entry != cache.end();)
			{
				auto drop = entry->second.table == nullptr;

				if (!drop)
				{
					// A copy that appeared in a higher-priority search path (AppData
					// before the game folder) must win on the next map even though the
					// file that was loaded is unchanged.
					std::string current_path{};
					drop = !filesystem::find_file(entry->second.name, &current_path) ||
						current_path != entry->second.real_path;
				}

				if (!drop)
				{
					std::error_code error{};
					const auto write_time = std::filesystem::last_write_time(entry->second.real_path, error);
					drop = error || write_time != entry->second.write_time;
				}

				entry = drop ? cache.erase(entry) : std::next(entry);
			}
		}

		void clear_cache()
		{
			std::lock_guard _(cache_mutex);
			cache.clear();
		}

		std::string escape_csv_cell(const char* value)
		{
			std::string text = value ? value : "";
			if (text.find_first_of(",\"\r\n") == std::string::npos)
			{
				return text;
			}

			return "\"" + utils::string::replace(text, "\"", "\"\"") + "\"";
		}

		void dump_string_table(const command::params& params)
		{
			if (params.size() < 2)
			{
				console::info("Usage: dumpstringtable <asset name> [output file]\n");
				console::info("Writes a loaded string table as CSV to s2x/dump/<asset name> (or s2x/<output file>).\n");
				console::info("Example: dumpstringtable mp/botDivisionTable.csv\n");
				return;
			}

			const std::string name = params[1];
			if (!is_safe_asset_name(name))
			{
				console::error("dumpstringtable: invalid asset name '%s'\n", name.data());
				return;
			}

			auto* table = overrides_disabled ? nullptr : find_override(name);
			if (!table)
			{
				if (!game::DB_XAssetExists(game::ASSET_TYPE_STRINGTABLE, name.data()))
				{
					console::error("dumpstringtable: string table '%s' is not loaded (use listassetpool %d <filter> to list names)\n",
						name.data(), static_cast<int>(game::ASSET_TYPE_STRINGTABLE));
					return;
				}

				table = game::DB_FindXAssetHeader(game::ASSET_TYPE_STRINGTABLE, name.data(), 0).stringTable;
			}

			if (!table || !table->values)
			{
				console::error("dumpstringtable: string table '%s' has no data\n", name.data());
				return;
			}

			std::string output{};
			for (auto row = 0; row < table->rowCount; ++row)
			{
				for (auto column = 0; column < table->columnCount; ++column)
				{
					if (column)
					{
						output += ',';
					}

					output += escape_csv_cell(table->values[row * table->columnCount + column].string);
				}

				output += "\r\n";
			}

			const auto base = utils::nt::library{}.get_folder() / "s2x";
			const auto path = params.size() >= 3
				? base / params[2]
				: base / "dump" / name;

			if (!utils::io::write_file(path.generic_string(), output))
			{
				console::error("dumpstringtable: failed to write '%s'\n", path.generic_string().data());
				return;
			}

			console::info("dumpstringtable: wrote '%s' (%d rows x %d columns) to '%s'\n",
				name.data(), table->rowCount, table->columnCount, path.generic_string().data());
		}
	}

	class component final : public generic_component
	{
	public:
		void post_unpack() override
		{
			db_find_x_asset_header_hook.create(game::DB_FindXAssetHeader, db_find_x_asset_header_stub);

			scripting::on_shutdown([](int)
			{
				invalidate_changed_entries();
			});

			command::add("dumpstringtable", dump_string_table);

			command::add("reloadstringtables", []
			{
				clear_cache();
				console::info("[stringtable] cache cleared; loose tables are reloaded on their next lookup\n");
			});
		}
	};
}

REGISTER_COMPONENT(stringtable_override::component)
