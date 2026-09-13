from pathlib import Path
p=Path('build/research/hq-tests/tests.cpp'); s=p.read_text(); marker='\tstd::string metadata_capture;'; s=s.replace(marker,'''\trequire(!hq_payroll::notification, "legacy manual claim emits no native reward push");
	require(hq_economy::transact([&](auto& next) {
		next.achievements.erase("payroll_officer");
		next.transactions.erase("payroll:" + std::to_string(live_now / 14400));
		return true;
	}), "prepare independent native notification test");
	require(achievement_engine::submit_event({"picked_up_payroll", static_cast<std::int64_t>(live_now * 1000000), {}}, true), "new native settlement");
	require(hq_payroll::notification.has_value(), "persisted settlement queues completion");
	rapidjson::Document push; push.Parse(hq_payroll::notification->c_str());
	require(!push.HasParseError() && std::string(push["reason"].GetString()) == "completed" &&
		std::string(push["status"].GetString()) == "finished" && push["kind"].GetInt() == 5 &&
		push["triggers"][0]["inventory"]["currencies"][0]["balance_delta"].GetUint() == 200 &&
		push["triggers"][0]["inventory"]["currencies"][0]["balance_before"].GetUint() == settled_wallet,
		"native completed push carries absolute balance inputs and payroll identity");
	hq_payroll::notification.reset();
	require(achievement_engine::submit_event({"18", static_cast<std::int64_t>(live_now * 1000000), {}}, true) &&
		!hq_payroll::notification, "event replay cannot replay reward animation");
	bdMarketplaceCurrency currency_wire{}; currency_wire.m_currencyId = 2; currency_wire.m_value = 200;
	byte_buffer currency_packet; currency_wire.serialize(&currency_packet);
	require(currency_packet.get_buffer() == std::string("\\x03\\x02\\x08\\xC8\\x00\\x00\\x00", 7), "native A49900 currency fields: ubyte then uint32");
''' + marker); p.write_bytes(s.replace('\n','\r\n').encode())
