"""Offline execution of shipped Contracts reward/price readers with local policy."""
from pathlib import Path
import sys
import re
import csv
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
rows=list(csv.reader((root/'build/research/tables/periodicChallengeTable.csv').open(newline='')))
retail={int(row[0]):row for row in rows[1:] if row[0].isdigit()}
assert len(rows)==839 and all(len(row)==21 for row in rows)
def lookup(file,key,value,column,*args):
    try:
        if file.lower()=='mp/periodicchallengetable.csv' and int(key)==0:
            return retail.get(int(value), [""]*21)[int(column)]
    except (ValueError,TypeError,IndexError,AttributeError):
        pass
    return "stock"
lua.globals().retail_lookup=lookup
lua.execute('Engine.TableLookup=function(...) return retail_lookup(...) end')
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
assert(Engine.TableLookup("mp/periodicchallengetable.csv",0,162,11)=="0x5000019")
assert(Engine.TableLookup("other",0,162,11)=="stock")
assert(Engine.TableLookup("mp/periodicchallengetable.csv",0,{},11)=="stock")
zombies=true
assert(Engine.TableLookup("mp/periodicchallengetable.csv",0,45,3)=="AEC_DAILY_ASSAULT_KILLS_TITLE")
''')
print('PASS: shipped reward reader renders XP/drop/weapon including completed contract; timers, cost token, malformed lookup and Zombies delegation')

lua.execute('zombies=false; scope={quartermaster={SKUInfos={}}}; LUI={FlowManager={GetScopedData=function() return scope end}}')
source=(root/'src/client/game/demonware/hq_marketplace.hpp').read_text()
skus=re.findall(r'\{(0x0800F[0-9A-F]+), (\d+), 100, "t:CONTRACT;c:(\d+);[^\n]+?\{(0x500[0-9A-Fa-f]+)\}',source)
assert len(skus)==9
for sku,price,id,token in skus:
    lua.execute(f'table.insert(scope.quartermaster.SKUInfos, {{items={{{{guid="{token.lower()}"}}}}, prices={{{{value={price}}}}}, skuID={int(sku,16)}}})')
script=(dec/'ui_s2_contracts_menu_uc.dec.lua').read_text()
readers=lua.execute(script[:script.rindex('\nreturn {')]+'\nreturn {price=f0_local8,sku=f0_local9,init=f0_local1,lookup=f0_local2}')
lua.execute("AEChallengeTable={File='mp/periodicchallengetable.csv',Cols={ID=0,Type=1,Title=3,Description=4,Flavor=5,Difficulty=6,TimeToComplete=10,CostItemGuid=11}}; AEPeriodicType={Contract='AEC_CONTRACT'}; GameChallengeGroup={Scheduled=1}; DwDataUtils={Vendor={Operation=1},GetCachedData={[1]=function() return records end}}")
lua.globals().records=lua.table_from([lua.table_from({'ID':int(id)}) for _,_,id,_ in skus])
readers.init(0)
stats=list(csv.reader((root/'build/research/tables/StatsTable.csv').open(newline='')))
for sku,price,id,token in skus:
    row=retail[int(id)]
    assert row[11].lower()==token.lower() and row[3].startswith('AEC_') and row[4].startswith('AEC_')
    assert any(token.lower() in [cell.lower() for cell in r] and 'contract' in r for r in stats)
    for col in range(21):
        assert lua.globals().Engine.TableLookup('mp/periodicchallengetable.csv',0,int(id),col)==row[col]
    guid=lua.globals().Engine.TableLookup('mp/periodicchallengetable.csv',0,int(id),11)
    guid=readers.lookup(int(id),11) # shipped cache lowercases the exact retail string (including LAD B9)
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
