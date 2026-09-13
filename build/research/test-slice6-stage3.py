from pathlib import Path
p=Path('build/research/hq-tests/tests.cpp'); s=p.read_text().replace('require(filtered["Achievements"].Empty(), "kind filter excludes unrelated records");','require(filtered["Achievements"].Size() == 3, "kind filter selects persisted weekly offers");')
at=s.index(' auto scheduled=request')
s=s[:at]+'''
	{
		hq_economy::state offers;
		const auto live = [](const auto& data, int kind) {
			std::vector<std::string> names;
			for (const auto& [name, entry] : data.achievements)
				if (entry.kind == kind && (entry.status == "available" || entry.status == "inProgress" || entry.status == "claimable")) names.push_back(name);
			return names;
		};
		constexpr unsigned day = 20708;
		require(achievement_engine::reconcile_offers(offers, day) && live(offers,1).size() == 3 && live(offers,2).size() == 3, "three offers per kind persisted");
		require(!achievement_engine::reconcile_offers(offers, day), "repeat fetch does not regenerate or write");
		const auto daily_names = live(offers,1); const auto weekly_names = live(offers,2);
		for (const auto& name : daily_names) { offers.achievements[name].status = "inProgress"; offers.achievements[name].progress = 2; }
		offers.achievements[daily_names[0]].status = "available";
		achievement_engine::reconcile_offers(offers, day);
		require(live(offers,1).size() == 3 && offers.achievements[daily_names[0]].status == "available", "accept three abandon one keeps three visible");
		achievement_engine::reconcile_offers(offers, day + 1);
		require(live(offers,1).size() == 3 && offers.achievements[daily_names[1]].status == "inProgress" && offers.achievements[daily_names[1]].progress == 2, "daily rollover carries active progress and fills remaining slot");
		require(live(offers,2) == weekly_names, "daily rollover leaves weekly offer identities unchanged");
		for (const auto& name : live(offers,1)) require(offers.achievements[name].offer_day == day + 1, "no stale daily offer date");
		offers.achievements[weekly_names[0]].status = "inProgress"; offers.achievements[weekly_names[0]].progress = 7;
		const auto week = (day / 7 + 1) * 7;
		achievement_engine::reconcile_offers(offers, week);
		require(live(offers,2).size() == 3 && offers.achievements[weekly_names[0]].progress == 7 && offers.achievements[weekly_names[0]].status == "inProgress", "weekly rollover preserves its active order independently");
		for (const auto& name : live(offers,2)) require(offers.achievements[name].offer_day == week, "weekly available offers use current date");
		for (const auto& name : live(offers,2)) offers.achievements[name].status = "finished";
		achievement_engine::reconcile_offers(offers, week);
		require(live(offers,2).size() == 3, "exhausted local weekly pool replenishes three offers");
	}
''' + s[at:]
p.write_bytes(s.replace('\n','\r\n').encode())
