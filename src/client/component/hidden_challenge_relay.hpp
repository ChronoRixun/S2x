#pragma once

#include <cstdint>

namespace hidden_challenge_relay
{
	void submit(std::uint64_t user_id, std::uint32_t group, std::uint32_t challenge);

	// A main-quest progression event for a remote player, with the chapter the
	// server attributed it to (hidden_challenges::unknown_chapter for none).
	void submit_progression(std::uint64_t user_id, std::uint32_t kind, std::uint64_t chapter);
}
