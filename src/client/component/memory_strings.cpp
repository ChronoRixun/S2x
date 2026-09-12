#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "command.hpp"
#include "console/console.hpp"

#include "game/game.hpp"

#include <utils/io.hpp>
#include <utils/string.hpp>

// findstrings <text> [minimum length]
// Scans the loaded game image for printable strings containing the text and
// writes them with their image-relative offsets to s2x/dump/strings/<text>.txt.
// The packed binary only reveals its strings in memory, so this is the way to
// find protocol field names, dvar names and similar constants.
namespace memory_strings
{
	namespace
	{
		constexpr std::size_t maximum_matches = 20000;
		constexpr std::size_t console_preview = 20;

		bool is_printable(const unsigned char character)
		{
			return character >= 0x20 && character <= 0x7e;
		}

		bool contains_insensitive(const std::string_view haystack, const std::string& needle_lower)
		{
			if (needle_lower.size() > haystack.size())
			{
				return false;
			}

			for (std::size_t start = 0; start + needle_lower.size() <= haystack.size(); ++start)
			{
				auto matches = true;
				for (std::size_t i = 0; i < needle_lower.size() && matches; ++i)
				{
					matches = std::tolower(static_cast<unsigned char>(haystack[start + i])) == needle_lower[i];
				}

				if (matches)
				{
					return true;
				}
			}

			return false;
		}

		void scan_region(const char* data, const std::size_t size, const std::size_t base_offset,
			const std::string& needle_lower, const std::size_t minimum_length, std::string& output,
			std::size_t& matches)
		{
			std::size_t run_start = 0;
			auto in_run = false;

			for (std::size_t i = 0; i <= size && matches < maximum_matches; ++i)
			{
				const auto printable = i < size && is_printable(static_cast<unsigned char>(data[i]));
				if (printable)
				{
					if (!in_run)
					{
						run_start = i;
						in_run = true;
					}

					continue;
				}

				if (!in_run)
				{
					continue;
				}

				in_run = false;
				const std::string_view run{data + run_start, i - run_start};
				if (run.size() >= minimum_length && contains_insensitive(run, needle_lower))
				{
					output += utils::string::va("0x%zX  ", base_offset + run_start);
					output.append(run.data(), run.size());
					output += "\r\n";
					++matches;
				}
			}
		}

		void find_strings(const command::params& params)
		{
			if (params.size() < 2)
			{
				console::info("Usage: findstrings <text> [minimum length]\n");
				return;
			}

			const std::string needle = params[1];
			const auto needle_lower = utils::string::to_lower(needle);
			const auto minimum_length = params.size() > 2 ? std::max(std::atoi(params[2]), 1) : 6;

			const auto base = game::get_base();
			const auto* dos_header = reinterpret_cast<const IMAGE_DOS_HEADER*>(base);
			const auto* nt_headers = reinterpret_cast<const IMAGE_NT_HEADERS*>(base + dos_header->e_lfanew);
			const std::size_t image_size = nt_headers->OptionalHeader.SizeOfImage;

			std::string output{};
			std::size_t matches = 0;
			std::size_t offset = 0;

			while (offset < image_size && matches < maximum_matches)
			{
				MEMORY_BASIC_INFORMATION info{};
				if (!VirtualQuery(reinterpret_cast<const void*>(base + offset), &info, sizeof(info)))
				{
					break;
				}

				const auto region_start = reinterpret_cast<std::size_t>(info.BaseAddress);
				const auto region_end = std::min(region_start + info.RegionSize, base + image_size);
				const auto readable = info.State == MEM_COMMIT && !(info.Protect & PAGE_GUARD) &&
					(info.Protect & (PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ |
						PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY));

				const auto scan_start = std::max(region_start, base + offset);
				if (readable && region_end > scan_start)
				{
					scan_region(reinterpret_cast<const char*>(scan_start), region_end - scan_start,
						scan_start - base, needle_lower, static_cast<std::size_t>(minimum_length), output, matches);
				}

				offset = region_end - base;
			}

			auto file_name = utils::string::to_lower(needle);
			for (auto& character : file_name)
			{
				if (!std::isalnum(static_cast<unsigned char>(character)))
				{
					character = '_';
				}
			}

			const auto path = utils::string::va("s2x/dump/strings/%s.txt", file_name.data());
			if (!utils::io::write_file(path, output))
			{
				console::error("findstrings: failed to write %s\n", path);
			}

			console::info("findstrings: %zu string(s) containing '%s' (image size 0x%zX) -> %s\n",
				matches, needle.data(), image_size, path);

			std::size_t shown = 0;
			for (const auto& line : utils::string::split(output, '\n'))
			{
				if (shown++ >= console_preview)
				{
					break;
				}

				if (!line.empty())
				{
					console::info("%s\n", line.data());
				}
			}
		}
	}

	class component final : public generic_component
	{
	public:
		void post_unpack() override
		{
			command::add("findstrings", find_strings);
		}
	};
}

REGISTER_COMPONENT(memory_strings::component)
