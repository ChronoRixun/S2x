# Payroll state, the payroll banner and the empty Contracts tab (Fable, 2026-09-13)

Branch `feat/39-hq-economy`, on top of `0b846ba`. Commits `32d4bb3`, `ef4eb50`,
`b30d990`. Evidence: the decompiled LUI (`build/research/luafiles/dec/`), new
Ghidra decompiles in `build/research/ghidra/decomp-payroll/`, the owner's console
log on build `c62f0f7` and the Demonware dumps for pid 35824.

New decompiles (all produced with the recipe in `ae-ghidra-findings.md`, JDK 21 on
PATH, project `S2xFull`): `1213B0` `AE_GetPlayerAchievementInfo`, `13A605`
(function `0x13A570`, the user/achievement record parser), `13E9A6`
(`get_user_achievements` handler), `13F216`, `142660`, `13EC88`, `13AA96`
(function `0x13A910`, the scheduled record parser), `121B0C`
(`AE_GetScheduledChallenges`), `122108` (`AE_GetPlayerActiveChallenges`),
`139C10`, `139D50`, `13AE50`, `4A0D90`, `7897A0`.

## The record layout the whole Achievement Engine shares

`0x13A570` parses one JSON achievement into a 0x40-byte record; `13E9A6`,
`13F216`, `142660` and the push handler `0x13C480` all merge that record into the
per-controller user achievement table at `0x60A4090 + controller * 0x13890`
(1000 records of 0x40, "fetched" byte at `0x60A4080`).

| offset | JSON key | read back by |
|---|---|---|
| +0x00 | `requiresClaim` | |
| +0x04 | `usageTimeTarget` | `timeLimit` |
| +0x08 | `kind` | `kind` |
| +0x0C | `name` resolved by `0x139D50` | `ID` |
| +0x10 | `progressTarget` / `globalProgressTarget` | `target` |
| +0x18 | `expirationTimestamp` | `expirationTimestamp` |
| +0x20 | `successRewards` (pointer into the reward array) | `reward` |
| +0x28 | `progress` (u16) | `progress` |
| +0x2C | `fulfilledTimes` / `num_times` / `completionCount` | **`fullfilledTimes`** |
| +0x30 | `completionTimestamp`, `time`, **or `eventEndTimestamp`/1000** | `lastCompletionTime`, `timeSinceLastCompletion` |
| +0x38 | `status` mapped by `0x139C10` | `status` |
| +0x3C | `usageTimeRemaining` | `timeLeft` |

`0x139C10` only knows `inactive` -> 1, `inProgress` -> 2, `claimable` -> 3,
`finished` -> 4. The *scheduled* parser `0x13A910` is a different function with a
different layout (status at +0x28) and its own vocabulary `available` -> 1,
`in_progress` -> 2, `claimable` -> 3, `completed` -> 4; both of our vocabularies
are therefore correct where they are used.

## 1. "PAYROLL 200" available with no countdown

### The Lua condition, quoted

`build/research/luafiles/dec/ui_s2_mail_officer_menu_uc.dec.lua`, with
`f0_local1 = 14400`:

```lua
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
```

So exactly two record fields decide it. `AE_GetPlayerAchievementInfo` (`0x1213B0`)
publishes `fullfilledTimes` straight from record+0x2C and computes

```c
uVar14 = FUN_7ff7a325f700();                       /* now, epoch seconds        */
lVar3   = *(longlong *)(&DAT_7ff7a92340c0 + lVar16); /* record+0x30              */
FUN_7ff7a325c810("timeSinceLastCompletion", format(uVar14 - lVar3), ...);
```

`requiresClaim`, `activationTimestamp`, `expirationTimestamp`,
`usageTimeRemaining`, `progress` and `status` play no part in the decision; the
`reward.currencyAmount` (record+0x20) only paints the "200"/"300" label.

### Root cause

`serialize()` emitted `eventEndTimestamp` immediately after `completionTimestamp`,
and `0x13A570` maps `eventEndTimestamp` to **record+0x30 divided by 1000**, i.e.
to the last-completion field, not to the expiration at +0x18:

```c
iVar5 = FUN_7ff7a3b94f40(uVar8,"eventEndTimestamp");
if (iVar5 == 0) {
  uVar9 = FUN_7ff7a340f7b0(param_1,lVar7);
  ...
  *(ulonglong *)(param_3 + 0x30) = (uVar9 - lVar10 >> 1) + lVar10 >> 9;   /* /1000 */
}
```

The owner's reply (`hq_injected_ae_response_35824_93.bin`) carried
`"completionTimestamp":1789272050 ... "eventEndTimestamp":1789344000`, so the
record's completion time became `1789344000/1000 = 1789344` (January 1970) and
`timeSinceLastCompletion` came back as ~1.79e9 s. `14400 <= 1.79e9` is always
true, so the kiosk always chose the collectable branch. Earlier builds showed the
countdown because they did not publish the key yet.

Nothing in the image reads `eventEndTimestamp` as an expiration: the only two
references are `0x13A570` and `0x13EC20` (an id-collecting parser that discards
the value), and the scheduled cache field `aecache` reports is filled from
`expirationTimestamp`.

### Fix

`src/client/game/demonware/achievement_engine.cpp:60-74` (commit `32d4bb3`) - the
`eventEndTimestamp` member is gone; `expirationTimestamp` alone is published.

## 2. "Unable to get payroll at this time" after a delivered push

### The Lua condition, quoted

Same file. The collect callback registers the handler, sends
`AEComplexEvents.GrabPayroll` and arms the notification with `delayShow = 5000`;
the only thing that cancels it is

```lua
local f0_local7 = function ( f4_arg0, f4_arg1 )
    f4_arg0:dispatchEventToRoot( {
        name = "player_interact_notification_cancel"
    } )
    if f4_arg1.eventType == AEEventType.CompletionUpdate and f4_arg1.kind == GameChallengeType.GameAchievementKind_AlwaysOn and f4_arg1.ID == Rank.GetPayrollAchievement( f4_arg1.controller ) then
        if f4_arg1.success == true then
            f0_local6( f4_arg0, f4_arg1.controller, f4_arg1.success )
```

(`AEEventType.CompletionUpdate = 0`, `GameAchievementKind_AlwaysOn = 5`,
`Rank.GetPayrollAchievement` = 345, or 757 at master prestige). Note the cancel is
unconditional at the top: *any* `achievementEngine` event reaching the menu clears
the banner, so the banner means no event arrived at all within 5 s.

### Root cause: the push was fine, the call was not

The JSON we handed the native handler (dump `hq_payroll_native_push_35824_84.bin`)
carries every member `0x13C480` requires - `name` `payroll_officer` (resolves to
345 through `0x139D50` and `dw/dwGameChallenges.csv` column 1), `kind` 5 as an
**int**, `reason` `completed` (-> `eventType` 0), `status` `finished` (-> 4),
`progress` 1, `type` `CHALLENGE`, and a `triggers` array whose
`SET_CURRENCY_BALANCE` entry carries `inventory.currencies`. `success` is not a
member of the push at all: `0x13C480` synthesises it (`local_6467 = 1`, cleared
only for `reason == "expired"`).

`hq_native::sync_wallet` called `0x13C480(0, bridge)`. Its first parameter is not
a controller index - the retail caller `0x8327B0` passes `*(void**)(task + 0x30)`,
the Achievement Engine **user context pointer** - and `0x13C480` maps it back with

```c
00789870  movsxd rax, ecx           ; 0x789870: return (&table)[controller * 0xd]
007897a0  test rcx, rcx             ; 0x7897A0: context pointer -> controller
007897a3  je 0x7897c5               ;   null -> -1
```

With `0` the context lookup `0x7897A0` returned **-1**, so
`0x4A0D90(-1, &instance)` took its `*param_2 = -1; return 0;` path and the
`achievementEngine` event was never raised - the banner. The same -1 also indexed
the user achievement table at `base - 0x13890`, writing the merged record 0x13890
bytes below it.

### Fix

`src/client/game/symbols.hpp:369-375` adds
`AE_GetUserContext{ 0x789870 }`; `src/client/component/hq_native.cpp:96-127`
(commit `ef4eb50`) resolves controller 0's context, keeps the notification queued
for the next 100 ms tick while it is null, passes it to `0x13C480`, and logs the
complete push JSON plus the controller the context resolved to.
`hq_native.cpp:551-599` adds `hqpayrollstate`, which prints the native record for
345/757 exactly as the kiosk reads it.

## 3. Empty Contracts tab

### What the decompiled scripts do say

The Contracts nav tab is not a SKU list of its own; it pushes a menu
(`ui_utility_mp_quartermaster_utils.dec.lua`):

```lua
{
    name = "MENU_CONTRACTS",
    action = function ( f56_arg0, f56_arg1 )
        if f56_arg0.id ~= "contracts_menu" and f56_arg0.id ~= "zm_contracts_menu" then
            ...
            LUI.FlowManager.RequestAddMenu( f56_arg0, "contracts_menu", true, f56_arg1, true, {
```

`ui/s2/contracts_menu` and `ui/s2/contracts_menu_uc` exist in LUAFILE pool 69 (they
appear in the owner's log) but are **not** among the 294 dumped scripts, so the
tab's own filter cannot be quoted yet. What the dumped scripts do fix is where its
data has to come from:

```lua
QuarterMasterUtils.GetContractCurrencies = function ( f7_arg0, f7_arg1 )
    for f7_local8, f7_local9 in ipairs( f7_arg1 ) do
        local f7_local5 = QuarterMasterUtils.FindSkuDataByType( Engine.Inventory_GetSKUInfoSKUData( f7_local9 ), QuarterMasterUtils.SKUDataKeys.CONTRACT_ID_CONTRACT )
        if f7_local5 then
            f7_local5 = tonumber( f7_local5 )
            QuarterMasterUtils.ClearCachedSKUInfoItems()
            local f7_local6, f7_local7 = Engine.Inventory_GetSKUInfoItems( f7_local9, QuarterMasterUtils.CachedSKUInfoItems )
            if f7_local7 >= 1 and 0 < Engine.Inventory_GetItemQuantity( f7_arg0, f7_local6[1].guid ) then
```

called from the Quartermaster `PreLoadFunc` as
`GetContractCurrencies( controller, DwDataUtils.GetCachedData[DwDataUtils.Vendor.Quartermaster]( controller ) )`,
and `DwDataUtils` only ever fetches one SKU list:

```lua
DwDataUtils._fetchSKUData = function ( f8_arg0 )
    Engine.Inventory_FetchAllSKUs( f8_arg0, SKUType.Quartermaster )
...
DwDataUtils._updateSKUData = function ( f18_arg0 )
    GameSKUList._cachedSKUs = Engine.Inventory_GetAllSKUIDs( SKUType.Quartermaster )
```

`SKUType.Contracts = 201` is defined in `ui/utility/mp/inventoryutils.lua` and
never used. The contract id belongs in the SKU data string (`c` =
CONTRACT_ID_CONTRACT for the activation id, `C` = CONTRACT_ID_QUARTERMASTER for the
"VIEW CONTRACT" jump and `AchievementEngineUtils.IsOrderAvailable(..., Vendor.Operation, GameChallengeGroup.Scheduled)`),
never in the type.

### What was wrong

* `hq_native::sku_lookup` wrote `entry->type` into the native cache record at
  +0x04, so the three contracts announced themselves as type 201 - not
  Quartermaster SKUs - even though the Demonware reply types them 100.
* The contract definitions carried **no reward**: `hq_economy::load_catalog` built
  them with a name, kind 4 and `usage_target`, nothing else, so their
  `successRewards` array was empty (see the owner's scheduled reply,
  `hq_injected_ae_response_35824_105.bin`). `AE_GetScheduledChallenges` (`0x121A00`)
  and `AE_GetPlayerActiveChallenges` (`0x121F40`) only publish the Lua `reward`
  table when the record's reward pointer at +0x20 is non-null, so the contracts
  reached the vendor with no reward at all while every daily and weekly had one.

Verified as *not* wrong, from the same run: contracts 33/34/35 are in the
scheduled cache as kind 4 with a future `expirationTimestamp`, `contract_mp_1`
activates (`activate_user_contract` -> ok) and comes back in the player-active
fetch as kind 4 `inProgress`, and the scheduled status vocabulary
(`available`/`in_progress`) is the one `0x13A910` accepts.

### Fix

`src/client/game/demonware/hq_marketplace.hpp:56-66` - the three contract SKUs are
type 100 (`SKUType.Quartermaster`), keeping `t:CONTRACT;c:<id>;C:<id>;i:s2_challenge_contracts`
and their 25/50/75 Armory Credit prices. `src/client/component/hq_economy.cpp:156-175`
- each contract now pays twice its SKU price (50/100/150 Armory Credits) as a
documented local policy. `src/client/component/hq_native.cpp:600-652` adds
`hqcontracts` (commit `b30d990`).

**Open**: `ui/s2/contracts_menu(_uc)` still has to be dumped
(`dumpluafiles contract`) before the tab's own list filter can be quoted. Run
`hqcontracts` and `aecache` from the same session as the walk.

## Harness

`build/research/hq-tests` (PASS). New/changed coverage:

* the completion push and the AlwaysOn fetch date the payroll claim with
  `completionTimestamp` and never carry `eventEndTimestamp`, and the fetched
  record leaves the kiosk inside the four-hour countdown
  (`now - completionTimestamp < 14400`, `fulfilledTimes > 0`);
* scheduled records and the owner-store orders carry `expirationTimestamp` and no
  `eventEndTimestamp`;
* the contract SKUs are typed 100 with matching `c`/`C` ids and prices;
* every offered contract carries a single `grant_currency` reward of 50/100/150 on
  currency 6 with `usageTimeTarget` 3600.

## In-game verification

Build `b30d990` is NOT installed and the game was not run (the owner was playing).
After the orchestrator installs:

1. `hqpayrollstate` in the console before touching Mail. Expect, within four hours
   of the last claim:

   ```
   [HQ payroll] user achievements fetched=1
   [HQ payroll] achievement 345 kind 5 status 4 progress 1/1 fullfilledTimes 1 lastCompletionTime <epoch seconds, today> timeSinceLastCompletion <under 14400> -> countdown <n>s
   ```

   `lastCompletionTime` must be a 2026 epoch value, never ~1789344.
2. Play > Headquarters > Mail officer. The Payroll tile must show
   "Credits Available In <h><m>" and the collect button must be disabled.
3. Wait out the period (or delete the `payroll:<period>` receipt from
   `players2/user/hq_economy.json` and `hqeconomy reload`), then collect. The
   console must show, within ~100 ms of `[HQ event] picked_up_payroll`:

   ```
   [HQ payroll] completion push json: {"name":"payroll_officer",...,"triggers":[...]}
   [HQ payroll] delivered completion push: payroll_officer kind 5 status finished reason completed, currency 6 300 -> 500 (settled) (context 000001... resolves to controller 0)
   ```

   `resolves to controller 0` is the check that matters - a `-1` there means the
   context table was not populated yet and the event went nowhere. No banner, the
   collected animation plays and the countdown starts.
4. Click collect again inside the same window: the same lines with
   `(replayed, already settled this period)`, still no banner, hammer counter
   unchanged.
5. Quartermaster > Contracts. Run `hqcontracts` and `aecache` in the same session
   and capture both: expect three `[HQ contracts] sku ... type=100 price=25|50|75
   currency=6 data="t:CONTRACT;c:33..."` lines and three
   `[HQ contracts] native kind 4 record ...` lines with a non-null reward pointer.
   Then `dumpluafiles contract` so the next pass can read the menu itself.
