# Quartermaster SKU data format and the buildItems assert (Fable, 2026-09-13)

Branch `feat/39-hq-economy`: `b60ffed` (LUAFILE dump commands), plus the SKU data fix.
Evidence: `build/research/luafiles/` (294 dumped `*.luac` + `*.strings.txt`) and
`build/research/luafiles/dec/` (the same files decompiled).

## Tooling

`dumpluafile <asset name> [outfile]` and `dumpluafiles <substring>` (cap 200) in
`src/client/component/command.cpp` write LUAFILE buffers to `<game>\s2x\dump\lua`.
Asset names are lowercase paths, `ui/s2/...`, `ui/lui/...`, `ui/utility/mp/...`;
`listassetpool 69` lists all 1808 of them. Dumped here: `quartermaster` (26),
`vendor` (3), `mail` (4), `sku` (11), `store` (11), `hub` (32), `menubuilder` (2),
`inventory` (6), `officer` (10), `collection` (26), `util` (83), `ui/lui/` (119).

Decompiler: `JariKCoding/CoDLuaDecompiler` 2.4.2, unpacked at
`D:\tools\CoDLuaDecompiler` (single .NET exe, takes a file or a directory of
extension-less copies). It handles this game's Havok Script cleanly.

## The SKU data string

`Engine.Inventory_GetSKUInfoSKUData(id)` returns one string that
`QuarterMasterUtils.FindSkuDataByType(data, key)` parses
(`ui_utility_mp_quartermaster_utils.dec.lua`):

```lua
QuarterMasterUtils.FindSkuDataByType = function(data, key)
    local record, rest = LUI.SingleSplit(data, ";")
    while record do
        local k, v = LUI.SingleSplit(record, ":")
        if k == key then return v end
        record, rest = LUI.SingleSplit(rest, ";")
    end
    return nil
end
```

so the format is `key:value;key:value;...`, native capacity 64 bytes. Keys
(`QuarterMasterUtils.SKUDataKeys`):

| key | name | value |
|---|---|---|
| `t` | TAG | `SupplyDropTypeTag`/`SkuTags` token: `MP`, `ZM`, `MP_H`, `ZM_H`, `MP_25%`, `MP_EPIC`, `MP_X20`, ... |
| `i` | IMAGE_OVERRIDE | image name |
| `f` | FLAGS | concatenated `SKUFlags` letters: `s` sale, `t` time remaining, `q` personal quantity remaining, `f` image fills button, `i` icon type, `p` image index override |
| `c` | CONTRACT_ID_CONTRACT | numeric AE challenge id (`tonumber`) |
| `C` | CONTRACT_ID_QUARTERMASTER | numeric AE challenge id |
| `l` | LIMITER_DATA | `"<itemGuid>\|<maxQuantity>"`, `SkuLimitReached` compares against `Inventory_GetItemQuantity` |
| `u` | UNLOCK_GUID | item guid; the SKU is locked while its quantity is 0 |
| `s` | SPECIAL_ICONS | icon list |
| `e` | EXPERIMENT_COHORT | `"<hash>\|<range>"` for `HashRangeUtils.IsPlayerInRange` |

Nothing in the vendor scripts reads rarity, collection or category out of this
string; collection SKUs need no SKU data at all.

Related: `promotionalText` is *not* free text - `QuarterMasterUtils.ProcessSkuInfo`
does `LUI.Split(promotionalText, ";")` and takes `[1]` as `name` and `[2]` as
`description`.

## The assert

`LUI.MenuBuilder.buildItems()` itself only asserts with messages ("No type in
itemDef!", "Unknown type for element definition: "). The bare
`assertion failed` comes from the Quartermaster menu's `PreLoadFunc`
(`ui_s2_quartermaster_menu_uc.dec.lua`), which runs inside
`BuildRegisteredType` -> `buildItems`:

```
PreLoadFunc -> QuarterMasterUtils.storeSKUInfo(menu, controller)
  -> GetAvailableSkuIDList(controller, Inventory_GetAllSKUIDs(SKUType.Quartermaster = 100))
  -> local helper: for _, entry in ipairs(list) do local id = entry.id; assert(id) ...
```

`GetAvailableSkuIDList` appends up to four optional scheduled specials
(`SPECIAL_1A..4E`, each gated by `Engine.IsCurrentTimeWithinRange` and a
`GetDvarString(...) ~= "none"`, so all absent here) and then **unconditionally**:

```lua
local mp = GetActiveAndAvailableScheduledEvent(..., EventScheduleData.SALE_MP)
   or { id = FindSKUIDByType(skus, SupplyDropTypeTag.ASD_MP) }    -- tag "MP"
assert(mp)                       -- passes: the table is truthy even with id = nil
local zm = ... SupplyDropTypeTag.ASD_ZOMBIE ...                   -- tag "ZM"
assert(zm)
```

`FindSKUIDByType` scans the SKU id list and returns the first id whose SKU data
has `t` equal to the tag. With no tagged SKU both ids are `nil`, and the loop's
`assert(entry.id)` fails on the first entry - before any
`Inventory_GetSKUInfo`/`Inventory_GetSKUInfoItems` call, which is exactly what the
in-game trace showed. `CountAvailableSKUs` returns `2 + specials`, matching the
`quartermaster_mp_2_sku` .. `quartermaster_mp_6_sku` widgets and
`CONDITION_HasExactNumSkus`.

## Fix

`hq_marketplace::vendor_skus` leads `catalog()` with two SKUs, GUIDs 2
(`sd_mp_rare`) and 6 (`sd_zombie_rare`) from `mp/supplyDropTypes.csv` column f5,
data `t:MP` and `t:ZM`, 1000 Armory Credits each. They lead because only the
first 400 catalog entries reach the native SKU cache and `FindSKUIDByType`
returns the first match. `sku::data` is written both by the Demonware SKU record
(`hq_vendor::catalog_result`) and by the synthesized native cache record
(`hq_native::sku_lookup`, +0x29C - the field the Lua actually reads, since that
hook intercepts every lookup for a catalog id). `find_sku` resolves the drops,
purchases of them stack (consumables), and `open_supply_drop` accepts
`sd_zombie_rare`.

Gap closed (see `payroll-banner.md`): `Engine.Inventory_GetSKUInfo` is binding
`0x11FF90` (`ghidra/decomp-slice5/11FF90.c`) and it emits `promotionalText` from
cache slot **+0x25C** and `skuData` from **+0x29C**, so each is a 64-byte field.
`hq_native::sku_lookup` now writes both, and the two vendor drops carry the game's
own `QuarterMasterUtils.SupplyDropPromoText` name keys `LUA_MENU_RARE_SUPPLY_DROP`
and `LUA_MENU_RARE_ZOMBIE_SUPPLY_DROP`; no shipped key describes those drops so the
`;description` half is omitted and `ProcessSkuInfo` stores `""`. The rest of the
slot, from the same binding: `+0xC maxQuantity`, `+0x30 + i*0x38` item id /
`+0x34 + i*0x38` quantity, `+0x240 productID`, `+0x244 numItems`,
`+0x248 remainingQuantity`, `+0x24C + i*8` price currency / `+0x250 + i*8` price
value, `+0x2DC saleEndTime`, `+0x2E0 soldOut`, `+0x2E1 numPrices`.

## Mail officer / "Unable to get payroll" (follow-up)

`ui_s2_mail_officer_menu_uc.dec.lua`: the collect callback

1. `assert(scoped.mailOfficer.canCollectPayroll)` - set by an earlier
   `Engine.AE_GetPlayerAchievementInfo(controller, Rank.GetPayrollAchievement(controller))`
   (id 345): collectable when `timeSinceLastCompletion >= 4 h` or
   `fullfilledTimes <= 0`; `reward.currencyAmount` drives the "200"/"300" label;
2. `AchievementEngineUtils.AE_SendComplexGameEvent(controller, AEComplexEvents.GrabPayroll, {1, masterPrestige})`.
   **False -> the banner immediately** (`player_interact_notification` data `{36, ""}`).
3. True -> the same notification is queued with `delayShow = 5000` and cancelled
   only by an `achievementEngine` event with
   `eventType == AEEventType.CompletionUpdate`,
   `kind == GameChallengeType.GameAchievementKind_AlwaysOn`,
   `ID == Rank.GetPayrollAchievement(controller)` and `success == true`.

So the banner means either the complex game event was rejected, or no AlwaysOn
CompletionUpdate for achievement 345 reached the UI within 5 s of the pickup.
Resolved in `payroll-banner.md`: the event is accepted (`-> true` in the owner's
trace) and the push handler is `0x13C480`; the completion was simply not published
on a pickup that fell inside an already settled four-hour period.
