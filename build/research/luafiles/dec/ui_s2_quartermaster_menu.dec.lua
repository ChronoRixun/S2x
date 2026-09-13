local f0_local0 = require( "s2.quartermaster_menu_uc" )
local f0_local1, f0_local2, f0_local3, f0_local4, f0_local5, f0_local6, f0_local7, f0_local8 = nil
if f0_local0 ~= nil and type( f0_local0 ) == "table" then
	f0_local1 = f0_local0.PreLoadFunc
	f0_local2 = f0_local0.PostLoadFunc
	f0_local3 = f0_local0.PushFunc
	f0_local4 = f0_local0.PushOverFunc
	f0_local5 = f0_local0.ResumeFunc
	f0_local6 = f0_local0.PopFunc
	f0_local7 = f0_local0.ACTION_ChangeTab
	f0_local8 = f0_local0.CONDITION_HasExactNumSkus
end
LUI.MenuBuilder.registerType( "quartermaster_menu", function ( menu, controller )
	local self = LUI.UIGenericNavigator.new( {
		left = 0 * _1080p,
		right = 0 * _1080p,
		top = 0 * _1080p,
		bottom = 0 * _1080p,
		leftAnchor = true,
		rightAnchor = true,
		topAnchor = true,
		bottomAnchor = true
	} )
	self.id = "quartermaster_menu"
	local f1_local1 = controller or {}
	local f1_local2 = f1_local1.controllerIndex
	if not f1_local2 then
		if Engine.InFrontend() then
			local f1_local3 = LUI.FlowManager.GetScopedData( self )
			assert( f1_local3 )
			f1_local2 = f1_local3.exclusiveControllerIndex
		else
			f1_local2 = self:getRootController()
		end
	end
	if f0_local1 then
		f0_local1( self, f1_local2, f1_local1 )
	end
	self:playSound( "menu_open" )
	local f1_local3 = self
	local characterTitleBar = nil
	
	characterTitleBar = LUI.MenuBuilder.BuildRegisteredType( "character_title_bar", {
		controllerIndex = f1_local2,
		fontIconSet = f1_local1.fontIconSet
	} )
	characterTitleBar.id = "characterTitleBar"
	self:addElement( characterTitleBar )
	self.characterTitleBar = characterTitleBar
	
	characterTitleBar:setAnchors( 0, 1, 0, 1, 0 )
	characterTitleBar:setBottom( _1080p * 127, 0 )
	characterTitleBar:setLeft( _1080p * 0, 0 )
	characterTitleBar:setRight( _1080p * 128, 0 )
	characterTitleBar:setTop( _1080p * -1, 0 )
	if characterTitleBar.characterDescription then
		characterTitleBar.characterDescription:setRGBFromInt( SWATCHES.Button.MenuWhite, 0 )
	end
	local button_helper_bar = nil
	
	button_helper_bar = LUI.MenuBuilder.BuildRegisteredType( "button_helper_bar", {
		controllerIndex = f1_local2,
		fontIconSet = f1_local1.fontIconSet
	} )
	button_helper_bar.id = "button_helper_bar"
	self:addElement( button_helper_bar )
	self.button_helper_bar = button_helper_bar
	
	button_helper_bar:setAnchors( 0, 1, 1, 0, 0 )
	button_helper_bar:setBottom( _1080p * -55, 0 )
	button_helper_bar:setLeft( _1080p * 0, 0 )
	button_helper_bar:setRight( _1080p * 1920, 0 )
	button_helper_bar:setTop( _1080p * -105, 0 )
	local hub_menu_fade_image0 = nil
	
	hub_menu_fade_image0 = LUI.MenuBuilder.BuildRegisteredType( "hub_menu_fade_image", {
		controllerIndex = f1_local2,
		fontIconSet = f1_local1.fontIconSet
	} )
	hub_menu_fade_image0.id = "hub_menu_fade_image0"
	self:addElement( hub_menu_fade_image0 )
	self.hub_menu_fade_image0 = hub_menu_fade_image0
	
	hub_menu_fade_image0:setAnchors( 0, 1, 0, 1, 0 )
	hub_menu_fade_image0:setBottom( _1080p * 1082, 0 )
	hub_menu_fade_image0:setLeft( _1080p * 0, 0 )
	hub_menu_fade_image0:setRight( _1080p * 1920, 0 )
	hub_menu_fade_image0:setTop( _1080p * 2, 0 )
	local purchased_hint_label = nil
	
	purchased_hint_label = LUI.UIText.new()
	purchased_hint_label.id = "purchased_hint_label"
	self:addElement( purchased_hint_label )
	self.purchased_hint_label = purchased_hint_label
	
	if f1_local1.fontIconSet ~= nil then
		purchased_hint_label:setFontIconSet( f1_local1.fontIconSet )
	end
	purchased_hint_label:setAlpha( 0, 0 )
	purchased_hint_label:setAnchors( 0, 1, 0, 1, 0 )
	purchased_hint_label:setBottom( _1080p * 1046.81, 0 )
	purchased_hint_label:setFont( FONTS.BodyFont.Font )
	purchased_hint_label:setFontSize( 35, 0 )
	purchased_hint_label:setHorizontalAlignment( LUI.HorizontalAlignment.Left )
	purchased_hint_label:setLeft( _1080p * 803.75, 0 )
	purchased_hint_label:setRight( _1080p * 1451.93, 0 )
	purchased_hint_label:setText( Engine.Localize( "HUB_SUPPLY_DROP_PURCHASED" ), 0 )
	purchased_hint_label:setTop( _1080p * 1013.19, 0 )
	purchased_hint_label:setVerticalAlignment( LUI.VerticalAlignment.Bottom )
	local purchased_hint_image = nil
	
	purchased_hint_image = LUI.UIImage.new()
	purchased_hint_image.id = "purchased_hint_image"
	self:addElement( purchased_hint_image )
	self.purchased_hint_image = purchased_hint_image
	
	purchased_hint_image:setAlpha( 0, 0 )
	purchased_hint_image:setAnchors( 0, 1, 0, 1, 0 )
	purchased_hint_image:setBottom( _1080p * 1080, 0 )
	purchased_hint_image:setLeft( _1080p * 695.28, 0 )
	purchased_hint_image:setRight( _1080p * 796.28, 0 )
	purchased_hint_image:setTop( _1080p * 979, 0 )
	local quartermaster_mp_0_sku0 = nil
	if f0_local8( f1_local2, 0 ) then
		quartermaster_mp_0_sku0 = LUI.MenuBuilder.BuildRegisteredType( "quartermaster_mp_0_sku", {
			controllerIndex = f1_local2,
			fontIconSet = f1_local1.fontIconSet
		} )
		quartermaster_mp_0_sku0.id = "quartermaster_mp_0_sku0"
		self:addElement( quartermaster_mp_0_sku0 )
		self.quartermaster_mp_0_sku0 = quartermaster_mp_0_sku0
		
		quartermaster_mp_0_sku0:setAnchors( 0, 1, 0, 1, 0 )
		quartermaster_mp_0_sku0:setBottom( _1080p * 1080, 0 )
		quartermaster_mp_0_sku0:setLeft( _1080p * 530, 0 )
		quartermaster_mp_0_sku0:setRight( _1080p * 1920, 0 )
		quartermaster_mp_0_sku0:setTop( _1080p * 0, 0 )
	end
	local quartermaster_mp_2_sku0 = nil
	if f0_local8( f1_local2, 2 ) then
		quartermaster_mp_2_sku0 = LUI.MenuBuilder.BuildRegisteredType( "quartermaster_mp_2_sku", {
			controllerIndex = f1_local2,
			fontIconSet = f1_local1.fontIconSet
		} )
		quartermaster_mp_2_sku0.id = "quartermaster_mp_2_sku0"
		self:addElement( quartermaster_mp_2_sku0 )
		self.quartermaster_mp_2_sku0 = quartermaster_mp_2_sku0
		
		quartermaster_mp_2_sku0:setAnchors( 0, 1, 0, 1, 0 )
		quartermaster_mp_2_sku0:setBottom( _1080p * 1080, 0 )
		quartermaster_mp_2_sku0:setLeft( _1080p * 530, 0 )
		quartermaster_mp_2_sku0:setRight( _1080p * 1920, 0 )
		quartermaster_mp_2_sku0:setTop( _1080p * 0, 0 )
	end
	local quartermaster_mp_3_sku0 = nil
	if f0_local8( f1_local2, 3 ) then
		quartermaster_mp_3_sku0 = LUI.MenuBuilder.BuildRegisteredType( "quartermaster_mp_3_sku", {
			controllerIndex = f1_local2,
			fontIconSet = f1_local1.fontIconSet
		} )
		quartermaster_mp_3_sku0.id = "quartermaster_mp_3_sku0"
		self:addElement( quartermaster_mp_3_sku0 )
		self.quartermaster_mp_3_sku0 = quartermaster_mp_3_sku0
		
		quartermaster_mp_3_sku0:setAnchors( 0, 1, 0, 1, 0 )
		quartermaster_mp_3_sku0:setBottom( _1080p * 1080, 0 )
		quartermaster_mp_3_sku0:setLeft( _1080p * 530, 0 )
		quartermaster_mp_3_sku0:setRight( _1080p * 1920, 0 )
		quartermaster_mp_3_sku0:setTop( _1080p * 0, 0 )
	end
	local quartermaster_mp_4_sku0 = nil
	if f0_local8( f1_local2, 4 ) then
		quartermaster_mp_4_sku0 = LUI.MenuBuilder.BuildRegisteredType( "quartermaster_mp_4_sku", {
			controllerIndex = f1_local2,
			fontIconSet = f1_local1.fontIconSet
		} )
		quartermaster_mp_4_sku0.id = "quartermaster_mp_4_sku0"
		self:addElement( quartermaster_mp_4_sku0 )
		self.quartermaster_mp_4_sku0 = quartermaster_mp_4_sku0
		
		quartermaster_mp_4_sku0:setAnchors( 0, 1, 0, 1, 0 )
		quartermaster_mp_4_sku0:setBottom( _1080p * 1080, 0 )
		quartermaster_mp_4_sku0:setLeft( _1080p * 530, 0 )
		quartermaster_mp_4_sku0:setRight( _1080p * 1920, 0 )
		quartermaster_mp_4_sku0:setTop( _1080p * 0, 0 )
	end
	local quartermaster_mp_5_sku0 = nil
	if f0_local8( f1_local2, 5 ) then
		quartermaster_mp_5_sku0 = LUI.MenuBuilder.BuildRegisteredType( "quartermaster_mp_5_sku", {
			controllerIndex = f1_local2,
			fontIconSet = f1_local1.fontIconSet
		} )
		quartermaster_mp_5_sku0.id = "quartermaster_mp_5_sku0"
		self:addElement( quartermaster_mp_5_sku0 )
		self.quartermaster_mp_5_sku0 = quartermaster_mp_5_sku0
		
		quartermaster_mp_5_sku0:setAnchors( 0, 1, 0, 1, 0 )
		quartermaster_mp_5_sku0:setBottom( _1080p * 1080, 0 )
		quartermaster_mp_5_sku0:setLeft( _1080p * 530, 0 )
		quartermaster_mp_5_sku0:setRight( _1080p * 1920, 0 )
		quartermaster_mp_5_sku0:setTop( _1080p * 0, 0 )
	end
	local quartermaster_mp_6_sku0 = nil
	if f0_local8( f1_local2, 6 ) then
		quartermaster_mp_6_sku0 = LUI.MenuBuilder.BuildRegisteredType( "quartermaster_mp_6_sku", {
			controllerIndex = f1_local2,
			fontIconSet = f1_local1.fontIconSet
		} )
		quartermaster_mp_6_sku0.id = "quartermaster_mp_6_sku0"
		self:addElement( quartermaster_mp_6_sku0 )
		self.quartermaster_mp_6_sku0 = quartermaster_mp_6_sku0
		
		quartermaster_mp_6_sku0:setAnchors( 0, 1, 0, 1, 0 )
		quartermaster_mp_6_sku0:setBottom( _1080p * 1080, 0 )
		quartermaster_mp_6_sku0:setLeft( _1080p * 530, 0 )
		quartermaster_mp_6_sku0:setRight( _1080p * 1920, 0 )
		quartermaster_mp_6_sku0:setTop( _1080p * 0, 0 )
	end
	local navigationBar = nil
	
	navigationBar = LUI.MenuBuilder.BuildRegisteredType( "masterNavigationBar", {
		controllerIndex = f1_local2,
		fontIconSet = f1_local1.fontIconSet,
		BarElements_maxVisibleColumns = DataSources.inFrontend.MP.Quartermaster.navTabCount:GetValue( f1_local2 ),
		BarElements_spacingX = _1080p * 32
	} )
	navigationBar.id = "navigationBar"
	self:addElement( navigationBar )
	self.navigationBar = navigationBar
	
	navigationBar:setAnchors( 0, 1, 0, 1, 0 )
	navigationBar:setBottom( _1080p * 140.63, 0 )
	navigationBar:setLeft( _1080p * 846.52, 0 )
	navigationBar:setRight( _1080p * 1830.45, 0 )
	navigationBar:setTop( _1080p * 94.63, 0 )
	if navigationBar.BarElements then
		navigationBar.BarElements:SetGridDataSource( DataSources.inFrontend.MP.Quartermaster.navTabs )
	end
	if quartermaster_mp_0_sku0 then
		if quartermaster_mp_0_sku0.navigation == nil then
			quartermaster_mp_0_sku0:initNavTables()
		end
		quartermaster_mp_0_sku0.navigation = {
			left = quartermaster_mp_4_sku0 or quartermaster_mp_3_sku0 or quartermaster_mp_2_sku0 or quartermaster_mp_6_sku0 or quartermaster_mp_5_sku0,
			up = quartermaster_mp_4_sku0 or quartermaster_mp_3_sku0 or quartermaster_mp_2_sku0 or quartermaster_mp_6_sku0 or quartermaster_mp_5_sku0,
			right = quartermaster_mp_5_sku0 or quartermaster_mp_3_sku0 or quartermaster_mp_2_sku0 or quartermaster_mp_4_sku0 or quartermaster_mp_6_sku0,
			down = quartermaster_mp_5_sku0 or quartermaster_mp_3_sku0 or quartermaster_mp_2_sku0 or quartermaster_mp_4_sku0 or quartermaster_mp_6_sku0
		}
	end
	if quartermaster_mp_2_sku0 then
		if quartermaster_mp_2_sku0.navigation == nil then
			quartermaster_mp_2_sku0:initNavTables()
		end
		quartermaster_mp_2_sku0.navigation = {
			left = quartermaster_mp_4_sku0 or quartermaster_mp_3_sku0 or quartermaster_mp_0_sku0 or quartermaster_mp_6_sku0 or quartermaster_mp_5_sku0,
			up = quartermaster_mp_4_sku0 or quartermaster_mp_3_sku0 or quartermaster_mp_0_sku0 or quartermaster_mp_6_sku0 or quartermaster_mp_5_sku0,
			right = quartermaster_mp_5_sku0 or quartermaster_mp_3_sku0 or quartermaster_mp_0_sku0 or quartermaster_mp_4_sku0 or quartermaster_mp_6_sku0,
			down = quartermaster_mp_5_sku0 or quartermaster_mp_3_sku0 or quartermaster_mp_0_sku0 or quartermaster_mp_4_sku0 or quartermaster_mp_6_sku0
		}
	end
	if quartermaster_mp_3_sku0 then
		if quartermaster_mp_3_sku0.navigation == nil then
			quartermaster_mp_3_sku0:initNavTables()
		end
		quartermaster_mp_3_sku0.navigation = {
			left = quartermaster_mp_4_sku0 or quartermaster_mp_2_sku0 or quartermaster_mp_0_sku0 or quartermaster_mp_6_sku0 or quartermaster_mp_5_sku0,
			up = quartermaster_mp_4_sku0 or quartermaster_mp_2_sku0 or quartermaster_mp_0_sku0 or quartermaster_mp_6_sku0 or quartermaster_mp_5_sku0,
			right = quartermaster_mp_5_sku0 or quartermaster_mp_2_sku0 or quartermaster_mp_0_sku0 or quartermaster_mp_4_sku0 or quartermaster_mp_6_sku0,
			down = quartermaster_mp_5_sku0 or quartermaster_mp_2_sku0 or quartermaster_mp_0_sku0 or quartermaster_mp_4_sku0 or quartermaster_mp_6_sku0
		}
	end
	if quartermaster_mp_4_sku0 then
		if quartermaster_mp_4_sku0.navigation == nil then
			quartermaster_mp_4_sku0:initNavTables()
		end
		quartermaster_mp_4_sku0.navigation = {
			left = quartermaster_mp_3_sku0 or quartermaster_mp_2_sku0 or quartermaster_mp_0_sku0 or quartermaster_mp_6_sku0 or quartermaster_mp_5_sku0,
			up = quartermaster_mp_3_sku0 or quartermaster_mp_2_sku0 or quartermaster_mp_0_sku0 or quartermaster_mp_6_sku0 or quartermaster_mp_5_sku0,
			right = quartermaster_mp_5_sku0 or quartermaster_mp_2_sku0 or quartermaster_mp_0_sku0 or quartermaster_mp_3_sku0 or quartermaster_mp_6_sku0,
			down = quartermaster_mp_5_sku0 or quartermaster_mp_2_sku0 or quartermaster_mp_0_sku0 or quartermaster_mp_3_sku0 or quartermaster_mp_6_sku0
		}
	end
	if quartermaster_mp_5_sku0 then
		if quartermaster_mp_5_sku0.navigation == nil then
			quartermaster_mp_5_sku0:initNavTables()
		end
		quartermaster_mp_5_sku0.navigation = {
			left = quartermaster_mp_3_sku0 or quartermaster_mp_2_sku0 or quartermaster_mp_0_sku0 or quartermaster_mp_6_sku0 or quartermaster_mp_4_sku0,
			up = quartermaster_mp_3_sku0 or quartermaster_mp_2_sku0 or quartermaster_mp_0_sku0 or quartermaster_mp_6_sku0 or quartermaster_mp_4_sku0,
			right = quartermaster_mp_4_sku0 or quartermaster_mp_2_sku0 or quartermaster_mp_0_sku0 or quartermaster_mp_3_sku0 or quartermaster_mp_6_sku0,
			down = quartermaster_mp_4_sku0 or quartermaster_mp_2_sku0 or quartermaster_mp_0_sku0 or quartermaster_mp_3_sku0 or quartermaster_mp_6_sku0
		}
	end
	if quartermaster_mp_6_sku0 then
		if quartermaster_mp_6_sku0.navigation == nil then
			quartermaster_mp_6_sku0:initNavTables()
		end
		quartermaster_mp_6_sku0.navigation = {
			left = quartermaster_mp_3_sku0 or quartermaster_mp_2_sku0 or quartermaster_mp_0_sku0 or quartermaster_mp_5_sku0 or quartermaster_mp_4_sku0,
			up = quartermaster_mp_3_sku0 or quartermaster_mp_2_sku0 or quartermaster_mp_0_sku0 or quartermaster_mp_5_sku0 or quartermaster_mp_4_sku0,
			right = quartermaster_mp_4_sku0 or quartermaster_mp_2_sku0 or quartermaster_mp_0_sku0 or quartermaster_mp_3_sku0 or quartermaster_mp_5_sku0,
			down = quartermaster_mp_4_sku0 or quartermaster_mp_2_sku0 or quartermaster_mp_0_sku0 or quartermaster_mp_3_sku0 or quartermaster_mp_5_sku0
		}
	end
	self.purchased_hint_image:RegisterAnimationSequences( {
		PurchasedHintShow = {
			{
				function ()
					return self.purchased_hint_image:setAlpha( 0, 0 )
				end,
				function ()
					return self.purchased_hint_image:setAlpha( 1, 281, LUI.EASING.linear )
				end,
				function ()
					return self.purchased_hint_image:setAlpha( 1, 1250, LUI.EASING.linear )
				end,
				function ()
					return self.purchased_hint_image:setAlpha( 0, 313, LUI.EASING.linear )
				end
			}
		}
	} )
	self.purchased_hint_label:RegisterAnimationSequences( {
		PurchasedHintShow = {
			{
				function ()
					return self.purchased_hint_label:setAlpha( 0, 0 )
				end,
				function ()
					return self.purchased_hint_label:setAlpha( 1, 281, LUI.EASING.linear )
				end,
				function ()
					return self.purchased_hint_label:setAlpha( 1, 1250, LUI.EASING.linear )
				end,
				function ()
					return self.purchased_hint_label:setAlpha( 0, 313, LUI.EASING.linear )
				end
			}
		}
	} )
	if quartermaster_mp_0_sku0 then
		self.quartermaster_mp_0_sku0:RegisterAnimationSequences( {
			FadeEverythingIn = {
				{
					function ()
						return self.quartermaster_mp_0_sku0:setAlpha( 0, 0 )
					end,
					function ()
						return self.quartermaster_mp_0_sku0:setAlpha( 1, 125, LUI.EASING.linear )
					end
				}
			},
			HideEverything = {
				{
					function ()
						return self.quartermaster_mp_0_sku0:setAlpha( 0, 0 )
					end
				}
			}
		} )
	end
	if quartermaster_mp_2_sku0 then
		self.quartermaster_mp_2_sku0:RegisterAnimationSequences( {
			FadeEverythingIn = {
				{
					function ()
						return self.quartermaster_mp_2_sku0:setAlpha( 0, 0 )
					end,
					function ()
						return self.quartermaster_mp_2_sku0:setAlpha( 1, 125, LUI.EASING.linear )
					end
				}
			},
			HideEverything = {
				{
					function ()
						return self.quartermaster_mp_2_sku0:setAlpha( 0, 0 )
					end
				}
			}
		} )
	end
	if quartermaster_mp_3_sku0 then
		self.quartermaster_mp_3_sku0:RegisterAnimationSequences( {
			FadeEverythingIn = {
				{
					function ()
						return self.quartermaster_mp_3_sku0:setAlpha( 0, 0 )
					end,
					function ()
						return self.quartermaster_mp_3_sku0:setAlpha( 1, 125, LUI.EASING.linear )
					end
				}
			},
			HideEverything = {
				{
					function ()
						return self.quartermaster_mp_3_sku0:setAlpha( 0, 0 )
					end
				}
			}
		} )
	end
	if quartermaster_mp_4_sku0 then
		self.quartermaster_mp_4_sku0:RegisterAnimationSequences( {
			FadeEverythingIn = {
				{
					function ()
						return self.quartermaster_mp_4_sku0:setAlpha( 0, 0 )
					end,
					function ()
						return self.quartermaster_mp_4_sku0:setAlpha( 1, 125, LUI.EASING.linear )
					end
				}
			},
			HideEverything = {
				{
					function ()
						return self.quartermaster_mp_4_sku0:setAlpha( 0, 0 )
					end
				}
			}
		} )
	end
	self._sequences = {
		FadeEverythingIn = function ()
			if quartermaster_mp_0_sku0 then
				self.quartermaster_mp_0_sku0:AnimateSequence( "FadeEverythingIn" )
			end
			if quartermaster_mp_2_sku0 then
				self.quartermaster_mp_2_sku0:AnimateSequence( "FadeEverythingIn" )
			end
			if quartermaster_mp_3_sku0 then
				self.quartermaster_mp_3_sku0:AnimateSequence( "FadeEverythingIn" )
			end
			if quartermaster_mp_4_sku0 then
				self.quartermaster_mp_4_sku0:AnimateSequence( "FadeEverythingIn" )
			end
		end,
		HideEverything = function ()
			if quartermaster_mp_0_sku0 then
				self.quartermaster_mp_0_sku0:AnimateSequence( "HideEverything" )
			end
			if quartermaster_mp_2_sku0 then
				self.quartermaster_mp_2_sku0:AnimateSequence( "HideEverything" )
			end
			if quartermaster_mp_3_sku0 then
				self.quartermaster_mp_3_sku0:AnimateSequence( "HideEverything" )
			end
			if quartermaster_mp_4_sku0 then
				self.quartermaster_mp_4_sku0:AnimateSequence( "HideEverything" )
			end
		end,
		PurchasedHintShow = function ()
			self.purchased_hint_image:AnimateSequence( "PurchasedHintShow" )
			self.purchased_hint_label:AnimateSequence( "PurchasedHintShow" )
		end
	}
	if navigationBar and navigationBar.BarElements then
		navigationBar:SubscribeToModelThroughElement( navigationBar.BarElements, "index", function ()
			local f25_local0 = {
				name = "datasource_event"
			}
			local f25_local1 = f25_local0.controller or f1_local2
			local f25_local2 = f0_local7
			local f25_local3 = self
			local f25_local4 = f25_local1
			local f25_local5 = navigationBar.BarElements:GetDataSource()
			f25_local2( f25_local3, f25_local4, f25_local5.index:GetValue( f25_local1 ) )
		end )
	end
	if f0_local2 then
		f0_local2( self, f1_local2, f1_local1 )
	end
	return self
end )
if f0_local3 then
	LUI.FlowManager.RegisterStackPushBehaviour( "quartermaster_menu", f0_local3 )
end
if f0_local4 then
	LUI.FlowManager.RegisterStackPushOverBehaviour( "quartermaster_menu", f0_local4 )
end
if f0_local5 then
	LUI.FlowManager.RegisterStackResumeBehaviour( "quartermaster_menu", f0_local5 )
end
if f0_local6 then
	LUI.FlowManager.RegisterStackPopBehaviour( "quartermaster_menu", f0_local6 )
end
