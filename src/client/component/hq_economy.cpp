#include <std_include.hpp>
#include "loader/component_loader.hpp"
#include "game/game.hpp"
#include "game/demonware/achievement_engine.hpp"
#include "component/scheduler.hpp"
#include "component/console/console.hpp"
#include <charconv>

namespace hq_economy
{
	namespace
	{
		const char* cell(const game::StringTable* table, int row, int column)
		{
			if (!table || !table->values || row < 0 || row >= table->rowCount || column < 0 || column >= table->columnCount) return "";
			const auto* value = table->values[row * table->columnCount + column].string;
			return value ? value : "";
		}

		void load_catalog()
		{
			const auto* daily = game::DB_FindXAssetHeader(game::ASSET_TYPE_STRINGTABLE, "mp/dailychallengestable.csv", false).stringTable;
			const auto* definitions = game::DB_FindXAssetHeader(game::ASSET_TYPE_STRINGTABLE, "dw/dwgamechallenges.csv", false).stringTable;
			if (!daily || !definitions) return;
			// The UI table has no AE foreign key. Only unambiguous semantic joins are enabled.
			const std::map<std::string, std::string> joins
			{
				{"ch_daily_0", "daily_ch_kills"}, {"ch_daily_1", "daily_ch_headshots"},
				{"ch_daily_2", "daily_ch_1v1_wins"}, {"ch_daily_5", "daily_ch_commend"},
			};
			std::vector<demonware::hq_economy::achievement> catalog{};
			for (int row = 0; row < daily->rowCount; ++row)
			{
				const auto join = joins.find(cell(daily, row, 0));
				if (join == joins.end()) continue;
				for (int definition = 0; definition < definitions->rowCount; ++definition)
				{
					if (join->second != cell(definitions, definition, 1) || std::string_view{cell(definitions, definition, 2)} != "1") continue;
					demonware::hq_economy::achievement entry{};
					entry.name = join->second;
					entry.challenge_name = join->first;
					const std::string_view target{cell(daily, row, 9)};
					const auto parsed = std::from_chars(target.data(), target.data() + target.size(), entry.target);
					if (parsed.ec != std::errc{} || parsed.ptr != target.data() + target.size() || !entry.target) continue;
					// Column 10 is XP, not an established wallet currency or product reward.
					catalog.push_back(entry);
				}
			}
			// Minimal local contract policy; prices/reward bundles are not in dwGameChallenges.
			for (int row = 0; row < definitions->rowCount; ++row)
			{
				const std::string name{cell(definitions, row, 1)};
				if (name != "contract_mp_1" && name != "contract_mp_2" && name != "contract_mp_3") continue;
				if (std::string_view{cell(definitions, row, 2)} != "4") continue;
				demonware::hq_economy::achievement entry{};
				entry.name = name;
				entry.challenge_name = name;
				entry.kind = 4;
				entry.usage_target = 3600;
				catalog.push_back(entry);
			}
			demonware::achievement_engine::set_catalog(std::move(catalog));
		}
	}

	class component final : public multiplayer_component
	{
	public:
		void post_unpack() override
		{
			if (game::environment::is_dedicated() || game::environment::is_zombies()) return;
			scheduler::loop(load_catalog, scheduler::pipeline::main, 5s);
		}
	};
}

REGISTER_COMPONENT(hq_economy::component)
