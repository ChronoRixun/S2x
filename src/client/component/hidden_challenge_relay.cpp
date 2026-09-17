#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "hidden_challenge_relay.hpp"

#include "command.hpp"
#include "console/console.hpp"
#include "hidden_challenges.hpp"
#include "scheduler.hpp"

#include "game/game.hpp"

#include <charconv>
#include <deque>
#include <limits>
#include <mutex>

#include <utils/hook.hpp>

namespace hidden_challenge_relay
{
	namespace
	{
		// s2x_hc is safe without the tilde because upstream clients hook
		// CG_DeployServerCommandString and consume it before the engine's
		// single-byte opcode dispatcher sees the 's'.
		constexpr std::string_view server_command = "s2x_hc";
		// s2x_zp is new to this branch and has no client-side hook on upstream,
		// so a stock client would route it into the engine's 's' handler.
		// CG_DeployServerCommandString (0x431F1D) ignores first bytes above 0x7C;
		// tilde keeps stock clients out of the opcode dispatch.
		constexpr std::string_view progression_command = "~s2x_zp";
		constexpr auto maximum_pending_forwards = 128u;
		constexpr auto minimum_command_client_state = 4;

		// Either a hidden challenge completion (group, challenge) or a main-quest
		// progression event (kind, chapter code) bound for one player.
		struct pending_forward
		{
			std::uint64_t user_id{};
			bool progression{};
			std::uint32_t group{};
			std::uint32_t challenge{};
			std::uint32_t kind{};
			std::uint32_t chapter_code{};
		};

		utils::hook::detour deploy_server_command_hook;
		std::atomic_bool accepting_forwards{};
		std::mutex pending_forward_mutex{};
		std::deque<pending_forward> pending_forwards{};

		bool parse_unsigned(const char* text, std::uint32_t& value)
		{
			if (!text || !*text)
			{
				return false;
			}

			const auto* end = text + std::strlen(text);
			const auto result = std::from_chars(text, end, value);
			return result.ec == std::errc{} && result.ptr == end;
		}

		// The chapter crosses the wire as 0 for none, otherwise chapter + 1.
		std::uint32_t encode_chapter(const std::uint64_t chapter)
		{
			return chapter >= std::numeric_limits<std::uint32_t>::max() ? 0u : static_cast<std::uint32_t>(chapter + 1);
		}

		std::uint64_t decode_chapter(const std::uint32_t code)
		{
			return code == 0 ? hidden_challenges::unknown_chapter : static_cast<std::uint64_t>(code - 1);
		}

		void deploy_server_command_stub(const unsigned int local_client_num)
		{
			// CG_DeployServerCommandString is entered with the reliable command
			// already tokenized by the stock client command path.
			const command::params params{};
			if (params.size() == 0)
			{
				deploy_server_command_hook.invoke<void>(local_client_num);
				return;
			}

			const std::string_view command{params[0]};
			if (command == progression_command)
			{
				std::uint32_t kind{};
				std::uint32_t chapter_code{};
				if (params.size() != 3 || !parse_unsigned(params[1], kind) || !parse_unsigned(params[2], chapter_code))
				{
					console::debug("[zombies_progression] ignored malformed server progression\n");
					return;
				}

				hidden_challenges::submit_progression(kind, decode_chapter(chapter_code));
				return;
			}

			if (command != server_command)
			{
				deploy_server_command_hook.invoke<void>(local_client_num);
				return;
			}

			std::uint32_t group{};
			std::uint32_t challenge{};
			if (params.size() != 3 || !parse_unsigned(params[1], group) ||
				!parse_unsigned(params[2], challenge))
			{
				console::debug("[hidden_challenges] ignored malformed server completion\n");
				return;
			}

			console::debug("[hidden_challenges] received server completion: group=%u slot=%u\n",
				group, challenge);
			hidden_challenges::submit_completion(group, challenge);
		}

		void process_pending_forwards()
		{
			if (!game::SV_Loaded())
			{
				return;
			}

			auto* party = game::Live_GetGameParty();
			auto* clients = *game::mp::svs_clients;
			const auto max_clients = *game::sv_maxclients;
			if (!party || !clients || max_clients <= 0)
			{
				return;
			}

			std::deque<pending_forward> forwards{};
			{
				std::lock_guard lock{pending_forward_mutex};
				forwards.swap(pending_forwards);
			}

			for (const auto& forward : forwards)
			{
				// The stock Achievement Engine sender resolves its XUID through this
				// party lookup and uses the returned member as the svs_clients index.
				const auto client_num = game::Party_FindMemberByXUID(party, forward.user_id);
				if (client_num == std::numeric_limits<std::uint8_t>::max() ||
					client_num >= max_clients || clients[client_num].state < minimum_command_client_state)
				{
					console::debug("[hidden_challenges] discarded completion for disconnected XUID %llu\n",
						static_cast<unsigned long long>(forward.user_id));
					continue;
				}

				if (forward.progression)
				{
					console::debug(
						"[zombies_progression] forwarding XUID %llu to client %u: kind=%u chapter code=%u\n",
						static_cast<unsigned long long>(forward.user_id), client_num,
						forward.kind, forward.chapter_code);
					game::SV_SendServerCommand(&clients[client_num], game::SV_CMD_RELIABLE,
						"%s %u %u", progression_command.data(), forward.kind, forward.chapter_code);
					continue;
				}

				console::debug(
					"[hidden_challenges] forwarding XUID %llu to client %u: group=%u slot=%u\n",
					static_cast<unsigned long long>(forward.user_id), client_num,
					forward.group, forward.challenge);
				game::SV_SendServerCommand(&clients[client_num], game::SV_CMD_RELIABLE,
					"%s %u %u", server_command.data(), forward.group, forward.challenge);
			}
		}

		void clear_pending_forwards()
		{
			std::lock_guard lock{pending_forward_mutex};
			pending_forwards.clear();
		}
	}

	void submit(const std::uint64_t user_id, const std::uint32_t group,
		const std::uint32_t challenge)
	{
		if (!accepting_forwards.load())
		{
			return;
		}

		std::lock_guard lock{pending_forward_mutex};
		if (!accepting_forwards.load())
		{
			return;
		}

		if (pending_forwards.size() >= maximum_pending_forwards)
		{
			console::debug("[hidden_challenges] pending forward queue is full\n");
			return;
		}

		pending_forward forward{};
		forward.user_id = user_id;
		forward.group = group;
		forward.challenge = challenge;
		pending_forwards.push_back(std::move(forward));
	}

	void submit_progression(const std::uint64_t user_id, const std::uint32_t kind, const std::uint64_t chapter)
	{
		if (!accepting_forwards.load())
		{
			return;
		}

		std::lock_guard lock{pending_forward_mutex};
		if (!accepting_forwards.load())
		{
			return;
		}

		if (pending_forwards.size() >= maximum_pending_forwards)
		{
			console::debug("[zombies_progression] pending forward queue is full\n");
			return;
		}

		pending_forward forward{};
		forward.user_id = user_id;
		forward.progression = true;
		forward.kind = kind;
		forward.chapter_code = encode_chapter(chapter);
		pending_forwards.push_back(std::move(forward));
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

			accepting_forwards = true;
			scheduler::loop(process_pending_forwards, scheduler::pipeline::server);

			if (!game::environment::is_dedicated())
			{
				deploy_server_command_hook.create(game::CG_DeployServerCommandString,
					deploy_server_command_stub);
			}
		}

		void pre_destroy() override
		{
			accepting_forwards = false;
			clear_pending_forwards();
		}
	};
}

REGISTER_COMPONENT(hidden_challenge_relay::component)
