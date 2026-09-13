from pathlib import Path
def edit(p,f):
 p=Path(p); s=p.read_text(); p.write_bytes(f(s).replace('\r\n','\n').replace('\n','\r\n').encode())
edit('src/client/game/demonware/hq_payroll.hpp',lambda s:s.replace('#include "hq_economy.hpp"','#include "hq_economy.hpp"\n#include <mutex>\n#include <optional>').replace('\n\t// Local policy:', '''
	// Transport thread publishes only after a new settlement has persisted. The
	// main thread consumes the native notification; retries cannot publish twice.
	inline std::mutex notification_mutex;
	inline std::optional<std::string> notification;

	// Local policy:'''))
edit('src/client/game/demonware/achievement_engine.cpp',lambda s:s.replace('''		if (payroll && native_payroll)
			return hq_economy::transact([&](hq_economy::state& data) { return hq_payroll::settle(data, event.timestamp, now); });''','''		if (payroll && native_payroll)
		{
			std::string notification;
			const auto ok = hq_economy::transact([&](hq_economy::state& data)
			{
				const auto before = data.currencies.contains(2) ? data.currencies.at(2) : 0;
				if (!hq_payroll::settle(data, event.timestamp, now)) return false;
				const auto after = data.currencies.contains(2) ? data.currencies.at(2) : 0;
				if (after != before)
				{
					rapidjson::Document push{rapidjson::kObjectType};
					auto& alloc = push.GetAllocator();
					auto record = serialize(data.achievements.at("payroll_officer"), alloc);
					push.CopyFrom(record, alloc);
					push.AddMember("type", "CHALLENGE", alloc);
					push.AddMember("reason", "completed", alloc);
					rapidjson::Value triggers{rapidjson::kArrayType}, trigger{rapidjson::kObjectType};
					rapidjson::Value inventory{rapidjson::kObjectType}, currencies{rapidjson::kArrayType}, currency{rapidjson::kObjectType};
					currency.AddMember("currency_id", 2, alloc);
					currency.AddMember("balance_before", before, alloc);
					currency.AddMember("balance_delta", after - before, alloc);
					currencies.PushBack(currency, alloc);
					inventory.AddMember("currencies", currencies, alloc);
					trigger.AddMember("type", "SET_CURRENCY_BALANCE", alloc);
					trigger.AddMember("inventory", inventory, alloc);
					triggers.PushBack(trigger, alloc);
					push.AddMember("triggers", triggers, alloc);
					notification = encode(push);
				}
				return true;
			});
			if (ok && !notification.empty())
			{
				std::lock_guard lock{hq_payroll::notification_mutex};
				hq_payroll::notification = std::move(notification);
			}
			return ok;
		}'''))
edit('src/client/component/hq_native.cpp',lambda s:s.replace('#include "game/demonware/hq_vendor.hpp"','#include "game/demonware/hq_vendor.hpp"\n#include "game/demonware/hq_payroll.hpp"\n#include "component/scheduler.hpp"').replace('\n\t\tvoid status()', '''
		void wallet_status()
		{
			console::info("[HQ wallet] ready=%u count=%u ArmoryCredits=%u (Inventory_GetCurrencyBalance)\\n",
				*reinterpret_cast<const unsigned char*>(0x7F6FE94_g),
				*reinterpret_cast<const unsigned*>(0x7F6FE90_g),
				utils::hook::invoke<unsigned>(0x279780_g, 0, 2));
			for (unsigned i = 0; i < 13; ++i)
			{
				const auto* slot = reinterpret_cast<const unsigned char*>(0x7F6FBB8_g) + i * 0x38;
				console::info("[HQ wallet] slot %u currency=%u balance=%u\\n", i, slot[0x20],
					*reinterpret_cast<const unsigned*>(slot + 0x24));
			}
		}

		void sync_wallet()
		{
			// Never race the initial native balance fetch or run native UI on the DW thread.
			if (!*reinterpret_cast<const unsigned char*>(0x7F6FE94_g)) return;
			try
			{
				std::optional<std::string> notification;
				{
					std::lock_guard lock{demonware::hq_payroll::notification_mutex};
					notification.swap(demonware::hq_payroll::notification);
				}
				if (notification)
				{
					auto* bridge = game::AE_UserAchievementTaskData.get() + 0xF8;
					if (game::AE_SetResponseString(bridge, notification->c_str()))
					{
						demonware::hq_protocol::trace("payroll_native_push", *notification);
						// 13C480 is the achievement push handler, distinct from task replies.
						utils::hook::invoke<void>(0x13C480_g, 0, bridge);
						console::info("[HQ payroll] delivered persisted completion push\\n");
					}
				}
				const auto data = demonware::hq_economy::snapshot();
				for (const auto& [id, amount] : data.currencies)
				{
					if (!id || utils::hook::invoke<unsigned>(0x279780_g, 0, unsigned(id)) == amount) continue;
					// Native absolute setter + inventory eventType 5; no second grant.
					utils::hook::invoke<void>(0x27D510_g, 0, unsigned(id), amount);
				}
			}
			catch (const std::exception& error)
			{
				static bool warned{};
				if (!std::exchange(warned, true)) console::warn("[HQ wallet] sync failed: %s\\n", error.what());
			}
		}

		void status()''').replace('command::add("hqnative", status);','command::add("hqnative", status);\n\t\t\tcommand::add("hqwallet", wallet_status);\n\t\t\tscheduler::loop(sync_wallet, scheduler::pipeline::main, 100ms);'))
edit('src/client/game/demonware/services/bdMarketplace.cpp',lambda s:s.replace('''		hq_protocol::trace("marketplace_130", buffer->get_remaining());		// TODO:
		auto reply = server->create_reply(this->task_id());
		reply.send();''','''		if (game::environment::is_zombies())
		{
			hq_protocol::trace("marketplace_130", buffer->get_remaining());
			server->create_reply(this->task_id()).send();
			return;
		}
		// Both SDK balance variants use the same currency reader (A49900).
		getBalanceV2(server, buffer);''').replace('hq_protocol::trace("marketplace_132", buffer->get_remaining());','hq_protocol::trace(this->task_id() == 130 ? "marketplace_130" : "marketplace_132", buffer->get_remaining());').replace('''				result->m_value = amount;
				reply.add(result);''','''				result->m_value = amount;
				if (!game::environment::is_zombies())
				{
					byte_buffer encoded; result->serialize(&encoded);
					hq_protocol::trace(this->task_id() == 130 ? "marketplace_130_currency" : "marketplace_132_currency", encoded.get_buffer());
				}
				reply.add(result);'''))
