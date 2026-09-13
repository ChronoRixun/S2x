# The "Unable to get payroll at this time" banner (Fable, 2026-09-13)

Branch `feat/39-hq-economy`, on top of `87b17f4`. Evidence: the decompiled LUI
(`build/research/luafiles/dec/`), the Ghidra decompiles under
`build/research/ghidra/decomp-slice2|slice5`, and the owner's console log
(`<game>\s2x\logs\console.log`, lines 100797-116512).

## The Lua condition, quoted

`build/research/luafiles/dec/ui_s2_mail_officer_menu_uc.dec.lua`. The collect
callback registers a handler and sends the complex game event:

```lua
f6_arg0:registerEventHandler( "achievementEngine", function ( element, event )
    event.controller = f6_arg1
    f0_local7( element, event )
end )
...
if AchievementEngineUtils.AE_SendComplexGameEvent( f6_arg1, AEComplexEvents.GrabPayroll, { 1, f6_local1 } ) then
    ACTIONS.SetInputEnabled( f6_arg0, false )
    ACTIONS.Hide( f6_arg0.ButtonHelperBar )
    ACTIONS.AnimateSequence( f6_arg0.Payroll, "Loading" )
    f6_arg0:dispatchEventToRoot( {
        name = "player_interact_notification",
        data = { 36, "" },
        menu = f6_arg0,
        delayShow = 5000,
        callback = f0_local8
    } )
else
    f6_arg0:dispatchEventToRoot( { name = "player_interact_notification", data = { 36, "" } } )
end
```

and the only thing that cancels the armed notification is

```lua
local f0_local7 = function ( f4_arg0, f4_arg1 )
    f4_arg0:dispatchEventToRoot( { name = "player_interact_notification_cancel" } )
    if f4_arg1.eventType == AEEventType.CompletionUpdate and f4_arg1.kind == GameChallengeType.GameAchievementKind_AlwaysOn and f4_arg1.ID == Rank.GetPayrollAchievement( f4_arg1.controller ) then
        if f4_arg1.success == true then
            f0_local6( f4_arg0, f4_arg1.controller, f4_arg1.success )
```

with `AEEventType.CompletionUpdate = 0` and
`GameChallengeType.GameAchievementKind_AlwaysOn = 5`
(`ui_utility_mp_achievementengineutils.dec.lua`), and
`Rank.GetPayrollAchievement` (`ui_lui_common_menus_rankutils.dec.lua`) returning
`HardcodedAchievements.PayrollReceived = 345` or, for a master prestige player,
`PayrollReceivedMasterPrestige = 757`. `AEComplexEvents.GrabPayroll` is
`{event = 18, key = {1, 2}, value = {1, 0}}`, sent as
`Engine.Reward_GameEventComplexNotification(controller, 2, 18, 1, 1, 2, masterPrestige)`.

Note `f0_local6(element, controller, true)`: it sets
`secondsUntilNextPayroll = 14400` and `canCollectPayroll = false` from the event
alone, so the countdown does not depend on a follow-up
`AE_GetPlayerAchievementInfo`.

## The native producer

`0x13C480` (`build/research/ghidra/decomp-slice5/13C480.c`) - the achievement
**push** handler, distinct from `AE_ProcessResponse` task replies. Given a JSON
document in the AE string object it:

1. requires `name` and resolves it to an achievement ID with `0x139D50`
   (`dw/dwGameChallenges.csv` column 1: `345,payroll_officer,5,18,,Gold` and
   `757,payroll_officer_masterprestige,...`); `-1` returns early;
2. requires `kind` (int), `reason` (string), `status` (string, mapper `0x139C10`),
   `progress` (int) and `type` in {`ACHIEVEMENT`, `CHALLENGE`};
3. maps `reason` to the Lua event type: `inProgress` -> 1, `claimable` -> 6,
   `completed` -> **0 = CompletionUpdate**, `expired` -> 0 with `success = 0`;
   any other reason leaves it at -1 and **no event is raised**;
4. merges the record into the native user achievement table (`0x60A4090 + c*0x13890`);
5. requires a `triggers` array - the whole event block sits inside that test - and,
   for a `GRANT_CURRENCY`/`SET_CURRENCY_BALANCE` trigger, requires
   `inventory.currencies`, which it feeds to the currency push parser `0x27C480`
   (`currency_id`, `balance_before`, `balance_delta`);
6. finally raises, through the same LUI event builder the scheduled-fetch callback
   `0x13C220` uses:
   `achievementEngine { eventType, success, challengeName, ID, kind, itemsReceived,
   currenciesReceived, dispatchChildren = 1 }`.

Key names verified by reading the string constants at the image offsets the
decompile references (`0xB34B48 name`, `0xB403F8 kind`, `0xB407E4 ID`,
`0xB407FC type`, `0xB406A8 achievementEngine`, `0xB40840 success`,
`0xB406C0 eventType`, `0xB350E0 dispatchChildren`).

## Why the banner appeared

The complex game event *was* accepted and the JSON push *was* the right shape.
From the owner's log:

```
[LUI] [LUI flow] RequestAddMenu(mail_officer_menu)
[LUI] [LUI trace] Engine.Reward_GameEventComplexNotification(0, 2, 18, 1, 1, 2, 0) -> true
[HQ event] picked_up_payroll (picked_up_payroll), timestamp 1789275619000000, 2 parameters
```

`-> true`, so the banner is always the 5 s delayed one, and no
`[HQ payroll] delivered ...` line follows any of those pickups.

`achievement_engine::submit_event` built the push only `if (after != before)` -
i.e. only when the Armory Credit balance actually moved. `hq_payroll::settle`
grants once per UTC four-hour period, so:

* the first pickup of a period pushed the completion (run-25248, timestamp
  1789272049, `hq_payroll_native_push_25248_78.bin`);
* every later pickup **in the same period** - 1789275346, 1789275419, 1789275619,
  1789275820, 1789278765, all inside period 124255 - settled to "already paid",
  published nothing, and the kiosk banner fired 5 s later.

The kiosk keeps offering the pickup because nothing had updated the native user
achievement record for 345 in that session, so `canCollectPayroll` stayed true and
every further click banners. A wrong kind/ID/CompletionUpdate flag was **not** the
cause.

## The fix

`src/client/game/demonware/hq_payroll.hpp` - `settle` now returns an outcome
(`rejected` / `stale` / `granted` / `replayed`) instead of a bool.

`src/client/game/demonware/achievement_engine.cpp` - the native payroll branch
publishes a completion push for **every** accepted pickup in the current period,
not only the paying one:

* `granted` - the record plus a `SET_CURRENCY_BALANCE` trigger with the real delta;
* `replayed` - the same record with `balance_delta = 0` (the grant stays once per
  period; only the animation and the CompletionUpdate repeat);
* `stale` (a batch from another period) - acknowledged, nothing published;
* `rejected` - the bdReward task fails, as before.

The published copy is normalised to `status: "finished"` with `progress = target`,
and is named `payroll_officer_masterprestige` when the event's selector `2` is 1,
so the ID the native handler resolves matches `Rank.GetPayrollAchievement` for a
master prestige player. The store keeps a single `payroll_officer` entry either way.

`src/client/component/hq_native.cpp` - the queued push carries a summary, and
delivery now logs what went out.

Also closed here (the `quartermaster-skudata.md` "known gap"): the promotional-text
offset. `Inventory_GetSKUInfo` (binding `0x11FF90`,
`build/research/ghidra/decomp-slice5/11FF90.c`) emits `promotionalText` from cache
slot **+0x25C** and `skuData` from **+0x29C**, so each is a 64-byte field.
`hq_native::sku_lookup` now writes both, and the two vendor drops carry the game's
own `QuarterMasterUtils.SupplyDropPromoText` name keys
(`LUA_MENU_RARE_SUPPLY_DROP`, `LUA_MENU_RARE_ZOMBIE_SUPPLY_DROP`). No shipped
localization key describes those drops, so the `;description` half is left off:
`LUI.Split` returns one element and `ProcessSkuInfo` stores `""`. Full slot map
recovered from `0x11FF90`: `+0xC maxQuantity`, `+0x30 + i*0x38` item id /
`+0x34 + i*0x38` quantity, `+0x240 productID`, `+0x244 numItems`,
`+0x248 remainingQuantity`, `+0x24C + i*8` price currency / `+0x250 + i*8` price
value, `+0x25C promotionalText`, `+0x29C skuData`, `+0x2DC saleEndTime`,
`+0x2E0 soldOut`, `+0x2E1 numPrices`.

## Harness

`build/research/hq-tests` (PASS). New coverage:

* a replayed pickup queues a push whose record is `payroll_officer` / `CHALLENGE` /
  `completed` / `finished` / kind 5 with a `SET_CURRENCY_BALANCE` trigger on
  currency 6 and `balance_delta == 0`;
* the alias event `18` republishes with a zero delta and cannot pay twice;
* a master prestige pickup publishes `payroll_officer_masterprestige` (757) without
  forking the stored record;
* a batch from an earlier period is acknowledged and publishes nothing;
* `settle` outcomes for first pickup / duplicate batch / stale batch / next period /
  invalid timestamp;
* both vendor SKU strings fit the 64-byte native fields and carry the shipped keys.

## In-game verification

1. Play > Headquarters > Mail officer (Headquarters Post), collect the payroll.
   The console must show, within ~100 ms of `[HQ event] picked_up_payroll`:

   ```
   [HQ payroll] delivered completion push: payroll_officer kind 5 status finished reason completed, currency 6 200 -> 400 (settled)
   ```

   and **no** "Unable to get payroll at this time" banner; the Payroll tile plays
   its collected animation and the 4 h countdown starts.
2. Click collect again inside the same four-hour window. Expect

   ```
   [HQ payroll] delivered completion push: payroll_officer kind 5 status finished reason completed, currency 6 400 -> 400 (replayed, already settled this period)
   ```

   again no banner, and no change in the hammer counter.
3. `hqwallet` and the HUD hammer counter show currency 6 at the new balance after
   step 1 (`SET_CURRENCY_BALANCE` -> `0x27C480`, plus the 100 ms `sync_wallet` loop).
4. Quartermaster: the two supply drop tiles should now show a name instead of an
   empty label (the description stays blank by design).

If the banner still appears after a logged `delivered completion push`, the next
target is `0x13C480`'s early returns - hook it and log which member lookup fails.
