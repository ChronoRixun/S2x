#include <std_include.hpp>
#include "game/demonware/achievement_engine.hpp"
#include "game/demonware/hq_marketplace.hpp"
#include "game/demonware/hq_protocol.hpp"
#include "game/demonware/hq_mail.hpp"
#include "game/demonware/hq_vendor.hpp"
#include "game/demonware/hq_payroll.hpp"
#include "game/demonware/hq_products.hpp"
#include "game/types/demonware.hpp"

using namespace game::demonware;
#include "game/demonware/hq_item_data.hpp"
#include "game/demonware/hq_inventory_cache.hpp"
#include "game/demonware/hq_event_relay.hpp"
#include "game/demonware/byte_buffer.hpp"
#include "game/demonware/data_types.hpp"
#include "game/demonware/reply.hpp"
#include "game/demonware/achievement_store.hpp"
#include <utils/io.hpp>
namespace utils::flags
{
	bool has_flag(const std::string&) { return false; }
}

namespace demonware
{
	std::uint64_t service_reply::transaction_id = 0;
	std::string captured_reply;
	void remote_reply::send(byte_buffer* buffer, const bool encrypted)
	{
		if (!encrypted) throw std::runtime_error("expected encrypted service reply");
		captured_reply = buffer->get_buffer();
	}
}
namespace utils::io {
bool read_file(const std::string& path, std::string* result) {
 std::ifstream file(path, std::ios::binary); if (!file) return false;
 result->assign(std::istreambuf_iterator<char>(file), {}); return !file.bad();
}
}
namespace utils::io {
bool write_file(const std::string& path, const std::string& data, bool append) {
 std::filesystem::create_directories(std::filesystem::path(path).parent_path());
 std::ofstream file(path, std::ios::binary | (append ? std::ios::app : std::ios::trunc));
 file.write(data.data(), data.size()); return bool(file);
}
}
namespace demonware {
const char* get_achievement_status_name(achievement_status) { return "finished"; }
namespace achievement_store { std::vector<achievement_record> get_all() {
 achievement_record record{}; record.name="zombies_preserved"; record.kind=5;
 return {record};
} }
}
using namespace demonware;
void require(bool condition, const char* label) { if (!condition) throw std::runtime_error(label); }
rapidjson::Document request(const std::string& json) {
 auto result=achievement_engine::dispatch(json); rapidjson::Document d; d.Parse(result.c_str());
 require(!d.HasParseError(), "valid response JSON"); return d;
}
int main() {
 try {
	std::string captured_conversion;
	require(utils::io::read_file("../run-40144/dw/hq_marketplace_242_40144_31.bin", &captured_conversion), "load conversion fixture");
	byte_buffer conversion_capture(captured_conversion);
	std::string captured_conversion_body, expected_conversion_reply;
	require(conversion_capture.read_struct(&captured_conversion_body, 65536) &&
		hq_vendor::reply_body(captured_conversion_body, expected_conversion_reply), "captured conversion request");
	// Exercise production service_reply framing before the encryption boundary.
	for (const auto task : {111, 242})
	{
		service_reply reply{nullptr, static_cast<std::uint8_t>(task), 0};
		if (task == 111) reply.send();
		else
		{
			auto result = std::make_unique<hq_vendor::result>();
			result->body = expected_conversion_reply;
			reply.add(result);
			reply.send_struct();
		}
		byte_buffer wire{captured_reply};
		std::uint64_t transaction{};
		std::uint32_t error{}, count = 1;
		unsigned char type{};
		require(wire.read_uint64(&transaction) && transaction != 0 &&
			wire.read_uint32(&error) && error == 0 && wire.read_ubyte(&type) && type == task,
			"marketplace success header");
		if (task == 111) require(wire.read_uint32(&count) && count == 0, "empty SKU result count");
		else
		{
			std::string body;
			require(wire.read_struct(&body, 65536) && body == expected_conversion_reply, "conversion structured reply body");
		}
		require(wire.get_remaining().empty(), "no unexpected marketplace reply fields");
	}
	// Fixtures live above the harness directory; read them before the working directory moves.
	std::string owner_store, task99_request, task99_page;
	require(utils::io::read_file("../crash-store/hq_economy.json", &owner_store) && owner_store.size() == 6233,
		"load the owner's slice 5 store fixture");
	require(utils::io::read_file("../crash-store/bdMarketplace_99_request.bin", &task99_request) && task99_request.size() == 40,
		"load the captured bdMarketplace task 99 request");
	// Owner's walk on 6560cdc: the first 100-id product page of the 400-SKU catalog (typed task id byte first).
	require(utils::io::read_file("../run-25248/dw/hq_marketplace_99_25248_61.bin", &task99_page) && task99_page.size() == 538,
		"load the captured bdMarketplace task 99 product page");
	// Use the captured definition table, exactly the columns used by load_catalog.
	std::map<std::string, hq_event_predicate::rule> table_rules;
	{
		std::ifstream table("../tables/dwgamechallenges.csv");
		require(bool(table), "open definition table");
		std::string line;
		unsigned predicates{};
		while (std::getline(table, line))
		{
			std::vector<std::string> cells;
			std::size_t start{};
			for (auto end = line.find(','); end != std::string::npos; end = line.find(',', start))
			{ cells.push_back(line.substr(start, end - start)); start = end + 1; }
			cells.push_back(line.substr(start));
			if (cells.size() < 6 || cells[0] == "a0") continue;
			if (!cells[4].empty()) ++predicates;
			require(hq_event_predicate::evaluate(cells[4], {}).valid, "every captured table predicate parses");
			if (cells[2] >= "1" && cells[2] <= "4" && !cells[3].empty())
				table_rules.emplace(cells[1], hq_event_predicate::rule{static_cast<unsigned>(std::stoul(cells[3])), cells[4]});
		}
		require(predicates > 100 && table_rules.contains("daily_ch_silenced_smg"), "real table rules loaded");
		achievement_engine::set_event_rules(table_rules);
	}
 const auto dir=std::filesystem::absolute(std::string("run-")+std::to_string(GetCurrentProcessId()));
 std::filesystem::create_directories(dir); std::filesystem::current_path(dir);
 require(hq_economy::snapshot().inventory.empty(), "empty start");
 require(hq_economy::transact([](auto& s) { return hq_economy::grant(s,{"GRANT_CURRENCY",2,100}); }), "grant");
 require(hq_economy::snapshot().currencies.at(2)==100, "persistent snapshot");
 require(!hq_economy::transact([](auto& s) { hq_economy::grant(s,{"GRANT_CURRENCY",2,10}); return false; }), "rollback");
 require(hq_economy::snapshot().currencies.at(2)==100, "rollback balance");
 require(!hq_economy::transact([](auto& s) { return hq_economy::grant(s,{"GRANT_CURRENCY",2,UINT32_MAX}); }), "overflow");
 std::vector<hq_economy::achievement> catalog;
 for (int i=0;i<4;++i) { hq_economy::achievement a; a.name="daily"+std::to_string(i); a.target=10; a.rewards={{"GRANT_CURRENCY",2,25},{"GRANT_PRODUCT",0x20000D,1}}; catalog.push_back(a); }
 for (int i=0;i<3;++i) { hq_economy::achievement a; a.name="weekly"+std::to_string(i); a.kind=2; catalog.push_back(a); }
 achievement_engine::set_catalog(catalog);

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

	{
		// The LUI shows "New Orders Available in" from the period boundary we publish, and
		// treats an offer whose end time is not in the future as expired: it must be the
		// START OF THE NEXT period for every time of day, including the day/week boundary.
		const std::uint64_t samples[] = {
			1789257600ull,            // 2026-09-13 00:00:00 UTC, exactly on a day boundary
			1789257601ull,            // one second into the day
			1789268878ull,            // 03:07:58 UTC, the owner's failing run
			1789300800ull,            // 12:00:00 UTC
			1789343999ull,            // 23:59:59 UTC, the last second of the day
			1789344000ull,            // the next UTC midnight
			1789603199ull,            // the last second of the UTC week
			1789603200ull,            // the next UTC week boundary
		};
		for (const auto now : samples)
		{
			const auto day = now / 86400;
			for (const auto kind : {1, 2, 4})
			{
				const auto next = achievement_engine::period_end(kind, day);
				require(next > now, "period boundary is strictly in the future");
				require(next % 86400 == 0, "period boundary lands on a UTC midnight");
				if (kind == 2) require(next % (7 * 86400) == 0 && next <= now + 7 * 86400, "weekly boundary is the next UTC week");
				else require(next == (day + 1) * 86400, "daily boundary is the next UTC midnight");
			}
		}
		require(achievement_engine::period_end(1, 20709) == 1789344000ull && achievement_engine::period_end(2, 20709) == 1789603200ull,
			"period boundaries match the published NextPeriodStartTimes");
	}
 auto scheduled=request(R"({"Action":"get_scheduled_user_achievements"})");
 require(scheduled["Achievements"].Size()==6, "three daily plus three weekly offers");
 const std::string name=scheduled["Achievements"][0]["name"].GetString();
 const auto activate=std::string(R"({"Action":"activate_scheduled_user_achievement","AchievementKind":1,"AchievementName":")")+name+R"("})";
 require(std::string(request(activate)["Status"].GetString())=="ok", "activation");
 const auto claim=std::string(R"({"Action":"claim_achievement_reward","ClientTx":"test-claim","AchievementKind":1,"AchievementName":")")+name+R"("})";
 require(std::string(request(claim)["Status"].GetString())=="error", "incomplete claim refused");
 require(hq_economy::transact([&](auto& s) { auto& a=s.achievements.at(name); a.status="claimable"; a.progress=a.target; return true; }), "completion fixture");
 auto claimed=request(claim);
 require(claimed["itemsReceived"].Size()==1 && claimed["currenciesReceived"].Size()==1, "claim rewards");
 require(hq_economy::snapshot().currencies.at(2)==125, "claim balance");
 request(claim); require(hq_economy::snapshot().currencies.at(2)==125, "replay no duplicate");
 require(hq_economy::snapshot().inventory.at({0x20000D,0}).quantity==1, "item exactly once");
 auto legacy=request(R"({"Action":"get_user_achievements"})");
 require(std::string(legacy["Achievements"][0]["name"].GetString())=="zombies_preserved", "Zombies projection");
 require(std::string(request("{")["Status"].GetString())=="error", "malformed JSON");
	for (const auto limit : {"-1", "0", "null"})
	{
		require(std::string(request(std::string{R"({"Action":"get_user_achievements","Limit":)"} +
			limit + "}")["Status"].GetString()) == "ok", "tolerant limit policy");
	}
	const auto native_schedule = request(R"({"Version":0,"Action":"get_scheduled_user_achievements","ClientTx":"abcdefghijklmnopqrstuv=="})");
	require(std::string{native_schedule["ClientTx"].GetString()} == "abcdefghijklmnopqrstuv==" &&
		native_schedule["Achievements"].Size() == 6, "native scheduled transaction preserved");
	const auto native_active = request(R"({"Version":0,"Action":"get_user_achievements","ClientTx":"abcdefghijklmnopqrstuv==","AchievementStatuses":["inProgress","claimable","finished"],"AchievementKinds":[1,2,3,4,6,7,8,9,10,11,12,13],"Limit":50})");
	require(std::string{native_active["ClientTx"].GetString()} == "abcdefghijklmnopqrstuv==" &&
		native_active["Achievements"].Size() == 1, "native active request filters kind 5");

	const auto filtered = request(R"({"Action":"get_user_achievements","AchievementKinds":[2]})");
	require(filtered["Achievements"].Size() == 3, "kind filter selects persisted weekly offers");
	const auto foreign = request(R"({"Action":"get_user_achievements_for_users","UserIDs":[43]})");
	require(foreign["Achievements"]["43"].Empty(), "foreign users do not share local records");
	const auto local = request(R"({"Action":"get_user_achievements_for_users","UserIDs":[42],"AchievementKinds":[1],"Limit":1})");
	require(local["Achievements"]["42"].Size() == 1, "local for-users projection");
	const auto another = std::string{scheduled["Achievements"][1]["name"].GetString()};
	request(std::string{R"({"Action":"activate_scheduled_user_achievement","AchievementName":")"} + another + R"(","AchievementKind":1})");
	const auto active_schedule = request(R"({"Action":"get_scheduled_user_achievements"})");
	bool native_status{};
	for (const auto& entry : active_schedule["Achievements"].GetArray())
		if (another == entry["name"].GetString()) native_status = std::string_view{entry["status"].GetString()} == "in_progress";
	require(native_status, "scheduled status vocabulary");
	auto abandoned = request(std::string{R"({"Action":"deactivate_user_achievement","AchievementName":")"} + another + R"("})");
	require(std::string_view{abandoned["Status"].GetString()} == "ok" && hq_economy::snapshot().achievements.at(another).status == "available", "native abandon without kind");
	{
		// After abandoning an order the board must still offer three daily and three weekly
		// slots in the current period, each carrying a future end time under the only key
		// the native record parsers read for it, "expirationTimestamp".
		const auto rolled = request(R"({"Action":"get_scheduled_user_achievements"})");
		const auto now = static_cast<std::uint64_t>(time(nullptr));
		for (const char* kind : {"1", "2", "4"})
			require(rolled["NextPeriodStartTimes"].HasMember(kind) &&
				rolled["NextPeriodStartTimes"][kind].GetUint64() > now, "published period start is in the future");
		std::size_t daily{}, weekly{};
		for (const auto& entry : rolled["Achievements"].GetArray())
		{
			require(entry.HasMember("expirationTimestamp") && !entry.HasMember("eventEndTimestamp"),
				"scheduled record carries expirationTimestamp and never eventEndTimestamp");
			require(entry["expirationTimestamp"].GetUint64() > now, "scheduled record end time is in the future");
			const std::string_view status{entry["status"].GetString()};
			if (status != "available" && status != "in_progress") continue;
			if (entry["kind"].GetInt() == 1) ++daily;
			else if (entry["kind"].GetInt() == 2) ++weekly;
		}
		require(daily == 3 && weekly == 3, "three daily and three weekly offers stay visible after abandon");
	}
	require(std::string_view{scheduled["Achievements"][0]["successRewards"][0]["type"].GetString()} == "grant_currency", "lowercase reward type");
	require(scheduled["Achievements"][0]["successRewards"][0]["currency"]["id"].GetUint() == 2, "nested currency payload");

	hq_economy::achievement kills; kills.name = "daily_ch_kills"; kills.target = 2;
	kills.status = "inProgress"; kills.rewards = {{"GRANT_CURRENCY", 2, 25}};
	require(hq_economy::transact([&](auto& state) { state.achievements[kills.name] = kills; return true; }), "event fixture");
	require(achievement_engine::submit_event({"1", 10001, {}}), "first kill");
	require(achievement_engine::submit_event({"1", 10001, {}}), "replayed kill");
	require(hq_economy::snapshot().achievements.at(kills.name).progress == 1, "event replay does not double progress");
	require(achievement_engine::submit_event({"killed_a_player", 10002, {}}), "second kill");
	require(hq_economy::snapshot().achievements.at(kills.name).status == "claimable", "kills reach claimable");
	const auto earned = request(R"({"Action":"claim_achievement_reward","AchievementName":"daily_ch_kills","ClientTx":"earned-kills"})");
	require(std::string_view{earned["Status"].GetString()} == "ok", "event-driven claim without kind");
	require(hq_economy::snapshot().currencies.at(2) == 150, "earned currency credited");
	require(achievement_engine::submit_event({"18", 20001, {}}), "payroll event");
	const auto payroll = request(R"({"Action":"get_user_achievements","AchievementKinds":[5],"AchievementStatuses":["claimable"]})");
	require(payroll["Achievements"].Size() == 1 && std::string_view{payroll["Achievements"][0]["name"].GetString()} == "payroll_officer", "payroll polling");
	request(R"({"Action":"claim_achievement_reward","AchievementName":"payroll_officer","ClientTx":"payroll-claim"})");
	require(hq_economy::snapshot().currencies.at(6) == 200, "payroll credited");
	achievement_engine::submit_event({"18", 20002, {}});
	require(hq_economy::snapshot().achievements.at("payroll_officer").status == "finished", "payroll cooldown");

	// A new payroll cycle must not reuse an already settled transaction on the same day.
	require(hq_economy::transact([](auto& state) {
		auto& a = state.achievements.at("payroll_officer"); a.status = "claimable";
		a.claim_transaction.clear(); return true;
	}), "new payroll cycle fixture");
	const auto reused_payroll = request(R"({"Action":"claim_achievement_reward","AchievementName":"payroll_officer","ClientTx":"payroll-claim"})");
	require(std::string_view{reused_payroll["Status"].GetString()} == "error" && hq_economy::snapshot().currencies.at(6) == 200, "settled payroll transaction cannot grant a new cycle");
 auto lock=CreateFileA("players2/user/hq_economy.lock",GENERIC_READ,0,nullptr,OPEN_EXISTING,0,nullptr);
 require(!hq_economy::transact([](auto&) {return true;}), "cross process lock"); CloseHandle(lock);
 auto temp=CreateFileA("players2/user/hq_economy.json.tmp",GENERIC_READ,0,nullptr,OPEN_ALWAYS,0,nullptr);
 require(!hq_economy::transact([](auto& s) {return hq_economy::grant(s,{"GRANT_CURRENCY",2,10});}), "save failure"); CloseHandle(temp);
 require(hq_economy::snapshot().currencies.at(2)==150, "save failure rollback");


 byte_buffer ae_wire; const std::string ae_json=R"({"Version":0,"Action":"get_user_achievements","ClientTx":"capture","AchievementKinds":[1,2,3,4,6,7,8,9,10,11,12,13],"Limit":50})";
 hq_protocol::write_ae(&ae_wire,ae_json); ae_wire.write(std::string(14,0));
 byte_buffer ae_reader(ae_wire.get_buffer()); std::string decoded;
 require(hq_protocol::parse_ae(&ae_reader,decoded) && decoded==ae_json, "reward mirrored framing");
 for (std::size_t i=0;i<ae_wire.size()-14;++i) {
  byte_buffer short_ae(ae_wire.get_buffer().substr(0,i));
  require(!hq_protocol::parse_ae(&short_ae,decoded), "truncated AE request");
 }
 require(hq_economy::transact([](auto& s) {
  hq_economy::achievement target; target.name="activation-target"; target.status="inactive"; target.kind=4;
  s.achievements.emplace(target.name,target);
  return hq_economy::grant(s,{"ACTIVATE_ACHIEVEMENT",0,0,"activation-target"});
 }), "activation reward");
 require(hq_economy::snapshot().achievements.at("activation-target").status=="inProgress", "activation reward persisted");
 require(hq_economy::transact([](auto& s) { return hq_economy::grant(s,{"SET_CURRENCY_BALANCE",3,70}); }), "set balance reward");
 require(hq_economy::snapshot().currencies.at(3)==70, "set balance persisted");
 hq_economy::state page_state;
 require(hq_marketplace::inventory_page(page_state,{1,500},100).empty(), "empty inventory page");
 for (unsigned i=1;i<=501;++i) page_state.inventory[{i,0}]={i,1,0,0,0};
 require(hq_marketplace::inventory_page(page_state,{1,500},100).size()==500, "500 first page");
 require(hq_marketplace::inventory_page(page_state,{2,500},100).size()==1, "501st second page");
 require(hq_marketplace::inventory_page(page_state,{2,500},100)[0].guid==501, "stable second page");
 require(hq_marketplace::inventory_page(page_state,{3,500},100).empty(), "empty final page");
 require(hq_marketplace::inventory_page(page_state,{0,500},100).empty(), "page zero");
 require(hq_marketplace::inventory_page(page_state,{UINT32_MAX,500},100).empty(), "page arithmetic overflow");
 page_state.inventory[{1,0}].expires=50;
 require(hq_marketplace::inventory_page(page_state,{1,500},100)[0].guid==2, "expired excluded");
 require(hq_marketplace::inventory_page(page_state,{1,500},100,true).size()==1, "expired listing");
 byte_buffer encoded;
 encoded.write_string("s2_steam"); encoded.write_uint32(1); encoded.write_uint32(500); encoded.write(std::string(4,0));
 byte_buffer inventory_wire(encoded.get_buffer()); hq_marketplace::inventory_request query;
 require(hq_marketplace::parse_inventory(&inventory_wire,query) && query.page==1 && query.limit==500, "captured inventory framing");
 for (std::size_t i=0;i<20;++i) {
  byte_buffer short_wire(encoded.get_buffer().substr(0,i));
  require(!hq_marketplace::parse_inventory(&short_wire,query), "truncated inventory rejected");
 }
	const std::string vendor_request = std::string("\x0a\x08s2_steam\x12\x24", 12) +
		"3cf6ce39-7313-4bd0-1fcf-c8ba7b0eecd6" + "\x1a\x18" + "j_S8AQAAAABQ_-mXoAEAAA==" + "\x20\x01";
	std::string vendor_reply;
	require(hq_vendor::reply_body(vendor_request, vendor_reply) && vendor_reply.size() == 82, "conversion native response framing");
	const auto expected_rule = std::string("\x0a\x08s2_steam\x12\x00\x1a\x24", 14) +
		"3cf6ce39-7313-4bd0-1fcf-c8ba7b0eecd6" + std::string("\x20\x01", 2);
	const auto expected_conversion = std::string("\x0a\x18", 2) + "j_S8AQAAAABQ_-mXoAEAAA==" +
		std::string("\x10\x00\x1a\x34", 4) + expected_rule;
	require(vendor_reply == expected_conversion, "conversion read-side field layout");
	auto unknown_rule = vendor_request; unknown_rule[12] = '0';
	require(!hq_vendor::reply_body(unknown_rule, vendor_reply), "unknown conversion rule rejected");

	for (std::size_t i = 0; i < vendor_request.size(); ++i)
		require(!hq_vendor::reply_body(vendor_request.substr(0, i), vendor_reply), "truncated vendor request");
	// Native pickup settlement is distinct from the synthetic claimable test above.

	hq_economy::state legacy_payroll;
	legacy_payroll.currencies = {{2, 950}, {7, 50}, {3, 99}};
	legacy_payroll.transactions = {{"payroll:124254", "1789259964000000"}, {"claim:manual", "payroll_officer:20709"}};
	require(hq_economy::migrate_payroll(legacy_payroll), "legacy_payroll migration applies");
	require(legacy_payroll.currencies.at(2) == 800 && legacy_payroll.currencies.at(6) == 200 && legacy_payroll.currencies.at(7) == 0 &&
		legacy_payroll.currencies.at(3) == 99, "migration drains the Social Score slot first then CP, capped by the receipt total");
	require(!hq_economy::migrate_payroll(legacy_payroll) && legacy_payroll.currencies.at(6) == 200, "migration marker prevents replay");
	hq_economy::state spent; spent.currencies[2] = 30; spent.transactions["payroll:124254"] = "1789259964000000";
	require(hq_economy::migrate_payroll(spent) && spent.currencies.at(2) == 0 && spent.currencies.at(6) == 30, "migration cannot overdraw spent legacy credits");
	const std::uint64_t payroll_now = 1789256008;
	hq_economy::state payroll_state;
	require(hq_payroll::settle(payroll_state, 1789255507000000, payroll_now) == hq_payroll::outcome::granted, "native payroll first pickup");
	require(payroll_state.currencies.at(6) == 200, "native payroll +200");
	require(hq_payroll::settle(payroll_state, 1789255507000000, payroll_now) == hq_payroll::outcome::replayed &&
		hq_payroll::settle(payroll_state, 1789256008000000, payroll_now) == hq_payroll::outcome::replayed &&
		payroll_state.currencies.at(6) == 200, "captured duplicate batches replay the completion without paying twice");
	require(hq_payroll::settle(payroll_state, 1789255507000000, payroll_now + 14400) == hq_payroll::outcome::stale &&
		payroll_state.currencies.at(6) == 200, "old pickup cannot grant in next period");
	require(hq_payroll::settle(payroll_state, (payroll_now + 14400) * 1000000, payroll_now + 14400) == hq_payroll::outcome::granted &&
		payroll_state.currencies.at(6) == 400, "new payroll period");
	require(hq_payroll::settle(payroll_state, 0, payroll_now) == hq_payroll::outcome::rejected, "payroll invalid timestamp");
	const auto saved_wallet = hq_economy::snapshot().currencies.at(6);
	const auto live_now = static_cast<std::uint64_t>(time(nullptr));
	require(achievement_engine::submit_event({"picked_up_payroll", static_cast<std::int64_t>(live_now * 1000000), {{"1", 1}, {"2", 0}}}, true), "native payroll persisted");
	const auto settled_wallet = hq_economy::snapshot().currencies.at(6);
	hq_economy::invalidate();
	require(achievement_engine::submit_event({"18", static_cast<std::int64_t>(live_now * 1000000), {}}, true) &&
		hq_economy::snapshot().currencies.at(6) == settled_wallet, "native payroll alias replay after reload");
	require(settled_wallet == saved_wallet, "legacy manual payroll claim prevents duplicate settlement");
	// The kiosk re-sends the pickup batch (same event, later a second pickup in the same
	// period): both must be acknowledged as success without a second grant.
	const auto same_period_pickup = live_now % 14400 ? live_now - 1 : live_now;
	require(achievement_engine::submit_event({"picked_up_payroll", static_cast<std::int64_t>(live_now * 1000000), {{"1", 1}, {"2", 0}}}, true) &&
		achievement_engine::submit_event({"picked_up_payroll", static_cast<std::int64_t>(same_period_pickup * 1000000), {{"1", 1}, {"2", 0}}}, true) &&
		hq_economy::snapshot().currencies.at(6) == settled_wallet, "second pickup in the same period is a success with no double credit");
	{
		// bdReward tasks 11/12 are struct tasks (typed 0x17 request payload): the acknowledgement
		// must be a structured reply with a typed empty body, never a count-framed one.
		service_reply reply{nullptr, 12, 0};
		auto body = std::make_unique<hq_protocol::empty_struct_result>();
		reply.add(body);
		reply.send_struct();
		byte_buffer wire{captured_reply};
		std::uint64_t transaction{};
		std::uint32_t error{};
		unsigned char type{};
		std::string payload{"x"};
		require(wire.read_uint64(&transaction) && wire.read_uint32(&error) && error == 0 && wire.read_ubyte(&type) && type == 12 &&
			wire.read_struct(&payload, 65536) && payload.empty() && !wire.has_more_data(), "reward game event acknowledgement is a typed empty struct");
	}
	// The kiosk arms a 5 s "Unable to get payroll at this time" banner on every click and
	// cancels it only on an achievementEngine CompletionUpdate, so a pickup replayed inside
	// an already settled period still publishes the completion - with a zero currency delta.
	require(hq_payroll::notification.has_value(), "a replayed pickup still queues a completion push");
	{
		rapidjson::Document replay; replay.Parse(hq_payroll::notification->json.c_str());
		require(!replay.HasParseError() && std::string(replay["name"].GetString()) == "payroll_officer" &&
			std::string(replay["challengeName"].GetString()) == "payroll_officer" &&
			std::string(replay["type"].GetString()) == "CHALLENGE" && std::string(replay["reason"].GetString()) == "completed" &&
			std::string(replay["status"].GetString()) == "finished" && replay["kind"].GetInt() == 5 &&
			std::string(replay["triggers"][0]["type"].GetString()) == "SET_CURRENCY_BALANCE" &&
			replay["triggers"][0]["inventory"]["currencies"][0]["currency_id"].GetUint() == 6 &&
			replay["triggers"][0]["inventory"]["currencies"][0]["balance_delta"].GetUint() == 0 &&
			replay["triggers"][0]["inventory"]["currencies"][0]["balance_before"].GetUint() == settled_wallet,
			"the replayed push repeats the payroll completion record with a zero delta");
	}
	hq_payroll::notification.reset();
	require(hq_economy::transact([&](auto& next) {
		next.achievements.erase("payroll_officer");
		next.transactions.erase("payroll:" + std::to_string(live_now / 14400));
		return true;
	}), "prepare independent native notification test");
	require(achievement_engine::submit_event({"picked_up_payroll", static_cast<std::int64_t>(live_now * 1000000), {}}, true), "new native settlement");
	require(hq_payroll::notification.has_value(), "persisted settlement queues completion");
	rapidjson::Document push; push.Parse(hq_payroll::notification->json.c_str());
	require(!push.HasParseError() && std::string(push["reason"].GetString()) == "completed" &&
		std::string(push["status"].GetString()) == "finished" && push["kind"].GetInt() == 5 &&
		push["triggers"][0]["inventory"]["currencies"][0]["balance_delta"].GetUint() == 200 &&
		push["triggers"][0]["inventory"]["currencies"][0]["balance_before"].GetUint() == settled_wallet,
		"native completed push carries absolute balance inputs and payroll identity");
	// The native record parser 0x13A570 maps "eventEndTimestamp" to record+0x30 (divided by
	// 1000) - the LAST COMPLETION TIME that AE_GetPlayerAchievementInfo (0x1213B0) publishes
	// as "timeSinceLastCompletion" - not to the expiration at record+0x18. Emitting it after
	// "completionTimestamp" overwrote the real completion time with period_end/1000, so the
	// kiosk's "14400 <= timeSinceLastCompletion or fullfilledTimes <= 0" test always chose
	// the collectable branch and the four-hour countdown never appeared. The push and every
	// fetch must date the claim with completionTimestamp alone.
	require(!push.HasMember("eventEndTimestamp") && push.HasMember("expirationTimestamp") &&
		push["completionTimestamp"].GetUint64() == hq_economy::snapshot().achievements.at("payroll_officer").completion &&
		push["completionTimestamp"].GetUint64() > push["expirationTimestamp"].GetUint64() / 1000 &&
		push["fulfilledTimes"].GetInt() == 1,
		"the completion push dates the payroll claim and never carries eventEndTimestamp");
	{
		const auto fetched = request(R"({"Action":"get_user_achievements","AchievementKinds":[5]})");
		bool checked{};
		for (const auto& entry : fetched["Achievements"].GetArray())
		{
			if (std::string_view{entry["name"].GetString()} != "payroll_officer") continue;
			const auto stamp = static_cast<std::uint64_t>(time(nullptr));
			const auto completion = entry["completionTimestamp"].GetUint64();
			require(!entry.HasMember("eventEndTimestamp") && entry["fulfilledTimes"].GetInt() > 0 &&
				completion <= stamp && stamp - completion < 14400,
				"the payroll fetch leaves the kiosk inside the four-hour countdown");
			checked = true;
		}
		require(checked, "the payroll record is part of the AlwaysOn fetch");
	}
	hq_payroll::notification.reset();
	require(achievement_engine::submit_event({"18", static_cast<std::int64_t>(live_now * 1000000), {}}, true) &&
		hq_payroll::notification.has_value(), "the alias event republishes the completion for the kiosk");
	{
		rapidjson::Document replayed; replayed.Parse(hq_payroll::notification->json.c_str());
		require(!replayed.HasParseError() &&
			replayed["triggers"][0]["inventory"]["currencies"][0]["balance_delta"].GetUint() == 0 &&
			replayed["triggers"][0]["inventory"]["currencies"][0]["balance_before"].GetUint() == hq_economy::snapshot().currencies.at(6),
			"event replay cannot replay the credit grant");
	}
	// GrabPayroll carries {1, masterPrestige}; Rank.GetPayrollAchievement then expects 757
	// (payroll_officer_masterprestige), which the native handler resolves from the record name.
	hq_payroll::notification.reset();
	require(achievement_engine::submit_event({"picked_up_payroll", static_cast<std::int64_t>(live_now * 1000000), {{"1", 1}, {"2", 1}}}, true) &&
		hq_payroll::notification.has_value(), "master prestige pickup queues a completion push");
	{
		rapidjson::Document prestige; prestige.Parse(hq_payroll::notification->json.c_str());
		require(!prestige.HasParseError() && std::string(prestige["name"].GetString()) == "payroll_officer_masterprestige" &&
			std::string(prestige["challengeName"].GetString()) == "payroll_officer_masterprestige" && prestige["kind"].GetInt() == 5,
			"a master prestige pickup publishes the 757 record name");
	}
	require(hq_economy::snapshot().achievements.count("payroll_officer_masterprestige") == 0,
		"the published master prestige name never forks the stored payroll record");
	hq_payroll::notification.reset();
	require(achievement_engine::submit_event({"picked_up_payroll", static_cast<std::int64_t>((live_now - 14400) * 1000000), {}}, true) &&
		!hq_payroll::notification, "a batch from an earlier period is acknowledged but animates nothing");
	bdMarketplaceCurrency native_currency{}; native_currency.m_currencyId = 2; native_currency.m_value = 200;
	byte_buffer currency_packet; native_currency.serialize(&currency_packet);
	require(currency_packet.get_buffer() == std::string("\x03\x02\x08\xC8\x00\x00\x00", 7), "native A49900 currency fields: ubyte then uint32");
	std::string metadata_capture;
	require(utils::io::read_file("../../run-40144/dw/bdMarketplace_168_002.bin", &metadata_capture), "load PID 40144 metadata capture");
	byte_buffer metadata_wire(metadata_capture);
	std::string metadata_tx;
	std::vector<hq_item_data::update> metadata_updates;
	require(hq_item_data::parse(&metadata_wire, 8481039780627572585ULL, metadata_tx, metadata_updates) &&
		metadata_updates.size() == 3 && metadata_tx == "htfJNwAAAABg0veXoAEAAA==", "captured task168 parser");
	for (std::size_t i = 0; i < metadata_capture.size() - 4; ++i)
	{
		byte_buffer truncated(metadata_capture.substr(0, i));
		std::vector<hq_item_data::update> ignored;
		require(!hq_item_data::parse(&truncated, 8481039780627572585ULL, metadata_tx, ignored), "task168 truncated record");
	}
	metadata_tx = "htfJNwAAAABg0veXoAEAAA==";
	byte_buffer foreign_metadata(metadata_capture);
	std::vector<hq_item_data::update> ignored_metadata;
	require(!hq_item_data::parse(&foreign_metadata, 42, metadata_tx, ignored_metadata), "task168 foreign owner");
	require(hq_economy::transact([&](auto& data) {
		for (const auto& entry : metadata_updates) if (!hq_economy::grant(data, {"GRANT_PRODUCT", entry.guid, 1})) return false;
		return true;
	}), "metadata owned fixture");
	require(hq_item_data::apply(metadata_tx, metadata_updates), "metadata update atomic");
	hq_economy::invalidate();
	require(hq_economy::snapshot().inventory.at({4194366, 0}).metadata == std::string("\x02", 1) + std::string(63, 0), "metadata persists arbitrary bytes");
	auto newer = metadata_updates; newer[0].bytes[0] = '\xff';
	require(hq_item_data::apply("newer-metadata", newer), "later metadata");
	require(hq_item_data::apply(metadata_tx, metadata_updates) && hq_economy::snapshot().inventory.at({4194366, 0}).metadata[0] == '\xff', "old replay does not rewind metadata");
	require(!hq_item_data::apply(metadata_tx, newer), "metadata transaction conflict");
	auto invalid_metadata = newer; invalid_metadata[1].guid = 0x7ffffffe;
	require(!hq_item_data::apply("unknown-item", invalid_metadata), "unknown metadata item rejects batch");
	require(hq_economy::snapshot().inventory.at({4194366, 0}).quantity == 1, "metadata never grants quantity");
	service_reply audit_reply(nullptr, 168, 0);
	auto audit = std::make_unique<hq_item_data::audit_result>(); audit->transaction = metadata_tx;
	audit_reply.add(audit); audit_reply.send();
	byte_buffer audit_wire(captured_reply); std::uint64_t audit_id{}; std::uint32_t audit_error{}, audit_count{}, audit_total{}; unsigned char audit_task{}; std::string audit_tx;
	require(audit_wire.read_uint64(&audit_id) && audit_wire.read_uint32(&audit_error) && audit_error == 0 &&
		audit_wire.read_ubyte(&audit_task) && audit_task == 168 && audit_wire.read_uint32(&audit_count) && audit_count == 1 &&
		audit_wire.read_uint32(&audit_total) && audit_total == 1 && audit_wire.read_string(&audit_tx) && audit_tx == metadata_tx &&
		audit_wire.get_remaining().empty(), "SDK audit reply one allocated string result");
 const auto mail=hq_mail::empty_slots(0);
 require(mail.size()==14*18, "mail minimum allocated slots");
 for (std::size_t i=0;i<14;++i) require(mail[i*18+2]==8 && mail[i*18+3]==0, "mail zero ID cannot redeem");
 require(hq_mail::empty_slots(SIZE_MAX).size()==4096*18, "mail bounded allocation");
 byte_buffer sku; sku.write_string("s2_steam"); sku.write_uint32(1); sku.write_uint32(100);
 sku.write_bool(false); sku.write_uint32(0); sku.write_uint32(1); sku.write_ubyte(150); sku.write_string("");
 byte_buffer sku_reader(sku.get_buffer());
 require(hq_marketplace::parse_skus(&sku_reader,query) && query.limit==100, "native SKU query");
 for (std::size_t i=0;i<sku.size();++i) {
  byte_buffer truncated(sku.get_buffer().substr(0,i));
  require(!hq_marketplace::parse_skus(&truncated,query), "truncated SKU query");
 }

 {
 require(hq_mail::valid_slot(0,13,14) && hq_mail::valid_slot(1,0,14), "last allocated mail slot valid");
 require(!hq_mail::valid_slot(0,14,14) && !hq_mail::valid_slot(0,-1,14) &&
  !hq_mail::valid_slot(-1,0,14) && !hq_mail::valid_slot(2,0,14) &&
  !hq_mail::valid_slot(0,0,0) && !hq_mail::valid_slot(0,0,4097), "unknown category and malformed mail bounds");
 // Native catalog read-side order A4A2C0/A4A510/A4A5A0, including bounded blobs.
 hq_vendor::catalog_result offer; offer.entry = *hq_marketplace::find_sku(0x20000D); byte_buffer offer_wire; offer.serialize(&offer_wire);
 byte_buffer offer_reader(offer_wire.get_buffer());
 unsigned sku_id{}, product{}, value{}, price_count{}, max_quantity{}; unsigned short collision{};
 unsigned char field{}, currency_id{}, sku_type{}; bool sold_out{}; std::string sku_data{}, promo{};
 require(offer_reader.read_uint32(&sku_id) && sku_id == 0x20000D && offer_reader.read_uint32(&product) && product == 0x20000D &&
  offer_reader.read_ubyte(&field) && offer_reader.read_blob(&sku_data) && sku_data == std::string(1, '\0') &&
  offer_reader.read_ubyte(&field) && offer_reader.read_uint32(&value) && offer_reader.read_uint32(&value) &&
  offer_reader.read_uint32(&value) && offer_reader.read_ubyte(&field) && offer_reader.read_blob(&promo) && promo == std::string(1, '\0') &&
  offer_reader.read_uint32(&value) && offer_reader.read_uint16(&collision) && offer_reader.read_uint32(&value) &&
  offer_reader.read_ubyte(&field) && offer_reader.read_uint32(&price_count) && price_count == 1 &&
  offer_reader.read_ubyte(&currency_id) && currency_id == 6 && offer_reader.read_uint32(&value) && value == 50 &&
  offer_reader.read_ubyte(&sku_type) && sku_type == 100 && offer_reader.read_uint32(&max_quantity) && max_quantity == 1 &&
  offer_reader.read_bool(&sold_out) && !sold_out && !offer_reader.has_more_data(), "native SKU record layout and price");
 auto catalog_query = [](unsigned page, unsigned type, unsigned id, const std::string& token) {
  byte_buffer b; b.write_string("s2_steam"); b.write_uint32(page); b.write_uint32(1); b.write_bool(false);
  b.write_uint32(id ? 1 : 0); if(id) b.write_uint32(id); b.write_uint32(1); b.write_ubyte(static_cast<unsigned char>(type)); b.write_string(token); return b.get_buffer();
 };
 bool selected{};
 for (auto type : {100u,150u}) for (auto page : {1u,2u}) for (auto id : {0u,0x20000Du,999u}) {
  byte_buffer b(catalog_query(page,type,id,""));
  require(hq_marketplace::parse_skus(&b,query,&selected) && selected == (id == 0 || (id == 0x20000D && page == 1)), "SKU page and type/ID filtering");
 }
 auto catalog_capture = catalog_query(1,100,0,"");
 for(std::size_t n=0;n<catalog_capture.size();++n) {
  byte_buffer b(catalog_capture.substr(0,n)); selected=true;
  require(!hq_marketplace::parse_skus(&b,query,&selected) && !selected, "truncated catalog cannot select offer");
 }
 byte_buffer unknown_catalog(catalog_query(1,100,0,"unknown"));
 require(!hq_marketplace::parse_skus(&unknown_catalog,query,&selected) && !selected, "unknown catalog token cannot select offer");
 }

	{
		const auto entries = hq_marketplace::catalog();
		const auto vendors = std::size(hq_marketplace::vendor_skus);
		require(entries.size() == 774 + vendors && !hq_marketplace::find_sku(1), "full table-derived collection catalog plus the vendor drops");
		// QuarterMasterUtils.GetAvailableSkuIDList asserts on the ids of the "MP" and "ZM"
		// tagged SKUs, so both must lead the catalog with a parseable SKU data string.
		const auto tag_of = [](const std::string& data) -> std::string {
			for (std::size_t at = 0; at < data.size();) {
				const auto end = std::min(data.find(';', at), data.size());
				const auto split = data.find(':', at);
				if (split < end && data.compare(at, split - at, "t") == 0) return data.substr(split + 1, end - split - 1);
				at = end + 1;
			}
			return {};
		};
		require(entries[0].id == 2 && entries[1].id == 6 && tag_of(entries[0].data) == "MP" && tag_of(entries[1].data) == "ZM" &&
			entries[0].type == 100 && entries[1].type == 100, "quartermaster supply drop SKUs lead the catalog with their tags");
		require(hq_marketplace::find_sku(2) && hq_marketplace::find_sku(6) && tag_of(hq_marketplace::find_sku(2)->data) == "MP" &&
			hq_marketplace::find_sku(2)->price == hq_marketplace::find_sku(6)->price, "vendor drops resolve through find_sku");
		for (const auto& id : {0x20000Du, 0x40000Au}) require(tag_of(hq_marketplace::find_sku(id)->data).empty() &&
			*hq_marketplace::find_sku(id)->data == 0, "collection items carry no SKU data");
		// Inventory_GetSKUInfo (binding 0x11FF90) reads promotionalText at cache slot +0x25C
		// and skuData at +0x29C, so each string field holds 63 characters plus a terminator;
		// ProcessSkuInfo splits the promotional text on ';' into the tile name and description.
		require(std::string_view{hq_marketplace::find_sku(2)->promotional_text} == "LUA_MENU_RARE_SUPPLY_DROP;3 random items" &&
			std::string_view{hq_marketplace::find_sku(6)->promotional_text} == "LUA_MENU_RARE_ZOMBIE_SUPPLY_DROP;3 random items",
			"the vendor drop tiles carry the shipped supply drop name keys");
		for (const auto& entry : hq_marketplace::vendor_skus)
			require(std::string_view{entry.promotional_text}.size() < 64 && std::string_view{entry.data}.size() < 64,
				"vendor SKU strings fit the native cache slot fields");
		{
			hq_vendor::catalog_result drop; drop.entry = *hq_marketplace::find_sku(2);
			byte_buffer wire; drop.serialize(&wire); byte_buffer reader(wire.get_buffer());
			unsigned value{}; unsigned char field{}; std::string data{};
			require(reader.read_uint32(&value) && value == 2 && reader.read_uint32(&value) && reader.read_ubyte(&field) &&
				reader.read_blob(&data) && data == std::string("t:MP") + '\0', "vendor drop record carries its tag");
		}
		std::set<std::string> cwl_tags;
		unsigned contracts{};
		for (const auto& entry : hq_marketplace::vendor_skus)
		{
			const auto tag = tag_of(entry.data);
			if (tag.starts_with("CWL_")) {
				cwl_tags.insert(tag);
				require(hq_marketplace::granted_items(entry).size() == 5 && !entry.consumable, "CWL pack contains five permanent cosmetics");
			}
			if (*entry.contract) {
				++contracts;
				require(hq_marketplace::granted_items(entry) == std::vector<std::uint32_t>{0x5000000u + contracts},
					"contract first item matches local periodic CostItemGuid, not SKU id");
				require(entry.type == 100 && std::string(entry.data).find("c:" + std::to_string(32 + contracts)) != std::string::npos &&
					std::string(entry.data).find("C:" + std::to_string(32 + contracts)) != std::string::npos && entry.price == 25 * contracts,
					"contract SKU id and price match local contract catalog, typed as a Quartermaster SKU");
			}
			require(std::string(entry.promotional_text).find(';') != std::string::npos, "vendor tiles carry name and description");
		}
		require(cwl_tags.size() == 16 && cwl_tags.contains("CWL_CWL") && contracts == 3, "all fixed CWL slots and three contracts populated");
		hq_marketplace::sku_request contracts_page; contracts_page.page = 1; contracts_page.limit = 100; contracts_page.types = {201};
		require(hq_marketplace::sku_page(contracts_page).size() == 3, "Contracts SKU type 201 supported");
		std::vector<unsigned> seen;
		hq_marketplace::sku_request page; page.limit = 100; page.types = {100};
		for (page.page = 1; ; ++page.page)
		{
			const auto values = hq_marketplace::sku_page(page);
			for (const auto& value : values) seen.push_back(value.id);
			if (values.size() < page.limit) break;
			require(page.page < 10, "catalog paging terminates");
		}
		require(seen.size() == entries.size() && std::adjacent_find(seen.begin(), seen.end()) == seen.end() && page.page == 8, "all catalog pages covered without duplicates");
		page.page = UINT32_MAX; require(hq_marketplace::sku_page(page).empty(), "page multiplication cannot overflow");
		page.page = 1; page.ids = {entries.front().id, entries.front().id}; page.types = {100,150};
		require(hq_marketplace::sku_page(page).size() == 2, "mixed byte type filters and duplicate ID filter");
		page.types = {99}; require(hq_marketplace::sku_page(page).empty(), "undefined SKU type has no fabricated offers");
		const auto collection_front = entries[vendors].id;
		hq_marketplace::set_rarities({{collection_front, 4}, {entries.back().id, 999}});
		require(hq_marketplace::find_sku(collection_front)->price == 5000 && hq_marketplace::find_sku(entries.back().id)->price == 50, "single rarity price policy bounds");
		require(hq_marketplace::find_sku(2)->price == 1000, "vendor drop price is fixed, not rarity derived");
		const auto buy_id = entries.back().id;
		require(hq_economy::transact([](auto& next) { next.currencies[6] = 49; return true; }), "purchase funds fixture");
		const auto before = hq_economy::snapshot();
		require(hq_marketplace::purchase("buy-test", buy_id, 1) == BD_MARKETPLACE_INSUFFICIENT_FUNDS_ERROR, "proper insufficient funds code");
		require(hq_economy::snapshot().revision == before.revision && !hq_economy::snapshot().inventory.contains({buy_id,0}), "failed purchase cannot grant or persist");
		require(hq_economy::transact([](auto& next) { next.currencies[6] = 150; return true; }), "fund purchase");
		require(hq_marketplace::purchase("buy-test", buy_id, 1) == BD_NO_ERROR, "collection purchase commits");
		hq_economy::invalidate();
		require(hq_marketplace::purchase("buy-test", buy_id, 1) == BD_NO_ERROR && hq_economy::snapshot().currencies.at(6) == 100 && hq_economy::snapshot().inventory.at({buy_id,0}).quantity == 1, "purchase replay after reload is exactly once");
		require(hq_marketplace::purchase("buy-test", collection_front, 1) == BD_MARKETPLACE_RESOURCE_CONFLICT, "purchase transaction reuse rejected");
		{
			// Serialized granted purchase item: exact SDK inventory fields consumed by
			// the native purchase success callback and by task 165 after reconnect.
			const auto granted = hq_economy::snapshot().inventory.at({buy_id, 0});
			bdMarketplaceInventory result{};
			hq_inventory_cache::fill_result(result, granted, 123, time(nullptr));
			byte_buffer wire; result.serialize(&wire); byte_buffer reader(wire.get_buffer());
			std::uint64_t user{}; std::string account, metadata; std::uint32_t id{}, quantity{}, xp{}, expiry{}, modified{};
			std::int64_t duration{}; std::uint16_t collision{};
			require(reader.read_uint64(&user) && user == 123 && reader.read_string(&account) && account == "steam" &&
				reader.read_uint32(&id) && id == buy_id && reader.read_uint32(&quantity) && quantity == 1 &&
				reader.read_uint32(&xp) && reader.read_blob(&metadata) && reader.read_uint32(&expiry) &&
				reader.read_int64(&duration) && reader.read_uint16(&collision) && reader.read_uint32(&modified) &&
				reader.get_remaining().empty(), "serialized purchase grant round trip");
			require(expiry == UINT32_MAX && duration == INT64_MAX && collision == 0,
				"purchased permanent item passes native 27A260 expiration predicate");
		}
		require(hq_marketplace::purchase("buy-again", buy_id, 1) == BD_MARKETPLACE_ITEM_MULTIPLE_PURCHASE_ERROR, "owned collection item cannot be charged twice");
		// Supply drops are consumables: owning one may not block the next purchase.
		require(hq_economy::transact([](auto& next) { next.currencies[6] = 2000; return true; }), "fund drop purchases");
		require(hq_marketplace::purchase("drop-1", 2, 1) == BD_NO_ERROR && hq_marketplace::purchase("drop-2", 2, 1) == BD_NO_ERROR &&
			hq_economy::snapshot().inventory.at({2, 0}).quantity == 2 && hq_economy::snapshot().currencies.at(6) == 0,
			"vendor drop purchases stack and debit");
		const auto cwl = *hq_marketplace::find_sku(0x200012f);
		require(hq_economy::transact([](auto& next) { next.currencies[6] = 2000; return true; }), "fund CWL bundle");
		require(hq_marketplace::purchase("cwl-pack", cwl.id, 1) == BD_NO_ERROR, "CWL purchase commits");
		for (const auto item : hq_marketplace::granted_items(cwl))
			require(hq_economy::snapshot().inventory.at({item,0}).quantity >= 1, "CWL purchase grants every previewed cosmetic");
		require(hq_marketplace::purchase("cwl-pack", cwl.id, 1) == BD_NO_ERROR &&
			hq_economy::snapshot().currencies.at(6) == 1000 &&
			hq_marketplace::purchase("cwl-again", cwl.id, 1) == BD_MARKETPLACE_ITEM_MULTIPLE_PURCHASE_ERROR,
			"CWL replay and repeat purchase cannot double charge");
		const auto products = hq_products::answer({1, 1, 1, {cwl.id}});
		require(products.size() == 1 && products[0].items.size() == 5, "task 99 and native purchase agree on CWL contents");
		require(hq_marketplace::purchase("bad", buy_id, UINT32_MAX) == BD_MARKETPLACE_INVALID_PARAMETER && hq_marketplace::purchase("bad", 1, 1) == BD_MARKETPLACE_RESOURCE_NOT_FOUND, "invalid quantity and supply SKU rejected");
	}
 byte_buffer no_terminator(std::string("\x10s2_steam",9)); std::string text;
 require(!no_terminator.read_string(&text), "unterminated string");
 byte_buffer blob; blob.write_data_type(0x13); blob.write_uint32(UINT32_MAX);
 byte_buffer bad_blob(blob.get_buffer()); require(!bad_blob.read_blob(&text), "oversize blob");
 bdMarketplaceInventory wire_item{}; wire_item.m_playerId=42; wire_item.unk="steam";
 wire_item.m_itemId=0x20000D; wire_item.m_itemQuantity=3; wire_item.m_expiryDuration=-1;
 byte_buffer put_wire; put_wire.write_string("s2_steam"); put_wire.write_uint32(1); wire_item.serialize(&put_wire);
 byte_buffer put_reader(put_wire.get_buffer()); std::vector<hq_economy::item> put_items;
 require(hq_marketplace::parse_put(&put_reader,42,put_items) && hq_marketplace::put(put_items), "put serializer roundtrip");
 byte_buffer wrong_owner(put_wire.get_buffer()); require(!hq_marketplace::parse_put(&wrong_owner,43,put_items), "foreign owner rejected");
 byte_buffer pawn_wire; pawn_wire.write_string("s2_steam"); pawn_wire.write_string("pawn-test"); pawn_wire.write_uint32(1);
 pawn_wire.write_uint32(0x20000D); pawn_wire.write_uint32(2); pawn_wire.write_uint16(0);
 byte_buffer pawn_reader(pawn_wire.get_buffer()); std::string pawn_tx; std::vector<hq_economy::item> pawn_items;
 require(hq_marketplace::parse_pawn(&pawn_reader,pawn_tx,pawn_items), "pawn candidate parser");
 require(hq_marketplace::pawn(pawn_tx,pawn_items), "pawn reconciliation");
 require(hq_marketplace::pawn(pawn_tx,pawn_items), "pawn replay");
 pawn_items[0].quantity=1; require(!hq_marketplace::pawn(pawn_tx,pawn_items), "transaction reuse rejected");
 pawn_items[0].quantity=4; require(!hq_marketplace::pawn("pawn-increase",pawn_items), "pawn cannot mint");
 require(hq_economy::snapshot().inventory.at({0x20000D,0}).quantity==2, "pawn state persisted");
 bdMarketplaceCurrency currency{}; currency.m_currencyId=2; currency.m_value=125;
 byte_buffer currency_wire; currency.serialize(&currency_wire);
 byte_buffer currency_read(currency_wire.get_buffer()); unsigned char currency_id{}; unsigned balance{};
 require(currency_read.read_ubyte(&currency_id) && currency_id==2 && currency_read.read_uint32(&balance) && balance==125, "currency serializer");
	achievement_engine::set_loot_catalog({0x20000D});
	require(hq_economy::transact([](auto& s) { return hq_economy::grant(s,{"GRANT_PRODUCT",1,2}); }), "drop grant");
	const auto loot_before=hq_economy::snapshot().inventory.at({0x20000D,0}).quantity;
	const auto open=R"({"Action":"open_supply_drop","SupplyDropID":"sd_mp","ClientTx":"drop-test"})";
	const auto first_drop=request(open);
	require(std::string_view{first_drop["Status"].GetString()}=="ok" && first_drop["GrantedItems"].Size()==3, "drop native vocabulary");
	require(first_drop["GrantedItems"][0]["id"].GetUint()==0x20000D && first_drop["DetailedInventory"].Size()==2, "drop inventory reconciliation");
	require(hq_economy::snapshot().inventory.at({1,0}).quantity==1 && hq_economy::snapshot().inventory.at({0x20000D,0}).quantity==loot_before+3, "atomic drop consume and grant");
	const auto fetched_drops = hq_marketplace::inventory_page(hq_economy::snapshot(), {1,500}, time(nullptr));
	require(std::any_of(fetched_drops.begin(), fetched_drops.end(), [](const auto& item) { return item.guid == 1 && item.quantity == 1; }), "task165 includes remaining common drop quantity");
	for (const auto& value : first_drop["GrantedItems"].GetArray())
	{
		const auto guid = value["id"].GetUint();
		hq_economy::invalidate();
		const auto inventory = hq_marketplace::inventory_page(hq_economy::snapshot(), {1, 500}, time(nullptr));
		const auto item = std::find_if(inventory.begin(), inventory.end(), [guid](const auto& entry) { return entry.guid == guid; });
		require(item != inventory.end() && item->quantity >= 1, "supply-drop loot persists in task 165 inventory");
		bdMarketplaceInventory reply{}; hq_inventory_cache::fill_result(reply, *item, 123, time(nullptr));
		require(reply.m_itemQuantity >= 1 && reply.m_expireDateTime == UINT32_MAX && reply.m_expiryDuration == INT64_MAX,
			"every opened loot grant uses permanent native ownership, not only the drop container");
	}
	const auto cached_drop = hq_inventory_cache::project(hq_economy::snapshot().inventory.at({1,0}), time(nullptr));
	require(cached_drop.id == 1 && cached_drop.quantity == 1 && cached_drop.duration == INT64_MAX && cached_drop.expires == UINT32_MAX, "refresh matches native165 inventory projection");
	hq_economy::invalidate();
	request(open);
	require(hq_economy::snapshot().inventory.at({1,0}).quantity==1, "drop restart replay");
	const auto wrong_drop=request(R"({"Action":"open_supply_drop","SupplyDropID":"sd_mp_rare","ClientTx":"drop-test"})");
	require(std::string_view{wrong_drop["Status"].GetString()}=="error", "drop transaction conflict");
	request(R"({"Action":"open_supply_drop","SupplyDropID":"sd_mp","ClientTx":"drop-second"})");
	const auto old_drop=request(open);
	require(old_drop["DetailedInventory"][0]["item_quantity"].GetUint()==0, "drop replay does not rewind native quantity");
	require(hq_inventory_cache::project(hq_economy::snapshot().inventory.at({1,0}), time(nullptr)).quantity == 0, "opening last drop explicitly refreshes zero quantity");
	hq_economy::item expired_drop{2, 5}; expired_drop.expires = 100;
	require(hq_inventory_cache::project(expired_drop, 99).quantity == 5 && hq_inventory_cache::project(expired_drop, 100).quantity == 0, "expiry refresh cannot resurrect stale drops");
	require(hq_economy::snapshot().inventory.at({0x20000D,0}).quantity==loot_before+6, "two drops only");
	const auto unavailable=request(R"({"Action":"open_supply_drop","SupplyDropID":"sd_mp","ClientTx":"drop-third"})");
	require(std::string_view{unavailable["Status"].GetString()}=="error", "unowned drop rejected");
	for(const auto payload : {R"({"Action":"open_supply_drop","SupplyDropID":[],"ClientTx":"bad"})",
		R"({"Action":"open_supply_drop","SupplyDropID":"sd_mp"})",
		R"({"Action":"open_supply_drop","SupplyDropID":"sd_zombie","ClientTx":"bad"})"}) {
		const auto bad=request(payload); require(std::string_view{bad["Status"].GetString()}=="error", "invalid drop rejected");
	}
	require(hq_economy::transact([](auto& s) {
		return hq_economy::grant(s,{"GRANT_PRODUCT",1,1}) && hq_economy::grant(s,{"GRANT_PRODUCT",0x400050,UINT32_MAX});
	}), "drop overflow fixture");
	achievement_engine::set_loot_catalog({0x400050});
	const auto overflow_drop=request(R"({"Action":"open_supply_drop","SupplyDropID":"sd_mp","ClientTx":"drop-overflow"})");
	require(std::string_view{overflow_drop["Status"].GetString()}=="error" && hq_economy::snapshot().inventory.at({1,0}).quantity==1, "failed loot grant rolls back drop debit");
	// Exercise the actual accept/abandon router with three occupied slots.
	achievement_engine::set_catalog(catalog);
	require(hq_economy::transact([](auto& next) {
		std::erase_if(next.achievements, [](const auto& pair) { return pair.second.kind == 1 || pair.second.kind == 2; }); return true;
	}), "fresh offer router fixture");
	const auto three = request(R"({"Action":"get_scheduled_user_achievements","AchievementKind":1})");
	std::string abandon_name;
	for (const auto& entry : three["Achievements"].GetArray())
	{
		abandon_name = entry["name"].GetString();
		const auto accepted = request(std::string{R"({"Action":"activate_scheduled_user_achievement","AchievementKind":1,"AchievementName":")"} + abandon_name + R"("})");
		require(std::string_view{accepted["Status"].GetString()} == "ok", "accept all three through router");
	}
	const auto abandoned_three = request(std::string{R"({"Action":"deactivate_user_achievement","AchievementName":")"} + abandon_name + R"("})");
	require(std::string_view{abandoned_three["Status"].GetString()} == "ok", "abandon one of three through router");
	const auto visible_three = request(R"({"Action":"get_scheduled_user_achievements","AchievementKind":1})");
	require(visible_three["Achievements"].Size() == 3 && hq_economy::snapshot().achievements.at(abandon_name).status == "available" &&
		hq_economy::snapshot().achievements.at(abandon_name).offer_day == static_cast<std::uint64_t>(time(nullptr)) / 86400, "abandoned order reoffered today with two active companions");
	const auto today = static_cast<std::uint64_t>(time(nullptr)) / 86400;
	require(visible_three["NextPeriodStartTimes"]["1"].GetUint64() == (today + 1) * 86400 &&
		visible_three["NextPeriodStartTimes"]["2"].GetUint64() == (today / 7 + 1) * 7 * 86400, "daily and weekly rollover boundaries");
	// Regression for the startup fail-fast investigation: the owner's real store
	// (players2/user/hq_economy.json.crashbak2, revision 72, currency 2 = 200, ten
	// items, eight achievements, thirteen receipts) must load through the production
	// code, migrate to Armory Credits and survive every path that runs at startup,
	// without dropping a single item, currency or receipt.
	{
		require(utils::io::write_file("players2/user/hq_economy.json", owner_store, false), "install the owner store");
		hq_economy::invalidate();
		const auto loaded = hq_economy::snapshot();
		require(loaded.revision == 73 && loaded.inventory.size() == 10 && loaded.achievements.size() == 8 &&
			loaded.transactions.size() == 14, "owner store loads and migrates without dropping anything");
		require(loaded.currencies.at(6) == 200 && loaded.currencies.at(2) == 0, "payroll balance moves to Armory Credits");
		require(loaded.transactions.at("payroll:124254") == "1789259964000000" &&
			loaded.transactions.count("migration:payroll-currency6-v1") == 1 &&
			loaded.transactions.count("drop:KxJ3GwAAAADokvCXoAEAAA==") == 1, "receipts preserved, migration stamped once");
		require(loaded.achievements.at("payroll_officer").rewards.at(0).id == 6 &&
			loaded.achievements.at("daily_ch_commend").rewards.at(0).id == 6 &&
			loaded.achievements.at("weekly_ch_wins").rewards.at(0).id == 6, "persisted CP reward definitions retargeted");
		require(loaded.inventory.at({1, 0}).quantity == 0 && loaded.inventory.at({4194366, 0}).quantity == 1 &&
			loaded.inventory.at({117563413, 0}).metadata.size() == 64, "loot and drop records survive verbatim");
		// sync_wallet pushes at most the 13 native slots; sync_inventory hands the
		// native cache a byte-sized metadata length that must never exceed 64.
		require(loaded.currencies.size() <= 13 && !loaded.currencies.contains(0), "wallet sync stays inside the native slot table");
		for (const auto& [key, entry] : loaded.inventory)
			require(entry.metadata.size() <= 64 && hq_inventory_cache::project(entry, time(nullptr)).id == entry.guid,
				"every owner item projects into the native inventory cache");
		hq_economy::invalidate();
		require(hq_economy::snapshot().revision == 73, "the payroll migration runs exactly once");

		std::vector<hq_economy::achievement> production;
		for (const auto& [name, target] : std::map<std::string, std::uint32_t>{{"daily_ch_kills", 10},
			{"daily_ch_headshots", 3}, {"daily_ch_1v1_wins", 3}, {"daily_ch_commend", 5}})
		{
			hq_economy::achievement entry; entry.name = name; entry.challenge_name = name;
			entry.kind = 1; entry.target = target; entry.rewards = {{"GRANT_CURRENCY", 6, 25}};
			production.push_back(entry);
		}
		for (const auto& [name, target] : std::map<std::string, std::uint32_t>{{"weekly_ch_kills", 100},
			{"weekly_ch_wins", 10}, {"weekly_ch_scorestreak_calls", 25}})
		{
			hq_economy::achievement entry; entry.name = name; entry.challenge_name = name;
			entry.kind = 2; entry.target = target; entry.rewards = {{"GRANT_CURRENCY", 6, 100}};
			production.push_back(entry);
		}
		for (const auto* name : {"contract_mp_1", "contract_mp_2", "contract_mp_3"})
		{
			hq_economy::achievement entry; entry.name = name; entry.challenge_name = name;
			entry.kind = 4; entry.usage_target = 3600;
			const auto payout = std::string_view{name} == "contract_mp_1" ? 50u : std::string_view{name} == "contract_mp_2" ? 100u : 150u;
			entry.rewards = {{"GRANT_CURRENCY", 6, payout}};
			production.push_back(entry);
		}
		achievement_engine::set_catalog(production);
		const auto orders = request(R"({"Action":"get_scheduled_user_achievements","AchievementKind":1})");
		require(orders["Achievements"].Size() == 3, "the owner store still offers three daily orders");
		for (const auto& entry : orders["Achievements"].GetArray())
			require(entry.HasMember("expirationTimestamp") && !entry.HasMember("eventEndTimestamp") &&
				entry["expirationTimestamp"].GetUint64() > static_cast<std::uint64_t>(time(nullptr)),
				"the owner store's orders carry a future native end time and no eventEndTimestamp");
		// AE_GetScheduledChallenges (0x121A00) and AE_GetPlayerActiveChallenges (0x121F40)
		// only publish the Lua "reward" table when the parsed record's reward pointer is
		// non-null, so a contract offered with an empty successRewards array reaches the
		// vendor with no reward at all while every daily and weekly carries one.
		{
			const auto offered = request(R"({"Action":"get_scheduled_user_achievements","AchievementKind":4})");
			require(offered["Achievements"].Size() == 3, "three contracts are offered");
			unsigned index{};
			for (const auto& entry : offered["Achievements"].GetArray())
				require(entry["kind"].GetInt() == 4 && entry["usageTimeTarget"].GetInt() == 3600 &&
					entry["successRewards"].Size() == 1 &&
					std::string_view{entry["successRewards"][0]["type"].GetString()} == "grant_currency" &&
					entry["successRewards"][0]["currency"]["id"].GetUint() == 6 &&
					entry["successRewards"][0]["currency"]["amount"].GetUint() == 50u * ++index,
					"every offered contract carries a currency reward the vendor can render");
		}
		require(request(R"({"Action":"get_scheduled_user_achievements","AchievementKind":2})")["Achievements"].Size() == 3 &&
			request(R"({"Action":"get_user_achievements"})")["Achievements"].Size() >= 8, "weekly and full fetches answer");
		const auto rolled = hq_economy::snapshot();
		for (const auto* name : {"daily_ch_1v1_wins", "daily_ch_commend", "daily_ch_headshots", "daily_ch_kills",
			"payroll_officer", "weekly_ch_kills", "weekly_ch_scorestreak_calls", "weekly_ch_wins"})
			require(rolled.achievements.contains(name), "offer rollover keeps every owner achievement");
		require(rolled.achievements.at("daily_ch_commend").activation == 1789260024 &&
			rolled.achievements.at("weekly_ch_kills").status == "inProgress" &&
			rolled.achievements.at("payroll_officer").claim_transaction == "payroll:124254", "owner progress and receipts survive rollover");
		require(rolled.currencies.at(6) == 200 && rolled.inventory.size() == 10, "rollover cannot spend or drop inventory");

		const auto period = std::uint64_t{4} * 3600;
		const auto recorded = 124254 * period + 60;
		require(hq_economy::transact([&](auto& next) { return hq_payroll::settle(next, std::int64_t(recorded) * 1000000, recorded) != hq_payroll::outcome::rejected; }),
			"payroll replay inside the recorded period is accepted");
		require(hq_economy::snapshot().currencies.at(6) == 200, "payroll replay cannot pay twice");
		const auto next_period = 124255 * period + 60;
		require(hq_economy::transact([&](auto& next) { return hq_payroll::settle(next, std::int64_t(next_period) * 1000000, next_period) != hq_payroll::outcome::rejected; }),
			"payroll settles in the following period");
		require(hq_economy::snapshot().currencies.at(6) == 400 &&
			hq_economy::snapshot().transactions.count("payroll:124255") == 1, "payroll pays Armory Credits once per period");

		// Task 99 = product query of the per-frame marketplace pump 0x27D160 (see hq_products.hpp).
		// Slice-5 capture: a one-SKU catalog asks for product 1 (page 1, count 1, limit 1).
		byte_buffer task99(task99_request);
		hq_products::request single{};
		require(hq_products::parse(&task99, single) && single.page == 1 && single.count == 1 && single.limit == 1 &&
			single.ids == std::vector<std::uint32_t>{1}, "captured one-SKU task 99 request parses");
		// Owner's capture: page 1 of the 400-SKU collection catalog, 100 sorted GUIDs.
		byte_buffer page_buffer(task99_page);
		unsigned char page_task{};
		hq_products::request page{};
		require(page_buffer.read_ubyte(&page_task) && page_task == hq_products::task && hq_products::parse(&page_buffer, page) &&
			page.page == 1 && page.count == 100 && page.limit == 100 && page.ids.size() == 100 &&
			page.ids.front() == 0x20000D && page.ids.back() == 0x40000E && std::is_sorted(page.ids.begin(), page.ids.end()),
			"captured 100-id task 99 product page parses");
		require(hq_products::describe(page) == "1,100,100:2097165,2097183,2097186,2097187,...,4194318", "task 99 request summary");
		{
			// Production framing: the reply must carry one product record per requested id,
			// each in the exact read order of the native deserializer 0xA488C0 / 0xA486F0.
			service_reply reply{nullptr, hq_products::task, 0};
			auto products = hq_products::answer(page);
			require(products.size() == 100, "every requested product id is answered");
			for (auto& product : products)
			{
				auto result = std::make_unique<hq_products::product_result>(std::move(product));
				reply.add(result);
			}
			reply.send();
			byte_buffer wire{captured_reply};
			std::uint64_t transaction{};
			std::uint32_t error{}, count{}, again{};
			unsigned char type{};
			require(wire.read_uint64(&transaction) && wire.read_uint32(&error) && error == 0 && wire.read_ubyte(&type) && type == 99 &&
				wire.read_uint32(&count) && count == 100 && wire.read_uint32(&again) && again == 100, "task 99 success header and result count");
			for (std::size_t i = 0; i < 100; ++i)
			{
				std::uint32_t product_id{}, value{}, item_count{}, item_id{}, quantity{}, pairs{}, pairs2{};
				unsigned short flags{};
				std::string name{}, description{}, data{};
				require(wire.read_uint32(&product_id) && product_id == page.ids[i] &&
					wire.read_blob(&name) && name == std::to_string(product_id) + '\0' && name.size() <= hq_products::name_capacity &&
					wire.read_blob(&description) && description.size() == 1 && wire.read_blob(&data) && data.size() == 1 &&
					wire.read_uint16(&flags) && wire.read_uint32(&value) &&
					wire.read_uint32(&item_count) && item_count == 1 &&
					wire.read_uint32(&item_id) && item_id == product_id && wire.read_uint32(&quantity) && quantity == 1 &&
					wire.read_uint32(&pairs) && pairs == 0 && wire.read_uint32(&pairs2) && pairs2 == 0, "native product record layout");
			}
			require(!wire.has_more_data(), "no unexpected task 99 reply fields");
		}
		require(hq_products::answer(single).size() == 1 && hq_products::answer(single)[0].id == 1 &&
			hq_products::answer(single)[0].items == std::vector<std::pair<std::uint32_t, std::uint32_t>>{{1, 1}}, "single product answer");
		{
			auto paged = page; paged.limit = 40;
			require(hq_products::answer(paged).size() == 40 && hq_products::answer(paged).back().id == page.ids[39], "limit bounds the product page");
			paged.page = 3; require(hq_products::answer(paged).size() == 20 && hq_products::answer(paged).front().id == page.ids[80], "later product pages offset by limit");
			paged.page = UINT32_MAX; require(hq_products::answer(paged).empty(), "page offset cannot overflow");
		}
		byte_buffer foreign(std::string("\x10""other\x00", 7));
		hq_products::request ignored{};
		require(!hq_products::parse(&foreign, ignored), "task 99 rejects a foreign title context");
		for (std::size_t i = 1; i < task99_page.size(); ++i)
		{
			byte_buffer truncated(task99_page.substr(1, i));
			hq_products::request partial{};
			require(!hq_products::parse(&truncated, partial), "truncated task 99 request rejected");
		}
		{
			byte_buffer mismatch(task99_page.substr(1, 12 + 15 + 5 * 99));
			hq_products::request partial{};
			require(!hq_products::parse(&mismatch, partial), "task 99 id count must match the declared count");
			std::string oversized = task99_page.substr(1, 12);
			byte_buffer oversized_writer; oversized_writer.write_uint32(1); oversized_writer.write_uint32(101); oversized_writer.write_uint32(101);
			for (unsigned id = 1; id <= 101; ++id) oversized_writer.write_uint32(id);
			byte_buffer oversized_buffer(oversized + oversized_writer.get_buffer());
			require(!hq_products::parse(&oversized_buffer, partial), "task 99 rejects more than 100 ids");
		}
		for (unsigned i = 0; i < 10; ++i) hq_products::observe(page), ++hq_products::requests;
		require(!hq_products::observe(page), "task 99 request logging stops after the first requests");
	}
	{
		reward_game_events::event large{"killed_a_player", 910000, {}};
		for (unsigned i = 0; i < 256; ++i) large.parameters.push_back({std::to_string(i), UINT64_MAX});
		const auto wire = hq_event_relay::encode(123, large);
		reward_game_events::event decoded{};
		require(!wire.empty() && hq_event_relay::decode(wire, 123, decoded) && decoded.parameters.size() == 256,
			"maximum relay event round trips with uint64 values and selector 255");
		const auto parts = hq_event_relay::chunks(123, wire);
		require(parts.size() > 1, "large event fragmented");
		hq_event_relay::receiver receiver;
		unsigned applied{};
		const auto submit = [&](const auto& event) { ++applied; return event.parameters.size() == 256; };
		for (const auto& part : parts)
			require(part.size() <= 1023 && receiver.accept(part, 123, 1, submit), "bounded chunk accepted");
		require(applied == 1, "only complete event applied");
		require(!receiver.accept(parts.back(), 123, 1, submit), "orphan continuation rejected");
		require(!receiver.accept(parts.front(), 999, 1, submit), "foreign chunk rejected");
		require(receiver.accept(parts.front(), 123, 1, submit) &&
			!receiver.accept(parts[1], 123, 10002, submit), "partial assembly expires");
		require(receiver.accept(parts.front(), 123, 1, submit) && receiver.accept(parts[1], 123, 1, submit) &&
			!receiver.accept(parts[1], 123, 1, submit), "duplicate continuation rejected");
		auto corrupt = parts; corrupt.back().back() = corrupt.back().back() == '0' ? '1' : '0';
		for (std::size_t i = 0; i + 1 < corrupt.size(); ++i) require(receiver.accept(corrupt[i], 123, 1, submit), "corrupt fixture prefix");
		require(!receiver.accept(corrupt.back(), 123, 1, submit) && applied == 1, "whole event fingerprint checked before submit");
		large.parameters.push_back({"0", 1});
		require(hq_event_relay::encode(123, large).empty(), "over-limit event rejected");
		large.parameters.pop_back(); large.parameters.back().selector = "0";
		require(hq_event_relay::encode(123, large).empty(), "duplicate selector rejected");

		// Exercise the real task-11 parser, including its old ten-parameter failure.
		const auto varint = [](std::uint64_t value) {
			std::string out; do { auto byte = static_cast<unsigned char>(value & 127); value >>= 7; out += static_cast<char>(byte | (value ? 128 : 0)); } while (value); return out;
		};
		const auto field = [&](unsigned tag, const std::string& value) { return varint((tag << 3) | 2) + varint(value.size()) + value; };
		std::string event = field(1, "killed_a_player") + varint(24) + varint(1820000);
		for (unsigned i = 0; i < 150; ++i) event += field(4, field(1, std::to_string(i)) + varint(16) + varint(i));
		const auto account = varint(8) + varint(123) + field(2, "steam");
		auto payload = field(1, "s2_steam") + field(2, field(1, account) + field(2, event));
		byte_buffer request; request.write_struct(payload.data(), static_cast<unsigned int>(payload.size()));
		byte_buffer input(request.get_buffer()), legacy(request.get_buffer());
		std::vector<reward_game_events::user_event_batch> users;
		require(reward_game_events::parse_report_for_users_request(&input, users, true) && users.size() == 1 &&
			users[0].events[0].parameters.size() == 150, "MP task 11 accepts 150 parameters");
		require(!reward_game_events::parse_report_for_users_request(&legacy, users), "Zombies parser retains original bound");
	}

	{
		require(hq_economy::transact([](auto& state) {
			for (const auto* name : {"daily_ch_kills", "daily_ch_headshots", "weekly_ch_kills", "weekly_ch_wins"}) {
				auto& order = state.achievements[name]; order.name = name;
				order.status = "inProgress"; order.progress = 0; order.target = 2;
			}
			return true;
		}), "relay order fixture");
		const auto submit = [](const auto& event) { return achievement_engine::submit_event(event, true); };
		const auto wire = hq_event_relay::encode(123, {"1", 900001, {{"6", 1}}});
		require(!wire.empty() && hq_event_relay::apply(wire, 123, submit), "client applies relayed headshot");
		require(hq_event_relay::apply(wire, 123, submit), "reliable reward replay acknowledged");
		require(hq_economy::snapshot().achievements.at("daily_ch_kills").progress == 1 &&
			hq_economy::snapshot().achievements.at("daily_ch_headshots").progress == 1, "relay advances once through shared event store");
		reward_game_events::event named{};
		require(hq_event_relay::decode(hq_event_relay::encode(123, {"killed_a_player", 123456, {{"6", 1}}}), 123, named) &&
			named.name == "killed_a_player" && named.parameters[0].value == 1, "relay preserves named as well as numeric events");
		const auto revision = hq_economy::snapshot().revision;
		for (const auto& bad : {"s2x_hq 2 123 0 1 0", "s2x_hq 1 999 0 1 0", "s2x_hq 1 123 -1 1 0",
			"s2x_hq 1 123 0 1 17", "s2x_hq 1 123 0 1 1 6", "s2x_hq 1 123 0 1 1 6 -1",
			"s2x_hq 1 123 0 1 2 6 1 6 1", "s2x_hq 1 123 0 1 0 junk", "s2x_hq 1 123 0 1 1 6 18446744073709551616"})
			require(!hq_event_relay::apply(bad, 123, submit), "malformed/foreign relay rejected before applying");
		require(!hq_event_relay::apply(std::string(769, '1'), 123, submit) &&
			hq_economy::snapshot().revision == revision, "invalid relay leaves store untouched");
		require(hq_event_relay::apply(hq_event_relay::encode(123, {"1", 900002, {}}), 123, submit), "second relayed kill");
		require(hq_economy::snapshot().achievements.at("daily_ch_kills").status == "claimable" &&
			hq_economy::snapshot().achievements.at("weekly_ch_kills").status == "claimable" &&
			hq_economy::snapshot().achievements.at("daily_ch_headshots").progress == 1, "daily/weekly kills claimable, non-headshot isolated");
		for (const auto stamp : {900003, 900004})
			require(hq_event_relay::apply(hq_event_relay::encode(123, {"5", stamp, {}}), 123, submit), "end-game event relayed");
		require(hq_economy::snapshot().achievements.at("weekly_ch_wins").status == "claimable", "definition-backed event 5 order claimable");
	}
	{
		const reward_game_events::event event{"killed_a_player", 920000, {{"1", 8}, {"6", 1}, {"9", 6}, {"130", 132}, {"128", 2097152}}};
		for (const auto* expression : {"", "(6:1)", "(1:8)||(1:9)", "(130:4)&&(130:128)",
			"((9:5)||(9:6))&&(128:2097152)", "(6:0)&&(1:9)||(130:4)", "(6:1)||(1:9)&&(130:8)"})
			require(hq_event_predicate::evaluate(expression, event).matches, "equality, flag masks, AND/OR, nesting and precedence");
		for (const auto* expression : {"(1:9)", "(130:8)", "(6:1)&&(1:9)", "(8:0)", "(130:4)&&(130:8)"})
		{
			const auto result = hq_event_predicate::evaluate(expression, event);
			require(result.valid && !result.matches, "predicate false and missing selector is not zero");
		}
		for (const auto* expression : {"(1:8)||", "(1:8)||garbage", "(1:9)&&garbage", "(6:1", "(6:1))", "(256:1)",
			"(1:-1)", "(1:18446744073709551616)", "(6=1)", "!(6:1)", "(6:1)&(1:8)", "(6:1) trailing"})
			require(!hq_event_predicate::evaluate(expression, event).valid, "malformed expressions fail closed including short-circuit branches");
		require(!hq_event_predicate::evaluate(std::string(33, '(') + "6:1" + std::string(33, ')'), event).valid &&
			!hq_event_predicate::evaluate(std::string(2049, '('), event).valid, "predicate depth and length bounded");
		require(hq_event_predicate::evaluate("(7:18446744073709551615)", {"1", 0, {{"7", UINT64_MAX}}}).matches,
			"predicate uint64 boundary");
		require(!hq_event_predicate::evaluate("", {"1", 0, {{"6", 1}, {"06", 0}}}).valid, "ambiguous selectors rejected");

		const auto reset_orders = []() {
			return hq_economy::transact([](auto& state) {
				for (const auto* name : {"daily_ch_kills", "daily_ch_headshots", "daily_ch_dom_caps", "daily_ch_killstreak",
					"daily_ch_silenced_smg", "daily_ch_equipment_kills", "weekly_ch_wins", "contract_mp_3"})
				{
					auto& order = state.achievements[name]; order.name = name; order.progress = 0; order.target = 100;
					order.status = "inProgress";
				}
				return true;
			});
		};
		require(reset_orders(), "table predicate order fixtures");
		reward_game_events::event kill{"killed_a_player", 920001, {}};
		for (unsigned i = 0; i < 150; ++i) kill.parameters.push_back({std::to_string(i), i == 6 ? 1u : i == 130 ? 132u : i == 1 ? 8u : 0u});
		reward_game_events::event decoded;
		const auto wire = hq_event_relay::encode(123, kill);
		require(hq_event_relay::decode(wire, 123, decoded) && decoded.parameters.size() == 150, "150 parameter kill roundtrip");
		hq_event_relay::receiver receiver;
		const auto submit = [](const reward_game_events::event& value) { return achievement_engine::submit_event(value, true); };
		for (const auto& part : hq_event_relay::chunks(123, wire)) require(receiver.accept(part, 123, 1, submit), "large headshot delivered through client receiver");
		const auto progress = [](const char* name) { return hq_economy::snapshot().achievements.at(name).progress; };
		require(progress("daily_ch_kills") == 1 && progress("daily_ch_headshots") == 1 &&
			progress("daily_ch_silenced_smg") == 1 && progress("daily_ch_equipment_kills") == 1, "large kill advances kills/headshots/weapon flags/OR predicate");
		std::reverse(kill.parameters.begin(), kill.parameters.end()); kill.name = "1";
		require(submit(kill) && progress("daily_ch_kills") == 1, "alias and parameter-order replay deduplicated");
		require(submit({"multi_kill", 920002, {{"1", 4}, {"2", 1}, {"3", 2}}}) &&
			progress("daily_ch_kills") == 1 && progress("contract_mp_3") == 1, "multi-kill is one event-2 occurrence, no double counted kills");
		require(submit({"gamemode_action", 920003, {{"1", 7}}}) && progress("daily_ch_dom_caps") == 1,
			"dom caps follow table event 3 once, not parameter value");
		require(submit({"streak", 920004, {{"1", 10}}}) && progress("daily_ch_killstreak") == 1, "killstreak follows event 4 once");
		require(submit({"end_game", 920005, {}}) && progress("weekly_ch_wins") == 1, "win follows table event 5");
		kill.timestamp = 920006;
		for (auto& parameter : kill.parameters) if (parameter.selector == "6") parameter.value = 0;
		require(submit(kill) && progress("daily_ch_kills") == 2 && progress("daily_ch_headshots") == 1, "non-headshot only advances matching predicates");
		kill.parameters.push_back({"6", 1});
		require(!submit(kill) && progress("daily_ch_kills") == 2, "invalid direct event cannot advance orders");
	}

	{
		// Reticle purchased in the owner's morning log. Exercise the real catalog and
		// persisted task-165 projection rather than a fabricated generic item id.
		constexpr unsigned reticle = 0x70200d8;
		require(hq_economy::transact([](auto& state) {
			state.inventory.erase({reticle, 0}); state.currencies[6] = 10000; return true;
		}), "reticle ownership fixture");
		require(hq_marketplace::purchase("slice9-reticle", reticle, 1) == BD_NO_ERROR, "buy owner reticle");
		hq_economy::invalidate();
		const auto items = hq_marketplace::inventory_page(hq_economy::snapshot(), {1, 500}, time(nullptr));
		const auto item = std::find_if(items.begin(), items.end(), [](const auto& entry) { return entry.guid == reticle; });
		require(item != items.end() && item->quantity == 1, "bought reticle survives reload and next task 165");
		bdMarketplaceInventory reply{}; hq_inventory_cache::fill_result(reply, *item, 123, time(nullptr));
		const auto immediate = hq_inventory_cache::project(*item, time(nullptr));
		require(reply.m_itemId == immediate.id && reply.m_itemQuantity == immediate.quantity &&
			reply.m_expireDateTime == UINT32_MAX && reply.m_expiryDuration == INT64_MAX,
			"reticle immediate cache insertion and next fetch agree on quantity and native usability");
	}
	{
		// Real two-step Contracts menu flow: purchase cost token, then activate via AE.
		require(hq_economy::transact([](auto& state) {
			state.currencies[6] = 150;
			for (const auto& sku : hq_marketplace::vendor_skus) if (*sku.contract) {
				state.achievements.erase(sku.contract);
				state.inventory.erase({sku.items[0], 0});
			}
			return true;
		}), "reset contract purchases");
		for (const auto& sku : hq_marketplace::vendor_skus) if (*sku.contract) {
			const auto activate = std::string{R"({"Action":"activate_user_contract","AchievementName":")"} + sku.contract + R"(","AchievementKind":4})";
			require(std::string(request(activate)["Status"].GetString()) != "ok", "unpaid contract activation rejected");
			require(hq_marketplace::purchase(sku.contract, sku.id, 1) == BD_NO_ERROR, "buy contract token");
			hq_economy::invalidate();
			require(hq_economy::snapshot().inventory.at({sku.items[0], 0}).quantity == 1, "paid token survives reload before activation");
			require(std::string(request(activate)["Status"].GetString()) == "ok", "paid AE contract activation");
			require(std::string(request(activate)["Status"].GetString()) == "ok", "activation replay needs no second token");
			const auto state = hq_economy::snapshot();
			require(state.inventory.at({sku.items[0], 0}).quantity == 0 && state.achievements.at(sku.contract).status == "inProgress",
				"activation and token consumption commit together");
			require(hq_marketplace::purchase(sku.contract, sku.id, 1) == BD_NO_ERROR &&
				hq_economy::snapshot().inventory.at({sku.items[0], 0}).quantity == 0, "purchase replay cannot resurrect consumed token");
			require(hq_marketplace::purchase(std::string{sku.contract} + "-again", sku.id, 1) == BD_MARKETPLACE_ITEM_MULTIPLE_PURCHASE_ERROR,
				"active contract cannot be charged again");
		}
		require(hq_economy::snapshot().currencies.at(6) == 0, "three contract prices debit currency 6 exactly once");
		const auto active = request(R"({"Action":"get_user_achievements","AchievementKind":4,"Statuses":["inProgress"]})");
		require(active["Achievements"].Size() == 3, "purchased contracts reach Orders active records");
	}

 std::ofstream("players2/user/hq_economy.json") << "corrupt";
 require(!hq_economy::transact([](auto&) {return true;}), "corrupt state rejected");
 std::string preserved; utils::io::read_file("players2/user/hq_economy.json", &preserved);
 require(preserved=="corrupt", "corrupt original preserved");
 hq_economy::invalidate();
 auto zombie_after_corruption=request(R"({"Action":"get_user_achievements"})");
 require(std::string(zombie_after_corruption["Achievements"][0]["name"].GetString())=="zombies_preserved", "HQ corruption cannot hide Zombies");
 std::cout << "PASS: store, atomic failure, lock, offer rollover/abandon, claim/replay, malformed JSON, Zombies isolation, pagination, typed packets, inventory mutations, supply drops, mail placeholders, full SKU catalog/purchases, payroll migration/periods, task 168 metadata, task 242 conversion, owner store fail-fast regression, task 99 product pages, payroll replay + reward struct acknowledgement, payroll completion push + vendor promo text, full task-11 events, bounded relay reassembly, table predicates + event progress\n";
 return 0;
 } catch(const std::exception& e) { std::cerr<<e.what()<<"\n"; return 1; }
}
