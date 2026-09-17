#pragma once

namespace unlock_zombies
{
	struct hidden_challenge_unlock_result
	{
		bool persisted{};
		int completed{};
		int total{};
	};

	hidden_challenge_unlock_result unlock_hidden_challenges();

	// Marks the Zombies main quests (Tortured Path chapters, their Easter eggs,
	// the red skull and the DLC3 survival unlock) as completed.
	hidden_challenge_unlock_result unlock_easter_eggs();
}
