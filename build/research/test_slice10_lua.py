"""Offline execution of shipped Contracts reward/price readers with local policy."""
from pathlib import Path
import sys
import re
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
assert(Engine.TableLookup("mp/periodicchallengetable.csv",0,162,11)=="0x50f0001")
assert(Engine.TableLookup("other",0,162,11)=="stock")
assert(Engine.TableLookup("mp/periodicchallengetable.csv",0,{},11)=="stock")
zombies=true
assert(Engine.TableLookup("mp/periodicchallengetable.csv",0,162,11)=="stock")
''')
print('PASS: shipped reward reader renders XP/drop/weapon including completed contract; timers, cost token, malformed lookup and Zombies delegation')

lua.execute('zombies=false; scope={quartermaster={SKUInfos={}}}; LUI={FlowManager={GetScopedData=function() return scope end}}')
source=(root/'src/client/game/demonware/hq_marketplace.hpp').read_text()
skus=re.findall(r'\{(0x0800F[0-9A-F]+), (\d+), 100, "t:CONTRACT;c:(\d+);[^\n]+?\{(0x50F[0-9A-F]+)\}',source)
assert len(skus)==9
for sku,price,id,token in skus:
    lua.execute(f'table.insert(scope.quartermaster.SKUInfos, {{items={{{{guid="{token.lower()}"}}}}, prices={{{{value={price}}}}}, skuID={int(sku,16)}}})')
script=(dec/'ui_s2_contracts_menu_uc.dec.lua').read_text()
readers=lua.execute(script[:script.rindex('\nreturn {')]+'\nreturn {price=f0_local8,sku=f0_local9}')
for sku,price,id,token in skus:
    guid=lua.globals().Engine.TableLookup('mp/periodicchallengetable.csv',0,int(id),11)
    assert readers.price(None,guid,lua.globals().scope)==int(price)
    assert readers.sku(None,guid,lua.globals().scope)==int(sku,16)
assert lua.globals().Engine.TableLookup('mp/periodicchallengetable.csv',0,45,13)=='2x Supply Drops'
print('PASS: all nine shipped contract cost/SKU lookups match lowercase native GUIDs; rifle order advertises two drops')

mail=LuaRuntime(unpack_returned_tuples=True)
mail.execute('''
zombies=false; claimed=false; popup=false
CONDITIONS={IsZombiesMode=function() return zombies end}
Engine={Inventory_GetVoucherItems=function() return nil end, Inventory_RedeemVoucherItem=function() return false end}
InventoryUtils={GetLootData=function() return nil end}
S2xHQMail={List=function(controller)
 if claimed or controller~=0 then return {} end
 return {{guid="0x50E0001",slot=8,name="Welcome",desc="500 AC",image="s2_armory_credits_icon",itemQuantity=1}}
 end, Redeem=function(controller,slot) assert(controller==0 and slot==8); claimed=true; return true end}
scope={mailOfficer={controllerIndex=0}}
LUI={FlowManager={GetScopedData=function() return scope end, RequestAddMenu=function() popup=true end}}
Store={ShouldShowPreOrder=function() return false end}
''')
source=(root/'src/client/component/mail_guard.cpp').read_text()
mail.execute(source.split('R"lua(',1)[1].split(')lua"',1)[0])
script=(dec/'ui_s2_mail_officer_menu_uc.dec.lua').read_text()
functions=mail.execute(script[:script.rindex('\nreturn {')]+'\nreturn {list=f0_local19,collect=f0_local10}')
functions.list(mail.table())
assert mail.eval('#scope.mailOfficer.messages')==1
mail.execute('menu={Messages={_targetPosition={x=0,y=0},GetMaxVisibleColumns=function() return 3 end}}')
functions.collect(mail.globals().menu,0)
assert mail.eval('claimed and popup')
functions.list(mail.table())
assert mail.eval('#scope.mailOfficer.messages')==0
mail.execute('zombies=true; assert(Engine.Inventory_GetVoucherItems(0)==nil)')
print('PASS: shipped Mail kiosk lists local voucher metadata, collects via shared redeem bridge, and empties after claim; Zombies preserves nil')
