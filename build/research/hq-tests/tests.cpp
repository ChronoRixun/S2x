#include <std_include.hpp>
#include "game/demonware/achievement_engine.hpp"
#include "game/demonware/hq_marketplace.hpp"
#include "game/demonware/hq_protocol.hpp"
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
	// Exercise production service_reply framing before the encryption boundary.
	for (const auto task : {111, 242})
	{
		service_reply reply{nullptr, static_cast<std::uint8_t>(task), 0};
		if (task == 111) reply.send();
		else
		{
			auto result = std::make_unique<hq_protocol::empty_struct_result>();
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
			require(wire.read_struct(&body, 65536) && body.empty(), "empty structured reply body");
		}
		require(wire.get_remaining().empty(), "no unexpected marketplace reply fields");
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
	require(filtered["Achievements"].Empty(), "kind filter excludes unrelated records");
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
	require(hq_economy::snapshot().currencies.at(2) == 350, "payroll credited");
	achievement_engine::submit_event({"18", 20002, {}});
	require(hq_economy::snapshot().achievements.at("payroll_officer").status == "finished", "payroll cooldown");

	// A new payroll cycle must not reuse an already settled transaction on the same day.
	require(hq_economy::transact([](auto& state) {
		auto& a = state.achievements.at("payroll_officer"); a.status = "claimable";
		a.claim_transaction.clear(); return true;
	}), "new payroll cycle fixture");
	const auto reused_payroll = request(R"({"Action":"claim_achievement_reward","AchievementName":"payroll_officer","ClientTx":"payroll-claim"})");
	require(std::string_view{reused_payroll["Status"].GetString()} == "error" && hq_economy::snapshot().currencies.at(2) == 350, "settled payroll transaction cannot grant a new cycle");
 auto lock=CreateFileA("players2/user/hq_economy.lock",GENERIC_READ,0,nullptr,OPEN_EXISTING,0,nullptr);
 require(!hq_economy::transact([](auto&) {return true;}), "cross process lock"); CloseHandle(lock);
 auto temp=CreateFileA("players2/user/hq_economy.json.tmp",GENERIC_READ,0,nullptr,OPEN_ALWAYS,0,nullptr);
 require(!hq_economy::transact([](auto& s) {return hq_economy::grant(s,{"GRANT_CURRENCY",2,10});}), "save failure"); CloseHandle(temp);
 require(hq_economy::snapshot().currencies.at(2)==350, "save failure rollback");


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
 std::ofstream("players2/user/hq_economy.json") << "corrupt";
 require(!hq_economy::transact([](auto&) {return true;}), "corrupt state rejected");
 std::string preserved; utils::io::read_file("players2/user/hq_economy.json", &preserved);
 require(preserved=="corrupt", "corrupt original preserved");
 auto zombie_after_corruption=request(R"({"Action":"get_user_achievements"})");
 require(std::string(zombie_after_corruption["Achievements"][0]["name"].GetString())=="zombies_preserved", "HQ corruption cannot hide Zombies");
 std::cout << "PASS: store, atomic failure, lock, rotation, activation, claim/replay, malformed JSON, Zombies isolation, pagination, typed packets, inventory mutations\n";
 return 0;
 } catch(const std::exception& e) { std::cerr<<e.what()<<"\n"; return 1; }
}
