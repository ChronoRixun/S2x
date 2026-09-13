local f0_local0 = false
local f0_local1 = function ( f1_arg0 )
	ACTIONS.SetInputEnabled( f1_arg0, false )
end

local f0_local2 = function ( f2_arg0 )
	ACTIONS.SetInputEnabled( f2_arg0, true )
end

local f0_local3 = function ( f3_arg0 )
	ACTIONS.AnimateSequence( f3_arg0, "HideEverything" )
end

local f0_local4 = function ( f4_arg0 )
	ACTIONS.AnimateSequence( f4_arg0, "FadeEverythingIn" )
end

local f0_local5 = function ( f5_arg0, f5_arg1, f5_arg2, f5_arg3, f5_arg4 )
	if f5_arg3 == nil then
		return 
	elseif f5_arg3 == 0 then
		ACTIONS.AnimateSequence( f5_arg0, f5_arg4 .. "InfoHide" )
	else
		local f5_local0 = ACTIONS.AnimateSequence
		local f5_local1 = f5_arg0
		local f5_local2
		if f5_arg2 < f5_arg3 then
			f5_local2 = f5_arg4 .. "InfoColorRed"
			if not f5_local2 then
			
			else
				f5_local0( f5_local1, f5_local2 )
				ACTIONS.AnimateSequence( f5_arg0, f5_arg4 .. "InfoShow" )
			end
		end
		f5_local2 = f5_arg4 .. "InfoColorBlack"
	end
end

local f0_local6 = function ( f6_arg0, f6_arg1, f6_arg2 )
	ACTIONS.LeaveMenu( f6_arg0 )
	ACTIONS.HubCharacterExitMenu()
end

local f0_local7 = function ( f7_arg0 )
	local f7_local0 = 125
	local f7_local1 = 156
	f7_arg0:setAlpha( 0, 0 )
	local f7_local2 = f7_arg0:wait( f7_local0 )
	f7_local2.onComplete = function ()
		f7_arg0:setAlpha( 1, f7_local1 )
	end
	
end

local f0_local8 = function ( f9_arg0, f9_arg1 )
	for f9_local3, f9_local4 in ipairs( LUI.Split( f9_arg1, ";" ) ) do
		local f9_local5 = LUI.Split( f9_local4, ":" )
		if f9_local5[1] == QuarterMasterUtils.SKUDataKeys.TAG and f9_local5[2] == "special" then
			return true
		end
	end
	return false
end

local f0_local9 = function ( f10_arg0, f10_arg1 )
	QuarterMasterUtils.UpdateSkuInfoIfSameCount( f10_arg0, f10_arg1 )
	f10_arg0:dispatchEventToChildren( {
		name = "update_quartermaster_sku_button"
	} )
	f0_local2( f10_arg0 )
end

local f0_local10 = function ( f11_arg0, f11_arg1 )
	f0_local2( f11_arg0 )
end

local f0_local11 = function ( f12_arg0, f12_arg1 )
	Character_Scene.curVendor.changeTab = nil
	if Character_Scene.curVendor.enterSubMenu then
		Character_Scene.curVendor.enterSubMenu = nil
		return 
	end
	local f12_local0 = Engine.Inventory_GetCurrencyBalance( f12_arg0, QuarterMasterUtils.InventoryCurrencyType.CoDPoints )
	local f12_local1 = Engine.Inventory_GetCurrencyBalance( f12_arg0, QuarterMasterUtils.InventoryCurrencyType.ArmoryCredits )
	local f12_local2 = 9
	local f12_local3 = Lobby.GetRankForXP( Engine.GetPlayerDataMPXP( f12_arg0 ), AAR.GetPrestigeLevel( f12_arg0 ) )
	local f12_local4 = Cao.GetActiveCostume()
	local f12_local5 = Cao.GetHeadGender( Cao.GetGearGuid( Cao.Types.Head, f12_local4.head ) )
	local f12_local6 = "afford_nothing_greeting"
	if f12_local1 >= 100 then
		f12_local6 = "afford_collection_greeting"
	end
	if f12_local0 >= 200 then
		f12_local6 = "afford_rsd_greeting"
	end
	if Character_Scene.curVendor.name ~= "MaleQm" and f12_local2 < f12_local3 then
		f12_local6 = f12_local6 .. "_rank"
		if f12_local5 == Cao.Gender.Female then
			f12_local6 = f12_local6 .. "_f"
		else
			f12_local6 = f12_local6 .. "_m"
		end
	end
	if Character_Scene.curVendor.timesVisited and Character_Scene.curVendor.visitLimit < Character_Scene.curVendor.timesVisited then
		f12_local6 = "spam"
	end
	if f12_arg1 then
		f12_local6 = "first_greeting"
	end
	Character_Scene.PlayVendorAnim( f12_local6, "idle" )
end

local f0_local12 = function ( f13_arg0, f13_arg1 )
	f13_arg0.button_helper_bar:SetButtonDisabled( LuaButton.primary, f13_arg1.currencyNotEnough )
	if f13_arg1.currencyNotEnough == true then
		Character_Scene.PlayVendorAnim( "deny", "idle" )
	end
end

return {
	PreLoadFunc = function ( f14_arg0, f14_arg1, f14_arg2 )
		local f14_local0 = LUI.FlowManager.GetScopedData( f14_arg0 )
		f14_local0.quartermaster = {
			availableSkus = {},
			skusInfo = {},
			selectedSkuId = nil,
			lastPurchase = nil
		}
		DataModel.SetModelValue( DataSources.inFrontend.MP.CharacterTitleBar.characterTitle:GetModel( f14_arg1 ), Engine.Localize( "@HUB_QUARTERMASTER" ) )
		DataModel.SetModelValue( DataSources.inFrontend.MP.CharacterTitleBar.characterDescription:GetModel( f14_arg1 ), Engine.Localize( "@HUB_QUARTERMASTER_DESC" ) )
		local f14_local1
		if Engine.GetPlayerData( f14_arg1, CoD.StatsGroup.Ranked, "hubStats", "menuTutorialComplete_quartermaster" ) ~= false then
			f14_local1 = Engine.GetDvarBool( "hub_forceMenuTutorials" )
			if f14_local1 then
			
			else
				f0_local0 = f14_local1
				QuarterMasterUtils.PopulateQMNavTabs( f14_arg0, f14_arg1, DataSources.inFrontend.MP.Quartermaster.navTabs )
				f14_arg0._IsSKUsDataReady = false
				f14_arg0._IsSupplyDropListReady = false
				f14_arg0._SupplyDropLastEntry = {
					x = 0,
					y = 0
				}
				QuarterMasterUtils.BeginQMVendor( f14_arg1, f14_arg2.male )
				DwDataUtils.UpdateData[DwDataUtils.Vendor.Quartermaster]( f14_arg1 )
				QuarterMasterUtils.storeSKUInfo( f14_arg0, f14_arg1 )
				QuarterMasterUtils.ActivateMissedContracts( f14_arg1, QuarterMasterUtils.GetContractCurrencies( f14_arg1, DwDataUtils.GetCachedData[DwDataUtils.Vendor.Quartermaster]( f14_arg1 ) ) )
			end
		end
		f14_local1 = not Engine.GetDvarBool( "hub_preventMenuTutorials" )
	end
	,
	PostLoadFunc = function ( f15_arg0, f15_arg1, f15_arg2 )
		local f15_local0 = LUI.FlowManager.GetScopedData( f15_arg0 )
		local f15_local1 = nil
		if f15_local0.lastPrimaryCallback then
			f15_local1 = f15_local0.lastPrimaryCallback
		end
		local f15_local2 = f15_arg0.button_helper_bar:BeginSet()
		f15_local2 = f15_local2:AddBackButton()
		f15_local2 = f15_local2:AddLeft( LuaButton.primary, "LUA_MENU_SELECT", f15_local1 )
		f15_local2:Finish()
		f15_arg0.button_helper_bar.dontCloseMenusOnStartPress = true
		f15_arg0:addEventHandler( "check_currency", f0_local12 )
		f15_arg0:registerEventHandler( "inventory", function ( element, event )
			if event.inventoryEventType == InventoryEventType.TaskCompleted and event.inventoryTaskType == InventoryTaskType.PurchaseSKUS then
				if event.success == true then
					f0_local9( element, f15_arg1 )
				else
					f0_local10( element, f15_arg1 )
				end
			end
		end )
		f0_local1( f15_arg0 )
		f0_local3( f15_arg0 )
		f15_local2 = f15_arg0:wait( 400 )
		f15_local2.onComplete = function ()
			f0_local2( f15_arg0 )
			f0_local4( f15_arg0 )
			f15_local0.intButtonHelperBarDone = true
		end
		
		if f0_local0 == true then
			f15_local2 = 17
			if Engine.GetDvarBool( "4670" ) then
				f15_local2 = 54
			end
			local f15_local3 = {
				tutorialId = f15_local2
			}
			CharacterScene.Show( Character_Scene.vendorHandle, false )
			Character_Scene.curVendor.forceHide = true
			f15_arg0:registerEventHandler( "menu_tutorial_completed", function ( element, event )
				f0_local11( f15_arg1, true )
				Character_Scene.curVendor.forceHide = nil
				CharacterScene.Show( Character_Scene.vendorHandle, true )
			end )
			LUI.FlowManager.RequestAddMenu( nil, "menu_tutorial_modal_container", true, f15_arg1, false, f15_local3 )
			Engine.SetPlayerData( f15_arg1, CoD.StatsGroup.Ranked, "hubStats", "menuTutorialComplete_quartermaster", true )
			ACTIONS.UploadStats()
		else
			f0_local11( f15_arg1 )
		end
	end
	,
	PushFunc = function ( f19_arg0 )
		if not Character_Scene.curVendor or not Character_Scene.curVendor.enterSubMenu then
			PersistentForeground.MenuTransitionFade()
		end
	end
	,
	PopFunc = function ( f20_arg0 )
		if Character_Scene.curVendor.changeTab then
			return 
		end
		Character_Scene.EndVendor()
		ACTIONS.HubCharacterExitMenu()
		local f20_local0 = Engine.GetLuiRoot()
		if LUI.FlowManager.IsInStack( f20_local0.flowManager, "hub_menu" ) then
			Character_Scene.SetMode( Character_Scene.Actors.Avatar, Character_Scene.Views.NoAvatar, f20_arg0 )
		end
	end
	,
	ResumeFunc = function ( f21_arg0, f21_arg1, f21_arg2 )
		if f21_arg1 == "collections_operation_menu" then
			PersistentForeground.MenuTransitionFade()
		end
	end
	,
	ACTION_ChangeTab = function ( f22_arg0, f22_arg1, f22_arg2 )
		QuarterMasterUtils.HandleTabChange( f22_arg0, f22_arg1, f22_arg2 )
	end
	,
	CONDITION_HasExactNumSkus = function ( f23_arg0, f23_arg1 )
		if QuarterMasterUtils.CountAvailableSKUs( f23_arg0, DwDataUtils.GetCachedData[DwDataUtils.Vendor.Quartermaster]( f23_arg0 ) ) == f23_arg1 then
			return true
		else
			return false
		end
	end
	
}
