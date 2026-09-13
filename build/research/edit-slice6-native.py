from pathlib import Path
def edit(p,fn):
 p=Path(p); p.write_bytes(fn(p.read_text()).replace('\n','\r\n').encode())
edit('src/client/component/hq_economy.cpp',lambda s:s.replace('#include <charconv>','#include <charconv>\n#include "game/demonware/hq_marketplace.hpp"\n#include <utils/hook.hpp>'))
native='''
		// Dedicated storage: never enlarge a loop writing the original 400-entry
		// cache or the 400-element Lua binding stack buffer.
		std::map<unsigned, std::array<unsigned char, 0x2E8>> native_skus;
		utils::hook::detour sku_lookup_hook, sku_ids_hook, collection_price_hook;

		unsigned long long collection_price(const unsigned id)
		{
			const auto entry = demonware::hq_marketplace::find_sku(id);
			return entry ? (std::uint64_t{entry->price} << 32) | demonware::hq_economy::armory_credits : 0;
		}

		unsigned sku_lookup(const unsigned id, void** output)
		{
			const auto entry = demonware::hq_marketplace::find_sku(id);
			if (!entry) return sku_lookup_hook.invoke<unsigned>(id, output);
			auto [it, inserted] = native_skus.try_emplace(id);
			auto* bytes = it->second.data();
			if (inserted)
			{
				utils::hook::invoke<void>(0x20D440_g, bytes + 0x10);
				const auto put = [&](const std::size_t offset, const unsigned value) { std::memcpy(bytes + offset, &value, 4); };
				put(0, id); put(4, 100); put(8, id); put(12, 1);
				put(0x30, id); put(0x34, 1); // first initialized product record
				put(0x240, id); bytes[0x244] = 1; put(0x248, 1);
				put(0x24C, demonware::hq_economy::armory_credits); bytes[0x2E1] = 1;
				const auto text = std::to_string(id); std::memcpy(bytes + 0x29C, text.c_str(), text.size() + 1);
			}
			std::memcpy(bytes + 0x250, &entry->price, 4);
			if (output) *output = bytes;
			return 0; // successful lookup; consumers of this hook use the output pointer
		}

		int sku_ids(game::hks::lua_State* state)
		{
			const auto valid = state->m_apistack.top - state->m_apistack.base == 1 &&
				state->m_apistack.base->t == game::hks::TNUMBER;
			const auto type = valid ? state->m_apistack.base->v.number : 0.0f;
			const auto entries = demonware::hq_marketplace::catalog();
			const auto ready = *reinterpret_cast<const unsigned char*>(0x81038A8_g) != 0;
			const auto count = ready && (type == 100.0f || type == 150.0f) ? entries.size() : 0;
			game::hks::HksObject table{}; table.t = game::hks::TTABLE;
			table.v.table = game::hks::Hashtable_Create(state, static_cast<unsigned>(count), 0);
			*state->m_apistack.top++ = table; // GC root throughout string allocation
			for (std::size_t i = 0; i < count; ++i)
			{
				game::hks::HksObject key{}; key.t = game::hks::TNUMBER; key.v.number = static_cast<float>(i + 1);
				// Same GUID-string conversion as native120760, preserving exact integers.
				utils::hook::invoke<void>(0xCAF40_g, state, entries[i].id);
				game::hks::hks_obj_settable(state, &table, &key, state->m_apistack.top - 1);
				--state->m_apistack.top;
			}
			return 1;
		}

		void refresh_item(const demonware::hq_economy::item& entry)
		{
			// 20C8B0 projection consumed by27DD30; absolute quantity, no delta.
			struct native_item { unsigned id, quantity, expires, pad; std::int64_t duration; unsigned short collision; unsigned char tail[6]; };
			static_assert(sizeof(native_item) == 32);
			const native_item item{entry.guid, entry.quantity, entry.expires, 0, INT64_MAX, entry.collision, {}};
			utils::hook::invoke<unsigned>(0x27DD30_g, 0, &item, 0, 0, entry.metadata.data(), static_cast<unsigned char>(entry.metadata.size()));
		}

		void purchase_entry(const unsigned controller, const unsigned id, const unsigned quantity, void* transaction, const int type)
		{
			if (!transaction) return;
			std::memset(transaction, 0, 25);
			if (controller != 0 || (type != 0 && type != 100 && type != 150)) return;
			// Keep native transaction generation and eventType24 completion contract.
			std::array<unsigned char, 25> tx{};
			utils::hook::invoke<void>(0x8390A0_g, tx.data());
			const auto* text = utils::hook::invoke<const char*>(0x839020_g, tx.data());
			if (!text) return;
			const std::string key{text, strnlen(text, 25)};
			if (key.empty() || key.size() >= 25) return;
			std::memcpy(transaction, tx.data(), tx.size());
			// Next main tick lets Lua register its transaction listener before completion.
			scheduler::once([tx, key, id, quantity]
			{
				unsigned error = demonware::BD_MARKETPLACE_STORAGE_ERROR;
				try
				{
					error = demonware::hq_marketplace::purchase(key, id, quantity);
					if (!error)
					{
						const auto data = demonware::hq_economy::snapshot();
						utils::hook::invoke<void>(0x27D510_g, 0, unsigned(demonware::hq_economy::armory_credits), data.currencies.at(demonware::hq_economy::armory_credits));
						refresh_item(data.inventory.at({id, 0}));
						utils::hook::invoke<void>(0xD5F30_g, 0);
						utils::hook::invoke<void>(0x2752E0_g, 0, 2);
					}
				}
				catch (const std::exception& e) { console::warn("[HQ purchase] %s\\n", e.what()); }
				demonware::hq_protocol::trace("native_purchase", key + ":" + std::to_string(id) + ":" + std::to_string(quantity) + ":error=" + std::to_string(error));
				console::info("[HQ purchase] sku=%u quantity=%u error=%u tx=%s\\n", id, quantity, error, key.c_str());
				utils::hook::invoke<void>(0x275360_g, 0, 24, error == 0, tx.data());
			}, scheduler::pipeline::main);
		}
'''
edit('src/client/component/hq_native.cpp',lambda s:s[:s.index('\t\tvoid reject_purchase')]+native+'\n'+s[s.index('\t\tvoid vendor_status'):])
edit('src/client/component/hq_native.cpp',lambda s:s.replace('purchase_hook.create(0x276580_g, reject_purchase);','purchase_hook.create(0x276580_g, purchase_entry);\n\t\t\tsku_ids_hook.create(0x120760_g, sku_ids);\n\t\t\tsku_lookup_hook.create(0x2797E0_g, sku_lookup);\n\t\t\tcollection_price_hook.create(0x274970_g, collection_price);'))
