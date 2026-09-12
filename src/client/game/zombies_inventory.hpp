#pragma once

namespace game::zombies_inventory
{
	// The Zombies tutorial progression item (Groesten Haus survival unlock).
	bool is_progression_item(unsigned int item_guid);

	// True when cg_unlock_zm_progression asks S2x to treat progression items as owned.
	bool is_progression_unlock_forced();
}
