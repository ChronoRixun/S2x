local f0_local0 = 14400000
local f0_local1 = 14400
local f0_local2 = "mail-interact"
local f0_local3 = "0x800076"
local f0_local4 = function ( f1_arg0, f1_arg1 )
	local f1_local0 = LUI.FlowManager.GetScopedData( f1_arg0 )
	local f1_local1 = nil
	if f1_local0.mailOfficer.secondsUntilNextPayroll <= 0 then
		ACTIONS.AnimateSequence( f1_arg0.Payroll, "NewMail" )
		f1_local1 = 0
	else
		ACTIONS.AnimateSequence( f1_arg0.Payroll, "ItemCollected" )
		f1_local1 = Game.GetTime() + 1000 * f1_local0.mailOfficer.secondsUntilNextPayroll
	end
	assert( f1_local1 )
	f1_arg0.CollectCreditsCountdown:setEndTime( f1_local1 )
end

local f0_local5 = function ( f2_arg0, f2_arg1, f2_arg2 )
	if f2_arg2 then
		f2_arg0.ButtonHelperBar:HideButtonsWithTag( f0_local2 )
		f2_arg0.AvailableCreditCount:setAlpha( 0 )
		f2_arg0.CreditsAvailableIn:setAlpha( 1 )
	else
		f2_arg0.AvailableCreditCount:setAlpha( 1 )
		f2_arg0.CreditsAvailableIn:setAlpha( 0 )
		if f2_arg0.Payroll:isInFocus() then
			f2_arg0.ButtonHelperBar:ShowButtonsWithTag( f0_local2 )
		end
	end
	f2_arg0.CollectCreditsCountdown:setAlpha( f2_arg2 )
	if Rank.IsMasterPrestigeXP( f2_arg1, CoD.PlayMode.Core ) or Rank.IsMasterPrestigeXP( f2_arg1, CoD.PlayMode.Zombies ) then
		f2_arg0.PayrollTitle:setText( Engine.Localize( "LUA_MENU_MTX5_DAILY_LOGIN_MASTER_PRESTIGE_BONUS_CAPS" ) )
		f2_arg0.PayrollTitle:setFontSize( 27, 0 )
		f2_arg0.PayrollDesc:setText( Engine.Localize( "LUA_MENU_MTX5_DAILY_LOGIN_MASTER_PRESTIGE_DESCRIPTION" ) )
	else
		f2_arg0.PayrollTitle:setText( Engine.Localize( "HUB_DAILY_LOGIN_BONUS_CAPS" ) )
		f2_arg0.PayrollTitle:setFontSize( 30, 0 )
		f2_arg0.PayrollDesc:setText( Engine.Localize( "HUB_DAILY_LOGIN_DESCRIPTION" ) )
	end
end

local f0_local6 = function ( f3_arg0, f3_arg1, f3_arg2 )
	local f3_local0 = LUI.FlowManager.GetScopedData( f3_arg0 )
	if f3_arg2 then
		f3_local0.mailOfficer.secondsUntilNextPayroll = f0_local1
		f3_local0.mailOfficer.canCollectPayroll = false
	else
		local f3_local1 = Engine.AE_GetPlayerAchievementInfo( f3_arg1, Rank.GetPayrollAchievement( f3_arg1 ) )
		local f3_local2 = tonumber( f3_local1.timeSinceLastCompletion )
		if f3_local2 == nil or f3_local2 < 0 then
			f3_local2 = 0
		end
		if f0_local1 <= f3_local2 or f3_local1.fullfilledTimes <= 0 then
			f3_local0.mailOfficer.secondsUntilNextPayroll = 0
			f3_local0.mailOfficer.canCollectPayroll = true
		else
			f3_local0.mailOfficer.secondsUntilNextPayroll = f0_local1 - f3_local2
			f3_local0.mailOfficer.canCollectPayroll = false
		end
		if f3_local1.reward and f3_local1.reward.currencyAmount and f3_local1.reward.currencyAmount > 0 then
			f3_arg0.AvailableCreditCount:setText( f3_local1.reward.currencyAmount )
		elseif Rank.IsMasterPrestigeXP( f3_arg1, CoD.PlayMode.Core ) or Rank.IsMasterPrestigeXP( f3_arg1, CoD.PlayMode.Zombies ) then
			f3_arg0.AvailableCreditCount:setText( "300" )
		else
			f3_arg0.AvailableCreditCount:setText( "200" )
		end
	end
	f0_local4( f3_arg0, f3_arg1 )
	f0_local5( f3_arg0, f3_arg1, not f3_local0.mailOfficer.canCollectPayroll )
end

local f0_local7 = function ( f4_arg0, f4_arg1 )
	f4_arg0:dispatchEventToRoot( {
		name = "player_interact_notification_cancel"
	} )
	if f4_arg1.eventType == AEEventType.CompletionUpdate and f4_arg1.kind == GameChallengeType.GameAchievementKind_AlwaysOn and f4_arg1.ID == Rank.GetPayrollAchievement( f4_arg1.controller ) then
		if f4_arg1.success == true then
			f0_local6( f4_arg0, f4_arg1.controller, f4_arg1.success )
			f4_arg0:dispatchEventToRoot( {
				name = "update_vendor_notifications",
				data = {
					"mail_officer_menu"
				}
			} )
		else
			
		end
		ACTIONS.AnimateSequence( f4_arg0.Payroll, "NotLoading" )
		ACTIONS.Show( f4_arg0.ButtonHelperBar )
		ACTIONS.SetInputEnabled( f4_arg0, true )
	end
end

local f0_local8 = function ( f5_arg0 )
	if f5_arg0 then
		ACTIONS.AnimateSequence( f5_arg0.Payroll, "NotLoading" )
	end
end

local f0_local9 = function ( f6_arg0, f6_arg1, f6_arg2 )
	local f6_local0 = LUI.FlowManager.GetScopedData( f6_arg0 )
	assert( f6_local0.mailOfficer.canCollectPayroll )
	f6_arg0:registerEventHandler( "achievementEngine", function ( element, event )
		event.controller = f6_arg1
		f0_local7( element, event )
	end )
	local f6_local1
	if Rank.IsMasterPrestigeXP( f6_arg1, CoD.PlayMode.Core ) or Rank.IsMasterPrestigeXP( f6_arg1, CoD.PlayMode.Zombies ) then
		f6_local1 = 1
		if not f6_local1 then
		
		else
			if AchievementEngineUtils.AE_SendComplexGameEvent( f6_arg1, AEComplexEvents.GrabPayroll, {
				1,
				f6_local1
			} ) then
				ACTIONS.SetInputEnabled( f6_arg0, false )
				ACTIONS.Hide( f6_arg0.ButtonHelperBar )
				ACTIONS.AnimateSequence( f6_arg0.Payroll, "Loading" )
				f6_arg0:dispatchEventToRoot( {
					name = "player_interact_notification",
					data = {
						36,
						""
					},
					menu = f6_arg0,
					delayShow = 5000,
					callback = f0_local8
				} )
			else
				f6_arg0:dispatchEventToRoot( {
					name = "player_interact_notification",
					data = {
						36,
						""
					}
				} )
			end
		end
	end
	f6_local1 = 0
end

local f0_local10 = function ( f8_arg0, f8_arg1 )
	local f8_local0 = f8_arg0.Messages._targetPosition
	if f8_local0 then
		local f8_local1 = LUI.FlowManager.GetScopedData( f8_arg0 )
		local f8_local2 = f8_local1.mailOfficer.messages[f8_local0.x + f8_local0.y * f8_arg0.Messages:GetMaxVisibleColumns() + 1]
		if f8_local2 and f8_local2.guid ~= f0_local3 and Engine.Inventory_RedeemVoucherItem( f8_arg1, f8_local2.guid ) then
			if f8_local2.guid == "0x800070" or f8_local2.guid == "0x8000b1" then
				f8_local1.mailOfficer.redeemingMPUpgradeVoucher = true
			end
			LUI.FlowManager.RequestAddMenu( f8_arg0, "popup_claimingvoucher", true, f8_arg1, false )
		elseif f8_local2 and f8_local2.guid == f0_local3 then
			Engine.Exec( "showPreOrder" )
		end
	end
end

local f0_local11 = function ( f9_arg0, f9_arg1 )
	local f9_local0 = LUI.FlowManager.GetScopedData( f9_arg0 )
	f9_arg0.ButtonHelperBar:ShowButtonsWithTag( f0_local2 )
	f9_arg0.ButtonHelperBar:SetButtonText( LuaButton.primary, "HUB_MAIL_COLLECT_CREDITS" )
	f9_arg0.ButtonHelperBar:SetButtonDisabled( LuaButton.primary, not f9_local0.mailOfficer.canCollectPayroll )
	if f9_local0.mailOfficer.canCollectPayroll then
		f9_arg0.ButtonHelperBar:SetButtonCallback( LuaButton.primary, f0_local9 )
		ACTIONS.AnimateSequence( f9_arg0.Payroll, "NewMail" )
	end
	f0_local5( f9_arg0, f9_arg1, not f9_local0.mailOfficer.canCollectPayroll )
end

local f0_local12 = function ( f10_arg0 )
	if f10_arg0.desc == "LOOT_MTX5_VOUCHER_DESC_PRO_RANKED_HELMET" then
		local f10_local0 = RankedPlay.GetRewardSeasonFromGUID( f10_arg0.guid )
		if f10_local0 ~= -1 then
			return Engine.Localize( f10_arg0.desc, f10_local0 )
		end
	end
	return Engine.Localize( f10_arg0.desc )
end

local f0_local13 = function ( f11_arg0, f11_arg1, f11_arg2 )
	local f11_local0 = f11_arg0:getParent()
	local f11_local1 = LUI.FlowManager.GetScopedData( f11_local0 )
	local f11_local2 = f11_local1.mailOfficer.messages[f11_arg1 + f11_arg2 * f11_arg0:GetMaxVisibleColumns() + 1]
	if not f11_local2 then
		return 
	else
		f11_local0.ContentImage:setImage( RegisterMaterial( MODIFIERS.CacheIconMaterial( f11_local2.image or "" ) ) )
		f11_local0.ContentImage:setAlpha( 1 )
		f11_local0.ContentTitle:setText( Engine.Localize( f11_local2.name ) )
		f11_local0.ContentText:setText( f0_local12( f11_local2 ) )
		f11_local0.ButtonHelperBar:ShowButtonsWithTag( f0_local2 )
		local f11_local3 = f11_local0.ButtonHelperBar
		local f11_local4 = f11_local3
		f11_local3 = f11_local3.SetButtonText
		local f11_local5 = LuaButton.primary
		local f11_local6 = f11_local2.guid
		local f11_local7 = f0_local3
		f11_local3( f11_local4, f11_local5, REG12 and "HUB_MAIL_COLLECT_ITEM" or "LUA_MENU_DOWNLOAD" )
		f11_local0.ButtonHelperBar:SetButtonDisabled( LuaButton.primary, false )
		f11_local0.ButtonHelperBar:SetButtonCallback( LuaButton.primary, f0_local10 )
	end
end

local f0_local14 = function ( f12_arg0, f12_arg1, f12_arg2 )
	local f12_local0 = f12_arg0:getParent()
	local f12_local1 = LUI.FlowManager.GetScopedData( f12_local0 )
	local f12_local2 = f12_local1.mailOfficer.messages[f12_arg1 + f12_arg2 * f12_local0:GetMaxVisibleColumns() + 1]
	if f12_local2 then
		f12_arg0.Icon:setImage( RegisterMaterial( MODIFIERS.CacheIconMaterial( f12_local2.image or "" ) ) )
		if f12_local2.itemQuantity > 1 then
			f12_arg0.Quantity:setText( Engine.Localize( "LUA_MP_FRONTEND_TIMES", f12_local2.itemQuantity ) )
			f12_arg0.Quantity:setAlpha( 1 )
			local f12_local3, f12_local4 = f12_arg0.Quantity:getElementTextDims( true )
			f12_arg0.QuantityBG:setWidth( f12_local3 * _1080p + 20 * _1080p )
			f12_arg0.QuantityBG:setAlpha( 0.8 )
		else
			f12_arg0.Quantity:setAlpha( 0 )
			f12_arg0.QuantityBG:setAlpha( 0 )
		end
		f12_arg0.m_ignoreMouseFocus = false
		f12_arg0.m_inputDisabled = false
	else
		ACTIONS.AnimateSequence( f12_arg0, "ButtonEmpty" )
		f12_arg0.Quantity:setAlpha( 0 )
		f12_arg0.QuantityBG:setAlpha( 0 )
		f12_arg0.m_ignoreMouseFocus = true
		f12_arg0.m_inputDisabled = true
	end
	f12_arg0:registerEventHandler( "gain_focus", function ( element, event )
		f0_local13( f12_local0, f12_arg1, f12_arg2 )
		LUI.UIButton.gainFocus( element, event )
	end )
end

local f0_local15 = function ( f14_arg0, f14_arg1, f14_arg2 )
	local f14_local0 = LUI.FlowManager.GetScopedData( f14_arg0 )
	return f14_local0.mailOfficer.messages[f14_arg1 + f14_arg2 * f14_arg0:GetMaxVisibleColumns() + 1] ~= nil
end

local f0_local16 = function ( f15_arg0, f15_arg1, f15_arg2 )
	local f15_local0 = LUI.FlowManager.GetScopedData( f15_arg0 )
	if CONDITIONS.IsInHubTutorial( f15_arg1 ) then
		return f15_arg0.Payroll, "HUB_MAIL_COLLECT_CREDITS", f0_local9, not f15_local0.mailOfficer.canCollectPayroll, true, true
	elseif f15_local0.mailOfficer.canCollectPayroll then
		return f15_arg0.Payroll, "HUB_MAIL_COLLECT_CREDITS", f0_local9, false, true, true
	elseif #f15_local0.mailOfficer.messages > 0 then
		return f15_arg0.Messages, "HUB_MAIL_COLLECT_ITEM", f0_local10, true, true, true
	else
		return f15_arg0.Payroll, "HUB_MAIL_COLLECT_CREDITS", f0_local9, not f15_local0.mailOfficer.canCollectPayroll, true, true
	end
end

local f0_local17 = function ( f16_arg0, f16_arg1 )
	f16_arg0.firstFocusableChild = f0_local16( f16_arg0, f16_arg1, LUI.FlowManager.GetScopedData( f16_arg0 ) )
end

local f0_local18 = function ( f17_arg0, f17_arg1, f17_arg2 )
	if #f17_arg2.mailOfficer.messages == 0 then
		return false
	else
		return LUI.UIElement.canFocus( f17_arg0, f17_arg1 )
	end
end

local f0_local19 = function ( f18_arg0 )
	local f18_local0 = LUI.FlowManager.GetScopedData( f18_arg0 )
	local f18_local1 = Engine.Inventory_GetVoucherItems( f18_local0.mailOfficer.controllerIndex )
	f18_local0.mailOfficer.messages = {}
	if f18_local1 ~= nil then
		for f18_local2 = 1, #f18_local1, 1 do
			local f18_local5 = InventoryUtils.GetLootData( f18_local1[f18_local2].itemID )
			if f18_local5 then
				table.insert( f18_local0.mailOfficer.messages, f18_local5 )
			end
		end
	end
	if Store.ShouldShowPreOrder( f18_local0.mailOfficer.controllerIndex ) then
		local f18_local2 = InventoryUtils.GetLootData( f0_local3 )
		if f18_local2 then
			f18_local2.itemQuantity = 1
			table.insert( f18_local0.mailOfficer.messages, f18_local2 )
		end
	end
end

return {
	PreLoadFunc = function ( f19_arg0, f19_arg1, f19_arg2 )
		local f19_local0 = LUI.FlowManager.GetScopedData( f19_arg0 )
		f19_local0.mailOfficer = {
			controllerIndex = f19_arg1,
			messages = {},
			secondsUntilNextPayroll = 0,
			canCollectPayroll = false,
			redeemingMPUpgradeVoucher = false
		}
		DataSources.inFrontend.MP.CharacterTitleBar.characterTitle:SetValue( f19_arg1, Engine.Localize( "HUB_MENU_MAIL" ) )
		DataSources.inFrontend.MP.CharacterTitleBar.characterDescription:SetValue( f19_arg1, Engine.Localize( "HUB_MAIL_MENU_DESC" ) )
		f0_local19( f19_arg0 )
	end
	,
	PostLoadFunc = function ( f20_arg0, f20_arg1, f20_arg2 )
		MODIFIERS.CacheIconMaterial( "ui_vendor_mail_bg" )
		f20_arg0.BackgroundOverlay:setupFullWindowElement()
		PersistentForeground.MenuTransitionFade()
		local f20_local0 = LUI.FlowManager.GetScopedData( f20_arg0 )
		f20_arg0.CollectCreditsCountdown.menu = f20_arg0
		f20_arg0.CollectCreditsCountdown:registerEventHandler( "timeout", function ( element, event )
			f0_local6( element.menu, f20_arg1 )
			if element.menu.Payroll:isInFocus() then
				element.menu.ButtonHelperBar:SetButtonText( LuaButton.primary, "HUB_MAIL_COLLECT_CREDITS" )
				element.menu.ButtonHelperBar:SetButtonDisabled( LuaButton.primary, false )
				element.menu.ButtonHelperBar:SetButtonCallback( LuaButton.primary, f0_local9 )
			end
		end )
		f0_local6( f20_arg0, f20_arg1 )
		local f20_local1, f20_local2, f20_local3, f20_local4, f20_local5, f20_local6 = f0_local16( f20_arg0, f20_arg1, f20_local0 )
		local f20_local7 = f20_arg0.ButtonHelperBar:BeginSet()
		f20_local7 = f20_local7:AddBackButton( LUI.ButtonHelperBarBuilder.BackButtonTypes.HubVendor )
		f20_local7 = f20_local7:AddLeft( LuaButton.primary, f20_local2, f20_local3, 0, not f20_local4 )
		f20_local7 = f20_local7:TagButton( LuaButton.primary, f0_local2 )
		if not f20_local6 then
			f20_local7:HideTag( f0_local2 )
		end
		f20_local7:Finish()
		f20_arg0.ButtonHelperBar.dontCloseMenusOnStartPress = true
		if not Engine.IsConsoleGame() then
			ButtonHelperBarUtils.BindElementToButton( f20_arg0.Payroll, LuaButton.primary, f20_arg1 )
		end
		local f20_local8 = f20_arg0.Messages:GetMaxVisibleColumns() * f20_arg0.Messages:GetMaxVisibleRows()
		f20_arg0.Messages:SetNumChildren( math.max( #f20_local0.mailOfficer.messages, f20_local8 ) )
		f20_arg0.Messages:SetScrollbar( f20_arg0.MessagesScrollbar )
		f20_arg0.Messages.canFocus = function ( f22_arg0, f22_arg1 )
			return f0_local18( f22_arg0, f22_arg1, f20_local0 )
		end
		
		f20_arg0:registerEventHandler( "messages_grid_clicked", function ( element, event )
			f0_local10( element, f20_arg1 )
		end )
		if #f20_local0.mailOfficer.messages == 0 then
			ACTIONS.AnimateSequence( f20_arg0, "NoMail" )
			f20_arg0.ContentTitle:setText( Engine.Localize( "HUB_MAIL_EMPTY_TITLE" ) )
			f20_arg0.ContentText:setText( Engine.Localize( "HUB_MAIL_EMPTY_DESC" ) )
		end
		f20_arg0:registerEventHandler( "inventory", function ( element, event )
			if event.inventoryEventType == InventoryEventType.TaskCompleted then
				if event.inventoryTaskType == InventoryTaskType.ApplyConversionRule then
					local f24_local0 = LUI.FlowManager.GetScopedData( element )
					if event.success == true then
						if f24_local0.mailOfficer.redeemingMPUpgradeVoucher then
							PrestigeUtils.GivePrestigeToken( f20_arg1 )
						end
						f0_local19( element )
						element.Messages:SetNumChildren( math.max( #f24_local0.mailOfficer.messages, f20_local8 ) )
						element.Messages:RefreshContent()
						element:dispatchEventToRoot( {
							name = "update_vendor_notifications",
							data = {
								"mail_officer_menu"
							}
						} )
						Engine.PlaySound( CoD.SFX.CollectionPurchase )
						if #f24_local0.mailOfficer.messages > 0 then
							element.Messages:processEvent( {
								name = "gain_focus"
							} )
							ACTIONS.AnimateSequence( element, "DefaultSequence" )
						else
							element.Messages:SetLastFocusIndex( nil )
							element.Payroll:processEvent( {
								name = "gain_focus"
							} )
							ACTIONS.AnimateSequence( element, "NoMail" )
							element.ContentTitle:setText( Engine.Localize( "HUB_MAIL_EMPTY_TITLE" ) )
							element.ContentText:setText( Engine.Localize( "HUB_MAIL_EMPTY_DESC" ) )
						end
					end
					f24_local0.mailOfficer.redeemingMPUpgradeVoucher = false
					LUI.FlowManager.RequestLeaveMenuByName( "popup_claimingvoucher" )
				end
			elseif event.inventoryEventType == InventoryEventType.InventoryModified and InventoryUtils.IsValidGuid( event.itemGUID ) then
				InventoryUtils.SetItemBreadCrumbState( f20_arg1, event.itemGUID, true )
			end
		end )
		f20_arg0.Payroll.navigation = {
			right = f20_arg0.Messages
		}
		f20_arg0.Messages.navigation = {
			left = f20_arg0.Payroll
		}
		if CONDITIONS.IsInHubTutorial( f20_arg1 ) then
			ACTIONS.AnimateSequence( f20_arg0.Payroll, "NewMail" )
			f20_arg0.FTE_Image_Overlay:setAlpha( 0.75 )
			f20_arg0.Payroll.navigation = {}
		else
			f20_arg0.FTE_Image_Overlay:setAlpha( 0 )
		end
		if (Engine.GetPlayerData( f20_arg1, CoD.StatsGroup.Ranked, "hubStats", "menuTutorialComplete_mail" ) == false or Engine.GetDvarBool( "hub_forceMenuTutorials" )) and not Engine.GetDvarBool( "hub_preventMenuTutorials" ) then
			LUI.FlowManager.RequestAddMenu( nil, "menu_tutorial_modal_container", true, f20_arg1, false, {
				tutorialId = 51
			} )
			Engine.SetPlayerData( f20_arg1, CoD.StatsGroup.Ranked, "hubStats", "menuTutorialComplete_mail", true )
			ACTIONS.UploadStats()
		end
		PersistentForeground.UpdateCurrencyVisibility( "all", f20_arg1 )
	end
	,
	PopFunc = function ( f25_arg0 )
		ACTIONS.HubCharacterExitMenu()
	end
	,
	ACTION_OnLoginBonusFocused = f0_local11,
	FUNCTOR_GridRefreshChild = f0_local14,
	FUNCTOR_IsPositionFocusable = f0_local15,
	ACTION_SetInitiallyFocusedItem = f0_local17
}
