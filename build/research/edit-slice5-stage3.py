from pathlib import Path
def edit(p,f):
 p=Path(p);p.write_bytes(f(p.read_text()).replace('\n','\r\n').encode())
edit('src/client/game/demonware/hq_mail.hpp',lambda s:s.replace('#include <algorithm>','#include <algorithm>\n#include <atomic>\n#include <cstdint>').replace('\n\tinline std::string empty_slots', '''
	inline std::atomic_uint32_t native_reads{}, native_redeems{}, rejected_indices{};

	inline bool valid_slot(const int controller, const int slot, const std::uint32_t count)
	{
		return controller >= 0 && controller < 2 && count >= 14 && count <= 4096 &&
			slot >= 0 && static_cast<std::uint32_t>(slot) < count;
	}

	inline std::string empty_slots'''))
edit('src/client/component/mail_guard.cpp',lambda s:s.replace('#include "game/game.hpp"','#include "game/game.hpp"\n#include "game/demonware/hq_mail.hpp"').replace('\t\tutils::hook::detour poll_hook;', '''		utils::hook::detour poll_hook;
		utils::hook::detour message_hook;
		utils::hook::detour redeem_hook;
		utils::hook::detour success_hook;

		void trace_access(const char* action, const int controller, const int category, const int index)
		{
			if (controller < 0 || controller >= 2)
			{
				++demonware::hq_mail::rejected_indices;
				console::warn("[HQ mail] %s rejected controller=%d\\n", action, controller);
				return;
			}
			const auto* state = game::MarketingComms_MailState.get() + controller * mail_state_stride;
			const auto count = *reinterpret_cast<const unsigned*>(state + 0xBC);
			const auto slot = utils::hook::invoke<int>(0x3723B0_g, category, index);
			const auto valid = demonware::hq_mail::valid_slot(controller, slot, count);
			if (!valid) ++demonware::hq_mail::rejected_indices;
			console::info("[HQ mail] %s controller=%d category=%d index=%d mapped=%d count=%u inRange=%u; local inbox has no claimable messages\\n",
				action, controller, category, index, slot, count, unsigned(valid));
		}

		bool message_stub(int controller, int category, int index, char* output, int capacity)
		{
			++demonware::hq_mail::native_reads;
			trace_access("read", controller, category, index);
			if (output && capacity > 0) *output = 0;
			// Explicit MP empty-inbox policy. 125020 returns zero Lua values on false.
			// Do not let 3722F0 dereference an unchecked category-to-slot result.
			return false;
		}

		void redeem_stub(int controller, int category, int index)
		{
			++demonware::hq_mail::native_redeems;
			trace_access("redeem suppressed", controller, category, index);
			// No fabricated code/reward and no native task from a cleared/stale UI slot.
		}

		void success_stub(void* task)
		{
			success_hook.invoke<void>(task);
			const auto controller = *reinterpret_cast<const int*>(static_cast<const std::byte*>(task) + 4);
			if (controller < 0 || controller >= 2) return;
			const auto* state = game::MarketingComms_MailState.get() + controller * mail_state_stride;
			console::info("[HQ mail] native fetch success controller=%d ready=%d count=%u capacity=%u slots=%p; empty-inbox policy active\\n",
				controller, *reinterpret_cast<const int*>(state + 0x24),
				*reinterpret_cast<const unsigned*>(state + 0xBC), *reinterpret_cast<const unsigned*>(state + 0xB8),
				*reinterpret_cast<void* const*>(state + 0xB0));
		}''').replace('return poll_hook.invoke<bool>();','// The local inbox advertises no unread messages; keep the allocation intact.\n\t\t\treturn false;').replace('poll_hook.create(game::MarketingComms_HasUnreadMail, poll_stub);','''poll_hook.create(game::MarketingComms_HasUnreadMail, poll_stub);
			message_hook.create(0x3722F0_g, message_stub);
			redeem_hook.create(0x3726F0_g, redeem_stub);
			success_hook.create(0x3726A0_g, success_stub);'''))
edit('src/client/component/hq_native.cpp',lambda s:s.replace('#include "game/demonware/hq_payroll.hpp"','#include "game/demonware/hq_payroll.hpp"\n#include "game/demonware/hq_mail.hpp"').replace('''			const auto ready = *reinterpret_cast<const int*>(0x8A14F84_g);''','''			console::info("[HQ mail native] policy=empty inbox; reads=%u redeemsSuppressed=%u invalidIndices=%u count=%u capacity=%u\\n",
				demonware::hq_mail::native_reads.load(), demonware::hq_mail::native_redeems.load(),
				demonware::hq_mail::rejected_indices.load(), *reinterpret_cast<const unsigned*>(0x8A1501C_g),
				*reinterpret_cast<const unsigned*>(0x8A15018_g));
			const auto ready = *reinterpret_cast<const int*>(0x8A14F84_g);''').replace('if (!ready || !slots) return;', 'if (!ready || !slots || *reinterpret_cast<const unsigned*>(0x8A1501C_g) < 14) return;'))
edit('build/research/hq-tests/tests.cpp',lambda s:s.replace(' // Native catalog read-side order', ''' require(hq_mail::valid_slot(0,13,14) && hq_mail::valid_slot(1,0,14), "last allocated mail slot valid");
 require(!hq_mail::valid_slot(0,14,14) && !hq_mail::valid_slot(0,-1,14) &&
  !hq_mail::valid_slot(-1,0,14) && !hq_mail::valid_slot(2,0,14) &&
  !hq_mail::valid_slot(0,0,0) && !hq_mail::valid_slot(0,0,4097), "unknown category and malformed mail bounds");
 // Native catalog read-side order'''))
