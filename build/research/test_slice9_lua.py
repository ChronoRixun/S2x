"""Exercise the shipped Lua list builder with the embedded local contract policy.
Run: python build/research/test_slice9_lua.py (lupa under slice9-python or installed).
This is a mocked Lua test, not an in-game/UI verification.
"""
from pathlib import Path
import sys
sys.path.insert(0, str(Path(__file__).parent / "slice9-python"))
from lupa import LuaRuntime
root = Path(__file__).resolve().parents[2]
dec = root / "build/research/luafiles/dec"
lua = LuaRuntime(unpack_returned_tuples=True)
lua.execute("""
zombies = false
CONDITIONS = { IsZombiesMode = function() return zombies end, IsInHubTutorial = function() return false end }
LUI = { SingleSplit = function(text, sep) return string.match(text, "^(.-)" .. sep .. "(.*)$") end }
Engine = { TableLookup = function(...) return "stock" end }
""")
source = (root / "src/client/component/hq_contracts.cpp").read_text()
lua.execute(source.split('R"lua(', 1)[1].split(')lua"', 1)[0])
utils = (dec / "ui_utility_mp_achievementengineutils.dec.lua").read_text()
lua.execute(utils[:utils.index("AchievementEngineUtils.GetSpecialZMMaterialByMTX")])
start = utils.index("local f0_local3 = function ( f25_arg0 )")
end = utils.index("AchievementEngineUtils.GetConversionOverrideByID")
lua.execute(utils[start:end])
lua.execute("""
for id = 33, 35 do
 assert(AchievementEngineUtils.ShouldDisplayChallengeByID(0, id))
 assert(Engine.TableLookup(AEChallengeTable.File, 0, id, 11) == "0x500000" .. (id - 32))
end
assert(Engine.TableLookup(AEChallengeTable.File, 0, 99, 11) == "stock")
assert(Engine.TableLookup("other.csv", 0, 33, 11) == "stock")
assert(Engine.TableLookup(AEChallengeTable.File, 0, {}, 11) == "stock")
assert(Engine.TableLookup(AEChallengeTable.File, 0, 33, 1.5) == "stock")
zombies = true
assert(Engine.TableLookup(AEChallengeTable.File, 0, 33, 11) == "stock")
zombies = false
local function model(value)
 return { GetValue = function() return value end, SetValue = function(self, controller, v) value = v end }
end
local function grid()
 return { Populate = function(self, count, populate, focus, controller)
  self.count = count
  for index = 0, count - 1 do
   local row = setmetatable({}, { __index = function(t, k) local m = model(false); rawset(t, k, m); return m end })
   populate(row, index, controller)
  end
 end }
end
AEPeriodicType = {Contract = "AEC_CONTRACT", Tutorial = "AEC_FTE"}
GameChallengeType = { GameAchievementKind_FTE = 6, GameAchievementKind_Order_Contract = 4 }
GameChallengeStatus = { GameChallengeStatus_Expired = 5, GameChallengeStatus_Claimable = 3, GameChallengeStatus_Completed = 4 }
GameChallengeGroup = { Scheduled = 1, PlayerActive = 2 }
scheduled = {}
active = {}
for id = 33, 35 do scheduled[#scheduled + 1] = { ID = id, kind = 4, target = 1, status = 1, timeLimit = 3600, expirationTimestamp = "9999999999" } end
scheduled[4] = { ID = 10, kind = 1 }
scope = { periodicContractData = { ActiveContracts = {}, allContractsActive = true }, navigationInfo = {}, quartermaster = { SKUInfos = {} } }
for id = 33, 35 do scope.quartermaster.SKUInfos[#scope.quartermaster.SKUInfos + 1] = { items = {{guid = "0x500000" .. (id - 32)}}, prices = {{value = 25 * (id - 32)}}, skuID = 134279168 + id } end
LUI.FlowManager = { GetScopedData = function() return scope end }
DwDataUtils = { Vendor = { Operation = 1 }, GetCachedData = { function(controller, group) if group == 1 then return scheduled else return active end end },
 IsPlayerActiveChallenge = function(controller, id) return active[1] and active[1].ID == id end,
 GetPlayerActiveChallenge = function() return active[1] end, IsContractExpired = function() return false end }
DataSources = { Shared = { Restore = { FromSubMenu = model(false) }, MP = { DailyOrders = { contractsList = grid(), supplyContractsList = grid() } } } }
menu = { contractGrid = { setAlpha = function() end }, viewContractGrid = { setAlpha = function() end } }
""")
menu = (dec / "ui_s2_contracts_menu_uc.dec.lua").read_text()
functions = lua.execute(menu[:menu.rindex("\nreturn {")] + "\nreturn { cache=f0_local1, price=f0_local8, sku=f0_local9, populate=f0_local27 }")
functions.cache(0)
functions.populate(lua.globals().menu, 0)
assert lua.eval("DataSources.Shared.MP.DailyOrders.contractsList.count") == 3
for n in range(1, 4):
    token = f"0x500000{n}"
    assert functions.price(None, token, lua.globals().scope) == 25 * n
    assert functions.sku(None, token, lua.globals().scope) == 0x0800F020 + n
lua.execute('active[1] = {ID=34, kind=4, target=1, progress=1, status=3, timeLeft="3500"}')
functions.populate(lua.globals().menu, 0)
assert lua.eval("scope.periodicContractData.menuContracts[2].status") == 3
print("PASS: shipped Contracts list/filter, three prices/SKUs, active substitution, malformed arguments, Zombies and unrelated table delegation")
