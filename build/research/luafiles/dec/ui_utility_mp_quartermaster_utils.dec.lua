QuarterMasterUtils = QuarterMasterUtils or {}
GameSKUList = {
	_cachedSKUs = {}
}
QuarterMasterUtils.SD_TYPE_QUARTERMASTER = 99
QuarterMasterUtils.InventoryCurrencyType = {
	XP = 1,
	CoDPoints = 2,
	SupplyKeys = 5,
	ArmoryCredits = 6,
	SocialXP = 7
}
QuarterMasterUtils.InventoryItemType = {
	Common = "0",
	Rare = "1",
	Legendary = "2",
	Epic = "3",
	General = "4",
	Pack = "5"
}
QuarterMasterUtils.LootTypeIcons = {
	[0] = "tutorial_icon_contracts",
	[1] = "s2_loot_type_camo",
	[2] = "s2_loot_type_helmet",
	[3] = "s2_loot_type_uniform",
	[4] = "s2_loot_type_weapon",
	[5] = "s2_loot_type_melee",
	[6] = "s2_loot_type_charm",
	[7] = "s2_loot_type_emote",
	[8] = "s2_loot_type_reticle",
	[9] = "s2_loot_type_face_camo",
	[10] = "s2_loot_type_rifle",
	[11] = "s2_loot_type_smg",
	[12] = "s2_loot_type_lmg",
	[13] = "s2_loot_type_sniper",
	[14] = "s2_loot_type_shotgun",
	[17] = "warning_cac_division_infantry",
	[18] = "warning_cac_division_airborne",
	[19] = "warning_cac_division_armored",
	[20] = "warning_cac_division_mountain",
	[21] = "warning_cac_division_expeditionary",
	[22] = "warning_cac_division_resistance",
	[23] = "s2_loot_type_calling_card",
	[25] = "warning_cac_division_grenadier",
	[26] = "warning_cac_division_commando",
	[27] = "s2_operation_shamrock_and_awe",
	[28] = "s2_loot_dupe_protected"
}
QuarterMasterUtils.SkuTypeIcons = {
	[0] = "s2_supply_drop_icon",
	[1] = OperationUtils.GetOperationImage( "winter" ),
	[2] = OperationUtils.GetOperationImage( "resistance" ),
	[3] = OperationUtils.GetOperationImage( "escalation" ),
	[4] = OperationUtils.GetOperationImage( "confrontation" ),
	[5] = OperationUtils.GetOperationImage( "liberation" ),
	[6] = OperationUtils.GetOperationImage( "special" ),
	[7] = OperationUtils.GetOperationImage( "undead" ),
	[8] = "s2_cwl_icon",
	[9] = OperationUtils.GetOperationImage( "summer" ),
	[10] = "s2_operation_shamrock_and_awe",
	[11] = OperationUtils.GetOperationImage( "halloween" )
}
QuarterMasterUtils.SkuSaleStrings = {
	[0] = {
		label = "",
		description = ""
	},
	[1] = {
		label = "LUA_MENU_MTX5_CTA_1_LABEL",
		description = "LUA_MENU_MTX5_CTA_1_DESC"
	},
	[2] = {
		label = "LUA_MENU_MTX5_CTA_2_LABEL",
		description = "LUA_MENU_MTX5_CTA_2_DESC"
	},
	[3] = {
		label = "LUA_MENU_MTX5_CTA_3_LABEL",
		description = "LUA_MENU_MTX5_CTA_3_DESC"
	},
	[4] = {
		label = "LUA_MENU_MTX5_CTA_4_LABEL",
		description = "LUA_MENU_MTX5_CTA_4_DESC"
	},
	[5] = {
		label = "LUA_MENU_MTX5_CTA_5_LABEL",
		description = "LUA_MENU_MTX5_CTA_5_DESC"
	},
	[6] = {
		label = "LUA_MENU_MTX5_CTA_6_LABEL",
		description = "LUA_MENU_MTX5_CTA_6_DESC"
	},
	[7] = {
		label = "LUA_MENU_MTX5_CTA_7_LABEL",
		description = "LUA_MENU_MTX5_CTA_7_DESC"
	},
	[8] = {
		label = "LUA_MENU_MTX5_CTA_8_LABEL",
		description = "LUA_MENU_MTX5_CTA_8_DESC"
	},
	[9] = {
		label = "LUA_MENU_MTX5_CTA_9_LABEL",
		description = "LUA_MENU_MTX5_CTA_9_DESC"
	},
	[10] = {
		label = "LUA_MENU_MTX5_CTA_10_LABEL",
		description = "LUA_MENU_MTX5_CTA_10_DESC"
	},
	[11] = {
		label = "LUA_MENU_MTX5_CTA_11_LABEL",
		description = "LUA_MENU_MTX5_CTA_11_DESC"
	},
	[12] = {
		label = "LUA_MENU_MTX5_CTA_12_LABEL",
		description = "LUA_MENU_MTX5_CTA_12_DESC"
	},
	[13] = {
		label = "LUA_MENU_MTX5_CTA_13_LABEL",
		description = "LUA_MENU_MTX5_CTA_13_DESC"
	}
}
QuarterMasterUtils.LootTypeNames = {
	[0] = {
		singular = "LUA_MENU_MTX5_GENERIC_ITEM",
		plural = "LUA_MENU_MTX5_GENERIC_ITEM_PLURAL"
	},
	[1] = {
		singular = Cac.LootTypeData.weapon_camo.Label,
		plural = "LUA_MENU_MTX5_LOOT_TYPE_CAMO_PLURAL"
	},
	[2] = {
		singular = Cac.LootTypeData.costume.Label,
		plural = "LUA_MENU_MTX5_LOOT_TYPE_HELMET_PLURAL"
	},
	[3] = {
		singular = Cac.LootTypeData.uniforms.Label,
		plural = "LUA_MENU_MTX5_LOOT_TYPE_UNIFORM_PLURAL"
	},
	[4] = {
		singular = Cac.LootTypeData.weapon.Label,
		plural = "LUA_MENU_MTX5_LOOT_TYPE_WEAPON_PLURAL"
	},
	[5] = {
		singular = "LOOT_MTX3_5_MELEE",
		plural = "LOOT_MTX3_5_MELEE"
	},
	[6] = {
		singular = Cac.LootTypeData.weapon_charm.Label,
		plural = "LUA_MENU_MTX5_LOOT_TYPE_WEAPON_CHARM_PLURAL"
	},
	[7] = {
		singular = Cac.LootTypeData.emote.Label,
		plural = "LUA_MENU_MTX5_LOOT_TYPE_EMOTE_PLURAL"
	},
	[8] = {
		singular = Cac.LootTypeData.site_reticle.Label,
		plural = "LUA_MENU_MTX5_LOOT_TYPE_SITE_RETICLE_PLURAL"
	},
	[9] = {
		singular = Cac.LootTypeData.face_camo.Label,
		plural = "LUA_MENU_MTX5_LOOT_TYPE_FACE_CAMO_PLURAL"
	},
	[10] = {
		singular = "MPUI_ASSAULT_RIFLE",
		plural = "MPUI_ASSAULT_RIFLES"
	},
	[11] = {
		singular = "MPUI_SUB_MACHINE_GUN",
		plural = "MPUI_SUB_MACHINE_GUNS"
	},
	[12] = {
		singular = "MPUI_LIGHT_MACHINE_GUN",
		plural = "MPUI_LIGHT_MACHINE_GUNS"
	},
	[13] = {
		singular = "MPUI_SNIPER_RIFLE",
		plural = "MPUI_SNIPER_RIFLES"
	},
	[14] = {
		singular = "MPUI_SHOTGUN",
		plural = "MPUI_SHOTGUNS"
	},
	[17] = {
		singular = "LUA_MENU_MTX5_INFANTRY_UNIFORM",
		plural = "LUA_MENU_MTX5_INFANTRY_UNIFORM_PLURAL"
	},
	[18] = {
		singular = "LUA_MENU_MTX5_AIRBORNE_UNIFORM",
		plural = "LUA_MENU_MTX5_AIRBORNE_UNIFORM_PLURAL"
	},
	[19] = {
		singular = "LUA_MENU_MTX5_ARMORED_UNIFORM",
		plural = "LUA_MENU_MTX5_ARMORED_UNIFORM_PLURAL"
	},
	[20] = {
		singular = "LUA_MENU_MTX5_MOUNTAIN_UNIFORM",
		plural = "LUA_MENU_MTX5_MOUNTAIN_UNIFORM_PLURAL"
	},
	[21] = {
		singular = "LUA_MENU_MTX5_EXPEDITIONARY_UNIFORM",
		plural = "LUA_MENU_MTX5_EXPEDITIONARY_UNIFORM_PLURAL"
	},
	[22] = {
		singular = "LUA_MENU_MTX5_RESISTANCE_UNIFORM",
		plural = "LUA_MENU_MTX5_RESISTANCE_UNIFORM_PLURAL"
	},
	[23] = {
		singular = "LUA_MENU_MTX5_ZOMBIE_CONSUMABLE",
		plural = "LUA_MENU_MTX5_ZOMBIE_CONSUMABLE_PLURAL"
	},
	[25] = {
		singular = "LUA_MENU_MTX7_CAVALRY_UNIFORM",
		plural = "LUA_MENU_MTX7_CAVALRY_UNIFORM_PLURAL"
	},
	[26] = {
		singular = "LUA_MENU_MTX8_COMMANDO_UNIFORM",
		plural = "LUA_MENU_MTX8_COMMANDO_UNIFORM_PLURAL"
	},
	[27] = {
		singular = "LUA_MENU_MTX7_SHAMROCK_ITEM",
		plural = "LUA_MENU_MTX7_SHAMROCK_ITEM_PLURAL"
	}
}
QuarterMasterUtils.CurrencyIndex = {
	Default = 1,
	CoDPoints = 0,
	SupplyKeys = 1
}
QuarterMasterUtils.SKUDataType = SKUType.Quartermaster
QuarterMasterUtils.SupplyDropPromoText = {
	ASD_MP = "LUA_MENU_RARE_SUPPLY_DROP",
	ASD_ZOMBIE = "LUA_MENU_RARE_ZOMBIE_SUPPLY_DROP"
}
QuarterMasterUtils.SupplyDropTypeTag = {
	ASD_MP = "MP",
	ASD_ZOMBIE = "ZM",
	ASD_MP_HEROIC = "MP_H",
	ASD_ZOMBIE_HEROIC = "ZM_H"
}
QuarterMasterUtils.SkuTags = {
	ASD_MP = "MP",
	ASD_MP_25_OFF = "MP_25%",
	ASD_MP_50_OFF = "MP_50%",
	ASD_ZM = "ZM",
	ASD_MP_EPIC = "MP_EPIC",
	ASD_MP_LEGENDARY = "MP_LEG",
	ASD_MP_WEAPON = "MP_WEP",
	PACK_5_WEAPON = "MP_X5_WEP",
	PACK_10_WEAPON = "MP_X10_WEP",
	PACK_20 = "MP_X20",
	PACK_20_25_OFF = "MP_X20_25%",
	PACK_20_50_OFF = "MP_X20_50%",
	PACK_TRIPLE_PLAY = "MP_TP",
	PACK_STARTER = "MP_STARTER",
	ASD_WINTER = "MP_WINTER",
	ASD_WINTER_BRIBE = "MP_WINT_BRIBE",
	PACK_5_WINTER = "MP_X5_WINT",
	PACK_10_WINTER = "MP_X10_WINT",
	PACK_13_WINTER = "MP_X13_WINT",
	PACK_FRONTLINES = "MP_FRONT",
	PACK_FRONT_25_OFF = "MP_FRONT_25%",
	PACK_5_ZOMBIE = "MP_X5_ZOM",
	ASD_RESISTANCE = "MP_RESIST",
	ASD_RESISTANCE_BRIBE = "MP_RESIST_BRIBE",
	PACK_5_RESIST = "MP_X5_RESIST",
	PACK_10_RESIST = "MP_X10_RESIST",
	PACK_10_RESIST_ZOM = "ZM_X10_RESIST",
	PACK_RESIST = "MP_PACK_RESIST",
	PACK_RESIST_TRIPLE = "MP_TP_RESIST",
	PACK_RESIST_BIG = "MP_BIG_RESIST",
	PACK_20_ZOMBIE = "ZM_X20",
	PACK_20_ZOMBIE_25_OFF = "ZM_X20_25%",
	PACK_RESIST_UPRISING = "MP_UT_RESIST",
	PACK_RESIST_HEROIC = "MP_HT_RESIST",
	PACK_RESIST_LAST = "MP_LAST_RESIST",
	AC_GOAT_II = "AC_TEST",
	PACK_HEROIC_TRIPLE = "MP_HT",
	PPSH_LOOT3 = "PPSH_LOOT3_2",
	STG_LOOT2 = "STG_LOOT2_1",
	SPRING_LOOT3 = "SPRING_LOOT3_1",
	GREASE_LOOT0 = "GREASE_LOOT0_2",
	PACK_10 = "MP_X10",
	PACK_10_25_OFF = "MP_X10_25%",
	PACK_10_50_OFF = "MP_X10_50%",
	PACK_STARTER_2 = "MP_STARTER_2",
	SDAC_EPIC_UNIFORM = "MP_EPIC_UNI_AC",
	PACK_EPIC_TRIPLE = "MP_ET",
	PACK_HEROIC_MONDAY = "MP_HM",
	SDAC_CHARM = "MP_CHARM_AC",
	PACK_EPIC_MONDAY = "MP_EM",
	SDAC_CAMO = "MP_CAMO_AC",
	PACK_BIG = "MP_X50",
	PACK_BIG_50_OFF = "MP_X50_50%",
	SDAC_HELMET = "MP_HELMET_AC",
	ASD_WARMACHINE_BRIBE = "MP_WM_BRIBE",
	PACK_10_1 = "MP_X10_1",
	PACK_15_5 = "MP_X15_5",
	PACK_SOLDIER_TRIPLE = "MP_ST",
	PACK_20_LIMITED = "MP_X20_15%",
	PACK_WM_15 = "MP_X15_WM",
	PACK_30 = "MP_X30",
	PACK_30_25_OFF = "MP_X30_25%",
	SDAC_EMOTE = "MP_EMOTE_AC",
	SD_EPIC_UNIFORM = "MP_EPIC_UNI",
	SDAC_EPIC_WEAPON = "MP_EPIC_WEAP_AC",
	SD_HEROIC_UNIFORM = "MP_HERO_UNI",
	SDAC_HEROIC_WEAPON = "MP_HERO_WEAP_AC",
	PACK_10_2 = "MP_X10_2",
	PACK_20_20ZM = "MP_20_20Z",
	PACK_5 = "MP_X5",
	PACK_5_50_OFF = "MP_X5_50%",
	PACK_5_1 = "MP_X5_1",
	PACK_AC_MEMORIAL_DAY = "MP_MD_AC",
	PACK_BIG_25_OFF = "MP_X50_25%",
	PACK_5_5ZM = "MP_5_5Z",
	SDAC_RETICLE = "MP_RETICLE_AC",
	SDAC_UNDEAD = "MP_UND_AC",
	PACK_10_10ZM = "MP_10_10Z",
	ASD_RIFLE = "MP_RIFLE",
	ASD_UNDEAD_BRIBE = "MP_UND_BRIBE",
	SDAC_UNIFORM = "MP_UNI_AC",
	PACK_SMG = "MP_X5_SMG",
	PACK_5_20_OFF = "MP_X5_20%",
	PACK_FRONT_UNDEAD = "MP_FRONT_UND",
	PACK_30_17_OFF = "MP_X30_17%",
	ASD_INFANTRY = "MP_INF",
	ASD_SNIPER = "MP_SNIPER",
	PACK_UNDEAD_15 = "MP_X15_UND",
	CWL_CWL = "CWL_CWL",
	CWL_ECHO_FOX = "CWL_EF",
	CWL_ENVY = "CWL_ENVY",
	CWL_EPSILON = "CWL_EPSI",
	CWL_EUNITED = "CWL_EU",
	CWL_EVIL_GENIUSES = "CWL_EVIL",
	CWL_FAZE = "CWL_FAZE",
	CWL_LUMINOSITY = "CWL_LUMI",
	CWL_MINDFREAK = "CWL_MIND",
	CWL_OPTIC = "CWL_OPT",
	CWL_RED_RESERVE = "CWL_RED",
	CWL_RISE_NATION = "CWL_RISE",
	CWL_SPLYCE = "CWL_SPLY",
	CWL_UNILAD = "CWL_UNI",
	CWL_VITALITY = "CWL_VITA",
	CWL_KALIBER = "CWL_KALI"
}
QuarterMasterUtils.SkuImages = {
	[QuarterMasterUtils.SkuTags.ASD_MP] = "advanced_supply_drop",
	[QuarterMasterUtils.SkuTags.ASD_MP_25_OFF] = "advanced_supply_drop",
	[QuarterMasterUtils.SkuTags.ASD_MP_50_OFF] = "advanced_supply_drop",
	[QuarterMasterUtils.SkuTags.ASD_ZM] = "advanced_zombie_supply_drop",
	[QuarterMasterUtils.SkuTags.ASD_MP_EPIC] = "epic_drop",
	[QuarterMasterUtils.SkuTags.ASD_MP_LEGENDARY] = "legendary_drop",
	[QuarterMasterUtils.SkuTags.ASD_MP_WEAPON] = "weapon_bribe",
	[QuarterMasterUtils.SkuTags.PACK_5_WEAPON] = "bundle_topper_5+1",
	[QuarterMasterUtils.SkuTags.PACK_10_WEAPON] = "bundle_topper_10+2",
	[QuarterMasterUtils.SkuTags.PACK_20] = "bundle_rare_20",
	[QuarterMasterUtils.SkuTags.PACK_20_25_OFF] = "bundle_rare_20",
	[QuarterMasterUtils.SkuTags.PACK_20_50_OFF] = "bundle_rare_20",
	[QuarterMasterUtils.SkuTags.PACK_TRIPLE_PLAY] = "bundle_premium_triple_threat",
	[QuarterMasterUtils.SkuTags.PACK_STARTER] = "bundle_starter_pack",
	[QuarterMasterUtils.SkuTags.ASD_WINTER] = "winter_supply_drop",
	[QuarterMasterUtils.SkuTags.ASD_WINTER_BRIBE] = "winter_bribe",
	[QuarterMasterUtils.SkuTags.PACK_5_WINTER] = "winter_bundle_topper_5+1",
	[QuarterMasterUtils.SkuTags.PACK_10_WINTER] = "winter_bundle_topper_10+2_2",
	[QuarterMasterUtils.SkuTags.PACK_13_WINTER] = "winter_bundle_topper_12+3",
	[QuarterMasterUtils.SkuTags.PACK_FRONTLINES] = "winter_bundle_frontlines",
	[QuarterMasterUtils.SkuTags.PACK_FRONT_25_OFF] = "winter_bundle_frontlines",
	[QuarterMasterUtils.SkuTags.PACK_5_ZOMBIE] = "winter_bundle_topper_5+1_zombies",
	[QuarterMasterUtils.SkuTags.ASD_RESISTANCE] = "resistance_supply_drop",
	[QuarterMasterUtils.SkuTags.ASD_RESISTANCE_BRIBE] = "resistance_bribe",
	[QuarterMasterUtils.SkuTags.PACK_5_RESIST] = "bundle_resistance_topper_5+1",
	[QuarterMasterUtils.SkuTags.PACK_10_RESIST] = "bundle_resistance_topper_10+2",
	[QuarterMasterUtils.SkuTags.PACK_10_RESIST_ZOM] = "bundle_resistance_topper_10+2_zombies",
	[QuarterMasterUtils.SkuTags.PACK_RESIST] = "bundle_resistance",
	[QuarterMasterUtils.SkuTags.PACK_RESIST_TRIPLE] = "bundle_resistance_uprising",
	[QuarterMasterUtils.SkuTags.PACK_RESIST_BIG] = "bundle_resistance_big",
	[QuarterMasterUtils.SkuTags.PACK_20_ZOMBIE] = "bundle_zombies_20",
	[QuarterMasterUtils.SkuTags.PACK_20_ZOMBIE_25_OFF] = "bundle_zombies_20",
	[QuarterMasterUtils.SkuTags.PACK_RESIST_UPRISING] = "bundle_resistance_uprising",
	[QuarterMasterUtils.SkuTags.PACK_RESIST_HEROIC] = "bundle_resistance_heroic_triple_play",
	[QuarterMasterUtils.SkuTags.PACK_RESIST_LAST] = "bundle_resistance",
	[QuarterMasterUtils.SkuTags.AC_GOAT_II] = "winter_bribe",
	[QuarterMasterUtils.SkuTags.PACK_HEROIC_TRIPLE] = "bundle_heroic_triple_play",
	[QuarterMasterUtils.SkuTags.PPSH_LOOT3] = "ppsh41_loot3",
	[QuarterMasterUtils.SkuTags.STG_LOOT2] = "stg44_loot2",
	[QuarterMasterUtils.SkuTags.SPRING_LOOT3] = "springfield_loot3",
	[QuarterMasterUtils.SkuTags.GREASE_LOOT0] = "greasegun_loot0",
	[QuarterMasterUtils.SkuTags.PACK_10] = "bundle_rare_20",
	[QuarterMasterUtils.SkuTags.PACK_10_25_OFF] = "bundle_rare_20",
	[QuarterMasterUtils.SkuTags.PACK_10_50_OFF] = "bundle_rare_20",
	[QuarterMasterUtils.SkuTags.PACK_STARTER_2] = "bundle_starter_pack_3",
	[QuarterMasterUtils.SkuTags.SDAC_EPIC_UNIFORM] = "epic_bribe",
	[QuarterMasterUtils.SkuTags.PACK_EPIC_TRIPLE] = "bundle_epic",
	[QuarterMasterUtils.SkuTags.PACK_HEROIC_MONDAY] = "bundle_heroic",
	[QuarterMasterUtils.SkuTags.SDAC_CHARM] = "weapon_bribe",
	[QuarterMasterUtils.SkuTags.PACK_EPIC_MONDAY] = "bundle_epic",
	[QuarterMasterUtils.SkuTags.SDAC_CAMO] = "weapon_bribe",
	[QuarterMasterUtils.SkuTags.PACK_BIG] = "bundle_starter_pack",
	[QuarterMasterUtils.SkuTags.PACK_BIG_50_OFF] = "bundle_starter_pack",
	[QuarterMasterUtils.SkuTags.SDAC_HELMET] = "weapon_bribe",
	[QuarterMasterUtils.SkuTags.ASD_WARMACHINE_BRIBE] = "war_machine_bribe",
	[QuarterMasterUtils.SkuTags.PACK_10_1] = "bundle_starter_pack",
	[QuarterMasterUtils.SkuTags.PACK_15_5] = "bundle_starter_pack",
	[QuarterMasterUtils.SkuTags.PACK_SOLDIER_TRIPLE] = "bundle_bribe",
	[QuarterMasterUtils.SkuTags.PACK_20_LIMITED] = "bundle_starter_pack",
	[QuarterMasterUtils.SkuTags.PACK_WM_15] = "bundle_warmachine_bribe",
	[QuarterMasterUtils.SkuTags.PACK_30] = "bundle_starter_pack",
	[QuarterMasterUtils.SkuTags.PACK_30_25_OFF] = "bundle_starter_pack",
	[QuarterMasterUtils.SkuTags.SDAC_EMOTE] = "weapon_bribe",
	[QuarterMasterUtils.SkuTags.SD_EPIC_UNIFORM] = "epic_bribe",
	[QuarterMasterUtils.SkuTags.SDAC_EPIC_WEAPON] = "epic_bribe",
	[QuarterMasterUtils.SkuTags.SD_HEROIC_UNIFORM] = "heroic_bribe",
	[QuarterMasterUtils.SkuTags.SDAC_HEROIC_WEAPON] = "heroic_bribe",
	[QuarterMasterUtils.SkuTags.PACK_10_2] = "bundle_starter_pack",
	[QuarterMasterUtils.SkuTags.PACK_20_20ZM] = "bundle_zombies",
	[QuarterMasterUtils.SkuTags.PACK_5] = "bundle_starter_pack",
	[QuarterMasterUtils.SkuTags.PACK_5_50_OFF] = "bundle_starter_pack",
	[QuarterMasterUtils.SkuTags.PACK_5_1] = "bundle_starter_pack",
	[QuarterMasterUtils.SkuTags.PACK_AC_MEMORIAL_DAY] = "bundle_3x_bribes",
	[QuarterMasterUtils.SkuTags.PACK_BIG_25_OFF] = "bundle_starter_pack",
	[QuarterMasterUtils.SkuTags.PACK_5_5ZM] = "bundle_zombies",
	[QuarterMasterUtils.SkuTags.SDAC_RETICLE] = "weapon_bribe",
	[QuarterMasterUtils.SkuTags.SDAC_UNDEAD] = "zombie_siege_bribe",
	[QuarterMasterUtils.SkuTags.PACK_10_10ZM] = "bundle_zombies",
	[QuarterMasterUtils.SkuTags.ASD_RIFLE] = "weapon_bribe",
	[QuarterMasterUtils.SkuTags.ASD_UNDEAD_BRIBE] = "zombie_siege_bribe",
	[QuarterMasterUtils.SkuTags.SDAC_UNIFORM] = "weapon_bribe",
	[QuarterMasterUtils.SkuTags.PACK_SMG] = "bundle_bribe",
	[QuarterMasterUtils.SkuTags.PACK_5_20_OFF] = "bundle_starter_pack",
	[QuarterMasterUtils.SkuTags.PACK_FRONT_UNDEAD] = "bundle_zombie_siege_frontlines",
	[QuarterMasterUtils.SkuTags.PACK_30_17_OFF] = "bundle_starter_pack",
	[QuarterMasterUtils.SkuTags.ASD_INFANTRY] = "weapon_bribe",
	[QuarterMasterUtils.SkuTags.ASD_SNIPER] = "weapon_bribe",
	[QuarterMasterUtils.SkuTags.PACK_UNDEAD_15] = "bundle_zombie_siege_last_chance",
	[QuarterMasterUtils.SkuTags.CWL_CWL] = "emblem_cwl",
	[QuarterMasterUtils.SkuTags.CWL_ECHO_FOX] = "emblem_echo_fox",
	[QuarterMasterUtils.SkuTags.CWL_ENVY] = "emblem_team_envy",
	[QuarterMasterUtils.SkuTags.CWL_EPSILON] = "emblem_eplison",
	[QuarterMasterUtils.SkuTags.CWL_EUNITED] = "emblem_eunited",
	[QuarterMasterUtils.SkuTags.CWL_EVIL_GENIUSES] = "emblem_evil_geniuses",
	[QuarterMasterUtils.SkuTags.CWL_FAZE] = "emblem_faze_clan",
	[QuarterMasterUtils.SkuTags.CWL_LUMINOSITY] = "emblem_luminosity",
	[QuarterMasterUtils.SkuTags.CWL_MINDFREAK] = "emblem_mindfreak",
	[QuarterMasterUtils.SkuTags.CWL_OPTIC] = "emblem_optic_gaming",
	[QuarterMasterUtils.SkuTags.CWL_RED_RESERVE] = "emblem_red_reserve",
	[QuarterMasterUtils.SkuTags.CWL_RISE_NATION] = "emblem_rise_nation",
	[QuarterMasterUtils.SkuTags.CWL_SPLYCE] = "emblem_splyce",
	[QuarterMasterUtils.SkuTags.CWL_UNILAD] = "emblem_unilad",
	[QuarterMasterUtils.SkuTags.CWL_VITALITY] = "emblem_team_vitality",
	[QuarterMasterUtils.SkuTags.CWL_KALIBER] = "emblem_team_kaliber"
}
QuarterMasterUtils.SkuIndexImages = {
	"advanced_supply_drop",
	"legendary_drop",
	"epic_drop",
	"epic_bribe",
	"heroic_bribe",
	"weapon_bribe",
	"bundle_epic",
	"bundle_heroic",
	"bundle_bribe",
	"bundle_3x_bribes",
	"advanced_zombie_supply_drop",
	"bundle_zombies",
	"bundle_zombies_20",
	"bundle_topper_5+1",
	"bundle_topper_10+2",
	"bundle_rare_20",
	"bundle_premium_triple_threat",
	"bundle_starter_pack",
	"bundle_heroic_triple_play",
	"bundle_starter_pack_3",
	"winter_supply_drop",
	"winter_bribe",
	"winter_bundle_topper_5+1",
	"winter_bundle_topper_10+2_2",
	"winter_bundle_topper_12+3",
	"winter_bundle_frontlines",
	"winter_bundle_topper_5+1_zombies",
	"resistance_supply_drop",
	"resistance_bribe",
	"bundle_resistance_topper_5+1",
	"bundle_resistance_topper_10+2",
	"bundle_resistance_topper_10+2_zombies",
	"bundle_resistance",
	"bundle_resistance_uprising",
	"bundle_resistance_big",
	"bundle_resistance_uprising",
	"bundle_resistance_heroic_triple_play",
	"ppsh41_loot3",
	"stg44_loot2",
	"springfield_loot3",
	"greasegun_loot0",
	"war_machine_bribe",
	"zombie_siege_bribe",
	"bundle_zombie_siege_frontlines",
	"bundle_zombie_siege_last_chance",
	"liberty_strike_bribe",
	"bundle_liberty_strike_bribe",
	"bundle_liberty_strike_double",
	"days_of_summer_bribe",
	"bundle_summer_bribe",
	"bundle_summer_double",
	"covert_storm_bribe",
	"bundle_covert_storm_bribe",
	"bundle_covert_storm_double",
	"bundle_summer_uniform",
	"halloween_scream_bribe",
	"bundle_halloween_scream_bribe",
	"bundle_halloween_scream_double",
	"erma_loot2",
	"kgm21_loot2"
}
QuarterMasterUtils.EventScheduleData = {
	SPECIAL_1A = {
		REF = "online_quartermaster_special_bundle_1a_ref",
		START = "online_quartermaster_special_bundle_1a_start",
		END = "online_quartermaster_special_bundle_1a_end"
	},
	SPECIAL_1B = {
		REF = "online_quartermaster_special_bundle_1b_ref",
		START = "online_quartermaster_special_bundle_1b_start",
		END = "online_quartermaster_special_bundle_1b_end"
	},
	SPECIAL_1C = {
		REF = "online_quartermaster_special_bundle_1c_ref",
		START = "online_quartermaster_special_bundle_1c_start",
		END = "online_quartermaster_special_bundle_1c_end"
	},
	SPECIAL_1D = {
		REF = "online_quartermaster_special_bundle_1d_ref",
		START = "online_quartermaster_special_bundle_1d_start",
		END = "online_quartermaster_special_bundle_1d_end"
	},
	SPECIAL_1E = {
		REF = "online_quartermaster_special_bundle_1e_ref",
		START = "online_quartermaster_special_bundle_1e_start",
		END = "online_quartermaster_special_bundle_1e_end"
	},
	SPECIAL_2A = {
		REF = "online_quartermaster_special_bundle_2a_ref",
		START = "online_quartermaster_special_bundle_2a_start",
		END = "online_quartermaster_special_bundle_2a_end"
	},
	SPECIAL_2B = {
		REF = "online_quartermaster_special_bundle_2b_ref",
		START = "online_quartermaster_special_bundle_2b_start",
		END = "online_quartermaster_special_bundle_2b_end"
	},
	SPECIAL_2C = {
		REF = "online_quartermaster_special_bundle_2c_ref",
		START = "online_quartermaster_special_bundle_2c_start",
		END = "online_quartermaster_special_bundle_2c_end"
	},
	SPECIAL_2D = {
		REF = "online_quartermaster_special_bundle_2d_ref",
		START = "online_quartermaster_special_bundle_2d_start",
		END = "online_quartermaster_special_bundle_2d_end"
	},
	SPECIAL_2E = {
		REF = "online_quartermaster_special_bundle_2e_ref",
		START = "online_quartermaster_special_bundle_2e_start",
		END = "online_quartermaster_special_bundle_2e_end"
	},
	SPECIAL_3A = {
		REF = "online_quartermaster_special_bundle_3a_ref",
		START = "online_quartermaster_special_bundle_3a_start",
		END = "online_quartermaster_special_bundle_3a_end"
	},
	SPECIAL_3B = {
		REF = "online_quartermaster_special_bundle_3b_ref",
		START = "online_quartermaster_special_bundle_3b_start",
		END = "online_quartermaster_special_bundle_3b_end"
	},
	SPECIAL_3C = {
		REF = "online_quartermaster_special_bundle_3c_ref",
		START = "online_quartermaster_special_bundle_3c_start",
		END = "online_quartermaster_special_bundle_3c_end"
	},
	SPECIAL_3D = {
		REF = "online_quartermaster_special_bundle_3d_ref",
		START = "online_quartermaster_special_bundle_3d_start",
		END = "online_quartermaster_special_bundle_3d_end"
	},
	SPECIAL_3E = {
		REF = "online_quartermaster_special_bundle_3e_ref",
		START = "online_quartermaster_special_bundle_3e_start",
		END = "online_quartermaster_special_bundle_3e_end"
	},
	SPECIAL_4A = {
		REF = "online_quartermaster_special_bundle_4a_ref",
		START = "online_quartermaster_special_bundle_4a_start",
		END = "online_quartermaster_special_bundle_4a_end"
	},
	SPECIAL_4B = {
		REF = "online_quartermaster_special_bundle_4b_ref",
		START = "online_quartermaster_special_bundle_4b_start",
		END = "online_quartermaster_special_bundle_4b_end"
	},
	SPECIAL_4C = {
		REF = "online_quartermaster_special_bundle_4c_ref",
		START = "online_quartermaster_special_bundle_4c_start",
		END = "online_quartermaster_special_bundle_4c_end"
	},
	SPECIAL_4D = {
		REF = "online_quartermaster_special_bundle_4d_ref",
		START = "online_quartermaster_special_bundle_4d_start",
		END = "online_quartermaster_special_bundle_4d_end"
	},
	SPECIAL_4E = {
		REF = "online_quartermaster_special_bundle_4e_ref",
		START = "online_quartermaster_special_bundle_4e_start",
		END = "online_quartermaster_special_bundle_4e_end"
	},
	SALE_MP = {
		REF = "online_quartermaster_sale_rare_mp_ref",
		START = "online_quartermaster_sale_rare_mp_start",
		END = "online_quartermaster_sale_rare_mp_end"
	},
	SALE_ZM = {
		REF = "online_quartermaster_sale_rare_zm_ref",
		START = "online_quartermaster_sale_rare_zm_start",
		END = "online_quartermaster_sale_rare_zm_end"
	}
}
QuarterMasterUtils.SKUDataKeys = {
	TAG = "t",
	IMAGE_OVERRIDE = "i",
	FLAGS = "f",
	CONTRACT_ID_CONTRACT = "c",
	CONTRACT_ID_QUARTERMASTER = "C",
	LIMITER_DATA = "l",
	UNLOCK_GUID = "u",
	SPECIAL_ICONS = "s",
	EXPERIMENT_COHORT = "e"
}
QuarterMasterUtils.SKUFlags = {
	SALE = "s",
	TIME_REMAINING = "t",
	QUANTITY_REMAIN_PERSONAL = "q",
	IMAGE_FILL_BUTTON = "f",
	ICON_TYPE = "i",
	IMAGE_INDEX_OVERRIDE = "p"
}
QuarterMasterUtils.SKUImageFormats = {
	NORMAL = 0,
	FILL_FRAME = 1
}
QuarterMasterUtils.AB_Conversions = {
	AllConversions = {
		[0] = {
			27,
			29
		},
		[1] = {
			28,
			30
		}
	},
	Treatment_1 = {},
	Treatment_2 = {},
	ActiveConversions = {
		[0] = {},
		[1] = {}
	}
}
QuarterMasterUtils.AB_FindOriginalSupplyDropType = function ( f1_arg0, f1_arg1 )
	for f1_local6, f1_local7 in pairs( QuarterMasterUtils.AB_Conversions.AllConversions ) do
		for f1_local3, f1_local4 in ipairs( f1_local7 ) do
			if f1_arg1 == f1_local4 then
				return f1_local6
			end
		end
	end
	return f1_arg1
end

QuarterMasterUtils.AB_GetNumBoosterPacksOfTypeAllConversions = function ( f2_arg0, f2_arg1 )
	if QuarterMasterUtils.AB_Conversions.AllConversions[f2_arg1] then
		local f2_local0 = f2_arg1
		local f2_local1 = Engine.Loot_GetNumBoosterPacksOfType( f2_arg0, f2_arg1 )
		for f2_local5, f2_local6 in ipairs( QuarterMasterUtils.AB_Conversions.AllConversions[f2_arg1] ) do
			local f2_local7 = Engine.Loot_GetNumBoosterPacksOfType( f2_arg0, f2_local6 )
			if f2_local7 > 0 then
				f2_local1 = f2_local1 + f2_local7
				f2_local0 = f2_local6
			end
		end
		return f2_local1, f2_local0
	else
		for f2_local3, f2_local4 in pairs( QuarterMasterUtils.AB_Conversions.AllConversions ) do
			for f2_local8, f2_local9 in ipairs( f2_local4 ) do
				if f2_local9 == f2_arg1 then
					return 0, f2_arg1
				end
			end
		end
		return Engine.Loot_GetNumBoosterPacksOfType( f2_arg0, f2_arg1 ), f2_arg1
	end
end

QuarterMasterUtils.AB_GetConvertedSupplyDropType = function ( f3_arg0, f3_arg1 )
	local f3_local0, f3_local1 = QuarterMasterUtils.AB_GetNumBoosterPacksOfTypeAllConversions( f3_arg0, f3_arg1 )
	if f3_local1 ~= f3_arg1 then
		return false, "", f3_local1
	elseif CONDITIONS.PlayerHasInitiated_sd_test( f3_arg0 ) then
		local f3_local2 = CONDITIONS.PlayerIsInRange1_sd_test( f3_arg0 )
		local f3_local3 = CONDITIONS.PlayerIsInRange2_sd_test( f3_arg0 )
		if f3_local2 and QuarterMasterUtils.AB_Conversions.Treatment_1[f3_arg1] then
			return true, QuarterMasterUtils.AB_Conversions.Treatment_1[f3_arg1].rule, QuarterMasterUtils.AB_Conversions.Treatment_1[f3_arg1].newType
		elseif f3_local3 and QuarterMasterUtils.AB_Conversions.Treatment_2[f3_arg1] then
			return true, QuarterMasterUtils.AB_Conversions.Treatment_2[f3_arg1].rule, QuarterMasterUtils.AB_Conversions.Treatment_2[f3_arg1].newType
		end
	end
	return false, "", f3_arg1
end

QuarterMasterUtils.CachedAvailableSkuIDList = nil
QuarterMasterUtils.CachedSKUInfoItems = {
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{}
}
local f0_local0 = function ( f4_arg0, f4_arg1 )
	local f4_local0 = f4_arg0:match( f4_arg1 .. "(%d*)" )
	local f4_local1 = 0
	if f4_local0 ~= nil then
		if f4_local0 == "" then
			local f4_local2 = 1
		end
		f4_local1 = f4_local2 or tonumber( f4_local0 )
	end
	return f4_local1
end

QuarterMasterUtils.ClearCachedSKUInfoItems = function ()
	for f5_local3, f5_local4 in ipairs( QuarterMasterUtils.CachedSKUInfoItems ) do
		f5_local4.guid = nil
		f5_local4.quantity = nil
	end
end

QuarterMasterUtils.FindSkuDataByType = function ( f6_arg0, f6_arg1 )
	local f6_local0, f6_local1 = LUI.SingleSplit( f6_arg0, ";" )
	while f6_local0 do
		local f6_local2, f6_local3 = LUI.SingleSplit( f6_local0, ":" )
		if f6_local2 == f6_arg1 then
			return f6_local3
		end
		f6_local0, f6_local1 = LUI.SingleSplit( f6_local1, ";" )
	end
	return nil
end

QuarterMasterUtils.GetContractCurrencies = function ( f7_arg0, f7_arg1 )
	local f7_local0 = {}
	local f7_local1 = 0
	for f7_local8, f7_local9 in ipairs( f7_arg1 ) do
		local f7_local5 = QuarterMasterUtils.FindSkuDataByType( Engine.Inventory_GetSKUInfoSKUData( f7_local9 ), QuarterMasterUtils.SKUDataKeys.CONTRACT_ID_CONTRACT )
		if f7_local5 then
			f7_local5 = tonumber( f7_local5 )
			QuarterMasterUtils.ClearCachedSKUInfoItems()
			local f7_local6, f7_local7 = Engine.Inventory_GetSKUInfoItems( f7_local9, QuarterMasterUtils.CachedSKUInfoItems )
			if f7_local7 >= 1 and 0 < Engine.Inventory_GetItemQuantity( f7_arg0, f7_local6[1].guid ) then
				f7_local0[f7_local1 + 1] = f7_local5
				f7_local1 = f7_local1 + 1
			end
		end
	end
	return f7_local0
end

QuarterMasterUtils.ActivateMissedContracts = function ( f8_arg0, f8_arg1 )
	if #f8_arg1 == 0 then
		return 
	end
	local f8_local0 = AchievementEngineUtils.CountActiveChallengesByType( f8_arg0, AEPeriodicType.Contract )
	local f8_local1 = DwDataUtils.GetCachedData[DwDataUtils.Vendor.Operation]( f8_arg0, GameChallengeGroup.PlayerActive )
	for f8_local2 = 1, #f8_arg1, 1 do
		if f8_local0 < 3 then
			local f8_local5 = false
			for f8_local6 = 1, #f8_local1, 1 do
				if f8_local1[f8_local6].ID == f8_arg1[f8_local2] then
					f8_local5 = true
				end
			end
			if not f8_local5 and Engine.AE_ActivatePlayerChallenge( f8_arg0, f8_arg1[f8_local2] ) then
				f8_local0 = f8_local0 + 1
			end
		end
	end
end

QuarterMasterUtils.FindSKUIDByType = function ( f9_arg0, f9_arg1 )
	for f9_local0 = 1, #f9_arg0, 1 do
		local f9_local3 = QuarterMasterUtils.FindSkuDataByType( Engine.Inventory_GetSKUInfoSKUData( f9_arg0[f9_local0] ), QuarterMasterUtils.SKUDataKeys.TAG )
		if f9_local3 and f9_local3 == f9_arg1 then
			return f9_arg0[f9_local0]
		end
	end
	return nil
end

QuarterMasterUtils.SkuLimitReached = function ( f10_arg0, f10_arg1 )
	local f10_local0 = QuarterMasterUtils.FindSkuDataByType( f10_arg1, QuarterMasterUtils.SKUDataKeys.LIMITER_DATA )
	if f10_local0 then
		local f10_local1, f10_local2 = nil
		local f10_local3 = string.find( f10_local0, "|" )
		if f10_local3 then
			f10_local1 = string.sub( f10_local0, 1, f10_local3 - 1 )
			f10_local2 = tonumber( string.sub( f10_local0, f10_local3 + 1 ) )
		end
		if not f10_local1 or not f10_local2 then
			return false
		else
			return f10_local2 <= Engine.Inventory_GetItemQuantity( f10_arg0, f10_local1 )
		end
	else
		return false
	end
end

QuarterMasterUtils.IsSkuLocked = function ( f11_arg0, f11_arg1 )
	local f11_local0 = QuarterMasterUtils.FindSkuDataByType( f11_arg1, QuarterMasterUtils.SKUDataKeys.UNLOCK_GUID )
	if f11_local0 then
		return Engine.Inventory_GetItemQuantity( f11_arg0, f11_local0 ) == 0
	else
		return false
	end
end

QuarterMasterUtils.IsSkuCohortEnabled = function ( f12_arg0, f12_arg1 )
	local f12_local0 = QuarterMasterUtils.FindSkuDataByType( f12_arg1, QuarterMasterUtils.SKUDataKeys.EXPERIMENT_COHORT )
	if not f12_local0 then
		return true
	end
	local f12_local1, f12_local2 = nil
	local f12_local3 = string.find( f12_local0, "|" )
	if f12_local3 then
		f12_local1 = string.sub( f12_local0, 1, f12_local3 - 1 )
		f12_local2 = tonumber( string.sub( f12_local0, f12_local3 + 1 ) )
	end
	if not f12_local1 or f12_local2 == nil then
		return true
	end
	return HashRangeUtils.IsPlayerInRange( f12_arg0, f12_local1, f12_local2 )
end

QuarterMasterUtils.GetActiveAndAvailableScheduledEvent = function ( f13_arg0, f13_arg1, f13_arg2 )
	if not Engine.IsCurrentTimeWithinRange( f13_arg2.START, f13_arg2.END ) then
		return nil
	end
	local f13_local0 = Engine.GetDvarString( f13_arg2.REF )
	if f13_local0 == "none" then
		return nil
	end
	local f13_local1 = QuarterMasterUtils.FindSKUIDByType( f13_arg1, f13_local0 )
	local f13_local2 = f13_local1 ~= nil
	if f13_local2 then
		local f13_local3 = Engine.Inventory_GetSKUInfo( f13_local1 )
		local f13_local4 = f13_local3.skuData
		local f13_local5 = QuarterMasterUtils.SkuLimitReached( f13_arg0, f13_local4 )
		local f13_local6 = QuarterMasterUtils.IsSkuLocked( f13_arg0, f13_local4 )
		local f13_local7
		if f13_local3.saleEndTime == "0x0" or Engine.EpochTimeToGameTime( f13_local3.saleEndTime ) ~= "0x0" then
			f13_local7 = false
		else
			f13_local7 = true
		end
		local f13_local8 = QuarterMasterUtils.IsSkuCohortEnabled( f13_arg0, f13_local4 )
		if not f13_local5 and not f13_local6 and not f13_local7 then
			f13_local2 = f13_local8
		else
			f13_local2 = false
		end
	end
	if f13_local2 then
		return {
			id = f13_local1,
			timeRemaining = Engine.EpochTimeToGameTime( f13_arg2.END )
		}
	end
	return nil
end

QuarterMasterUtils.IsSpecial1Available = function ( f14_arg0, f14_arg1 )
	local f14_local0
	if QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f14_arg0, f14_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_1A ) == nil and QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f14_arg0, f14_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_1B ) == nil and QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f14_arg0, f14_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_1C ) == nil and QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f14_arg0, f14_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_1D ) == nil and QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f14_arg0, f14_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_1E ) == nil then
		f14_local0 = false
	else
		f14_local0 = true
	end
	return f14_local0
end

QuarterMasterUtils.IsSpecial2Available = function ( f15_arg0, f15_arg1 )
	local f15_local0
	if QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f15_arg0, f15_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_2A ) == nil and QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f15_arg0, f15_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_2B ) == nil and QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f15_arg0, f15_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_2C ) == nil and QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f15_arg0, f15_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_2D ) == nil and QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f15_arg0, f15_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_2E ) == nil then
		f15_local0 = false
	else
		f15_local0 = true
	end
	return f15_local0
end

QuarterMasterUtils.IsSpecial3Available = function ( f16_arg0, f16_arg1 )
	local f16_local0
	if QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f16_arg0, f16_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_3A ) == nil and QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f16_arg0, f16_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_3B ) == nil and QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f16_arg0, f16_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_3C ) == nil and QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f16_arg0, f16_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_3D ) == nil and QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f16_arg0, f16_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_3E ) == nil then
		f16_local0 = false
	else
		f16_local0 = true
	end
	return f16_local0
end

QuarterMasterUtils.IsSpecial4Available = function ( f17_arg0, f17_arg1 )
	local f17_local0
	if QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f17_arg0, f17_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_4A ) == nil and QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f17_arg0, f17_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_4B ) == nil and QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f17_arg0, f17_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_4C ) == nil and QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f17_arg0, f17_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_4D ) == nil and QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f17_arg0, f17_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_4E ) == nil then
		f17_local0 = false
	else
		f17_local0 = true
	end
	return f17_local0
end

QuarterMasterUtils.CountAvailableSKUs = function ( f18_arg0, f18_arg1 )
	if not CONDITIONS.IsCODPointsEnabled() then
		return 0
	end
	local f18_local0 = 2
	if QuarterMasterUtils.IsSpecial1Available( f18_arg0, f18_arg1 ) then
		f18_local0 = f18_local0 + 1
	end
	if QuarterMasterUtils.IsSpecial2Available( f18_arg0, f18_arg1 ) then
		f18_local0 = f18_local0 + 1
	end
	if QuarterMasterUtils.IsSpecial3Available( f18_arg0, f18_arg1 ) then
		f18_local0 = f18_local0 + 1
	end
	if QuarterMasterUtils.IsSpecial4Available( f18_arg0, f18_arg1 ) then
		f18_local0 = f18_local0 + 1
	end
	return f18_local0
end

QuarterMasterUtils.GetAvailableSkuIDList = function ( f19_arg0, f19_arg1 )
	local f19_local0 = {}
	local f19_local1 = QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f19_arg0, f19_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_1A )
	if not f19_local1 then
		f19_local1 = QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f19_arg0, f19_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_1B )
		if not f19_local1 then
			f19_local1 = QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f19_arg0, f19_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_1C )
			if not f19_local1 then
				f19_local1 = QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f19_arg0, f19_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_1D )
				if not f19_local1 then
					f19_local1 = QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f19_arg0, f19_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_1E )
				end
			end
		end
	end
	if f19_local1 then
		f19_local0[#f19_local0 + 1] = f19_local1
	end
	local f19_local2 = QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f19_arg0, f19_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_2A )
	if not f19_local2 then
		f19_local2 = QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f19_arg0, f19_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_2B )
		if not f19_local2 then
			f19_local2 = QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f19_arg0, f19_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_2C )
			if not f19_local2 then
				f19_local2 = QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f19_arg0, f19_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_2D )
				if not f19_local2 then
					f19_local2 = QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f19_arg0, f19_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_2E )
				end
			end
		end
	end
	if f19_local2 then
		f19_local0[#f19_local0 + 1] = f19_local2
	end
	local f19_local3 = QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f19_arg0, f19_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_3A )
	if not f19_local3 then
		f19_local3 = QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f19_arg0, f19_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_3B )
		if not f19_local3 then
			f19_local3 = QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f19_arg0, f19_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_3C )
			if not f19_local3 then
				f19_local3 = QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f19_arg0, f19_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_3D )
				if not f19_local3 then
					f19_local3 = QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f19_arg0, f19_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_3E )
				end
			end
		end
	end
	if f19_local3 then
		f19_local0[#f19_local0 + 1] = f19_local3
	end
	local f19_local4 = QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f19_arg0, f19_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_4A )
	if not f19_local4 then
		f19_local4 = QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f19_arg0, f19_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_4B )
		if not f19_local4 then
			f19_local4 = QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f19_arg0, f19_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_4C )
			if not f19_local4 then
				f19_local4 = QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f19_arg0, f19_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_4D )
				if not f19_local4 then
					f19_local4 = QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f19_arg0, f19_arg1, QuarterMasterUtils.EventScheduleData.SPECIAL_4E )
				end
			end
		end
	end
	if f19_local4 then
		f19_local0[#f19_local0 + 1] = f19_local4
	end
	local f19_local5 = QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f19_arg0, f19_arg1, QuarterMasterUtils.EventScheduleData.SALE_MP )
	if not f19_local5 then
		f19_local5 = {
			id = QuarterMasterUtils.FindSKUIDByType( f19_arg1, QuarterMasterUtils.SupplyDropTypeTag.ASD_MP )
		}
	end
	assert( f19_local5 )
	f19_local0[#f19_local0 + 1] = f19_local5
	local f19_local6 = QuarterMasterUtils.GetActiveAndAvailableScheduledEvent( f19_arg0, f19_arg1, QuarterMasterUtils.EventScheduleData.SALE_ZM )
	if not f19_local6 then
		f19_local6 = {
			id = QuarterMasterUtils.FindSKUIDByType( f19_arg1, QuarterMasterUtils.SupplyDropTypeTag.ASD_ZOMBIE )
		}
	end
	assert( f19_local6 )
	f19_local0[#f19_local0 + 1] = f19_local6
	return f19_local0
end

QuarterMasterUtils.ProcessSkuInfo = function ( f20_arg0 )
	local f20_local0 = LUI.Split( f20_arg0.promotionalText, ";" )
	f20_arg0.name = f20_local0[1] or ""
	f20_arg0.description = f20_local0[2] or ""
	local f20_local1 = f20_arg0.prices[1].currency
	local f20_local2 = f20_arg0.prices[1].value
	if f20_local1 == QuarterMasterUtils.InventoryCurrencyType.CoDPoints then
		f20_arg0.CoDPointsPrice = f20_local2
	end
end

local f0_local1 = function ( f21_arg0, f21_arg1 )
	local f21_local0 = nil
	for f21_local4, f21_local5 in ipairs( f21_arg1 ) do
		local f21_local6 = f21_local5.id
		assert( f21_local6 )
		local f21_local7 = f21_local5.timeRemaining
		f21_arg0.quartermaster.availableSkus[f21_local4] = f21_local6
		f21_local0 = Engine.Inventory_GetSKUInfo( f21_local6 )
		QuarterMasterUtils.ProcessSkuInfo( f21_local0 )
		f21_arg0.quartermaster.skusInfo[f21_local6] = f21_local0
		f21_arg0.quartermaster.skusInfo[f21_local6].timeRemaining = f21_local7
		if f21_local4 == #f21_arg0.quartermaster.availableSkus - 1 then
			f21_arg0.quartermaster.skusInfo[f21_local6].SupplyDropType = QuarterMasterUtils.SupplyDropTypeTag.ASD_MP
		end
		if f21_local4 == #f21_arg0.quartermaster.availableSkus then
			f21_arg0.quartermaster.skusInfo.SupplyDropType = QuarterMasterUtils.SupplyDropTypeTag.ASD_ZOMBIE
		end
	end
end

QuarterMasterUtils.storeSKUInfo = function ( f22_arg0, f22_arg1 )
	local f22_local0 = nil
	local f22_local1 = 0
	local f22_local2 = LUI.FlowManager.GetScopedData( f22_arg0 )
	local f22_local3 = QuarterMasterUtils.GetAvailableSkuIDList( f22_arg1, DwDataUtils.GetCachedData[DwDataUtils.Vendor.Quartermaster]( f22_arg1 ) )
	f22_local2.quartermaster.availableSkus = {}
	f0_local1( f22_local2, f22_local3 )
	local f22_local4 = DataSources.inFrontend.MP.Quartermaster.contractsTileButton
	f22_local4.name:SetValue( f22_arg1, Engine.Localize( "MENU_CONTRACTS" ) )
	f22_local4.image:SetValue( f22_arg1, "menu_qm_contracts" )
	f22_local4.isImageFill:SetValue( f22_arg1, true )
	f22_local4 = DataSources.inFrontend.MP.Quartermaster.collectionTileButton
	f22_local4.name:SetValue( f22_arg1, Engine.Localize( "MENU_COLLECTIONS" ) )
	f22_local4.image:SetValue( f22_arg1, "menu_qm_collections" )
	f22_local4.isImageFill:SetValue( f22_arg1, true )
	f22_local4 = DataSources.inFrontend.MP.Quartermaster.codPointsTileButton
	f22_local4.name:SetValue( f22_arg1, Engine.Localize( "LUA_MENU_PURCHASE_COD_POINTS" ) )
	f22_local4.image:SetValue( f22_arg1, "menu_qm_codpoints" )
	f22_local4.isImageFill:SetValue( f22_arg1, true )
	f22_local4 = DataSources.inFrontend.MP.Quartermaster.ordersTileButton
	f22_local4.name:SetValue( f22_arg1, Engine.Localize( "LUA_MENU_HEADQUARTERS" ) )
	f22_local4.image:SetValue( f22_arg1, "menu_qm_collections" )
	f22_local4.isImageFill:SetValue( f22_arg1, true )
end

QuarterMasterUtils.UpdateSkuInfoIfSameCount = function ( f23_arg0, f23_arg1 )
	local f23_local0 = nil
	local f23_local1 = LUI.FlowManager.GetScopedData( f23_arg0 )
	local f23_local2 = QuarterMasterUtils.GetAvailableSkuIDList( f23_arg1, DwDataUtils.GetCachedData[DwDataUtils.Vendor.Quartermaster]( f23_arg1 ) )
	if #f23_local2 ~= #f23_local1.quartermaster.availableSkus then
		return false
	else
		f0_local1( f23_local1, f23_local2 )
		return true
	end
end

QuarterMasterUtils.ZMBreadcrumbCheck = function ( f24_arg0 )
	local f24_local0 = false
	local f24_local1 = DataSources.inFrontend.MP.Quartermaster.contractsTileButton.isNew:GetValue( f24_arg0 )
	if not f24_local0 then
		f24_local0 = f24_local1 or hasNewOrders
	end
	return f24_local0
end

QuarterMasterUtils.GetSkuImage = function ( f25_arg0, f25_arg1, f25_arg2 )
	if f25_arg2 then
		return f25_arg2
	else
		local f25_local0 = f0_local0( f25_arg1 or "", QuarterMasterUtils.SKUFlags.IMAGE_INDEX_OVERRIDE )
		if f25_local0 and QuarterMasterUtils.SkuIndexImages[f25_local0] then
			return QuarterMasterUtils.SkuIndexImages[f25_local0]
		elseif f25_arg0 and QuarterMasterUtils.SkuImages[f25_arg0] then
			return QuarterMasterUtils.SkuImages[f25_arg0]
		else
			return ""
		end
	end
end

QuarterMasterUtils.PurchaseSupplyDropSKUPopup = function ( f26_arg0, f26_arg1, f26_arg2, f26_arg3, f26_arg4, f26_arg5, f26_arg6, f26_arg7, f26_arg8, f26_arg9, f26_arg10, f26_arg11 )
	local f26_local0 = f26_arg2.prices[1].currency
	local f26_local1 = f26_arg2.prices[1].value
	local f26_local2 = f26_local1 <= Engine.Inventory_GetCurrencyBalance( f26_arg1, f26_local0 )
	local f26_local3, f26_local4, f26_local5 = nil
	local f26_local6 = {}
	local f26_local7 = nil
	local f26_local8 = LUI.FlowManager.GetTopMenuInfo
	local f26_local9 = Engine.GetLuiRoot()
	f26_local8 = f26_local8( f26_local9.flowManager.menuInfoStack, false )
	if f26_local8 then
		f26_local9 = f26_local8.name
		if not f26_local9 then
		
		else
			if f26_arg2.skuData then
				for f26_local13, f26_local14 in ipairs( LUI.Split( f26_arg2.skuData, ";" ) ) do
					local f26_local15 = LUI.Split( f26_local14, ":" )
					local f26_local16 = f26_local15[1]
					local f26_local17 = f26_local15[2]
					if f26_local16 == QuarterMasterUtils.SKUDataKeys.IMAGE_OVERRIDE then
						f26_local5 = f26_local17
					end
					if f26_local16 == QuarterMasterUtils.SKUDataKeys.TAG then
						f26_local3 = f26_local17
					end
					if f26_local16 == QuarterMasterUtils.SKUDataKeys.SPECIAL_ICONS then
						f26_local6 = LUI.Split( f26_local17, "," )
					end
					if f26_local16 == QuarterMasterUtils.SKUDataKeys.FLAGS then
						f26_local7 = f26_local17
					end
				end
			end
			DataSources.inFrontend.MP.Quartermaster.skuDetails.skuTag:SetValue( controller, f26_local3 )
			LUI.ComScore.LogScreenView( f26_arg1, "sku_purchase_modal" )
			f26_local4 = QuarterMasterUtils.GetSkuImage( f26_local3, f26_local7, f26_local5 )
			local f26_local18 = LUI.Split( f26_arg2.promotionalText, ";" )
			local f26_local10 = MODIFIERS.ToUpperCase( Engine.Localize( f26_local18[1] ) )
			local f26_local11 = 0
			local f26_local12 = 0
			local f26_local13 = function ( f27_arg0, f27_arg1 )
				local f27_local0 = Engine.Inventory_PurchaseSKU( f27_arg1, f26_arg3, 1 )
				local f27_local1 = LUI.FlowManager.GetTopMenuInfo
				local f27_local2 = Engine.GetLuiRoot()
				f27_local1 = f27_local1( f27_local2.flowManager.menuInfoStack, true )
				if f26_arg10 then
					if f26_local12 <= 0 then
						f26_local11 = 1
					else
						f26_local11 = math.min( f26_local11 + 1, #CoD.SFX.SupplyDropPurchaseSequence )
					end
					Engine.PlaySound( CoD.SFX.SupplyDropPurchaseSequence[f26_local11] )
					f26_local12 = f26_local12 + 1
					f27_local2 = f27_arg0:wait( 5000 )
					f27_local2.onComplete = function ()
						f26_local12 = f26_local12 - 1
					end
					
				else
					Engine.PlaySound( CoD.SFX.SupplyDropPurchase )
				end
				if f26_arg4 then
					f26_arg4()
				end
				if f27_local1 and f27_local1.name == "notification_modal" then
					f27_local2 = f27_local1.menu
					ACTIONS.SetInputEnabled( f27_arg0, false )
					ACTIONS.SetInputEnabled( f27_local2, false )
					ModalUtils.SetHoldCloseModalFlag( f27_local2, true )
					f27_local2.NotificationBody:FXStart( f27_arg1, ModalUtils.NotificationModalType.SupplyDropPurchaseNotification, f26_local10 )
					f27_local2:registerEventHandler( "NotificationModalHoldFinish", function ()
						ModalUtils.SetHoldCloseModalFlag( f27_local2, false )
						ACTIONS.SetInputEnabled( f27_arg0, true )
						if f26_arg10 then
							if f26_local1 <= Engine.Inventory_GetCurrencyBalance( f27_arg1, f26_local0 ) and not QuarterMasterUtils.SkuLimitReached( f27_arg1, f26_arg2.skuData ) then
								ACTIONS.SetInputEnabled( f27_local2, true )
								f27_local2.NotificationBody:FXRestorePurchaseBand( f27_arg1, Engine.Localize( "LOOT_PURCHASE_X_CAPS", f26_local10 ), Engine.Localize( "MENU_PURCHASE_CONFIRMATION_DETAIL" ) )
							else
								LUI.ComScore.LogScreenView( f27_arg1, f26_local9 )
								ACTIONS.LeaveMenu( f27_local2 )
							end
						else
							LUI.ComScore.LogScreenView( f27_arg1, f26_local9 )
							ACTIONS.LeaveMenu( f27_local2 )
						end
					end )
				else
					LUI.ComScore.LogScreenView( f27_arg1, f26_local9 )
					ACTIONS.LeaveMenu( f27_arg0 )
				end
			end
			
			local f26_local14 = function ()
				if f26_arg5 then
					f26_arg5()
				end
				ACTIONS.LeaveMenu()
				LUI.FlowManager.RequestAddMenu( f26_arg0, "store_menu", true, f26_arg1, false, {
					initCharacterScene = true,
					linkedItem = "5000codpoints",
					returnToPrevMenu = f26_arg6,
					disableHubButton = f26_arg7
				} )
			end
			
			local f26_local15 = function ()
				LUI.ComScore.LogScreenView( f26_arg1, f26_local9 )
				ACTIONS.LeaveMenu()
			end
			
			local f26_local16 = function ()
				LUI.ComScore.LogScreenView( f26_arg1, f26_local9 )
			end
			
			local f26_local17 = QuarterMasterUtils.FindSkuDataByType( f26_arg2.skuData, QuarterMasterUtils.SKUDataKeys.CONTRACT_ID_QUARTERMASTER )
			local f26_local19
			if not f26_arg8 then
				f26_local19 = AchievementEngineUtils.IsOrderAvailable( f26_arg0, f26_arg1, f26_local17, DwDataUtils.Vendor.Operation, GameChallengeGroup.Scheduled )
			else
				f26_local19 = false
			end
			local f26_local20 = nil
			local f26_local21 = false
			f26_local20 = {}
			if f26_local2 then
				local f26_local22 = "MENU_PURCHASE_WITH_COD_POINTS"
				if f26_local0 == QuarterMasterUtils.InventoryCurrencyType.ArmoryCredits then
					f26_local22 = Engine.Localize( "LUA_MENU_YES", f26_local1 )
				end
				local f26_local23 = {
					disableDefaultActionSound = true,
					text = Engine.Localize( f26_local22, f26_local1 ),
					callbackFunc = f26_local13,
					isDefault = f26_arg9 and f26_local2
				}
				table.insert( f26_local20, f26_local23 )
				f26_local21 = f26_local23.isDefault
			elseif f26_local0 == QuarterMasterUtils.InventoryCurrencyType.CoDPoints then
				local f26_local22 = {
					disableDefaultActionSound = false,
					text = "LUA_MENU_PURCHASE_COD_POINTS",
					callbackFunc = f26_local14
				}
				local f26_local23
				if not f26_local19 then
					f26_local23 = not f26_arg11
				else
					f26_local23 = false
				end
				f26_local22.isDefault = f26_local23
				table.insert( f26_local20, f26_local22 )
				f26_local21 = f26_local22.isDefault
			end
			if f26_local19 then
				local f26_local22 = {
					text = "LUA_MENU_VIEW_CONTRACT_CAPS",
					callbackFunc = function ( f33_arg0, f33_arg1 )
						f26_local15()
						Character_Scene.curVendor.enterSubMenu = true
						LUI.FlowManager.RequestAddMenu( f33_arg0, "contracts_menu", true, f33_arg1, false, {
							hasVendorMenu = true,
							viewMenuContractID = tonumber( f26_local17 )
						} )
					end,
					isDefault = not f26_local21
				}
				table.insert( f26_local20, f26_local22 )
				f26_local21 = f26_local22.isDefault
			end
			table.insert( f26_local20, {
				text = "MENU_NOT_NOW",
				callbackFunc = function ( f34_arg0, f34_arg1 )
					f26_local15()
				end,
				isDefault = not f26_local21
			} )
			f26_local21 = true
			local f26_local23 = nil
			if f26_local2 then
				local f26_local24 = ModalUtils.NotificationModalType.CoDPointPurchaseNotification
				if f26_local0 == QuarterMasterUtils.InventoryCurrencyType.ArmoryCredits then
					f26_local24 = ModalUtils.NotificationModalType.ArmoryCreditPurchaseNotification
				end
				f26_local23 = {
					modalType = f26_local24,
					titleText = Engine.Localize( "LOOT_PURCHASE_X_CAPS", f26_local10 ),
					descText = Engine.Localize( "MENU_PURCHASE_CONFIRMATION_DETAIL" ),
					icon = f26_local4,
					cost = f26_local1,
					exclusiveController = true,
					iconSubtypes = f26_local6,
					on_back_func = f26_local16
				}
			else
				local f26_local24 = ModalUtils.NotificationModalType.InsufficientCoDPointNotification
				local f26_local25 = "MENU_NOT_ENOUGH_COD_POINTS"
				local f26_local26 = "MENU_NOT_ENOUGH_COD_POINTS_DETAIL"
				if f26_local0 == QuarterMasterUtils.InventoryCurrencyType.ArmoryCredits then
					f26_local24 = ModalUtils.NotificationModalType.InsufficientArmoryCreditNotification
					f26_local25 = "LUA_MENU_NOT_ENOUGH_ARMORY_CREDITS"
					f26_local26 = "LUA_MENU_NOT_ENOUGH_ARMORY_CREDITS_DETAIL"
				end
				f26_local23 = {
					modalType = f26_local24,
					titleText = Engine.Localize( f26_local25 ),
					descText = Engine.Localize( f26_local26 ),
					icon = f26_local4,
					cost = f26_local1,
					exclusiveController = true,
					iconSubtypes = f26_local6,
					on_back_func = f26_local16
				}
			end
			ModalUtils.OpenNotification( f26_arg0, f26_arg1, f26_local20, f26_local23 )
		end
	end
	f26_local9 = ""
end

QuarterMasterUtils.OpenSupplyDropWidget = function ( f35_arg0, f35_arg1, f35_arg2 )
	if f35_arg1 ~= Engine.GetControllerForLocalClient( LocalClient0 ) then
		return 
	end
	ACTIONS.PlaySupplyDropSelectionOpenSound()
	LUI.FlowManager.RequestAddMenu( f35_arg0, "supplyDropMenuWidget", true, f35_arg1, false )
	if f35_arg0 then
		ACTIONS.SetInputEnabled( f35_arg0, false )
		if f35_arg2 then
			ACTIONS.Hide( f35_arg2 )
		end
		f35_arg0:registerEventHandler( "close_supply_drop", function ( element )
			ACTIONS.SetInputEnabled( element, true )
			if f35_arg2 then
				ACTIONS.Show( f35_arg2 )
			end
		end )
	end
end

QuarterMasterUtils.GetSupplyDropGUID = function ( f37_arg0 )
	local f37_local0 = Engine.TableLookup( SupplyDropTypesTable.File, SupplyDropTypesTable.Cols.Type, f37_arg0, SupplyDropTypesTable.Cols.ItemID )
	if f37_local0 ~= "" then
		return string.format( "0x%x", tonumber( f37_local0 ) )
	else
		return nil
	end
end

QuarterMasterUtils.GetSkuIsAvailable = function ( f38_arg0, f38_arg1 )
	if not (DataSources.inGame.HUD.DwDataUtils.skuDataFetchTracker:GetValue( f38_arg0 ) == DwDataUtils.AllSKUDataFetchCallTracker.Done) then
		return false
	end
	for f38_local3, f38_local4 in ipairs( QuarterMasterUtils.GetAvailableSkuIDList( f38_arg0, DwDataUtils.GetCachedData[DwDataUtils.Vendor.Quartermaster]( f38_arg0 ) ) ) do
		if f38_local4.id == f38_arg1 then
			return true
		end
	end
	return false
end

QuarterMasterUtils.GetAvailableSkuForSupplyDropType = function ( f39_arg0, f39_arg1, f39_arg2 )
	local f39_local0 = QuarterMasterUtils.GetSupplyDropGUID( f39_arg1 )
	if not f39_local0 then
		return nil
	elseif not (DataSources.inGame.HUD.DwDataUtils.skuDataFetchTracker:GetValue( f39_arg0 ) == DwDataUtils.AllSKUDataFetchCallTracker.Done) then
		return nil
	end
	local f39_local1 = nil
	if f39_arg2 and QuarterMasterUtils.CachedAvailableSkuIDList and #QuarterMasterUtils.CachedAvailableSkuIDList > 0 then
		f39_local1 = QuarterMasterUtils.CachedAvailableSkuIDList
	else
		f39_local1 = QuarterMasterUtils.GetAvailableSkuIDList( f39_arg0, DwDataUtils.GetCachedData[DwDataUtils.Vendor.Quartermaster]( f39_arg0 ) )
		if f39_arg2 then
			QuarterMasterUtils.CachedAvailableSkuIDList = f39_local1
		end
	end
	for f39_local10, f39_local11 in ipairs( f39_local1 ) do
		local f39_local12 = f39_local11.id
		local f39_local13 = Engine.Inventory_GetSKUInfoSKUData( f39_local12 )
		QuarterMasterUtils.ClearCachedSKUInfoItems()
		local f39_local14, f39_local15 = Engine.Inventory_GetSKUInfoItems( f39_local12, QuarterMasterUtils.CachedSKUInfoItems )
		if f39_local15 == 1 and f39_local14[1].quantity == 1 and f39_local14[1].guid == f39_local0 then
			return QuarterMasterUtils.FindSkuDataByType( f39_local13, QuarterMasterUtils.SKUDataKeys.TAG )
		elseif f39_local15 == 2 and QuarterMasterUtils.FindSkuDataByType( f39_local13, QuarterMasterUtils.SKUDataKeys.LIMITER_DATA ) then
			for f39_local8, f39_local9 in ipairs( f39_local14 ) do
				if f39_local9.quantity == 1 and f39_local9.guid == f39_local0 then
					return QuarterMasterUtils.FindSkuDataByType( f39_local13, QuarterMasterUtils.SKUDataKeys.TAG )
				end
			end
		end
	end
	return nil
end

QuarterMasterUtils.SelectSupplyDropTypeForOpen = function ( f40_arg0, f40_arg1, f40_arg2 )
	DataSources.inGame.HUD.supplyDrop.listActive:SetValue( f40_arg1, false )
	local f40_local0 = Engine.GetLuiRoot()
	assert( f40_local0 )
	if CONDITIONS.IsZombiesMode( f40_arg0 ) or f40_local0:AnyActiveMenusInStack() and (not CONDITIONS.IsHubSpawnAreaLoaded() or CONDITIONS.IsHubKillswitched()) then
		ACTIONS.LeaveMenuByName( "supplyDropMenuWidget" )
		LUI.FlowManager.RequestAddMenu( f40_arg0, "Supply_Drop_Reveal", true, f40_arg1, false, {
			supplyDropType = f40_arg2,
			useCharacterScene = true
		} )
	else
		PreventVendorInteraction = true
		Engine.NotifyServer( "hub_supply_drop_selection", f40_arg2 )
	end
end

local f0_local2 = {
	resetTimerCount = 0,
	repeatPurchaseCount = 1
}
QuarterMasterUtils.playSkuPurchaseSfx = function ( f41_arg0 )
	if f0_local2.resetTimerCount <= 0 then
		f0_local2.repeatPurchaseCount = 1
	else
		f0_local2.repeatPurchaseCount = math.min( f0_local2.repeatPurchaseCount + 1, #CoD.SFX.SupplyDropPurchaseSequence )
	end
	Engine.PlaySound( CoD.SFX.SupplyDropPurchaseSequence[f0_local2.repeatPurchaseCount] )
	f0_local2.resetTimerCount = f0_local2.resetTimerCount + 1
	local f41_local0 = f41_arg0:wait( 5000 )
	f41_local0.onComplete = function ()
		f0_local2.resetTimerCount = f0_local2.resetTimerCount - 1
	end
	
end

local f0_local3 = function ( f43_arg0, f43_arg1, f43_arg2, f43_arg3, f43_arg4, f43_arg5 )
	if f43_arg1 then
		return {
			disableDefaultActionSound = true,
			text = "LUA_MENU_PURCHASE_CAPS",
			callbackFunc = f43_arg2,
			isDefault = f43_arg4
		}
	elseif f43_arg0 == QuarterMasterUtils.InventoryCurrencyType.CoDPoints then
		local f43_local0 = {
			disableDefaultActionSound = false,
			text = "LUA_MENU_PURCHASE_COD_POINTS",
			callbackFunc = f43_arg3
		}
		local f43_local1
		if not f43_arg5 then
			f43_local1 = not f43_arg4
		else
			f43_local1 = false
		end
		f43_local0.isDefault = f43_local1
		return f43_local0
	else
		return nil
	end
end

local f0_local4 = function ( f44_arg0, f44_arg1 )
	return {
		text = "LUA_MENU_VIEW_CONTRACT_CAPS",
		callbackFunc = f44_arg1,
		isDefault = not f44_arg0
	}
end

local f0_local5 = function ( f45_arg0, f45_arg1 )
	return {
		text = "MENU_NOT_NOW",
		callbackFunc = f45_arg1,
		isDefault = not f45_arg0
	}
end

QuarterMasterUtils.GetSkuPurchaseChoices = function ( f46_arg0, f46_arg1, f46_arg2, f46_arg3, f46_arg4, f46_arg5, f46_arg6, f46_arg7, f46_arg8 )
	local f46_local0 = false
	local f46_local1 = {}
	local f46_local2 = nil
	if f46_arg1 then
		f46_local2 = f0_local3( f46_arg0, f46_arg2, f46_arg3, f46_arg4, f46_arg5, f46_arg6 )
		if f46_local2 ~= nil then
			table.insert( f46_local1, f46_local2 )
			f46_local0 = f46_local2.isDefault
		end
	end
	if f46_arg6 then
		f46_local2 = f0_local4( f46_local0, f46_arg8 )
		table.insert( f46_local1, f46_local2 )
		f46_local0 = f46_local2.isDefault
	end
	table.insert( f46_local1, f0_local5( f46_local0, f46_arg8 ) )
	return f46_local1
end

local f0_local6 = function ( f47_arg0 )
	local f47_local0 = {}
	if f47_arg0 then
		for f47_local4, f47_local5 in ipairs( LUI.Split( f47_arg0, ";" ) ) do
			local f47_local6 = LUI.Split( f47_local5, ":" )
			f47_local0[f47_local6[1]] = f47_local6[2]
		end
	end
	return f47_local0
end

local f0_local7 = function ( f48_arg0, f48_arg1, f48_arg2, f48_arg3, f48_arg4 )
	f48_arg0.skuTypeIcon:SetValue( f48_arg1, QuarterMasterUtils.SkuTypeIcons[f0_local0( f48_arg4 or "", QuarterMasterUtils.SKUFlags.ICON_TYPE )] )
	f48_arg0.saleType:SetValue( f48_arg1, f0_local0( f48_arg4 or "", QuarterMasterUtils.SKUFlags.SALE ) )
	f48_arg0.skuTag:SetValue( f48_arg1, f48_arg3 )
	f48_arg0.skuId:SetValue( f48_arg1, f48_arg2.skuID )
end

local f0_local8 = function ( f49_arg0, f49_arg1, f49_arg2, f49_arg3 )
	f49_arg0.name:SetValue( f49_arg1, f49_arg2.name )
	f49_arg0.description:SetValue( f49_arg1, f49_arg2.description )
	local f49_local0 = ""
	if f49_arg3 and f49_arg3:find( QuarterMasterUtils.SKUFlags.TIME_REMAINING ) then
		f49_local0 = f49_arg2.timeRemaining
	end
	f49_arg0.gameTimeEnd:SetValue( f49_arg1, f49_local0 )
end

local f0_local9 = function ( f50_arg0, f50_arg1, f50_arg2, f50_arg3, f50_arg4 )
	local f50_local0 = QuarterMasterUtils.GetSkuImage( f50_arg2, f50_arg4, f50_arg3 )
	local f50_local1 = QuarterMasterUtils.SKUImageFormats.NORMAL
	if f50_arg4 and f50_arg4:find( QuarterMasterUtils.SKUFlags.IMAGE_FILL_BUTTON ) then
		f50_local1 = QuarterMasterUtils.SKUImageFormats.FILL_FRAME
	end
	f50_arg0.image:SetValue( f50_arg1, f50_local0 )
	f50_arg0.imageFormat:SetValue( f50_arg1, f50_local1 )
end

local f0_local10 = function ( f51_arg0, f51_arg1, f51_arg2, f51_arg3 )
	local f51_local0, f51_local1 = f51_arg3:match( "([%w_]+)(_%d+%%)$" )
	local f51_local2 = nil
	if f51_local0 then
		local f51_local3 = QuarterMasterUtils.FindSKUIDByType( DwDataUtils.GetCachedData[DwDataUtils.Vendor.Quartermaster]( f51_arg1 ), f51_local0 )
		if f51_local3 then
			local f51_local4 = Engine.Inventory_GetSKUInfo( f51_local3 )
			if f51_local4 then
				f51_local2 = f51_local4.prices[1].value
			end
		end
	end
	f51_arg0.cost:SetValue( f51_arg1, f51_arg2.prices[1].value )
	f51_arg0.costCurrency:SetValue( f51_arg1, f51_arg2.prices[1].currency )
	f51_arg0.originalCost:SetValue( f51_arg1, f51_local2 or 0 )
end

local f0_local11 = function ( f52_arg0, f52_arg1, f52_arg2 )
	local f52_local0 = ""
	local f52_local1 = 0
	if f52_arg2 then
		local f52_local2 = LUI.Split( f52_arg2, "|" )
		f52_local0 = f52_local2[1]
		f52_local1 = tonumber( f52_local2[2] )
	end
	f52_arg0.limiterGuid:SetValue( f52_arg1, f52_local0 )
	f52_arg0.purchaseLimit:SetValue( f52_arg1, f52_local1 )
end

QuarterMasterUtils.PopulateSkuDetails = function ( f53_arg0, f53_arg1, f53_arg2 )
	local f53_local0 = f0_local6( f53_arg2.skuData )
	f0_local8( f53_arg0, f53_arg1, f53_arg2, f53_local0[QuarterMasterUtils.SKUDataKeys.Flags] )
	f0_local9( f53_arg0, f53_arg1, f53_local0[QuarterMasterUtils.SKUDataKeys.TAG], f53_local0[QuarterMasterUtils.SKUDataKeys.IMAGE_OVERRIDE], f53_local0[QuarterMasterUtils.SKUDataKeys.FLAGS] )
	f0_local10( f53_arg0, f53_arg1, f53_arg2, f53_local0[QuarterMasterUtils.SKUDataKeys.TAG] )
	f0_local11( f53_arg0, f53_arg1, f53_local0[QuarterMasterUtils.SKUDataKeys.LIMITER_DATA] )
	f0_local7( f53_arg0, f53_arg1, f53_arg2, f53_local0[QuarterMasterUtils.SKUDataKeys.TAG], f53_local0[QuarterMasterUtils.SKUDataKeys.FLAGS] )
end

QuarterMasterUtils.BeginQMVendor = function ( f54_arg0, f54_arg1 )
	if CONDITIONS.IsZombiesMode() then
		Character_Scene.BeginVendor( f54_arg0, "Zombie" )
	elseif f54_arg1 then
		Character_Scene.BeginVendor( f54_arg0, "MaleQm" )
	else
		Character_Scene.BeginVendor( f54_arg0, "Quartermaster" )
	end
end

QuarterMasterUtils.TabPages = nil
local f0_local12 = function ()
	if QuarterMasterUtils.TabPages then
		return 
	end
	QuarterMasterUtils.TabPages = {
		{
			name = "MENU_CONTRACTS",
			action = function ( f56_arg0, f56_arg1 )
				if f56_arg0.id ~= "contracts_menu" and f56_arg0.id ~= "zm_contracts_menu" then
					if Engine.IsZombiesMode() then
						LUI.FlowManager.RequestAddMenu( f56_arg0, "zm_contracts_menu", true, f56_arg1, true, {
							showNavBar = true
						} )
					else
						Character_Scene.curVendor.enterSubMenu = true
						Character_Scene.curVendor.changeTab = true
						LUI.FlowManager.RequestAddMenu( f56_arg0, "contracts_menu", true, f56_arg1, true, {
							hasVendorMenu = true,
							showNavBar = true
						} )
					end
				end
			end
		},
		{
			name = "LUA_MENU_MTX6_DEALS",
			action = function ( f57_arg0, f57_arg1 )
				if f57_arg0.id ~= "quartermaster_menu" and f57_arg0.id ~= "quartermaster_zm_menu" then
					if Engine.IsZombiesMode() then
						LUI.FlowManager.RequestAddMenu( f57_arg0, "quartermaster_zm_menu", true, f57_arg1, true )
					else
						Character_Scene.curVendor.enterSubMenu = true
						Character_Scene.curVendor.changeTab = true
						LUI.FlowManager.RequestAddMenu( f57_arg0, "quartermaster_menu", true, f57_arg1, true, {
							male = Engine.GetDvarBool( "spv_hub_special_qm" )
						} )
					end
				end
			end
		}
	}
	if CONDITIONS.IsCWLPacksEnabled() and not CONDITIONS.IsZombiesMode() then
		table.insert( QuarterMasterUtils.TabPages, {
			name = "LUA_MENU_MTX6_CWL_STORE",
			action = function ( f58_arg0, f58_arg1 )
				if f58_arg0.id ~= "quartermaster_cwl_menu" then
					Character_Scene.curVendor.enterSubMenu = true
					Character_Scene.curVendor.changeTab = true
					LUI.FlowManager.RequestAddMenu( f58_arg0, "quartermaster_cwl_menu", true, f58_arg1, true )
				end
			end
		} )
	end
end

QuarterMasterUtils.PopulateQMNavTabs = function ( f59_arg0, f59_arg1, f59_arg2 )
	f0_local12()
	local f59_local0 = function ( f60_arg0, f60_arg1, f60_arg2 )
		f60_arg0.name:SetValue( f60_arg2, Engine.Localize( QuarterMasterUtils.TabPages[f60_arg1 + 1].name ) )
		f60_arg0.index:SetValue( f60_arg2, f60_arg1 )
	end
	
	local f59_local1 = f59_arg0.id
	local f59_local2 = 1
	if f59_local1 == "contracts_menu" or f59_local1 == "zm_contracts_menu" then
		f59_local2 = 0
	elseif f59_local1 == "quartermaster_cwl_menu" then
		f59_local2 = 2
	end
	f59_arg2:Populate( #QuarterMasterUtils.TabPages, f59_local0, f59_local2, f59_arg1 )
end

QuarterMasterUtils.HandleTabChange = function ( f61_arg0, f61_arg1, f61_arg2 )
	QuarterMasterUtils.TabPages[f61_arg2 + 1].action( f61_arg0, f61_arg1 )
end

