#include <std_include.hpp>
#include "loader/component_loader.hpp"

#include "scheduler.hpp"
#include "scripting.hpp"

#include "console/console.hpp"

#include "game/game.hpp"

#include <utils/hook.hpp>

namespace lobby_client_slots
{
	namespace
	{
		// The lobby party pump at game+0x19940 walks all 48 entries of the game party's
		// member table (XUID at party+0x90 + i * 0x38, present byte at +0xC0 + i * 0x38)
		// and probes the matching server client slot for every present member:
		//
		//   19A53  CMP  byte ptr [RBX + 0x30],0x0   ; member present?
		//   19A57  JZ   19AA1                       ; no  -> next member
		//   19A59  MOV  RAX,qword ptr [1BD3778]     ; the sv_running dvar ("1080")
		//   19A60  CMP  byte ptr [RAX + 0x10],0x0   ; dvar_t::current.enabled
		//   19A64  JZ   19A73                       ; server idle -> no client slot
		//   19A66  MOV  RAX,qword ptr [C5FBA58]     ; svs_clients
		//   19A6D  CMP  dword ptr [RSI + RAX],0x1   ; svs_clients[i].state == 1?
		//   19A71  JZ   19AA1                       ; already connected -> next member
		//   19A73  ...                              ; drive this member's connect state
		//
		// RDI holds the member index and RSI carries i * sizeof(client_t) (0x11E870); the
		// index is never bounded by sv_maxclients. Stock S2 gets away with that because
		// SV_Startup (game+0x6DCDB0) sizes svs_clients by sv_maxclients and the dvar
		// defaults to 48 - exactly the size of the party member table. The dedicated party
		// sets sv_maxclients to party_maxplayers, so a four-player server owns a four-entry
		// array while this walk still reaches slot 47. The three dedicated-server crashes
		// of 2026-09-13 all faulted here on slot 11 (RSI = 0xC4FCD0, ~12.9 MB past a
		// 4.6 MB array) with a valid svs_clients pointer in RAX.
		//
		// Bound the probe by sv_maxclients, and by svs_clients being allocated at all. A
		// party slot with no client slot behind it simply is not connected, which is the
		// same conclusion the stock read reaches for every state other than 1.
		constexpr auto probe_site = 0x19A59;
		constexpr auto probe_not_connected = 0x19A73;
		constexpr auto probe_next_member = 0x19AA1;
		constexpr auto sv_running_dvar = 0x1BD3778;

		struct suppressed_probe_state
		{
			std::uint32_t count;
			std::uint32_t last_slot;
			std::uint32_t last_bound;
		};

		suppressed_probe_state suppressed_probes{};
		bool explained{};

		void lobby_party_client_slot_probe(utils::hook::assembler& a)
		{
			const auto not_connected = a.new_label();
			const auto out_of_range = a.new_label();
			const auto connected = a.new_label();

			// Replaced: the stock sv_running gate at 19A59.
			a.mov(rax, static_cast<std::uint64_t>(sv_running_dvar + game::get_base()));
			a.mov(rax, qword_ptr(rax));
			a.test(rax, rax);
			a.jz(not_connected);
			a.cmp(byte_ptr(rax, 0x10), 0);
			a.jz(not_connected);

			// Added: the party slot has to address an allocated client slot.
			a.mov(rax, reinterpret_cast<std::uint64_t>(game::sv_maxclients.get()));
			a.cmp(edi, dword_ptr(rax));
			a.jge(out_of_range);

			a.mov(rax, reinterpret_cast<std::uint64_t>(game::mp::svs_clients.get()));
			a.mov(rax, qword_ptr(rax));
			a.test(rax, rax);
			a.jz(out_of_range);

			// Replaced: CMP dword ptr [RSI + RAX],1 / JZ 19AA1.
			a.cmp(dword_ptr(rsi, rax), 1);
			a.jz(connected);
			a.jmp(not_connected);

			// Record what was suppressed. RCX is volatile and dead here - the stock
			// path at 19A73 loads it from the member entry - but restore it anyway.
			a.bind(out_of_range);
			a.push(rcx);
			a.mov(rcx, reinterpret_cast<std::uint64_t>(game::sv_maxclients.get()));
			a.mov(ecx, dword_ptr(rcx));
			a.mov(rax, reinterpret_cast<std::uint64_t>(&suppressed_probes));
			a.inc(dword_ptr(rax));
			a.mov(dword_ptr(rax, 4), edi);
			a.mov(dword_ptr(rax, 8), ecx);
			a.pop(rcx);

			a.bind(not_connected);
			a.mov(rax, static_cast<std::uint64_t>(probe_not_connected + game::get_base()));
			a.jmp(rax);

			a.bind(connected);
			a.mov(rax, static_cast<std::uint64_t>(probe_next_member + game::get_base()));
			a.jmp(rax);
		}

		// One line per match for the probes the guard skipped, then the counter
		// resets so every match reports its own walk. The host's own party slot
		// sits one past the client array, so a highest slot equal to sv_maxclients
		// is the expected dedicated-server case and stays informational; anything
		// above it means the party addresses more slots than the server owns.
		void report_suppressed_probes(const char* when)
		{
			const auto count = suppressed_probes.count;
			if (count == 0)
			{
				return;
			}

			suppressed_probes.count = 0;
			const auto slot = suppressed_probes.last_slot;
			const auto bound = suppressed_probes.last_bound;
			if (slot == bound)
			{
				console::info(
					"Lobby party walk: skipped %u probe%s past sv_maxclients %u %s "
					"(highest party slot %u, the host's own).\n",
					count, count == 1 ? "" : "s", bound, when, slot);
			}
			else
			{
				console::warn(
					"Lobby party walk: skipped %u probe%s past sv_maxclients %u %s "
					"(highest party slot %u).\n",
					count, count == 1 ? "" : "s", bound, when, slot);
			}

			if (!explained)
			{
				explained = true;
				console::info(
					"Lobby party walk: the game party addresses 48 slots but the server "
					"owns only sv_maxclients client slots; probes past the array are skipped.\n");
			}
		}
	}

	class component final : public multiplayer_component
	{
	public:
		void post_unpack() override
		{
			utils::hook::nop(probe_site + game::get_base(),
				probe_not_connected - probe_site);
			utils::hook::jump(probe_site + game::get_base(),
				utils::hook::assemble(lobby_party_client_slot_probe));

			// The walk runs while the party fills, which on a dedicated server is
			// after the level has loaded and before the match starts. Report once at
			// each level end (that level's lobby and play) and once at each level
			// start (anything between levels), so the count belongs to one level.
			scripting::on_shutdown([](int)
			{
				report_suppressed_probes("over this level");
			});

			scripting::on_init([]
			{
				report_suppressed_probes("between levels");
			});

			// The first report does not wait for a level boundary, so a server that
			// never reaches a match still says so, once.
			scheduler::loop([]
			{
				if (!explained)
				{
					report_suppressed_probes("while waiting in the lobby");
				}
			}, scheduler::main, 30s);
		}
	};
}

REGISTER_COMPONENT(lobby_client_slots::component)
