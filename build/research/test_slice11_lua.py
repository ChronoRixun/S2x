"""Slice 11: execute shipped timer selector and CWL builder with model stubs."""
from pathlib import Path
import sys
sys.path.insert(0, str(Path(__file__).parent / 'slice9-python'))
from lupa.lua51 import LuaRuntime
root = Path(__file__).resolve().parents[2]
dec = root / 'build/research/luafiles/dec'
lua = LuaRuntime(unpack_returned_tuples=True)
lua.execute("""
zombies=false
CONDITIONS={IsZombiesMode=function() return zombies end,IsPublicMatch=function() return false end,IsHubMode=function() return true end}
AEPeriodicType={Contract='AEC_CONTRACT',ContractZM='AEC_CONTRACT_ZM'}
GameChallengeStatus={GameChallengeStatus_InProgress=1,GameChallengeStatus_Completed=2,GameChallengeStatus_Claimable=3,GameChallengeStatus_Failed=4,GameChallengeStatus_Expired=5}
GameChallengeEmptyData={ID=-1}
DwDataUtils={IsContractExpired=function() return false end}
ACTIONS={AnimateSequence=function(self,name) self.sequence=name end}
Engine={Localize=function(key) return key end,EpochTimeToGameTime=function() return '100' end}
RegisterMaterial=function(name) return name end
function model(value) return {GetValue=function() return value end} end
source={type=model('AEC_CONTRACT'),id=model(162),timeRemaining=model(1200),expirationEpoch=model('0'),status=model(0)}
function visual() return {setImage=function(self,v) self.image=v end,setText=function(self,v) self.text=v end} end
menu={GetDataSource=function() return source,0 end,contractTimeActivatedIcon=visual(),contractTimeActivatedText=visual(),contractTimeUnactivatedIcon=visual(),contractTimeUnactivatedLabel=visual(),contractTimeFailedLabel=visual(),contractTimeFailedIcon=visual()}
""")
script=(dec/'ui_s2_daily_orders_descriptions_uc.dec.lua').read_text()
start=script.index('local f0_local3 = function')
end=script.index('\nlocal f0_local4 =',start)
select=lua.execute(script[start:end]+'\nreturn f0_local3')
select(lua.globals().menu,0)
lua.execute("assert(menu.sequence=='ShowContractUnactivatedTime' and menu.contractTimeUnactivatedLabel.text=='@MENU_CONTRACT_COMPLETION_TIME'); source.status=model(1)")
select(lua.globals().menu,0)
lua.execute("assert(menu.sequence=='ShowContractActivatedTime'); source.expirationEpoch=model('123456'); source.status=model(0)")
select(lua.globals().menu,0)
lua.execute("assert(menu.sequence=='ShowContractUnactivatedExpirationTime')")
print('PASS: shipped timer selects Completion Time for zero epoch, active match time for active zero epoch, expiration countdown for nonzero epoch')

# Execute the actual preview builder; retain its Cost subscription and all element creation.
lua = LuaRuntime(unpack_returned_tuples=True)
lua.execute("""
_1080p=1; zombies=false; selected=1; currency=6; price=1000
CONDITIONS={IsZombiesMode=function() return zombies end}
Engine={Localize=function(key) return key end,Inventory_GetSKUInfo=function(id) assert(id==selected); return info end}
RegisterMaterial=function(name) return name end
function model(fn) return {GetValue=function() return fn() end} end
source={id=model(function() return selected end),CoDPointsPrice=model(function() return price end)}
info={prices={{currency=currency,value=price}}}
local noop=function() end
function element()
 local self={callbacks={}}
 return setmetatable(self,{__index=function(t,key)
  if key=='GetDataSource' then return function() return source,0 end end
  if key=='SubscribeToModelThroughElement' then return function(t,through,name,fn) t.callbacks[name]=fn end end
  if key=='setImage' then return function(t,value) t.image=value end end
  if key=='setText' then return function(t,value) t.text=value end end
  if key=='addElement' or key=='registerEventHandler' or key:sub(1,3)=='set' then return noop end
 end})
end
LUI={MenuBuilder={m_types_build={}},UIElement={new=element},UIImage={new=element},UIText={new=element},UIMarqueeText={new=element},DIRECTION={horizontal=1},HorizontalAlignment={Left=1},VerticalAlignment={Bottom=1,Middle=2}}
LUI.MenuBuilder.registerType=function(name,fn) LUI.MenuBuilder.m_types_build[name]=fn end
LUI.MenuBuilder.BuildRegisteredType=function(name,properties) return LUI.MenuBuilder.m_types_build[name](nil,properties) end
FONTS={BodyBoldFont={Font='font'}}; SWATCHES={Button={MenuOffWhite=1,MenuCream=2}}
""")
lua.execute((dec/'ui_s2_cwl_preview.dec.lua').read_text())
lua.execute((root/'data/ui_scripts/mp/patches/cwl_currency.lua').read_text())
lua.execute("""
local build=LUI.MenuBuilder.BuildRegisteredType
preview=build('cwl_preview',{controllerIndex=0})
assert(preview.CodPoints.image=='s2_armory_credits_icon')
preview.Cost.callbacks.CoDPointsPrice()
assert(preview.Cost.text==1000)
info={prices={{currency=5,value=500}}}; selected=2
preview.callbacks.id(); assert(preview.CodPoints.image=='cod_points')
info={prices={{currency=6,value=1000}}}
preview.callbacks.CoDPointsPrice(); assert(preview.CodPoints.image=='s2_armory_credits_icon')
for _,bad in ipairs({false,7,{}, {prices=false}, {prices={false}}, {prices={{currency='bad'}}}}) do
 info=bad; preview.callbacks.CoDPointsPrice(); assert(preview.CodPoints.image=='cod_points')
end
source=nil; preview.callbacks.id(); assert(preview.CodPoints.image=='cod_points')
source={id={GetValue=function() return selected end}}
info={prices={{currency='6'}}}; preview.callbacks.id(); assert(preview.CodPoints.image=='s2_armory_credits_icon')
preview.CodPoints=nil; preview.callbacks.id(); preview.Cost=nil; preview.callbacks.CoDPointsPrice()
zombies=true
local zm=build('cwl_preview',{controllerIndex=0}); assert(zm.CodPoints.image=='cod_points' and not zm.s2xCurrencyPatched)
zombies=false
local direct=LUI.MenuBuilder.m_types_build.cwl_preview(nil,{controllerIndex=0}); assert(direct.CodPoints.image=='s2_armory_credits_icon')
LUI.MenuBuilder.m_types_build.cwl_preview=function() return {} end
assert(build('cwl_preview',{}).CodPoints==nil)
LUI.MenuBuilder.m_types_build.cwl_preview=function() return nil end
assert(build('cwl_preview',{})==nil)
""")
print('PASS: shipped CWL preview uses AC for currency 6, restores CP on SKU change, keeps Cost, tolerates missing/malformed data/elements, skips Zombies, and supports both builder paths')
