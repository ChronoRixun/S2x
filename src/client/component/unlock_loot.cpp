#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "component/console/console.hpp"
#include "game/zombies_inventory.hpp"

#include "game/game.hpp"

#include <utils/hook.hpp>

namespace unlock_loot
{
	namespace
	{
		const game::dvar_t* cg_unlock_all_loot{};
		const game::dvar_t* cg_unlock_zm_progression{};

		utils::hook::detour is_loot_item_unlocked_hook;
		std::atomic_bool progression_override_reported{};

		bool is_loot_item_unlocked_stub(const unsigned int item_id)
		{
			const auto unlock_all = cg_unlock_all_loot && cg_unlock_all_loot->current.enabled;

			if (game::zombies_inventory::is_progression_item(item_id))
			{
				// The tutorial progression item gates Groesten Haus. It is granted by
				// the marketplace service, which S2x does not persist yet, so a
				// separate toggle exposes it without folding it into the loot override.
				if (game::zombies_inventory::is_progression_unlock_forced())
				{
					return true;
				}

				if (unlock_all && !progression_override_reported.exchange(true))
				{
					console::info("[unlock_loot] cg_unlockall_loot keeps the Zombies progression item (Groesten Haus) "
						"on stock ownership; enable cg_unlock_zm_progression to unlock it.\n");
				}

				return is_loot_item_unlocked_hook.invoke<bool>(item_id);
			}

			return unlock_all || is_loot_item_unlocked_hook.invoke<bool>(item_id);
		}

		bool loot_item_unlocked()
		{
			return true;
		}
	}

	class component final : public multiplayer_component
	{
	public:
		void post_unpack() override
		{
			if (game::environment::is_dedicated())
			{
				utils::hook::jump(0xD0980_g, loot_item_unlocked);
				return;
			}

			cg_unlock_all_loot = game::Dvar_RegisterBool("cg_unlockall_loot", false, game::DVAR_FLAG_SAVED);
			cg_unlock_zm_progression = game::Dvar_RegisterBool("cg_unlock_zm_progression", false, game::DVAR_FLAG_SAVED);
			is_loot_item_unlocked_hook.create(0xD0980_g, is_loot_item_unlocked_stub);
		}
	};
}

REGISTER_COMPONENT(unlock_loot::component)
