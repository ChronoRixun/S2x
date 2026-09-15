#pragma once

#include <cstdint>
#include "game/demonware/reward_game_event.hpp"

namespace hidden_challenge_relay
{
	void submit(std::uint64_t user_id, std::uint32_t group, std::uint32_t challenge);
	void submit_reward(std::uint64_t user_id, const demonware::reward_game_events::event& event);

	// A main-quest progression event for a remote player, with the chapter the
	// server attributed it to (hidden_challenges::unknown_chapter for none).
	void submit_progression(std::uint64_t user_id, std::uint32_t kind, std::uint64_t chapter);
}
