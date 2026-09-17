#pragma once

#include <cstdint>
#include <limits>

namespace demonware::reward_game_events
{
	struct event;
}

namespace hidden_challenges
{
	// A main-quest event with no Tortured Path chapter to credit.
	constexpr std::uint64_t unknown_chapter = std::numeric_limits<std::uint64_t>::max();

	bool get_completion(const demonware::reward_game_events::event& event,
		std::uint32_t& group, std::uint32_t& challenge);
	void submit_completion(std::uint32_t group, std::uint32_t challenge);
	void submit_reward_game_event(demonware::reward_game_events::event event);

	// Main-quest progression for a remote player: `kind` numbers the four
	// events (1 map won, 2 survival unlock, 3 Easter egg, 4 red skull) and
	// `chapter` is the zero-based chapter the hosting server attributed the
	// event to, or unknown_chapter.
	bool get_progression(const demonware::reward_game_events::event& event, std::uint32_t& kind);
	void submit_progression(std::uint32_t kind, std::uint64_t chapter);

	// The chapter a main-quest event of `kind` handled now belongs to. False when
	// the event needs a chapter (map won, Easter egg) and no level is active, in
	// which case it must not be recorded or relayed; unknown_chapter on an active
	// level that is not a chapter, and for the chapter-independent unlocks
	// (survival, red skull), which need no level at all.
	bool attribute_progression(std::uint32_t kind, std::uint64_t& chapter);
}
