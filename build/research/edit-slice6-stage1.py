from pathlib import Path

def edit(path, fn):
 p=Path(path); p.write_bytes(fn(p.read_text()).replace('\r\n','\n').replace('\n','\r\n').encode())

base='src/client/game/demonware/'
edit(base+'hq_economy.hpp',lambda s:s.replace('\tstruct item','\t// Lua trace: currency 7 is the hammer/Armory Credits; 2 is COD Points.\n\tinline constexpr std::uint8_t armory_credits = 7;\n\t// Local policy; retail payroll amount has not been recovered.\n\tinline constexpr std::uint32_t payroll_amount = 200;\n\tbool migrate_payroll(struct state& data);\n\n\tstruct item',1))
edit(base+'hq_payroll.hpp',lambda s:s.replace('"GRANT_CURRENCY", 2, 200','"GRANT_CURRENCY", hq_economy::armory_credits, hq_economy::payroll_amount'))
edit(base+'achievement_engine.cpp',lambda s:s.replace('currencies.contains(2)','currencies.contains(hq_economy::armory_credits)').replace('currencies.at(2)','currencies.at(hq_economy::armory_credits)').replace('"currency_id", 2,','"currency_id", hq_economy::armory_credits,').replace('"GRANT_CURRENCY", 2, 200','"GRANT_CURRENCY", hq_economy::armory_credits, hq_economy::payroll_amount'))
edit('src/client/component/hq_economy.cpp',lambda s:s.replace('currency 2/25','currency 7/25').replace('"GRANT_CURRENCY", 2,','"GRANT_CURRENCY", demonware::hq_economy::armory_credits,'))
edit('src/client/component/hq_native.cpp',lambda s:s.replace('0x279780_g, 0, 2','0x279780_g, 0, unsigned(demonware::hq_economy::armory_credits)'))
migration='''
	bool migrate_payroll(state& data)
	{
		constexpr auto marker = "migration:payroll-currency7-v1";
		if (data.transactions.contains(marker)) return false;
		// Legacy native receipts contain a microsecond timestamp; manual claim
		// receipts contain payroll_officer:<day>. Native acknowledgement of a
		// manual claim is not another payment: conservatively take max per day.
		std::map<std::uint64_t, std::pair<unsigned, unsigned>> days;
		const auto parse = [](const std::string_view text, std::uint64_t& value)
		{
			const auto result = std::from_chars(text.data(), text.data() + text.size(), value);
			return !text.empty() && result.ec == std::errc{} && result.ptr == text.data() + text.size();
		};
		for (const auto& [id, request] : data.transactions)
		{
			std::uint64_t period{}, timestamp{};
			if (id.starts_with("payroll:") && parse(std::string_view{id}.substr(8), period) &&
				parse(request, timestamp) && timestamp && timestamp / 1000000 / 14400 == period)
				++days[timestamp / 1000000 / 86400].first;
			if (id.starts_with("claim:") && request.starts_with("payroll_officer:") &&
				parse(std::string_view{request}.substr(16), period)) ++days[period].second;
		}
		std::uint64_t accounted{};
		for (const auto& [day, counts] : days) accounted += std::max(counts.first, counts.second) * std::uint64_t{payroll_amount};
		const auto old = data.currencies.find(2);
		const auto ac = data.currencies.find(armory_credits);
		const auto balance = ac == data.currencies.end() ? 0 : ac->second;
		const auto moved = static_cast<std::uint32_t>(std::min({accounted,
			std::uint64_t{old == data.currencies.end() ? 0 : old->second}, std::uint64_t{UINT32_MAX - balance}}));
		if (moved) { old->second -= moved; data.currencies[armory_credits] = balance + moved; }
		// Persisted local AC reward definitions must also stop issuing CP.
		for (auto& [name, entry] : data.achievements)
			if (name == "payroll_officer" || name.starts_with("daily_ch_") || name.starts_with("weekly_ch_") || name.starts_with("contract_"))
				for (auto& reward : entry.rewards)
					if (reward.type == "GRANT_CURRENCY" && reward.id == 2) reward.id = armory_credits;
		data.transactions.emplace(marker, std::to_string(moved));
		return true;
	}
'''
edit(base+'hq_economy.cpp',lambda s:s.replace('#include <utils/io.hpp>','#include <utils/io.hpp>\n#include <charconv>').replace('\n\tstate snapshot()',migration+'\n\tstate snapshot()').replace('\t\t\tcached = load();','\t\t\tauto next = load();\n\t\t\tif (migrate_payroll(next))\n\t\t\t{\n\t\t\t\tif (next.revision == UINT64_MAX) throw std::runtime_error("economy revision overflow");\n\t\t\t\t++next.revision;\n\t\t\t\tif (!save(next)) throw std::runtime_error("payroll migration save failed");\n\t\t\t}\n\t\t\tcached = std::move(next);').replace('\t\t\tif (!mutation(next)', '\t\t\tmigrate_payroll(next);\n\t\t\tif (!mutation(next)'))
edit('build/research/hq-tests/tests.cpp',lambda s:s.replace('currencies.at(2) == 350','currencies.at(7) == 200').replace('payroll_state.currencies.at(2)','payroll_state.currencies.at(7)').replace('const auto saved_wallet = hq_economy::snapshot().currencies.at(2)','const auto saved_wallet = hq_economy::snapshot().currencies.at(7)').replace('const auto settled_wallet = hq_economy::snapshot().currencies.at(2)','const auto settled_wallet = hq_economy::snapshot().currencies.at(7)').replace('currencies.at(2) == settled_wallet','currencies.at(7) == settled_wallet').replace('\tconst std::uint64_t payroll_now', '''
	hq_economy::state legacy;
	legacy.currencies = {{2, 950}, {7, 50}, {3, 99}};
	legacy.transactions = {{"payroll:124254", "1789259964000000"}, {"claim:manual", "payroll_officer:20709"}};
	require(hq_economy::migrate_payroll(legacy), "legacy migration applies");
	require(legacy.currencies.at(2) == 750 && legacy.currencies.at(7) == 250 && legacy.currencies.at(3) == 99, "migration moves receipt-backed amount only, manual/native overlap once");
	require(!hq_economy::migrate_payroll(legacy) && legacy.currencies.at(7) == 250, "migration marker prevents replay");
	hq_economy::state spent; spent.currencies[2] = 30; spent.transactions["payroll:124254"] = "1789259964000000";
	require(hq_economy::migrate_payroll(spent) && spent.currencies.at(2) == 0 && spent.currencies.at(7) == 30, "migration cannot overdraw spent legacy credits");
	const std::uint64_t payroll_now'''))
