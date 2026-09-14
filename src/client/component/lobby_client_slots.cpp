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

		// Written by the probe stub: count and the highest party slot it skipped
		// since the last report (a running maximum, so an early slot 7 is not hidden
		// by a later slot 4), the sv_maxclients value seen last, and a sticky flag
		// set the moment any skipped slot exceeded the bound in force for that
		// probe - severity comes from that flag, not from comparing the maximum
		// with whatever the bound is at report time.
		struct suppressed_probe_state
		{
			std::uint32_t count;
			std::uint32_t max_slot;
			std::uint32_t last_bound;
			std::uint32_t overflowed;
			// The bound in force when max_slot was stored, and the first probe that
			// exceeded its bound, so the report never pairs numbers from different
			// probes.
			std::uint32_t max_slot_bound;
			std::uint32_t overflow_slot;
			std::uint32_t overflow_bound;
		};

		suppressed_probe_state suppressed_probes{};
		bool explained{};
		bool level_active{};

		void lobby_party_client_slot_probe(utils::hook::assembler& a)
		{
			const auto not_connected = a.new_label();
			const auto out_of_range = a.new_label();
			const auto slot_kept = a.new_label();
			const auto within_bound = a.new_label();
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
			// max_slot = max(max_slot, member index), storing on ties as well so the
			// bound is captured even when the first skipped slot is 0 (the report
			// resets both to 0).
			a.cmp(dword_ptr(rax, 4), edi);
			a.jg(slot_kept);
			a.mov(dword_ptr(rax, 4), edi);
			a.mov(dword_ptr(rax, 16), ecx);
			a.bind(slot_kept);
			a.mov(dword_ptr(rax, 8), ecx);
			// First probe past its own bound: set the sticky flag and keep the pair.
			a.cmp(edi, ecx);
			a.jle(within_bound);
			a.cmp(dword_ptr(rax, 12), 0);
			a.jne(within_bound);
			a.mov(dword_ptr(rax, 12), 1);
			a.mov(dword_ptr(rax, 20), edi);
			a.mov(dword_ptr(rax, 24), ecx);
			a.bind(within_bound);
			a.pop(rcx);

			a.bind(not_connected);
			a.mov(rax, static_cast<std::uint64_t>(probe_not_connected + game::get_base()));
			a.jmp(rax);

			a.bind(connected);
			a.mov(rax, static_cast<std::uint64_t>(probe_next_member + game::get_base()));
			a.jmp(rax);
		}

		// One line per level for the probes the guard skipped, then the counters
		// reset so every level reports its own walk. Severity comes from the
		// sticky overflow flag: informational when no probe exceeded the bound in
		// force for it (the highest slot is then the host's own party slot, one
		// past the client array, when it equals the bound it was seen with), a
		// warning when any probe did. The first report carries the explanation in
		// the same line.
		void report_suppressed_probes(const char* when)
		{
			const auto count = suppressed_probes.count;
			if (count == 0)
			{
				return;
			}

			const auto slot = suppressed_probes.max_slot;
			const auto slot_bound = suppressed_probes.max_slot_bound;
			const auto bound = suppressed_probes.last_bound;
			const auto overflowed = suppressed_probes.overflowed != 0;
			const auto overflow_slot = suppressed_probes.overflow_slot;
			const auto overflow_bound = suppressed_probes.overflow_bound;
			suppressed_probes.count = 0;
			suppressed_probes.max_slot = 0;
			suppressed_probes.max_slot_bound = 0;
			suppressed_probes.overflowed = 0;
			suppressed_probes.overflow_slot = 0;
			suppressed_probes.overflow_bound = 0;

			const auto* explanation = explained
				? ""
				: " The game party addresses 48 slots but the server owns only sv_maxclients client slots; probes with no client slot behind them are skipped.";
			explained = true;

			// Every probe stayed at or below its own bound: a highest slot equal to the
			// bound in force when it was seen is the host's own party slot, one past
			// the client array; anything else in the count had no client array at all.
			if (!overflowed)
			{
				console::info(
					"Lobby party walk: skipped %u client-slot probe%s with no allocated slot %s "
					"(highest party slot %u against sv_maxclients %u%s; last observed sv_maxclients %u).%s\n",
					count, count == 1 ? "" : "s", when, slot, slot_bound,
					slot == slot_bound ? ", the host's own" : "", bound, explanation);
			}
			else
			{
				console::warn(
					"Lobby party walk: skipped %u client-slot probe%s with no allocated slot %s; "
					"the party addressed more slots than the server owns (first: party slot %u against sv_maxclients %u; "
					"highest party slot %u against sv_maxclients %u; last observed sv_maxclients %u).%s\n",
					count, count == 1 ? "" : "s", when, overflow_slot, overflow_bound, slot, slot_bound, bound, explanation);
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
				level_active = false;
			});

			scripting::on_init([]
			{
				report_suppressed_probes("between levels");
				level_active = true;
			});

			// A server that never reaches a level still says so, once; while a level
			// is active its count belongs to the level-end report.
			scheduler::loop([]
			{
				if (!explained && !level_active)
				{
					report_suppressed_probes("outside a level");
				}
			}, scheduler::main, 30s);
		}
	};
}

REGISTER_COMPONENT(lobby_client_slots::component)
