#include <std_include.hpp>
#include "game/demonware/achievement_engine.hpp"
#include "game/demonware/hq_marketplace.hpp"
#include "game/demonware/hq_protocol.hpp"
#include "game/demonware/hq_mail.hpp"
#include "game/demonware/hq_vendor.hpp"
#include "game/demonware/hq_payroll.hpp"
#include "game/demonware/hq_item_data.hpp"
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
	const std::uint64_t payroll_now = 1789256008;
	hq_economy::state payroll_state;
	require(hq_payroll::settle(payroll_state, 1789255507000000, payroll_now), "native payroll first pickup");
	require(payroll_state.currencies.at(2) == 200, "native payroll +200");
	require(hq_payroll::settle(payroll_state, 1789255507000000, payroll_now) &&
		hq_payroll::settle(payroll_state, 1789256008000000, payroll_now) && payroll_state.currencies.at(2) == 200, "captured duplicate batches");
	require(hq_payroll::settle(payroll_state, 1789255507000000, payroll_now + 14400) &&
		payroll_state.currencies.at(2) == 200, "old pickup cannot grant in next period");
	require(hq_payroll::settle(payroll_state, (payroll_now + 14400) * 1000000, payroll_now + 14400) &&
		payroll_state.currencies.at(2) == 400, "new payroll period");
	require(!hq_payroll::settle(payroll_state, 0, payroll_now), "payroll invalid timestamp");
	const auto saved_wallet = hq_economy::snapshot().currencies.at(2);
	const auto live_now = static_cast<std::uint64_t>(time(nullptr));
	require(achievement_engine::submit_event({"picked_up_payroll", static_cast<std::int64_t>(live_now * 1000000), {{"1", 1}, {"2", 0}}}, true), "native payroll persisted");
	const auto settled_wallet = hq_economy::snapshot().currencies.at(2);
	hq_economy::invalidate();
	require(achievement_engine::submit_event({"18", static_cast<std::int64_t>(live_now * 1000000), {}}, true) &&
		hq_economy::snapshot().currencies.at(2) == settled_wallet, "native payroll alias replay after reload");
	require(settled_wallet == saved_wallet, "legacy manual payroll claim prevents duplicate settlement");
	require(!hq_payroll::notification, "legacy manual claim emits no native reward push");
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
 // Native catalog read-side order A4A2C0/A4A510/A4A5A0, including bounded blobs.
 hq_vendor::catalog_result offer; byte_buffer offer_wire; offer.serialize(&offer_wire);
 byte_buffer offer_reader(offer_wire.get_buffer());
 unsigned sku_id{}, product{}, value{}, price_count{}, max_quantity{}; unsigned short collision{};
 unsigned char field{}, currency_id{}, sku_type{}; bool sold_out{}; std::string sku_data{}, promo{};
 require(offer_reader.read_uint32(&sku_id) && sku_id == 1 && offer_reader.read_uint32(&product) && product == 1 &&
  offer_reader.read_ubyte(&field) && offer_reader.read_blob(&sku_data) && sku_data == "sd_mp" &&
  offer_reader.read_ubyte(&field) && offer_reader.read_uint32(&value) && offer_reader.read_uint32(&value) &&
  offer_reader.read_uint32(&value) && offer_reader.read_ubyte(&field) && offer_reader.read_blob(&promo) && promo.empty() &&
  offer_reader.read_uint32(&value) && offer_reader.read_uint16(&collision) && offer_reader.read_uint32(&value) &&
  offer_reader.read_ubyte(&field) && offer_reader.read_uint32(&price_count) && price_count == 1 &&
  offer_reader.read_ubyte(&currency_id) && currency_id == 2 && offer_reader.read_uint32(&value) && value == 200 &&
  offer_reader.read_ubyte(&sku_type) && sku_type == 100 && offer_reader.read_uint32(&max_quantity) && max_quantity == 1 &&
  offer_reader.read_bool(&sold_out) && !sold_out && !offer_reader.has_more_data(), "native SKU record layout and price");
 auto catalog_query = [](unsigned page, unsigned type, unsigned id, const std::string& token) {
  byte_buffer b; b.write_string("s2_steam"); b.write_uint32(page); b.write_uint32(1); b.write_bool(false);
  b.write_uint32(id ? 1 : 0); if(id) b.write_uint32(id); b.write_uint32(1); b.write_ubyte(static_cast<unsigned char>(type)); b.write_string(token); return b.get_buffer();
 };
 bool selected{};
 for (auto type : {100u,150u}) for (auto page : {1u,2u}) for (auto id : {0u,1u,999u}) {
  byte_buffer b(catalog_query(page,type,id,""));
  require(hq_marketplace::parse_skus(&b,query,&selected) && selected == (type==100 && page==1 && id!=999), "SKU page and type/ID filtering");
 }
 auto catalog_capture = catalog_query(1,100,0,"");
 for(std::size_t n=0;n<catalog_capture.size();++n) {
  byte_buffer b(catalog_capture.substr(0,n)); selected=true;
  require(!hq_marketplace::parse_skus(&b,query,&selected) && !selected, "truncated catalog cannot select offer");
 }
 byte_buffer unknown_catalog(catalog_query(1,100,0,"unknown"));
 require(hq_marketplace::parse_skus(&unknown_catalog,query,&selected) && !selected, "unknown catalog token cannot select offer");
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
	hq_economy::invalidate();
	request(open);
	require(hq_economy::snapshot().inventory.at({1,0}).quantity==1, "drop restart replay");
	const auto wrong_drop=request(R"({"Action":"open_supply_drop","SupplyDropID":"sd_mp_rare","ClientTx":"drop-test"})");
	require(std::string_view{wrong_drop["Status"].GetString()}=="error", "drop transaction conflict");
	request(R"({"Action":"open_supply_drop","SupplyDropID":"sd_mp","ClientTx":"drop-second"})");
	const auto old_drop=request(open);
	require(old_drop["DetailedInventory"][0]["item_quantity"].GetUint()==0, "drop replay does not rewind native quantity");
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
 std::ofstream("players2/user/hq_economy.json") << "corrupt";
 require(!hq_economy::transact([](auto&) {return true;}), "corrupt state rejected");
 std::string preserved; utils::io::read_file("players2/user/hq_economy.json", &preserved);
 require(preserved=="corrupt", "corrupt original preserved");
 auto zombie_after_corruption=request(R"({"Action":"get_user_achievements"})");
 require(std::string(zombie_after_corruption["Achievements"][0]["name"].GetString())=="zombies_preserved", "HQ corruption cannot hide Zombies");
 std::cout << "PASS: store, atomic failure, lock, rotation, activation, claim/replay, malformed JSON, Zombies isolation, pagination, typed packets, inventory mutations, supply drops, mail placeholders, native SKU parsing, payroll periods, task 168 metadata, task 242 conversion\n";
 return 0;
 } catch(const std::exception& e) { std::cerr<<e.what()<<"\n"; return 1; }
}
