from pathlib import Path
def edit(p,fn):
 p=Path(p); p.write_bytes(fn(p.read_text()).replace('\n','\r\n').encode())
p='src/client/game/demonware/achievement_engine.cpp'
reconcile='''	bool reconcile_offers(hq_economy::state& data, const std::uint64_t day)
	{
		std::lock_guard lock{catalog_mutex};
		bool changed{};
		for (const auto kind : {1, 2})
		{
			std::vector<hq_economy::achievement> pool;
			for (const auto& entry : definitions) if (entry.kind == kind) pool.push_back(entry);
			if (pool.empty()) continue; // table loading has not completed
			const auto current = [&](const auto& entry) { return kind == 2 ? entry.offer_day / 7 == day / 7 : entry.offer_day == day; };
			std::size_t live{};
			for (auto& [name, entry] : data.achievements)
			{
				if (entry.kind != kind) continue;
				if (entry.status == "inProgress" || entry.status == "claimable")
				{
					++live;
					// A carried order keeps progress/activation/reward and gets today's
					// offer date, so its UI expiration uses the current boundary.
					if (entry.offer_day != day) { entry.offer_day = day; changed = true; }
				}
				else if (entry.status == "available" && !current(entry))
				{ entry.status = "expired"; changed = true; }
			}
			// Preserve current available offers, including the just-abandoned one.
			for (auto& [name, entry] : data.achievements)
			{
				if (entry.kind != kind || entry.status != "available") continue;
				if (live >= 3) { entry.status = "expired"; changed = true; continue; }
				++live;
				if (entry.offer_day != day) { entry.offer_day = day; changed = true; }
			}
			const auto period = kind == 2 ? day / 7 : day;
			// Prefer unused definitions; if the small local pool is exhausted,
			// completed definitions may be offered again to maintain three slots.
			// The old receipt remains until activation, and cannot grant twice.
			for (const auto reuse_completed : {false, true})
				for (std::size_t i = 0; live < 3 && i < pool.size(); ++i)
				{
					auto entry = pool[(period + i) % pool.size()];
					const auto found = data.achievements.find(entry.name);
					if (found != data.achievements.end())
					{
						const auto& old = found->second;
						if (old.status == "available" || old.status == "inProgress" || old.status == "claimable") continue;
						if (!reuse_completed && old.status == "finished" && current(old)) continue;
						if (old.status == "finished" && current(old))
						{ entry.claim_transaction = old.claim_transaction; entry.completion = old.completion; }
					}
					entry.offer_day = day; entry.status = "available";
					data.achievements[entry.name] = entry;
					++live; changed = true;
				}
		}
		return changed;
	}

'''
edit(p,lambda s:s.replace('\tvoid set_catalog',reconcile+'\tvoid set_catalog',1).replace('(entry.offer_day + (entry.kind == 2 ? 7 : 1)) * 86400','(entry.kind == 2 ? (entry.offer_day / 7 + 1) * 7 : entry.offer_day + 1) * 86400').replace('const auto scheduled = offers(day);','auto scheduled = offers(day);'))
# Insert after the snapshot before action routing: reconcile on each fetch/transition,
# save only if needed, then project live offers from exactly that persisted state.
edit(p,lambda s:s.replace('\t\t\tif (action == "get_user_achievements_for_users")','''			const auto fetch = action == "get_user_achievements" || action == "get_scheduled_user_achievements" ||
				action == "get_expired_user_achievements" || action == "get_user_achievements_for_users";
			if (fetch || action.starts_with("activate_") || action == "deactivate_user_achievement")
			{
				auto preview = data;
				if (reconcile_offers(preview, day))
				{
					if (!hq_economy::transact([&](auto& next) { reconcile_offers(next, day); return true; })) return fail("offer_save_failed");
					data = hq_economy::snapshot();
				}
			}
			std::erase_if(scheduled, [](const auto& entry) { return entry.kind == 1 || entry.kind == 2; });
			for (const auto& [name, entry] : data.achievements)
				if ((entry.kind == 1 || entry.kind == 2) && (entry.status == "available" || entry.status == "inProgress" || entry.status == "claimable")) scheduled.push_back(entry);
			if (action == "get_user_achievements_for_users")''',1).replace('updated = *offer;\n\t\t\t\t\t\tupdated.activation', 'updated = *offer;\n\t\t\t\t\t\tupdated.claim_transaction.clear(); updated.completion = 0;\n\t\t\t\t\t\tupdated.activation').replace('entry.status = "available";\n\t\t\t\t\t\tentry.progress','entry.status = "available";\n\t\t\t\t\t\tentry.offer_day = day;\n\t\t\t\t\t\tentry.claim_transaction.clear(); entry.completion = 0;\n\t\t\t\t\t\tentry.progress').replace('if (entry.status == "finished") replay = true;', 'if (entry.status == "finished" || (entry.status == "available" && entry.completion && entry.claim_transaction == client_tx)) replay = true;'))
edit('src/client/game/demonware/achievement_engine.hpp',lambda s:s.replace('\tvoid set_catalog','\t// Reconcile persisted daily/weekly offers; deterministic day injection for tests.\n\tbool reconcile_offers(hq_economy::state& data, std::uint64_t day);\n\tvoid set_catalog',1))
