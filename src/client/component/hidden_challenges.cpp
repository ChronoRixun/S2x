#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "hidden_challenges.hpp"

#include "component/achievement_sync.hpp"
#include "component/console/console.hpp"
#include "component/scheduler.hpp"
#include "component/scripting.hpp"

#include "game/game.hpp"
#include "game/demonware/achievement_store.hpp"
#include "game/demonware/reward_game_event.hpp"

#include <utils/string.hpp>

#include <charconv>
#include <deque>
#include <mutex>
#include <unordered_map>

namespace hidden_challenges
{
	using reward_game_event = demonware::reward_game_events::event;

	namespace
	{
		constexpr auto hidden_challenge_event_id = 16;
		constexpr std::string_view hidden_challenge_event_name = "zombies";
		constexpr auto hidden_challenge_kind = 5;
		constexpr auto maximum_pending_events = 128u;

		constexpr auto reference_column = 0;
		constexpr auto category_challenges_column = 4;
		constexpr auto achievement_id_column = 5;
		constexpr auto challenge_bit_column = 5;

		constexpr auto definition_id_column = 0;
		constexpr auto definition_name_column = 1;
		constexpr auto definition_kind_column = 2;
		constexpr auto definition_event_column = 3;
		constexpr auto definition_predicate_column = 4;

		constexpr auto event_id_column = 0;
		constexpr auto event_name_column = 1;
		constexpr auto event_class_column = 2;

		struct hidden_group
		{
			int value;
			int achievement_id;
			std::string_view diagnostic_prefix;
		};

		// Selector 3 contains the stock hidden-character group value. The parent AE IDs
		// join the shipped tables, while the prefixes are only used in diagnostics.
		// Group 22 is intentionally unused by the stock mapping; selector 4 is a
		// zero-based challenge slot within the resolved group.
		constexpr std::array hidden_groups
		{
			hidden_group{1, 363, "treasure_set"},
			hidden_group{2, 365, "raven_set"},
			hidden_group{3, 366, "assassin_set"},
			hidden_group{4, 367, "survivalist_set"},
			hidden_group{5, 368, "mountain_man_set"},
			hidden_group{6, 369, "bat_elite_set"},
			hidden_group{7, 64, "survivalist_origin_set"},
			hidden_group{8, 65, "survivalist_bat_set"},
			hidden_group{9, 66, "survivalist_blood_set"},
			hidden_group{10, 67, "hunter_origin_set"},
			hidden_group{11, 68, "hunter_bat_set"},
			hidden_group{12, 69, "hunter_blood_set"},
			hidden_group{13, 70, "mountain_man_origin_set"},
			hidden_group{14, 71, "mountain_man_bat_set"},
			hidden_group{15, 72, "mountain_man_blood_set"},
			hidden_group{16, 73, "assassin_origin_set"},
			hidden_group{17, 74, "assassin_bat_set"},
			hidden_group{18, 75, "assassin_blood_set"},
			hidden_group{19, 350, "surgeon_set"},
			hidden_group{20, 351, "rebel_set"},
			hidden_group{21, 568, "super_soldier_set"},
			hidden_group{23, 1096, "arrow_set"},
			hidden_group{24, 1097, "captain_set"},
			hidden_group{25, 1098, "explorer_set"},
			hidden_group{26, 1136, "african_set"},
			hidden_group{27, 1137, "outlaw_set"},
			hidden_group{28, 1138, "arabic_set"},
			hidden_group{29, 1141, "wicht_set"},
		};

		// Zombies main-quest progression is reported through dw/dwGameEvents.csv
		// events 41-44. The Tortured Path chapter is resolved from the map being
		// played and attached to the event; chapter indices follow the DLC3
		// achievement order (ship, windmill, thule).
		constexpr std::string_view map_won_event_name = "zombies_map_won";
		constexpr std::string_view survival_unlock_event_name = "zombies_dlc3_sv_unlock";
		constexpr std::string_view easter_egg_unlock_event_name = "zombies_dlc3_ee_unlock";
		constexpr std::string_view skull_unlock_event_name = "zombies_dlc3_skull_unlock";
		// Diagnostics (event dumps, receipts, unmapped-event notes) print only when
		// this dvar is on; persisted changes are always logged.
		constexpr auto reward_event_log_dvar_name = "s2x_log_reward_events";

		constexpr int chapter_completion_achievement_id = 1112; // shotgun_maps_complete_zm
		constexpr int survival_unlock_achievement_id = 1114;    // dlc3_survival_unlock_complete_zm
		constexpr int skull_achievement_id = 761;               // zombies_dlc3_redskull
		// mp/zombieDlc3MapInfoTable.csv lists the chapters: mp_zombie_windmill (1),
		// mp_zombie_dnk (2), mp_zombie_dig_02 (3). Their Easter egg achievements are
		// zombies_dlc3_ee_windmill (759), zombies_dlc3_ee_ship (758) and
		// zombies_dlc3_ee_thule (760).
		constexpr auto chapter_table_name = "mp/zombiedlc3mapinfotable.csv";
		constexpr auto chapter_table_map_column = 0;
		constexpr auto chapter_table_chapter_column = 1;
		constexpr std::array chapter_easter_egg_achievement_ids{759, 758, 760};
		constexpr std::uint16_t chapter_completion_target = (1u << chapter_easter_egg_achievement_ids.size()) - 1;

		struct hidden_challenge_definition
		{
			std::string diagnostic_prefix{};
			std::string achievement_name{};
			std::string event_name{};
			int achievement_kind{};
			std::uint16_t full_mask{};
		};

		// A queued event and the chapter it was attributed to when it arrived. The
		// chapter travels beside the event, never inside its parameters, so a
		// selector in the payload cannot pose as it.
		struct pending_event
		{
			reward_game_event event{};
			std::uint64_t chapter{unknown_chapter};
		};

		// The level being played, captured on the main thread at level start, so
		// the Demonware worker never touches engine state to attribute an event.
		struct level_context
		{
			bool active{};
			std::uint64_t chapter{unknown_chapter};
			std::string map{};
		};

		std::atomic_bool accepting_events{};
		std::mutex pending_event_mutex{};
		std::deque<pending_event> pending_events{};
		std::mutex level_context_mutex{};
		level_context current_level{};
		const game::dvar_t* log_reward_events{};
		// The dvar is engine-owned and read on the main thread only; the worker
		// sees this copy, refreshed by the main-thread processor.
		std::atomic_bool diagnostics_enabled{};
		std::unordered_map<int, hidden_challenge_definition> definitions{};
		bool definitions_complete{};
		std::size_t last_reported_definition_count{std::numeric_limits<std::size_t>::max()};
		std::chrono::steady_clock::time_point next_definition_load{};

		const char* get_cell(const game::StringTable* table, const int row, const int column)
		{
			if (!table || !table->values || row < 0 || row >= table->rowCount || column < 0 ||
				column >= table->columnCount)
			{
				return nullptr;
			}

			return table->values[row * table->columnCount + column].string;
		}

		bool parse_integer(const char* text, int& value)
		{
			if (!text || !*text)
			{
				return false;
			}

			const auto* end = text + std::strlen(text);
			const auto result = std::from_chars(text, end, value);
			return result.ec == std::errc{} && result.ptr == end;
		}

		std::string_view trim(std::string_view value)
		{
			const auto first = value.find_first_not_of(" \t");
			if (first == std::string_view::npos)
			{
				return {};
			}

			const auto last = value.find_last_not_of(" \t");
			return value.substr(first, last - first + 1);
		}

		std::vector<std::string_view> split_references(const char* list)
		{
			std::vector<std::string_view> result{};
			if (!list || !*list)
			{
				return result;
			}

			std::string_view remaining{list};
			while (!remaining.empty())
			{
				const auto separator = remaining.find(',');
				const auto reference = trim(remaining.substr(0, separator));
				if (!reference.empty())
				{
					result.push_back(reference);
				}

				if (separator == std::string_view::npos)
				{
					break;
				}

				remaining.remove_prefix(separator + 1);
			}

			return result;
		}

		int find_row(const game::StringTable* table, const int column, const std::string_view value)
		{
			for (auto row = 0; table && row < table->rowCount; ++row)
			{
				const auto* cell = get_cell(table, row, column);
				if (cell && value == cell)
				{
					return row;
				}
			}

			return -1;
		}

		int find_category_row(const game::StringTable* table, const int achievement_id)
		{
			for (auto row = 0; table && row < table->rowCount; ++row)
			{
				const auto* reference = get_cell(table, row, reference_column);
				int row_achievement_id{};
				if (!reference || !std::string_view{reference}.starts_with("category"))
				{
					continue;
				}

				if (parse_integer(get_cell(table, row, achievement_id_column), row_achievement_id) &&
					row_achievement_id == achievement_id)
				{
					return row;
				}
			}

			return -1;
		}

		bool get_category_mask(const game::StringTable* table, const int category_row,
			std::uint16_t& full_mask)
		{
			const auto challenges = split_references(get_cell(table, category_row,
				category_challenges_column));
			if (challenges.empty())
			{
				return false;
			}

			std::uint32_t mask{};
			for (const auto challenge : challenges)
			{
				const auto challenge_row = find_row(table, reference_column, challenge);
				int bit{};
				if (challenge_row < 0 ||
					!parse_integer(get_cell(table, challenge_row, challenge_bit_column), bit) ||
					bit <= 0 || bit > std::numeric_limits<std::uint16_t>::digits)
				{
					return false;
				}

				const auto bit_mask = 1u << (bit - 1);
				if ((mask & bit_mask) != 0)
				{
					return false;
				}

				mask |= bit_mask;
			}

			if ((mask != 7 && mask != 31) ||
				mask > std::numeric_limits<std::uint16_t>::max())
			{
				return false;
			}

			full_mask = static_cast<std::uint16_t>(mask);
			return true;
		}

		bool build_definition(const hidden_group& group, const game::StringTable* challenges,
			const game::StringTable* achievement_definitions, const game::StringTable* game_events,
			hidden_challenge_definition& result)
		{
			const auto category_row = find_category_row(challenges, group.achievement_id);
			std::uint16_t full_mask{};
			if (category_row < 0 ||
				!get_category_mask(challenges, category_row, full_mask))
			{
				return false;
			}

			const auto definition_row = find_row(achievement_definitions, definition_id_column,
				std::to_string(group.achievement_id));
			int kind{};
			int event_id{};
			if (definition_row < 0 ||
				!parse_integer(get_cell(achievement_definitions, definition_row,
					definition_kind_column), kind) ||
				!parse_integer(get_cell(achievement_definitions, definition_row,
					definition_event_column), event_id) ||
				kind != hidden_challenge_kind || event_id != hidden_challenge_event_id)
			{
				return false;
			}

			const auto* predicate = get_cell(achievement_definitions, definition_row,
				definition_predicate_column);
			const auto* achievement_name = get_cell(achievement_definitions, definition_row,
				definition_name_column);
			if ((predicate && *predicate) || !achievement_name || !*achievement_name ||
				!std::string_view{achievement_name}.ends_with("_gear_bitfield_zm"))
			{
				return false;
			}

			const auto event_row = find_row(game_events, event_id_column, std::to_string(event_id));
			int event_class{};
			const auto* event_name = get_cell(game_events, event_row, event_name_column);
			if (event_row < 0 || !event_name || hidden_challenge_event_name != event_name ||
				!parse_integer(get_cell(game_events, event_row, event_class_column), event_class) ||
				event_class != 0)
			{
				return false;
			}

			result.diagnostic_prefix = group.diagnostic_prefix;
			result.achievement_name = achievement_name;
			result.event_name = event_name;
			result.achievement_kind = kind;
			result.full_mask = full_mask;
			return true;
		}

		void load_definitions()
		{
			if (definitions_complete)
			{
				return;
			}

			const auto now = std::chrono::steady_clock::now();
			if (now < next_definition_load)
			{
				return;
			}

			next_definition_load = now + 1s;
			const auto* challenges = game::DB_FindXAssetHeader(game::ASSET_TYPE_STRINGTABLE,
				"mp/zombieCostumeChallenges.csv", false).stringTable;
			const auto* achievement_definitions = game::DB_FindXAssetHeader(
				game::ASSET_TYPE_STRINGTABLE, "dw/dwGameChallenges.csv", false).stringTable;
			const auto* game_events = game::DB_FindXAssetHeader(game::ASSET_TYPE_STRINGTABLE,
				"dw/dwGameEvents.csv", false).stringTable;
			if (!challenges || !achievement_definitions || !game_events)
			{
				return;
			}

			if (challenges->rowCount <= 0 || achievement_definitions->rowCount <= 0 ||
				game_events->rowCount <= 0)
			{
				return;
			}

			std::unordered_map<int, hidden_challenge_definition> loaded{};
			for (const auto& group : hidden_groups)
			{
				hidden_challenge_definition definition{};
				if (build_definition(group, challenges, achievement_definitions, game_events, definition))
				{
					loaded.emplace(group.value, std::move(definition));
				}
			}

			if (loaded.size() >= definitions.size())
			{
				definitions = std::move(loaded);
			}

			definitions_complete = definitions.size() == hidden_groups.size();
			if (definitions.size() != last_reported_definition_count)
			{
				console::info("[hidden_challenges] loaded %zu of %zu character groups\n",
					definitions.size(), hidden_groups.size());
				last_reported_definition_count = definitions.size();
			}
		}

		bool get_parameter(const reward_game_event& event, const std::string_view selector,
			std::uint64_t& value)
		{
			bool found{};
			for (const auto& parameter : event.parameters)
			{
				if (parameter.selector != selector)
				{
					continue;
				}

				if (found)
				{
					return false;
				}

				found = true;
				value = parameter.value;
			}

			return found;
		}

		bool get_hidden_challenge_values(const reward_game_event& event,
			std::uint64_t& group_value, std::uint64_t& challenge_value)
		{
			return event.name == hidden_challenge_event_name &&
				get_parameter(event, "3", group_value) &&
				get_parameter(event, "4", challenge_value) &&
				group_value <= std::numeric_limits<int>::max() &&
				challenge_value < std::numeric_limits<std::uint16_t>::digits;
		}

		// Writes an achievement's progress and derives its completion state.
		// Returns whether the record changed.
		bool write_achievement_progress(demonware::achievement_record& record, const int kind,
			const std::uint16_t progress, const std::uint16_t target)
		{
			const auto completed = progress >= target;
			const auto status = completed
				? demonware::achievement_status::finished
				: demonware::achievement_status::in_progress;
			const auto fulfilled_times = completed ? std::max(record.fulfilled_times, 1) : 0;
			const auto completion_timestamp = completed
				? (record.completion_timestamp
					? record.completion_timestamp
					: static_cast<std::uint64_t>(time(nullptr)))
				: 0;

			const auto changed = record.kind != kind ||
				record.progress != progress ||
				record.progress_target != target ||
				record.fulfilled_times != fulfilled_times ||
				record.completion_timestamp != completion_timestamp ||
				record.status != status;
			record.kind = kind;
			record.progress = progress;
			record.progress_target = target;
			record.fulfilled_times = fulfilled_times;
			record.completion_timestamp = completion_timestamp;
			record.status = status;
			return changed;
		}

		void report_mutation(const demonware::achievement_store::mutation_result result,
			const std::string& achievement_name, const std::uint16_t previous_progress,
			const std::uint16_t updated_progress)
		{
			if (result == demonware::achievement_store::mutation_result::save_failed)
			{
				console::error("[hidden_challenges] failed to persist %s\n", achievement_name.data());
				return;
			}

			if (result == demonware::achievement_store::mutation_result::updated)
			{
				console::info("[hidden_challenges] %s: 0x%02X -> 0x%02X\n",
					achievement_name.data(), previous_progress, updated_progress);
				achievement_sync::request_refresh();
			}
		}

		void update_progress(const hidden_challenge_definition& definition, const int challenge_index)
		{
			const auto challenge_mask = static_cast<std::uint16_t>(1u << challenge_index);
			std::uint16_t previous_progress{};
			std::uint16_t updated_progress{};
			const auto result = demonware::achievement_store::mutate(definition.achievement_name,
				[&](demonware::achievement_record& record)
				{
					previous_progress = record.progress;
					updated_progress = static_cast<std::uint16_t>(
						(record.progress & definition.full_mask) | challenge_mask);
					return write_achievement_progress(record, definition.achievement_kind,
						updated_progress, definition.full_mask);
				});

			report_mutation(result, definition.achievement_name, previous_progress, updated_progress);
		}

		// Event names and selectors come off the wire; control characters must not
		// reach the log as line breaks or terminal escapes.
		std::string sanitize(const std::string_view text)
		{
			std::string clean{text};
			for (auto& character : clean)
			{
				if (static_cast<unsigned char>(character) < 0x20 || character == 0x7F)
				{
					character = '?';
				}
			}

			return clean;
		}

		std::string describe_event(const reward_game_event& event)
		{
			auto description = "'" + sanitize(event.name) + "'";
			for (const auto& parameter : event.parameters)
			{
				description += utils::string::va(" %s=%llu", sanitize(parameter.selector).data(),
					static_cast<unsigned long long>(parameter.value));
			}

			return description;
		}

		bool is_progression_event(const std::string_view name)
		{
			return name == map_won_event_name || name == survival_unlock_event_name ||
				name == easter_egg_unlock_event_name || name == skull_unlock_event_name;
		}

		// Resolves the zero-based Tortured Path chapter of `map` from the chapter
		// table. Main thread only: it reads an engine asset.
		std::uint64_t resolve_chapter(const std::string& map)
		{
			if (map.empty())
			{
				return unknown_chapter;
			}

			const auto* chapters = game::DB_FindXAssetHeader(game::ASSET_TYPE_STRINGTABLE,
				chapter_table_name, false).stringTable;
			for (auto row = 0; chapters && row < chapters->rowCount; ++row)
			{
				const auto* candidate = get_cell(chapters, row, chapter_table_map_column);
				int chapter{};
				if (candidate && _stricmp(candidate, map.data()) == 0 &&
					parse_integer(get_cell(chapters, row, chapter_table_chapter_column), chapter) &&
					chapter >= 1 && chapter <= static_cast<int>(chapter_easter_egg_achievement_ids.size()))
				{
					return static_cast<std::uint64_t>(chapter - 1);
				}
			}

			return unknown_chapter;
		}

		// Main thread, at level start: the map and its chapter are captured while
		// the engine's dvar and asset state are stable, as owned data.
		void capture_level_context()
		{
			const auto* mapname = game::Dvar_FindMalleableVar("mapname");
			std::string map = mapname && mapname->current.string ? mapname->current.string : "";
			const auto chapter = resolve_chapter(map);

			std::lock_guard lock{level_context_mutex};
			current_level.active = true;
			current_level.chapter = chapter;
			current_level.map = std::move(map);
		}

		// Main thread, at level end. The map name is kept for diagnostics only.
		void retire_level_context()
		{
			std::lock_guard lock{level_context_mutex};
			current_level.active = false;
		}

		struct chapter_attribution
		{
			std::uint64_t chapter{unknown_chapter};
			std::string map{};
			bool level_active{};
		};

		// Any thread: the chapter a progression event handled now belongs to. Only
		// the chapter being played is credited. The transport is in-process, so a
		// report is handled within a frame of being sent and the level that
		// produced it is still current; an event handled with no level active is
		// recorded as nothing rather than credited to a guess.
		chapter_attribution attribute_chapter()
		{
			std::lock_guard lock{level_context_mutex};
			chapter_attribution attribution{};
			attribution.map = current_level.map;
			attribution.level_active = current_level.active;
			if (current_level.active)
			{
				attribution.chapter = current_level.chapter;
			}

			return attribution;
		}

		// The four main-quest events by number, for the relay to a remote player.
		constexpr std::array progression_event_names{
			map_won_event_name, survival_unlock_event_name, easter_egg_unlock_event_name, skull_unlock_event_name};

		bool progression_kind_of(const std::string_view name, std::uint32_t& kind)
		{
			for (std::size_t index = 0; index < progression_event_names.size(); ++index)
			{
				if (name == progression_event_names[index])
				{
					kind = static_cast<std::uint32_t>(index + 1);
					return true;
				}
			}

			return false;
		}

		// Queues an event for the main-thread processor; false when the queue is
		// closed or full.
		bool enqueue(pending_event pending)
		{
			std::lock_guard lock{pending_event_mutex};
			if (!accepting_events.load())
			{
				return false;
			}

			if (pending_events.size() >= maximum_pending_events)
			{
				console::debug("[hidden_challenges] pending event queue is full\n");
				return false;
			}

			pending_events.push_back(std::move(pending));
			return true;
		}

		bool find_achievement_by_id(const int id, std::string& name, int& kind)
		{
			const auto* achievement_definitions = game::DB_FindXAssetHeader(
				game::ASSET_TYPE_STRINGTABLE, "dw/dwGameChallenges.csv", false).stringTable;
			const auto id_string = std::to_string(id);

			for (auto row = 0; achievement_definitions && row < achievement_definitions->rowCount; ++row)
			{
				const auto* value = get_cell(achievement_definitions, row, definition_id_column);
				if (!value || id_string != value)
				{
					continue;
				}

				const auto* achievement_name = get_cell(achievement_definitions, row, definition_name_column);
				if (!achievement_name || !*achievement_name ||
					!parse_integer(get_cell(achievement_definitions, row, definition_kind_column), kind))
				{
					return false;
				}

				name = achievement_name;
				return true;
			}

			return false;
		}

		// Records main-quest progress. Bitfield progress is OR-ed into the
		// record, plain progress is raised to the given value; the achievement
		// completes when the target is reached.
		void record_progression(const int achievement_id, const std::uint16_t progress,
			const std::uint16_t target, const bool bitfield)
		{
			std::string name{};
			int kind{};
			if (!find_achievement_by_id(achievement_id, name, kind))
			{
				console::warn("[zombies_progression] achievement %d is not defined in dw/dwGameChallenges.csv\n",
					achievement_id);
				return;
			}

			std::uint16_t previous_progress{};
			std::uint16_t updated_progress{};
			const auto result = demonware::achievement_store::mutate(name,
				[&](demonware::achievement_record& record)
				{
					previous_progress = record.progress;
					updated_progress = bitfield
						? static_cast<std::uint16_t>((record.progress & target) | progress)
						: std::max(record.progress, progress);
					return write_achievement_progress(record, kind, updated_progress, target);
				});

			report_mutation(result, name, previous_progress, updated_progress);
		}

		void process_progression_event(const reward_game_event& event, const std::uint64_t chapter)
		{
			const auto has_chapter = chapter < chapter_easter_egg_achievement_ids.size();

			if (event.name == map_won_event_name)
			{
				if (!has_chapter)
				{
					if (diagnostics_enabled.load(std::memory_order_relaxed))
					{
						console::info("[zombies_progression] map won outside the Tortured Path chapters; nothing recorded\n");
					}

					return;
				}

				record_progression(chapter_completion_achievement_id,
					static_cast<std::uint16_t>(1u << chapter), chapter_completion_target, true);
				return;
			}

			if (event.name == easter_egg_unlock_event_name)
			{
				if (!has_chapter)
				{
					if (diagnostics_enabled.load(std::memory_order_relaxed))
					{
						console::info("[zombies_progression] Easter egg unlock outside the Tortured Path chapters; nothing recorded\n");
					}

					return;
				}

				record_progression(chapter_easter_egg_achievement_ids[chapter], 1, 1, false);
				return;
			}

			if (event.name == survival_unlock_event_name)
			{
				record_progression(survival_unlock_achievement_id, 1, 1, false);
				return;
			}

			if (event.name == skull_unlock_event_name)
			{
				record_progression(skull_achievement_id, 1, 1, false);
			}
		}

		void process_event(const reward_game_event& event)
		{
			std::uint64_t group_value{};
			std::uint64_t challenge_value{};
			if (!get_hidden_challenge_values(event, group_value, challenge_value))
			{
				return;
			}

			const auto group = static_cast<int>(group_value);
			const auto definition = definitions.find(group);
			if (definition == definitions.end())
			{
				if (diagnostics_enabled.load(std::memory_order_relaxed))
				{
					console::info("[hidden_challenges] no character group is mapped to zombies event group %d (slot %llu)\n",
						group, static_cast<unsigned long long>(challenge_value));
				}

				return;
			}

			const auto challenge_index = static_cast<int>(challenge_value);
			if (event.name != definition->second.event_name ||
				(definition->second.full_mask & (1u << challenge_index)) == 0)
			{
				if (diagnostics_enabled.load(std::memory_order_relaxed))
				{
					console::info("[hidden_challenges] slot %d is outside %s (mask 0x%02X)\n",
						challenge_index, definition->second.achievement_name.data(), definition->second.full_mask);
				}

				return;
			}

			if (diagnostics_enabled.load(std::memory_order_relaxed))
			{
				console::info("[hidden_challenges] matched %s%d -> %s\n",
					definition->second.diagnostic_prefix.data(), challenge_index,
					definition->second.achievement_name.data());
			}

			update_progress(definition->second, challenge_index);
		}

		void process_pending_events()
		{
			if (log_reward_events)
			{
				diagnostics_enabled.store(log_reward_events->current.enabled, std::memory_order_relaxed);
			}

			load_definitions();

			// Main-quest events do not need the character group definitions;
			// hidden challenge events wait until those have loaded.
			std::deque<pending_event> events{};
			{
				std::lock_guard lock{pending_event_mutex};
				if (definitions_complete)
				{
					events.swap(pending_events);
				}
				else
				{
					for (auto pending = pending_events.begin(); pending != pending_events.end();)
					{
						if (is_progression_event(pending->event.name))
						{
							events.push_back(std::move(*pending));
							pending = pending_events.erase(pending);
						}
						else
						{
							++pending;
						}
					}
				}
			}

			while (!events.empty())
			{
				auto pending = std::move(events.front());
				events.pop_front();

				if (is_progression_event(pending.event.name))
				{
					process_progression_event(pending.event, pending.chapter);
				}
				else
				{
					process_event(pending.event);
				}
			}
		}

		void clear_pending_events()
		{
			std::lock_guard lock{pending_event_mutex};
			pending_events.clear();
		}
	}

	bool get_completion(const reward_game_event& event, std::uint32_t& group,
		std::uint32_t& challenge)
	{
		std::uint64_t group_value{};
		std::uint64_t challenge_value{};
		if (!get_hidden_challenge_values(event, group_value, challenge_value))
		{
			return false;
		}

		group = static_cast<std::uint32_t>(group_value);
		challenge = static_cast<std::uint32_t>(challenge_value);
		return true;
	}

	void submit_completion(const std::uint32_t group, const std::uint32_t challenge)
	{
		reward_game_event event{};
		event.name = hidden_challenge_event_name;
		event.parameters = {{"3", group}, {"4", challenge}};
		submit_reward_game_event(std::move(event));
	}

	void submit_reward_game_event(reward_game_event event)
	{
		if (!accepting_events.load())
		{
			return;
		}

		// The full dump is a diagnostic: formatting every event and writing it to
		// the log file on the Demonware thread is not free, and most events are
		// not for this component.
		const auto diagnostics = diagnostics_enabled.load(std::memory_order_relaxed);
		if (diagnostics)
		{
			console::info("[reward] %s\n", describe_event(event).data());
		}

		std::uint64_t group_value{};
		std::uint64_t challenge_value{};
		const auto hidden_challenge = get_hidden_challenge_values(event, group_value, challenge_value);
		const auto progression = is_progression_event(event.name);
		if (!hidden_challenge && !progression)
		{
			return;
		}

		auto chapter = unknown_chapter;
		if (progression)
		{
			// The event does not identify the map; the chapter comes from the level
			// context the main thread published, never from the payload. With no
			// level active there is nothing to credit the event to, chapter or not.
			const auto attribution = attribute_chapter();
			chapter = attribution.chapter;
			if (diagnostics)
			{
				console::info("[zombies_progression] %s on map '%s' (chapter %s)%s\n", sanitize(event.name).data(),
					attribution.map.empty() ? "?" : attribution.map.data(),
					chapter == unknown_chapter ? "unknown" : std::to_string(chapter + 1).data(),
					attribution.level_active ? "" : ": no level active, nothing recorded");
			}

			if (!attribution.level_active)
			{
				return;
			}
		}

		enqueue({std::move(event), chapter});
	}

	bool get_progression(const reward_game_event& event, std::uint32_t& kind)
	{
		return progression_kind_of(event.name, kind);
	}

	bool attribute_progression(std::uint64_t& chapter)
	{
		const auto attribution = attribute_chapter();
		chapter = attribution.chapter;
		return attribution.level_active;
	}

	void submit_progression(const std::uint32_t kind, const std::uint64_t chapter)
	{
		if (!accepting_events.load())
		{
			return;
		}

		if (kind < 1 || kind > progression_event_names.size())
		{
			console::debug("[zombies_progression] ignored a relayed event of unknown kind %u\n", kind);
			return;
		}

		pending_event pending{};
		pending.event.name = std::string{progression_event_names[kind - 1]};
		pending.chapter = chapter < chapter_easter_egg_achievement_ids.size() ? chapter : unknown_chapter;
		const auto name = pending.event.name;
		const auto admitted_chapter = pending.chapter;
		if (enqueue(std::move(pending)) && diagnostics_enabled.load(std::memory_order_relaxed))
		{
			console::info("[zombies_progression] %s relayed by the server (chapter %s)\n", name.data(),
				admitted_chapter == unknown_chapter ? "unknown" : std::to_string(admitted_chapter + 1).data());
		}
	}

	class component final : public multiplayer_component
	{
	public:
		void post_unpack() override
		{
			if (!game::environment::is_zombies())
			{
				return;
			}

			// The level context is kept on servers too: a dedicated server attributes
			// the chapter for the events it relays, though it persists nothing itself.
			scripting::on_init(capture_level_context);
			scripting::on_shutdown([](int)
			{
				retire_level_context();
			});

			if (game::environment::is_dedicated())
			{
				return;
			}

			log_reward_events = game::Dvar_RegisterBool(reward_event_log_dvar_name, false, game::DVAR_FLAG_NONE);
			accepting_events = true;
			scheduler::loop(process_pending_events, scheduler::pipeline::main, 50ms);
		}

		void pre_destroy() override
		{
			accepting_events = false;
			clear_pending_events();
		}
	};
}

REGISTER_COMPONENT(hidden_challenges::component)
