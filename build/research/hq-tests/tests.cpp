#include <std_include.hpp>
#include "game/demonware/achievement_engine.hpp"
#include "game/demonware/achievement_store.hpp"
#include <utils/io.hpp>
namespace utils::io {
bool read_file(const std::string& path, std::string* result) {
 std::ifstream file(path, std::ios::binary); if (!file) return false;
 result->assign(std::istreambuf_iterator<char>(file), {}); return !file.bad();
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
 achievement_engine::set_catalog(catalog);
 auto scheduled=request(R"({"Action":"get_scheduled_user_achievements"})");
 require(scheduled["Achievements"].Size()==3, "three daily offers");
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
 require(std::string(request(R"({"Action":"get_user_achievements","Limit":-1})")["Status"].GetString())=="error", "invalid limit");
 auto lock=CreateFileA("players2/user/hq_economy.lock",GENERIC_READ,0,nullptr,OPEN_EXISTING,0,nullptr);
 require(!hq_economy::transact([](auto&) {return true;}), "cross process lock"); CloseHandle(lock);
 auto temp=CreateFileA("players2/user/hq_economy.json.tmp",GENERIC_READ,0,nullptr,OPEN_ALWAYS,0,nullptr);
 require(!hq_economy::transact([](auto& s) {return hq_economy::grant(s,{"GRANT_CURRENCY",2,10});}), "save failure"); CloseHandle(temp);
 require(hq_economy::snapshot().currencies.at(2)==125, "save failure rollback");
 std::ofstream("players2/user/hq_economy.json") << "corrupt";
 require(!hq_economy::transact([](auto&) {return true;}), "corrupt state rejected");
 std::string preserved; utils::io::read_file("players2/user/hq_economy.json", &preserved);
 require(preserved=="corrupt", "corrupt original preserved");
 std::cout << "PASS: store, atomic failure, lock, rotation, activation, claim/replay, malformed JSON, Zombies isolation\n";
 return 0;
 } catch(const std::exception& e) { std::cerr<<e.what()<<"\n"; return 1; }
}
