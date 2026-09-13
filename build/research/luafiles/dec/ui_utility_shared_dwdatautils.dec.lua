DwDataUtils = DwDataUtils or {}
DwDataUtils.Vendor = {
	Operation = 1,
	Quartermaster = 2
}
DwDataUtils.FetchVendorData = {
	function ( f1_arg0, f1_arg1 )
		DwDataUtils._fetchChallengeData( f1_arg0, f1_arg1 )
	end,
	function ( f2_arg0 )
		DwDataUtils._fetchSKUData( f2_arg0 )
	end
}
DwDataUtils.UpdateData = {
	function ( f3_arg0, f3_arg1 )
		return DwDataUtils._updateChallengeData( f3_arg0, f3_arg1 )
	end,
	function ( f4_arg0 )
		return DwDataUtils._updateSKUData( f4_arg0 )
	end
}
DwDataUtils.GetCachedData = {
	function ( f5_arg0, f5_arg1 )
		return DwDataUtils._getCachedChallengeData( f5_arg0, f5_arg1 )
	end,
	function ( f6_arg0 )
		return DwDataUtils._getCachedSKUData( f6_arg0 )
	end
}
PlayerCommend_TaskType = {
	GetStatus = 19
}
PlayerVoteStatus = {
	Unfetched = 0,
	AlreadyVoted = 1,
	CanVote = 2
}
DailyRewardConversionTable = {
	[5] = {
		conversion = "Hack_Conversion_day1",
		newType = 72
	},
	[6] = {
		conversion = "Hack_Conversion_day2",
		newType = 73
	},
	[7] = {
		conversion = "Hack_Conversion_day3",
		newType = 74
	},
	[8] = {
		conversion = "Hack_Conversion_day4",
		newType = 75
	},
	[9] = {
		conversion = "Hack_Conversion_day5",
		newType = 76
	}
}
DwDataUtils.PlayerCachedData = {}
for f0_local0 = 0, Engine.GetMaxControllerCount() - 1, 1 do
	DwDataUtils.PlayerCachedData[f0_local0] = {}
	DwDataUtils.PlayerCachedData[f0_local0].CanCommendPlayer = false
	DwDataUtils.PlayerCachedData[f0_local0].HasRedeemableChallenges = false
	DwDataUtils.PlayerCachedData[f0_local0].DailyRewardTransactionID = ""
	DwDataUtils.PlayerCachedData[f0_local0].DailyRewardConversion = {
		TransactionID = "",
		OriginalType = -1
	}
	DwDataUtils.PlayerCachedData[f0_local0].PlayerAchievementsFetched = false
end
DwDataUtils.AllChallengeDataFetchCallTracker = {
	None = -1,
	Start = 0,
	Done = 2
}
DwDataUtils.AllSKUDataFetchCallTracker = {
	None = -1,
	Start = 0,
	Done = 2
}
DwDataUtils.ChallengeType = {
	AEC_DAILY = "Daily Orders",
	AEC_WEEKLY = "Weekly Orders",
	AEC_SPECIAL = "Special Orders",
	AEC_FTE = "Tutorial Orders"
}
DwDataUtils._fetchChallengeData = function ( f7_arg0, f7_arg1 )
	if f7_arg1 == GameChallengeGroup.Scheduled then
		Engine.AE_FetchScheduledChallenges( f7_arg0 )
	elseif f7_arg1 == GameChallengeGroup.PlayerActive then
		Engine.AE_FetchPlayerActiveChallenges( f7_arg0 )
	else
		assert( "Wrong challenge group type!" )
	end
end

DwDataUtils._fetchSKUData = function ( f8_arg0 )
	Engine.Inventory_FetchAllSKUs( f8_arg0, SKUType.Quartermaster )
	DataSources.inGame.HUD.DwDataUtils.skuDataFetchTracker:SetValue( f8_arg0, DwDataUtils.AllSKUDataFetchCallTracker.Start )
end

local f0_local0 = function ( f9_arg0, f9_arg1 )
	assert( f9_arg0 ~= nil )
	assert( f9_arg1 ~= nil )
	local f9_local0 = 1
	if f9_arg0.target ~= f9_arg1.target then
		f9_local0 = 0
	end
	if f9_arg0.status ~= f9_arg1.status then
		f9_local0 = 0
	end
	if f9_arg0.ID ~= f9_arg1.ID then
		f9_local0 = 0
	end
	if f9_arg0.kind ~= f9_arg1.kind then
		f9_local0 = 0
	end
	if f9_arg0.reward ~= f9_arg1.reward then
		f9_local0 = 0
	end
	return f9_local0
end

local f0_local1 = function ( f10_arg0 )
	for f10_local0 = 1, #GameChallengeList[f10_arg0]._cachedPlayerActiveChallenges, 1 do
		if GameChallengeList[f10_arg0]._cachedPlayerActiveChallenges[f10_local0] and GameChallengeList[f10_arg0]._cachedPlayerActiveChallenges[f10_local0].status == GameChallengeStatus.GameChallengeStatus_Claimable then
			DwDataUtils.PlayerCachedData[f10_arg0].HasRedeemableChallenges = true
			return 
		end
	end
end

DwDataUtils.UpdateExpiredChallengeData = function ( f11_arg0 )
	GameChallengeList[f11_arg0]._cachedExpiredChallengesID = Engine.AE_GetRecentlyExpiredAchievements( f11_arg0 )
	return GameChallengeList[f11_arg0]._cachedExpiredChallengesID
end

DwDataUtils.IsContractExpired = function ( f12_arg0, f12_arg1 )
	if f12_arg1 == nil then
		return false
	end
	GameChallengeList[f12_arg0]._cachedExpiredChallengesID = Engine.AE_GetRecentlyExpiredAchievements( f12_arg0 )
	for f12_local0 = 1, #GameChallengeList[f12_arg0]._cachedExpiredChallengesID, 1 do
		if f12_arg1 == GameChallengeList[f12_arg0]._cachedExpiredChallengesID[f12_local0] then
			return true
		end
	end
	return false
end

DwDataUtils.GetExpiredContractNum = function ( f13_arg0 )
	GameChallengeList[f13_arg0]._cachedExpiredChallengesID = Engine.AE_GetRecentlyExpiredAchievements( f13_arg0 )
	local f13_local0 = 0
	for f13_local1 = 1, #GameChallengeList[f13_arg0]._cachedExpiredChallengesID, 1 do
		if AchievementEngineUtils.GetTypeByID( GameChallengeList[f13_arg0]._cachedExpiredChallengesID[f13_local1] ) == AEPeriodicType.Contract then
			f13_local0 = f13_local0 + 1
		end
	end
	return f13_local0
end

DwDataUtils.IsSpecialZombieChallenge = function ( f14_arg0 )
	local f14_local0
	if f14_arg0 ~= 768 and f14_arg0 ~= 769 and f14_arg0 ~= 770 and f14_arg0 ~= 771 then
		f14_local0 = false
	else
		f14_local0 = true
	end
	return f14_local0
end

DwDataUtils.IsAnyActiveSpecialZombieChallenge = function ( f15_arg0 )
	for f15_local0 = 1, #GameChallengeList[f15_arg0]._cachedPlayerActiveChallenges, 1 do
		local f15_local3 = GameChallengeList[f15_arg0]._cachedPlayerActiveChallenges[f15_local0]
		if f15_local3 and DwDataUtils.IsSpecialZombieChallenge( f15_local3.ID ) then
			return true
		end
	end
	return false
end

DwDataUtils._updateChallengeDataByType = function ( f16_arg0, f16_arg1 )
	if f16_arg1 == GameChallengeGroup.Scheduled then
		GameChallengeList[f16_arg0]._cachedScheduledChallenges = Engine.AE_GetScheduledChallenges( f16_arg0 )
		return GameChallengeList[f16_arg0]._cachedScheduledChallenges
	elseif f16_arg1 == GameChallengeGroup.PlayerActive then
		GameChallengeList[f16_arg0]._cachedPlayerActiveChallenges = Engine.AE_GetPlayerActiveChallenges( f16_arg0, GameChallengeType.GameAchievementKind_ALL )
		if CONDITIONS.IsZombiesMode() then
			local f16_local0 = Engine.AE_GetPlayerActiveChallenges( f16_arg0, GameChallengeType.GameAchievementKind_ALL, GameChallengeType.GAME_ACHIEVEMENT_KINDS_ALL_MP_ORDERS )
			for f16_local1 = 1, #f16_local0, 1 do
				if DwDataUtils.IsSpecialZombieChallenge( f16_local0[f16_local1].ID ) then
					table.insert( GameChallengeList[f16_arg0]._cachedPlayerActiveChallenges, f16_local0[f16_local1] )
				end
			end
		end
		f0_local1( f16_arg0 )
		return GameChallengeList[f16_arg0]._cachedPlayerActiveChallenges
	else
		assert( "Wrong challenge group type!" )
		return nil
	end
end

DwDataUtils._updateChallengeData = function ( f17_arg0, f17_arg1, f17_arg2 )
	if f17_arg1 == GameChallengeGroup.All then
		return DwDataUtils._updateChallengeDataByType( f17_arg0, GameChallengeGroup.Scheduled ), DwDataUtils._updateChallengeDataByType( f17_arg0, GameChallengeGroup.PlayerActive )
	else
		return DwDataUtils._updateChallengeDataByType( f17_arg0, f17_arg1 )
	end
end

DwDataUtils._updateSKUData = function ( f18_arg0 )
	GameSKUList._cachedSKUs = Engine.Inventory_GetAllSKUIDs( SKUType.Quartermaster )
	return GameSKUList._cachedSKUs
end

DwDataUtils._getCachedChallengeData = function ( f19_arg0, f19_arg1 )
	if f19_arg1 == GameChallengeGroup.Scheduled then
		return GameChallengeList[f19_arg0]._cachedScheduledChallenges
	elseif f19_arg1 == GameChallengeGroup.PlayerActive then
		return GameChallengeList[f19_arg0]._cachedPlayerActiveChallenges
	else
		assert( "Wrong challenge group type!" )
		return nil
	end
end

DwDataUtils._getCachedSKUData = function ( f20_arg0 )
	return GameSKUList._cachedSKUs
end

DwDataUtils.IsPlayerActiveChallenge = function ( f21_arg0, f21_arg1 )
	if f21_arg1 == nil then
		return false
	end
	for f21_local0 = 1, #GameChallengeList[f21_arg0]._cachedPlayerActiveChallenges, 1 do
		if GameChallengeList[f21_arg0]._cachedPlayerActiveChallenges[f21_local0].ID == f21_arg1 then
			return true
		end
	end
	return false
end

DwDataUtils.GetPlayerActiveChallenge = function ( f22_arg0, f22_arg1 )
	if f22_arg1 == nil then
		return nil
	end
	for f22_local0 = 1, #GameChallengeList[f22_arg0]._cachedPlayerActiveChallenges, 1 do
		if GameChallengeList[f22_arg0]._cachedPlayerActiveChallenges[f22_local0].ID == f22_arg1 then
			return GameChallengeList[f22_arg0]._cachedPlayerActiveChallenges[f22_local0]
		end
	end
	return nil
end

DwDataUtils.GetScheduledChallenge = function ( f23_arg0, f23_arg1 )
	if f23_arg1 == nil then
		return nil
	end
	for f23_local0 = 1, #GameChallengeList[f23_arg0]._cachedScheduledChallenges, 1 do
		if GameChallengeList[f23_arg0]._cachedScheduledChallenges[f23_local0].ID == f23_arg1 then
			return GameChallengeList[f23_arg0]._cachedScheduledChallenges[f23_local0]
		end
	end
	return nil
end

DwDataUtils.GetPlayerExpiredChallenge = function ( f24_arg0, f24_arg1 )
	if f24_arg1 == nil then
		return nil
	end
	GameChallengeList[f24_arg0]._cachedExpiredChallengesID = Engine.AE_GetRecentlyExpiredAchievements( f24_arg0 )
	for f24_local0 = 1, #GameChallengeList[f24_arg0]._cachedExpiredChallengesID, 1 do
		if GameChallengeList[f24_arg0]._cachedExpiredChallengesID[f24_local0] == f24_arg1 then
			return DwDataUtils.GetScheduledChallenge( f24_arg0, f24_arg1 )
		end
	end
	return nil
end

DwDataUtils.UpdateCachedScheduledChallengeData = function ( f25_arg0, f25_arg1, f25_arg2 )
	for f25_local0 = 1, #GameChallengeList[f25_arg0]._cachedScheduledChallenges, 1 do
		if GameChallengeList[f25_arg0]._cachedScheduledChallenges[f25_local0].ID == f25_arg2 then
			GameChallengeList[f25_arg0]._cachedScheduledChallenges[f25_local0] = f25_arg1
			return true
		end
	end
	return false
end

DwDataUtils.Init = function ( f26_arg0 )
	local f26_local0 = Engine.GetLuiRoot()
	local f26_local1 = "DwUtilsListener"
	local self = nil
	if f26_local0.childRecord[f26_local1] then
		self = f26_local0.childRecord[f26_local1]
	else
		self = LUI.UIElement.new()
		self.id = f26_local1
		f26_local0:addElement( self )
	end
	self:registerEventHandler( "achievementEngine", function ( element, event )
		if event.eventType == AEEventType.PlayerAchievementsFetched then
			if event.success == true then
				DwDataUtils.PlayerCachedData[f26_arg0].PlayerAchievementsFetched = true
				DwDataUtils._updateChallengeDataByType( f26_arg0, GameChallengeGroup.PlayerActive )
				f26_local0:dispatchEventToRoot( {
					name = "update_vendor_notifications",
					data = {
						"mail_officer_menu"
					}
				} )
			end
		elseif event.eventType == AEEventType.ScheduledAchievementsFetched then
			if event.success == true then
				DwDataUtils._updateChallengeDataByType( f26_arg0, GameChallengeGroup.Scheduled )
			end
		elseif event.eventType == AEEventType.CompletionUpdate and event.kind == GameChallengeType.GameAchievementKind_AlwaysOn and AchievementEngineUtils.IsDailyLogin( event.ID ) and event.itemsReceived[1] then
			local f27_local0 = tonumber( event.itemsReceived[1].guid )
			if f27_local0 then
				local f27_local1 = tonumber( Engine.TableLookup( SupplyDropTypesTable.File, SupplyDropTypesTable.Cols.ItemID, tostring( f27_local0 ), SupplyDropTypesTable.Cols.Type ) )
				if f27_local1 then
					if CONDITIONS.ShouldPlayerGetAltLoginReward( f26_arg0 ) and DailyRewardConversionTable[f27_local1] then
						local f27_local2 = nil
						DwDataUtils.PlayerCachedData[f26_arg0].DailyRewardConversion.OriginalType = f27_local1
						local f27_local3 = DwDataUtils.PlayerCachedData[f26_arg0].DailyRewardConversion
						f27_local2, f27_local3.TransactionID = Engine.Inventory_ApplyConversionRule( f26_arg0, DailyRewardConversionTable[f27_local1].conversion )
					else
						DwDataUtils.PlayerCachedData[f26_arg0].DailyRewardTransactionID = Engine.Loot_OpenSupplyPackage( f26_arg0, f27_local1 )
					end
				end
			end
		end
	end )
	self:registerEventHandler( "inventory", function ( element, event )
		if event.inventoryEventType == InventoryEventType.TaskCompleted then
			if event.inventoryTaskType == InventoryTaskType.GetSKUS then
				if event.success == true then
					DwDataUtils._updateSKUData( f26_arg0 )
					DataSources.inGame.HUD.DwDataUtils.skuDataFetchTracker:SetValue( f26_arg0, DwDataUtils.AllSKUDataFetchCallTracker.Done )
				else
					DwDataUtils._fetchSKUData( f26_arg0 )
				end
			elseif event.inventoryTaskType == InventoryTaskType.ApplyConversionRule and event.trID == DwDataUtils.PlayerCachedData[f26_arg0].DailyRewardConversion.TransactionID then
				local f28_local0 = DwDataUtils.PlayerCachedData[f26_arg0].DailyRewardConversion.OriginalType
				if f28_local0 <= 0 then
					return 
				end
				local f28_local1 = DailyRewardConversionTable[f28_local0].newType
				if event.success then
					DwDataUtils.PlayerCachedData[f26_arg0].DailyRewardTransactionID = Engine.Loot_OpenSupplyPackage( f26_arg0, f28_local1 )
				else
					DwDataUtils.PlayerCachedData[f26_arg0].DailyRewardTransactionID = Engine.Loot_OpenSupplyPackage( f26_arg0, f28_local0 )
				end
				DwDataUtils.PlayerCachedData[f26_arg0].DailyRewardConversion.TransactionID = ""
				DwDataUtils.PlayerCachedData[f26_arg0].DailyRewardConversion.OriginalType = -1
			end
		end
	end )
	self:registerEventHandler( "OpenSupplyPackageSuccess", function ( element, event )
		if event.transactionID == DwDataUtils.PlayerCachedData[f26_arg0].DailyRewardTransactionID then
			local f29_local0, f29_local1 = Engine.Loot_GetSupplyPackageContent( f26_arg0, DwDataUtils.PlayerCachedData[f26_arg0].DailyRewardTransactionID )
			if f29_local1[1] then
				local f29_local2 = Engine.AE_GetPlayerAchievementInfo( f26_arg0, HardcodedAchievements.DailyLoginChain )
				PersistentForeground.ShowDailyLoginWidget( f29_local1[1].amount, f29_local2.progress or 1 )
				DwDataUtils.PlayerCachedData[f26_arg0].DailyRewardTransactionID = ""
			end
		else
			local f29_local0, f29_local1 = Engine.Loot_GetSupplyPackageContent( f26_arg0, event.transactionID )
			for f29_local2 = 1, #f29_local0, 1 do
				local f29_local5 = f29_local0[f29_local2].guid
				local f29_local6 = InventoryUtils.GetItemType( f29_local5 )
				if f29_local6 ~= ItemTypes.Consumable and f29_local6 ~= ItemTypes.ZombieConsumable and f29_local6 ~= ItemTypes.ArmoryCredits then
					if Engine.Inventory_GetItemQuantity( f26_arg0, f29_local5 ) == 1 then
						InventoryUtils.SetItemBreadCrumbState( f26_arg0, f29_local5, true, false )
						InventoryUtils.SetItemBreadCrumbState( f26_arg0, f29_local5, true, true )
					end
				end
				if f29_local6 == ItemTypes.ZombieConsumable then
					InventoryUtils.SetItemBreadCrumbState( f26_arg0, f29_local5, true, true )
				end
			end
		end
	end )
	DwDataUtils._fetchChallengeData( f26_arg0, GameChallengeGroup.PlayerActive )
	DwDataUtils._fetchChallengeData( f26_arg0, GameChallengeGroup.Scheduled )
	if Engine.IsHubMode() or CONDITIONS.IsZombiesMode() and not CONDITIONS.InGame() then
		if Engine.Inventory_AreSKUsFetched() then
			DwDataUtils._updateSKUData( f26_arg0 )
			DataSources.inGame.HUD.DwDataUtils.skuDataFetchTracker:SetValue( f26_arg0, DwDataUtils.AllSKUDataFetchCallTracker.Done )
		else
			DwDataUtils._fetchSKUData( f26_arg0 )
		end
	end
	if HashRangeUtils then
		HashRangeUtils.InitiatePlayerInAllActiveExperiments( f26_arg0 )
	end
end

