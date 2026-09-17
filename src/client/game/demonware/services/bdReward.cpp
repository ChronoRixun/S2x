#include <std_include.hpp>
#include "../dw_include.hpp"

#include "component/console/console.hpp"
#include "component/hidden_challenge_relay.hpp"
#include "component/hidden_challenges.hpp"

#include "game/game.hpp"
#include "game/demonware/reward_game_event.hpp"
#include "game/demonware/request_trace.hpp"

#include "steam/steam.hpp"

#include <chrono>
#include <limits>
#include <mutex>

namespace demonware
{
	namespace
	{
		// The stock parser rejects a whole batch when one event in it is malformed,
		// and ordinary play produces such batches, so the warning is capped: the
		// first few in full, then a running count at most once a minute.
		class malformed_request_throttle
		{
		public:
			explicit malformed_request_throttle(const char* task) : task_(task)
			{
			}

			void report()
			{
				std::lock_guard lock{mutex_};
				if (count_ < std::numeric_limits<unsigned>::max())
				{
					++count_;
				}

				const auto now = std::chrono::steady_clock::now();
				if (count_ <= detailed_reports)
				{
					console::warn("[hidden_challenges] ignored a malformed bdReward task %s request\n", task_);
					next_summary_ = now + summary_interval;
					return;
				}

				if (now >= next_summary_)
				{
					console::warn("[hidden_challenges] ignored %u malformed bdReward task %s requests so far; "
						"further ones are counted, not logged\n", count_, task_);
					next_summary_ = now + summary_interval;
				}
			}

		private:
			static constexpr unsigned detailed_reports = 3;
			static constexpr auto summary_interval = std::chrono::minutes{1};

			const char* task_;
			std::mutex mutex_{};
			unsigned count_{};
			std::chrono::steady_clock::time_point next_summary_{};
		};

		malformed_request_throttle task11_throttle{"11"};
		malformed_request_throttle task12_throttle{"12"};

		void submit_hidden_challenge_events(std::vector<reward_game_events::event>& events)
		{
			for (auto& event : events)
			{
				hidden_challenges::submit_reward_game_event(std::move(event));
			}
		}
	}

	bdReward::bdReward() : service(139, "bdReward")
	{
		this->register_task(1, &bdReward::incrementTime);
		this->register_task(2, &bdReward::claimRewardRoll);
		this->register_task(3, &bdReward::claimClientAchievements);
		this->register_task(4, &bdReward::reportRewardEvents);
		this->register_task(5, &bdReward::reportRewardEventsSync);

		this->register_task(11, &bdReward::reportRewardGameEventsForUsers);
		this->register_task(12, &bdReward::reportRewardGameEvents);
	}

	void bdReward::incrementTime(service_server* server, byte_buffer* buffer) const
	{
		request_trace::log("bdReward", "incrementTime", buffer);

		// TODO:
		auto reply = server->create_reply(this->task_id());
		reply.send();
	}

	void bdReward::claimRewardRoll(service_server* server, byte_buffer* buffer) const
	{
		request_trace::log("bdReward", "claimRewardRoll", buffer);

		// TODO:
		auto reply = server->create_reply(this->task_id());
		reply.send();
	}

	void bdReward::claimClientAchievements(service_server* server, byte_buffer* buffer) const
	{
		request_trace::log("bdReward", "claimClientAchievements", buffer);

		// TODO:
		auto reply = server->create_reply(this->task_id());
		reply.send();
	}

	void bdReward::reportRewardEvents(service_server* server, byte_buffer* buffer) const
	{
		request_trace::log("bdReward", "reportRewardEvents", buffer);

		// TODO:
		auto reply = server->create_reply(this->task_id());
		reply.send();
	}

	void bdReward::reportRewardGameEventsForUsers(service_server* server, byte_buffer* buffer) const
	{
		std::vector<reward_game_events::user_event_batch> users{};
		if (reward_game_events::parse_report_for_users_request(buffer, users))
		{
			const auto dedicated = game::environment::is_dedicated();
			const auto local_user_id = dedicated ? 0 : steam::SteamUser()->GetSteamID().bits;
			for (auto& user : users)
			{
				if (user.account_type != "steam")
				{
					continue;
				}

				for (auto& event : user.events)
				{
					// The local player's own events (hidden challenges and main quest
					// progression) are processed here; remote players receive their
					// hidden challenge completions and their main-quest progression
					// through the relay.
					if (!dedicated && user.user_id == local_user_id)
					{
						hidden_challenges::submit_reward_game_event(std::move(event));
						continue;
					}

					std::uint32_t group{};
					std::uint32_t challenge{};
					if (hidden_challenges::get_completion(event, group, challenge))
					{
						console::debug(
							"[hidden_challenges] task11 XUID %llu: zombies [3=%u, 4=%u]\n",
							static_cast<unsigned long long>(user.user_id), group, challenge);
						hidden_challenge_relay::submit(user.user_id, group, challenge);
						continue;
					}

					// The chapter is attributed here, where the level being played is
					// known, and travels with the relay to the player it belongs to. A
					// report handled with no level active is dropped, as a local one is.
					std::uint32_t kind{};
					if (hidden_challenges::get_progression(event, kind))
					{
						std::uint64_t chapter{};
						if (!hidden_challenges::attribute_progression(kind, chapter))
						{
							console::debug(
								"[zombies_progression] task11 XUID %llu: kind %u needs a chapter and no level is active; nothing relayed\n",
								static_cast<unsigned long long>(user.user_id), kind);
							continue;
						}

						console::debug(
							"[zombies_progression] task11 XUID %llu: kind %u, chapter %s\n",
							static_cast<unsigned long long>(user.user_id), kind,
							chapter == hidden_challenges::unknown_chapter ? "unknown" : std::to_string(chapter + 1).data());
						hidden_challenge_relay::submit_progression(user.user_id, kind, chapter);
					}
				}
			}
		}
		else
		{
			task11_throttle.report();
		}

		auto reply = server->create_reply(this->task_id());
		reply.send();
	}

	void bdReward::reportRewardEventsSync(service_server* server, byte_buffer* buffer) const
	{
		request_trace::log("bdReward", "reportRewardEventsSync", buffer);

		// TODO:
		auto reply = server->create_reply(this->task_id());
		reply.send();
	}

	void bdReward::reportRewardGameEvents(service_server* server, byte_buffer* buffer) const
	{
		std::vector<reward_game_events::event> events{};
		if (reward_game_events::parse_report_request(buffer, events))
		{
			submit_hidden_challenge_events(events);
		}
		else
		{
			task12_throttle.report();
		}

		auto reply = server->create_reply(this->task_id());
		reply.send();
	}
}
