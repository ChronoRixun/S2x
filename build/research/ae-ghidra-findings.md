# Achievement Engine: Ghidra findings (2026-09-12)

Source: the unpacked image dumped from the running MP client (`build/research/sections/*.bin`,
rebuilt as `build/research/ghidra/s2_mp64_ship_unpacked.exe`), decompiled headless with
`build/research/ghidra/scripts/DecompileAddrs.java` into `build/research/ghidra/decomp-quick/<offset>.c`.
Runtime image base of that dump: `0x7ff7a3190000`; every offset below is image-relative.

Ghidra lives in `D:\tools\ghidra_12.1.3_PUBLIC` with JDK `D:\tools\jdk-21.0.12.1+1`. Projects in
`D:\tools\ghidra-projects`: `S2x` (no auto-analysis, use for quick targeted decompiles) and `S2xFull`
(full auto-analysis, started 03:00, log `build/research/ghidra/full-analysis.log`). Targeted decompile:

```
set JAVA_HOME=D:\tools\jdk-21.0.12.1+1
D:\tools\ghidra_12.1.3_PUBLIC\support\analyzeHeadless.bat D:\tools\ghidra-projects S2x -process s2_mp64_ship_unpacked.exe -noanalysis -scriptPath D:\S2x\build\research\ghidra\scripts -postScript DecompileAddrs.java D:\S2x\build\research\ghidra\decomp-quick 13EF20 13A910
```

## AE_ProcessResponse (0x676A40)

`(controller, stringObject, group)`. Reads the JSON from the string object (`0xA3B850`), requires members
`Action`, `Status`, `ClientTx`; resolves Action -> task type(s) with `0x676860`; for each type finds the task
with `0x208270(group, controller, type)` (group table at `0x????`, 32 entries of 0x50), takes its task data
(`+0x28`), and only continues when the task's transaction (`data+0xD0`) equals `ClientTx` and `Status == "ok"`.
Then it dispatches by type. The string object passed in does not have to belong to the task (the user bridge
object works for every action).

| Action | type | handler |
|---|---|---|
| open_supply_drop | 0x7F | 0x2AF7A0 |
| start_mission | 0x2C | 0x2AF950 |
| end_mission | 0x30 | 0x2AF3A0 |
| reset_missions | 0x19 | (none in switch) |
| convert_parts_to_weapon | 0x82 | 0x2AF200 |
| get_scheduled_user_achievements | 0x8F | 0x13EF20 |
| pump_global_achievement_counters | 0x16 | 0x13A330 |
| activate_scheduled_user_achievement | 0x8D | 0x13E8B0 |
| activate_user_contract | 0x99 | 0x13E8B0 |
| deactivate_user_achievement | 0x8E | 0x13E950 |
| get_user_achievements | 0x84, 0x85 | 0x13E960 (user table), 0x13F190 |
| claim_achievement_reward | 0x9E | 0x13E910 |
| get_user_achievements_for_users | 0xA0 | 0x1425C0 |
| get_expired_user_achievements | 0x72 | 0x13EC20 |

## Scheduled challenges (Orders board)

- Issuer `0x1399C0(controller, tx)`; Lua wrapper `0x121760` builds a 32-byte tx buffer with
  `AE_GenerateTransactionId` (0x8390A0: 16 random/time bytes base64 -> 24 chars) and calls the issuer.
- Handler `0x13EF20(controller, doc, root)`: controller must be < 2. Reads `NextPeriodStartTimes` (object,
  keys "0".."13" -> uint64 table at `0x60CB1A0`), `ActivationLimits` (object, keys "0".."13" -> int table at
  `0x6039198`), then `Achievements` (array). Each element goes through the record parser `0x13A910`; accepted
  records are copied into the cache `0x5C94C60 + controller*0x1908`, 100 records of 0x30 bytes, the reward
  struct into the same block at `(300+i)*0x10`. Records with kind 13 additionally go to a 10-entry list
  (`0x5C983D0` ids, `0x5C98418` counters, count `0x5C98684`).
- Record parser `0x13A910` (record layout): `requiresClaim` -> +0 (bool), `usageTimeTarget` -> +4,
  `kind` -> +8, `name` -> +0xC = ID looked up in `dw/dwGameChallenges.csv` column 1 (`0x139D50`; -1 when
  unknown, and the record is then DROPPED), `progressTarget` or `globalProgressTarget` -> +0x10 (only when
  non-zero), `expirationTimestamp` -> +0x18 (uint64), `successRewards` -> reward struct pointer at +0x20,
  `status` -> +0x28: `available`=1, `in_progress`=2, `claimable`=3, `completed`=4, anything else 0,
  `globalCounterID` -> out parameter.
- Reward parser `0x13E610` (array of objects): `{"type":"grant_currency","currency":{"id":N,"amount":M}}`
  or `{"type":"grant_product","product":{"id":P,"currencies":[{"id","quantity"}],"items":[{"id","quantity"}]}}`.
  Lower-case type names. A reward with product 0 and (currency 0 or amount 0) is treated as none.
- Lua reader `0x121A00` (`Engine.AE_GetScheduledChallenges(controller)`): returns an empty table unless the
  ready byte `cache+0x1900` is 1; otherwise one entry per record with `ID`, `kind`, `target`, `status`,
  `timeLimit` (+4), `expirationTimestamp` (`%llu` string), and `reward = {productID, itemID, currencyID, currencyAmount}`.
- Task completion callbacks registered by the issuer: `0x13C220` success -> ready byte := 1 and LUI event
  `achievementEngine {success=1, eventType=4, transactionID}`; `0x13C120` failure -> ready byte := 0,
  `success=0`. Both then clear the task data (`0x206000`). The callbacks run when the bdReward task 4 reply
  completes; the JSON handler runs only when something calls AE_ProcessResponse. So: the cache must be
  filled (injection) before the success callback fires, and the bdReward reply must count as a success.

## User achievements (0x13E960 / parser 0x13A570)

Record (0x40 bytes in the per-controller table `0x60A4090 + c*0x13890`, 1000 entries, ID at +0xC):
`kind` +8, `name` -> ID +0xC, `requiresClaim` +0, `progress` +0x28 (u16), `fulfilledTimes`/`num_times`/
`completionCount` +0x2C, `eventEndTimestamp` (or `time`, `completionTimestamp`) +0x30, `progressTarget`/
`globalProgressTarget` +0x10, `status` +0x38 (mapped), `successRewards` out, `usageTimeTarget` +4,
`usageTimeRemaining` +0x3C, `activationTimestamp` or `expirationTimestamp` +0x18. `NextPageToken` is copied
into task data +0xF0 (max 0x20 bytes).

## Payroll

`dw/dwGameEvents.csv` event 18 `picked_up_payroll`; achievements `payroll_officer` (ID 345, kind 5) and
`payroll_officer_masterprestige` (757, kind 5). Killswitch dvar `spv_hub_payrollVendor_kswitch`. Observed
during a payroll attempt: bdReward task 11 (event batch) followed by task 5 `get_user_achievements_for_users`
(statuses [inProgress], kinds [1,8,2,9,3,10,4,11,7,12], the local user id, Limit 50) every few seconds; the
menu spins while our reply carries only unrelated finished kind-5 records.

## Slice 2: common delivery and action handlers

`0x8397E0(task)` starts a fully configured native task, marks it active and invokes
`0x839810` when online. Task layout relative to its argument: controller +4,
type +0xC, data +0x28, submit callback +0x30, success +0x38, failure +0x40.
The activation Lua wrapper 0x1222C0 installs its data/callbacks before calling it.
The MP bridge now hooks this shared submission function and processes AE responses
synchronously after submission returns, before the completion pump. It filters the
AE task types in the routing table. Controller 0 only, as before; Zombies does not
install this hook. The two old fetch detours are removed to avoid duplicate mutations.
The captured image contains detour jumps outside its mapped image at both fetch
entries, so their entry-point decompiles are unusable; see decomp-slice2 output.
Runtime timing of the new common hook still needs operator verification.

- Activate 0x13E8B0 optionally reads `DetailedInventory` (key at image offset B41510),
  forwarding entries to 0x27C1D0. That parser accepts item_id, collision_field,
  expiry_duration, item_quantity and mod_date_time. It does not read Achievements.
- Deactivate 0x13E950 is a no-op; completion callback owns the UI transition.
- Claim 0x13E910 compares ClientTx with active task data +0xD0 and returns a bool;
  it consumes no itemsReceived/currenciesReceived payload.
- For-users 0x1425C0 reads Achievements as an object keyed by decimal user ID,
  each value an array parsed by 0x13A570; NextPageToken is optional (32-byte cache).
  It only populates users already in the native pending-user table and caps each
  cache at 30 records. Additional native eligibility filtering can exclude payroll.
- Expired 0x13EC20 reads Achievements array, resolves each name with 0x139D50,
  and appends valid IDs to a maximum 100-entry expired list.
- Pump 0x13A330 reads CounterValues object: decimal counter IDs -> integer values.
- User status mapper 0x139C10 accepts exactly inactive=1, inProgress=2,
  claimable=3, finished=4; unknown=0. These differ from scheduled spellings.

Targeted output is under ghidra/decomp-slice2 and ghidra/decomp-quick. The weekly
UI table copy is empty (zero bytes); it cannot establish targets or rewards.
