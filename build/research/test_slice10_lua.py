"""Offline execution of shipped Contracts reward/price readers with local policy."""
from pathlib import Path
import sys
sys.path.insert(0,str(Path(__file__).parent/'slice9-python'))
from lupa.lua51 import LuaRuntime
root=Path(__file__).resolve().parents[2]
dec=root/'build/research/luafiles/dec'
lua=LuaRuntime(unpack_returned_tuples=True)
lua.execute('''
zombies=false
CONDITIONS={IsZombiesMode=function() return zombies end}
Engine={TableLookup=function() return "stock" end,
 GetItemGUIDFromReference=function(ref) assert(ref=="lad_mp"); return "0x123456" end,
 AE_GetScheduledChallenges=function() return records end,
 AE_GetPlayerActiveChallenges=function() return records end,
 Localize=function(key,amount) return amount and (key..amount) or key end}
records={{ID=162,kind=4,status=4},{ID=561,kind=4,status=1},{ID=146,kind=4},{ID=3048,kind=4}}
''')
source=(root/'src/client/component/hq_contracts.cpp').read_text()
lua.execute(source.split('R"lua(',1)[1].split(')lua"',1)[0])
utils=(dec/'ui_utility_mp_achievementengineutils.dec.lua').read_text()
lua.execute('''
AchievementEngineUtils={GetOverrideReward=function() return "" end,GetOverrideRewardIcon=function() return "" end}
OrderRewardLayout={Default=0,Weapon=1}
Currencies={ArmoryCredits=6,SocialScore=7,XP=1}
IsLanguageArabic=function() return false end
InventoryUtils={IsValidGuid=function(g) return g and g~="0x0" end,GetName=function(g) return g end,GetImage=function() return "supply_drop" end}
Engine.IsGuidAWeapon=function(g) return g=="0x123456" end
''')
start=utils.index('AchievementEngineUtils.GetRewardAndIcon =')
end=utils.index('\nAchievementEngineUtils.',start+1)
lua.execute(utils[start:end])
lua.execute('''
local a=Engine.AE_GetPlayerActiveChallenges(0)
assert(a[1].status==4 and a[1].reward.currencyID==1 and a[1].reward.currencyAmount==3000)
assert(AchievementEngineUtils.GetRewardAndIcon(a[1].reward,162)~="")
assert(AchievementEngineUtils.GetRewardAndIcon(a[3].reward,146)~="")
assert(AchievementEngineUtils.GetRewardAndIcon(a[4].reward,3048)~="")
assert(a[1].timeLimit==1200 and a[4].timeLimit==4800)
assert(Engine.TableLookup("mp/periodicchallengetable.csv",0,162,11)=="0x50F0001")
assert(Engine.TableLookup("other",0,162,11)=="stock")
assert(Engine.TableLookup("mp/periodicchallengetable.csv",0,{},11)=="stock")
zombies=true
assert(Engine.TableLookup("mp/periodicchallengetable.csv",0,162,11)=="stock")
''')
print('PASS: shipped reward reader renders XP/drop/weapon including completed contract; timers, cost token, malformed lookup and Zombies delegation')
