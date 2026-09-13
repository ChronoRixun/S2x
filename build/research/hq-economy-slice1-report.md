# HQ economy slice 1 implementation report

Date: 2026-09-12. Repository: `D:\S2x`. Branch: `feat/39-hq-economy` throughout.

## Result and limits

Implemented shared AE dispatch, deterministic daily offers, local activation/claim state, atomic economy persistence, developer grant commands, and Marketplace inventory/balance handlers. Release builds and the standalone C++ tests pass. **No game was launched, no files were installed, and the three reported in-game symptoms have not been verified as fixed.**

This is an economy/protocol foundation, not a complete Headquarters earn loop. In particular, payroll is not yet implemented, daily offers have empty reward bundles, gameplay does not yet complete Orders, and contracts use provisional free activation with placeholder targets. Those are material gaps, not successful implementations hidden behind empty acknowledgements. The task 4/5 response envelope also needs runtime confirmation.

## Stages and commits

1. `c041381` — `feat(hq): route Achievement Engine actions through shared handlers` (Release build passed).
2. `0c62bb3` — `feat(hq): persist economy transactions atomically and add grant commands` (Release build and standalone tests passed).
3. `a723e3e` — `feat(hq): serve marketplace inventory and balances with bounded request parsing` (Release build and expanded standalone tests passed).
4. This report is committed separately. All changes are under `src/client` or `build/research`; generated solution/binary artifacts are ignored. Other branches, `data/`, and the installed game were untouched. Nothing was pushed.

## Implemented code

- `src/client/game/demonware/achievement_engine.cpp/.hpp`: single JSON action dispatcher used by Glutton HTTP and bdReward tasks 4/5.
- `hq_economy.cpp/.hpp`: wallet, inventory, accepted/claimed achievements, reward snapshots, and transaction fingerprints.
- `hq_marketplace.cpp/.hpp`: bounded request parsing and inventory pagination/mutations, separate from transport.
- `hq_protocol.hpp`: shared AE framing, padding checks, and full raw diagnostics.
- `src/client/component/hq_economy.cpp`: copies catalog values from loaded string tables on the main thread every five seconds; registers `hqeconomy` and `hqgrant` for non-dedicated MP. Transport threads never retain game asset pointers.
- `byte_buffer.cpp`: bounded NUL search, bounded fixed-string copies, blob length validation, and overflow-safe primitive reads. Existing unbounded `read_struct(void*)` is not used by the added handlers.
- Marketplace and Reward handlers reuse the repository's service reply implementation and inventory/currency serializers.

### AE actions

| Action | Behavior |
|---|---|
| `get_user_achievements` | Existing Zombies serialization plus filtered HQ records, with numeric offset paging. Existing Zombies records still ignore request filters, as before. `achievement_response.cpp`, `achievement_store.cpp`, `achievement_sync.cpp`, hidden challenge event handlers, and their native refresh path remain unchanged. A corrupt HQ file does not suppress Zombies records. |
| `get_user_achievements_for_users` | Preserves the previous local Zombies projection under requested string/numeric UserIDs and local Steam fallback. Does not project HQ wallets or HQ records to other users. |
| `get_scheduled_user_achievements` | Three deterministic daily offers from four mapped definitions, plus three provisional contracts. UTC day is `time(nullptr)/86400`; daily indices are `(day+i)%4`, for `i=0..2`. Returns next midnight and three-slot activation limits by kind. |
| `activate_scheduled_user_achievement` | Validates current offer/name/kind and at most three active or claimable entries in that kind. Persists definition/reward snapshot, activation timestamp and `inProgress`. Already-active activation is idempotent. Completed/abandoned entries cannot be reaccepted on their offer day. |
| `activate_user_contract` | Same transition for kind 4; three provisional `contract_mp_*` entries, one-hour usage target, target 1, no price and no rewards. This is not a production-priced contract catalog. |
| `deactivate_user_achievement` | Active/claimable becomes `inactive`, without a refund. Repeated deactivation is accepted. |
| `get_expired_user_achievements` | Lists records explicitly marked `expired`, optionally with `completionTimestamp > Timestamp`, and honors HQ filters/paging. No gameplay usage clock is implemented to create these expirations automatically. |
| `pump_global_achievement_counters` | Empty `CounterValues` object. |
| `claim_achievement_reward` | Requires a known HQ record, matching kind, nonempty ClientTx, `claimable`, and progress at least target. Applies the stored reward snapshot and finished/claim markers in one transaction. It does not trust request-supplied rewards or progress. Repeated claims cannot grant twice. |
| Other actions | Explicit JSON error with `reason: unsupported_action`, console preview and complete raw JSON file. Includes `open_supply_drop`, `convert_parts_to_weapon`, `start_mission`, `end_mission`, `reset_missions`, `hq_context`, and `d_event` if used as actions. |

`GRANT_CURRENCY` adds with overflow protection; `SET_CURRENCY_BALANCE` sets a uint32 balance. `GRANT_PRODUCT` currently means a **locally resolved numeric inventory GUID**, not a backend SKU/bundle lookup. `ACTIVATE_ACHIEVEMENT` can activate an already-present inactive record by `achievementName`, respecting the three-slot limit; unresolved targets and unknown reward types reject the entire claim. There is no product-bundle resolver or arbitrary achievement-definition creation from rewards.

The original ClientTx receives its recorded reward snapshot on a repeated finished claim; another ClientTx receives empty received arrays. A fingerprint `name:offerDay` under `claim:<ClientTx>` prevents a prior transaction being reused to pay a later rotation instance. Original responses are reconstructed, not stored byte-for-byte. Claim receipts use `itemsReceived`, `currenciesReceived`, and `transactionID`.

### Daily table join and catalog limitations

The dumped `mp/dailychallengestable.csv` contains exactly six rows and eleven columns. Column 0 is a UI reference; column 9 is the target; column 10 is 2000 (treated as XP, not a known wallet currency). There is **no literal AE foreign key**. These are explicit semantic joins, checked against loaded definitions of kind 1:

| UI row | AE definition | Definition ID | Target |
|---|---|---:|---:|
| `ch_daily_0` | `daily_ch_kills` | 10 | 10 |
| `ch_daily_1` | `daily_ch_headshots` | 11 | 3 |
| `ch_daily_2` | `daily_ch_1v1_wins` | 5 | 3 |
| `ch_daily_5` | `daily_ch_commend` | 6 | 5 |

Sequence and boxing rows are omitted because a matching daily definition was not established. `weekly_ch_range_sequence` is kind 2; substituting it into a kind-1 daily offer would be incorrect. `challengeName` is the UI reference and `name` is the AE definition; that distinction is provisional. The schedule is a simple local policy, not a recovered historical backend rotation. Accepted Orders survive midnight and are not expired by offer refresh.

The definitions table identifies events/predicates but does not supply reward bundles, prices, or targets for the three original contracts (`contract_mp_1/2/3`, IDs 33/34/35). No 2000-XP wallet currency, AC ID, crate GUID, or reward quantity was invented. Therefore scheduled entries currently advertise empty `successRewards`, and XP itself is not awarded. The generic claim machinery is tested using explicit fixtures.

The read-only dumps inspected contain 83 supply-drop rows (including header), 1235 challenge rows (including header), 45 event rows, 109 collections, 108 item collections, 7 ranked reward rows, and 27 launch-item rows. Supply-drop rows describe types/products and presentation, not complete weighted roll pools. Collections contain numeric item GUIDs; launch-item UUIDs and supply-drop product numbers are not assumed to be those GUIDs. Consequently supply opening remains a logged stub.

### Persistent economy

Runtime file: `players2/user/hq_economy.json`, relative to the client's working directory. Single local profile/context, not a per-Steam-account database. Existing inventories and currencies start empty; no automatic balances or paid entitlements are granted.

Schema version 1 contains:

- `revision` and `currencies: [{currencyID, amount}]` (uint8 ID, uint32 balance).
- `inventory: [{guid, quantity, collision, modified, expires}]` (uint32 GUID/quantity/times; uint16 collision; zero expiry means permanent). Keys are GUID plus collision. Zero-quantity records are retained but not listed.
- `achievements`: name, challengeName, kind, progress, progressTarget, activationTimestamp, completionTimestamp, offerDay, usageTimeTarget, usageTime, status, claimTransaction, successRewards.
- Internal reward records: `{type, id, amount, achievementName}`. `achievementName` is optional when loading older version-1 snapshots. This internal representation is distinct from AE wire reward JSON.
- `transactions: [{id, request}]`, storing claim/pawn fingerprints.

A process mutex and exclusive `players2/user/hq_economy.lock` handle serialize access. Each operation reloads disk state while holding the lock, avoiding stale caches across multiple processes sharing a directory. Lock contention returns an error; it does not wait indefinitely. Mutations operate on a private snapshot, write `.json.tmp`, flush the file, and use same-directory `MoveFileEx(REPLACE_EXISTING | WRITE_THROUGH)` before success. A leftover temp file is not automatically promoted. Read/schema errors preserve the original and reject writes.

Limits: 16 MiB load size, 10,000 records per collection, at most 100 rewards per loaded achievement, bounded strings and numeric ranges. Reaching transaction capacity rejects writes rather than forgetting deduplication. There is no history compaction, account migration, or cloud synchronization. Supported mutations fit this bounded schema; external file edits must preserve its structure.

Commands:

```text
hqeconomy
hqgrant currency <decimal-or-0x-ID> <positive-amount>
hqgrant item <decimal-or-0x-GUID> <positive-quantity>
```

Commands print resulting state or a rejection. They do not force a native MP inventory/AE cache refresh; reopen the menu or restart to test refreshed reads. Currency IDs are not labeled AC/CP because those mappings are unverified.

## Protocol assumptions (all require runtime confirmation where noted)

### Reward and AE JSON

1. Observed task 4 input is typed string `s2_steam`, typed uint16 `1`, typed int32 `1`, typed JSON string, followed by up to 15 zero bytes interpreted as encryption padding. Only one JSON event per request is accepted. Task 5 is assumed to use the same input.
2. **Reply framing is provisional.** The task reply uses `send_struct`: standard typed uint64 server transaction, uint32 error, uint8 task, then the mirrored typed string context, uint16 count=1, int32 type=1, JSON string. There are no service object-count fields in this reply. This follows the requested mirroring assumption, not a captured successful S2 response.
3. Task 4 may instead require an empty acknowledgement plus asynchronous `BD_REWARD_EVENT_MESSAGE` push through `bdRewardEvent`; task 5 may require a distinct result type. Existing source has a candidate push serializer, but its unknown fields were not guessed. **This is the first capture gate if menus still time out.**
4. Raw files `s2x/dump/dw/hq_reward_request_<pid>_<sequence>.bin` contain the incoming task body; `hq_reward_reply_*.bin` contain the mirrored reply body before the standard service header/encryption. Console messages give full paths and byte sizes. Full unsupported HTTP/Reward JSON is saved as `hq_unsupported_ae_json_*.bin`. These diagnostics are currently unconditional and may accumulate.
5. HTTP `/secureingest/` still returns `{}`; all other HTTP bodies go through the dispatcher. Invalid JSON produces an error object instead of leaving the request unanswered. Requests are limited to 64 KiB, parsed iteratively. Unsupported actions do not pretend a grant succeeded.
6. JSON `Version: 0`, `Status: ok/error`, echoed Action and string ClientTx follow existing envelopes. `reason` is textual; no verified native `errorCode` mapping is provided. Malformed root JSON has only Status/reason because Action/ClientTx cannot be recovered.
7. Existing field casing is preserved: `kind`, `name`, `progress`, `progressTarget`, `requiresClaim`, `fulfilledTimes`, `completionTimestamp`, `status`; HQ adds the vocabulary from the string scan. Status spelling is `available`, `inProgress`, `claimable`, `finished`, `inactive`, or `expired` (not snake_case `in_progress`).
8. `NextPeriodStartTimes` and `ActivationLimits` are objects keyed by decimal kind (`"1"`, `"4"`) with UTC seconds and total simultaneous capacity. Their exact container/value schema is unverified. `CounterValues` is an empty object, not an array. No `DetailedInventory` envelope is invented.
9. `eventEndTimestamp` is next midnight only for available offers and zero for accepted records; usage fields use seconds. `fulfilledTimes`/`completionCount` become 1 after claim. `completionTimestamp` doubles as the expired-since comparison field for explicitly expired fixtures. Those lifecycle conventions are local assumptions.
10. PageToken is a decimal offset over the current result order; empty token starts at zero. Limit is 1..1000, default 100. HQ filters honor AchievementKind/Kinds, Names, and Statuses. Paging is not a snapshot token across intervening mutations. Multi-user Zombies behavior retains its previous unpaged response.
11. Received GUIDs and amounts are JSON numbers. GRANT_PRODUCT's product/id mapping, numeric reward shapes, ACTIVATE_ACHIEVEMENT's name field, and SET_CURRENCY_BALANCE's received amount (new target balance) are provisional. Tests demonstrate local transactions, not native parser acceptance.

### Marketplace

| Task | Request handling and assumed meaning | Result |
|---|---|---|
| 132 `getBalanceV2` | Captured context + uint32 13; 13 treated as max results, allowed 1..256. Up to 15 zero padding bytes. | Sorted stored currencies using existing `bdMarketplaceCurrency` (uint8 ID, uint32 value). Empty initial wallet has zero results; no inferred 13-entry zero wallet. |
| 165 `getInventoryPaginated` | Captured context + uint32 page 1 + uint32 limit 500 + zeros. One-based pages, 1..500 items/page; page 0 rejected. Stable `(guid,collision)` ordering; 64-bit offset arithmetic. | Existing `bdMarketplaceInventory`, excluding zero quantities and expired entries. Repeated pages are stable unless state changes. |
| 49 `getExpiredInventoryItems` | Captured context and 14 zero bytes, interpreted as context-only plus padding. | All nonzero expired items via `bdMarketplaceInventory`; response element type remains unverified. |
| 193 `putPlayersInventoryItems` | **Guessed** context, uint32 count <=500, then full inventory records in existing serializer order. Each owner must be local Steam ID; account must be empty or `steam`. XP must be 0, blob empty, duration 0 or -1; unsupported metadata is rejected. Duplicated keys reject the whole request. | Atomically sets quantities/expiry/collision; server assigns modified time. Empty service acknowledgement. No client transaction field assumed. Absolute puts are repeatable but lack stale-write ordering protection. |
| 199 `pawnItems` | **IW7-derived candidate**, not S2-observed: context, ClientTx, uint32 count <=100, repeated uint32 GUID, uint32 resulting quantity, uint16 collision. No repeated keys; known, nonexpired inventory only; quantities cannot increase. | Atomically reconciles quantities and persists a request fingerprint. Retries do not decrease again; reused ClientTx with a different fingerprint is rejected. **No AC payout is implemented**, because pawn rates/currency mapping are absent. This is quantity reconciliation only, not a complete sell/duplicate-conversion operation. Empty acknowledgement. |
| 232 `getEntitlements` | **Guessed** context-only plus padding. | Validates store availability, returns zero entitlement objects. Store-owned cosmetics are not treated as paid Steam entitlements. No entitlement serializer exists in the current data_types.hpp. |
| 242 | Unknown layout; full raw request saved. | Existing empty-success behavior retained with explicit warning. Quartermaster may depend on a real response here. |

Every guessed write/read task logs raw input (`hq_put_assumed_request_*`, `hq_pawn_assumed_request_*`, `hq_entitlements_assumed_request_*`, `hq_expired_request_*`, `hq_marketplace_242_*`). Structural parse failures return `BD_PARAM_PARSE_ERROR`; store/transition failures return `BD_HANDLE_TASK_FAILED`. Those are existing generic DW errors, not captured feature-specific error selections.

Inventory wire fields, exactly in existing serializer order: uint64 local owner; string `steam`; uint32 GUID, quantity, XP=0; empty blob; uint32 absolute expiry (0 permanent); int64 duration=-1; uint16 collision; uint32 modified time. Account string, permanent-expiry sentinels, and expired result type need native confirmation. Contexts other than `s2_steam` are rejected. Purchases, durable processing, balance V1 and other unchanged stubs remain outside this implementation.

## Publisher variables

`src/client/resources/dw/publisher_variables/mp_tu26_1_20.json` already has payroll, Quartermaster, commander and global vendor kill switches at `"0"`, and `allow_hub_vendor_menu="1"`. No vendor switch was changed. Other relevant existing switches remain: social NPC `1`, weapon-order switch `1`, collection reward post-op disable `1`. Their consuming code and feature-specific effects remain separate investigation points.

Payroll definitions exist: `payroll_officer` (ID 345) and `payroll_officer_masterprestige` (757), kind 5, event 18 `picked_up_payroll`. They do not establish a balance currency, amount, cooldown, or claimable-state initialization. They were not converted into arbitrary money-grant fixtures in production.

## Validation performed (without the game)

Regenerated via `./tools/premake5.exe vs2022`; ran the supplied Release/x64 solution build after each code stage. Logs remain locally at `build/research/hq-stage1-build.log`, `hq-stage2-build.log`, and `hq-stage3-build.log`. The final code build reports no warnings/errors. `git diff --check` passes.

Standalone tests compile **the actual production** economy store, AE router, achievement serializer, Marketplace core, byte buffer, and inventory/currency serializers. Test shims replace the game precompiled header, Steam identity, console output, and achievement store; Windows persistence/locking code is real. These tests never load the game binary. They run only in unique `build/research/hq-tests/run-<pid>` directories.

Coverage: empty store; persistent snapshots; callback rollback; currency overflow; failed temp-file open with original balance intact; exclusive lock contention; corrupt-file preservation; three daily offers; activation; incomplete-claim rejection; multi-resource claim; exactly-once replay; stored item reward; currency set and achievement activation reward; malformed JSON and invalid limits; Zombies record preservation including HQ corruption; typed AE envelope and all truncated prefixes; 0/500/501 inventory results, page zero/large pages and expiration filtering; captured-shape inventory request and truncated prefixes; unterminated string/oversized blob; put serializer round trip and foreign-owner rejection; pawn parsing/reconciliation/replay/conflicting transaction/increase rejection; currency serializer round trip.

Not tested: native UI parsing, asynchronous Reward delivery, Steam account/profile changes, physical power loss, live gameplay predicates, long-term transaction-capacity exhaustion, or competing inventory mutations between page requests. The catalog join is source/table-checked; no game-asset loader was exercised by the harness.

Reproduce:

```powershell
& 'C:/Program Files/Microsoft Visual Studio/2022/Community/MSBuild/Current/Bin/MSBuild.exe' build/research/hq-tests/hq-tests.vcxproj -m -v:minimal -nologo -p:Configuration=Release -p:Platform=x64
Push-Location build/research/hq-tests
./bin/hq-tests.exe
Pop-Location
```

Expected final line begins `PASS: store, atomic failure, lock, rotation, activation, claim/replay` and includes pagination, typed packets and inventory mutations. Build/test outputs and run fixtures are ignored, while test source/project/shims are committed.

## Exact subsequent in-game verification (for Owen; not performed)

### Preparation

1. Close the game and back up its existing `players2/user/achievements.json` and any `hq_economy.json`. Install the newly built exe/PDB only when you decide to test; this task did not copy them.
2. Start through the known working shortcut, enter online Multiplayer then Headquarters. Disable `cg_unlockall_loot` and `cg_unlockall_items` for ownership tests. Wait at least five seconds for the catalog-copy loop.
3. Run `hqeconomy`. New state should have no currency or inventory. Record console log lines and `s2x/dump/dw/hq_*` files; files now record the response body as well as the request. Do not infer success from an empty service acknowledgement.

### Orders board

1. Talk to Major Howard and open Orders. Record whether three daily offers appear, with targets matching the mapped UI row above. Confirm the current UTC-day offer selection repeats after closing/reopening the board.
2. Accept one shown daily Order. Run `hqeconomy`: it should have the AE name, correct target, `inProgress`, nonzero activation timestamp, and an empty reward snapshot. Reopen the board and restart the client; acceptance should persist without consuming another slot.
3. Abandon it. Expect `inactive`; same-day reaccept is rejected. On the next UTC day, offers rotate while any still-active Order remains visible in accepted Orders.
4. Do **not** expect real kills/matches to complete this slice's Orders. For a controlled claim test, accept a different Order, exit the game, and edit only its HQ fixture record: set `status` to `claimable`, `progress` to `progressTarget`, and `successRewards` to `[{"type":"GRANT_CURRENCY","id":2,"amount":25,"achievementName":""}]`. ID 2 here is an arbitrary test wallet, **not a verified AC mapping**. Preserve all other schema fields and keep `achievements.json` separate.
5. Restart, reopen Orders, attempt the native claim, then check `hqeconomy` and the raw reply: expect +25 in wallet 2 once and `finished`. Repeat/reopen/restart: no additional credit. If no claim button or no response appears, stop changing reward data and inspect the reply envelope/JSON container assumptions first.

### Payroll

1. Visit Mail/payroll and try to claim. Save the exact AE action, AchievementName/Kind, event and ClientTx sent, plus raw reply and visible error.
2. **Expected limitation:** no payroll instance/cooldown is seeded; an AE claim for `payroll_officer` currently rejects as unknown. This symptom is not fixed by the generic claim implementation. Confirm no wallet changes occur despite the failed claim.
3. Capture a native successful response if available, or recover the defining backend fields before adding a payroll policy. Record whether master-prestige uses a separate instance. Do not equate a manual hqgrant with a working payroll claim.

### Quartermaster and inventory

1. Open Quartermaster before granting items. Record whether it stays open; inspect `hq_marketplace_242_*` if it flickers/closes. Confirm the first inventory request is page 1/limit 500 and balance request carries 13.
2. Run `hqgrant item 0x20000D 1` (a GUID present in the dumped collection membership table), then `hqeconomy`. Reopen the menu or restart to trigger inventory fetch. Check that the corresponding collection member is owned and another ungranted member stays unowned with unlock overrides disabled. Confirm persistence after restart.
3. Optionally run `hqgrant currency 2 100` to test transport of a known test balance. Check which, if any, UI currency displays it; do not label it AC until the mapping is established. A zero UI result can mean wrong currency mapping, not failed persistence.
4. Opening a supply drop should produce a complete `open_supply_drop` JSON trace and explicit unsupported-action response, with **no inventory debit**. Supply drop rolling/reveal is not an acceptance criterion for this slice.
5. If the game sends 193/199/232, retain the full request and compare it with the documented candidate schema. Pawn presently changes only quantities and pays no currency; use only backed-up test inventory when exploring that path. The standalone harness exercises these provisional schemas without risking an installed profile.
6. For expiration verification, exit, set a test item's `expires` to 1, restart, and verify it is excluded from normal pages and included by task 49. Restore the backup when done.

## Next questions / remaining work

1. Confirm task 4 push versus mirrored reply, task 5 result type, and native schedule/activation-limit JSON shapes before concluding the Orders/Quartermaster symptoms are resolved.
2. Decode task 242 and the real 193/199/232 layouts. Confirm item account string and expiry sentinels; identify pawn values and currency payout semantics.
3. Recover actual Order/contract reward definitions, targets, costs, available-time rules, currency IDs, and product-to-GUID mappings. Replace the placeholder contract catalog and empty daily rewards.
4. Retain transaction identities in gameplay event parsing before connecting MP events to monetary progression. Current task 11/12 hidden-challenge behavior is preserved; no HQ progress or usage mutation is attached to those events.
5. Implement payroll instance/cooldown logic using evidence for `picked_up_payroll`, then validate a claim twice and across restart/cooldown. The supplied table alone is insufficient to choose money/currency semantics reliably.
6. Implement mission usage accounting/deduplication before expiring timed contracts; offline/lobby wall time must not consume eligible gameplay time.
7. Recover complete supply-drop pools/rules and persisted roll receipts before debiting crates; the supplydroptypes table alone does not provide a clean roll implementation.
8. Add native MP refresh, account separation if needed, and bounded transaction-history maintenance after protocol acceptance is established.


## Slice 1b � native MP delivery (2026-09-12)

### Result and evidence

The operator's Slice 1 Headquarters test received three contract offers in the inline bdReward task-4 JSON reply but left Orders empty. Inline success is therefore not evidence of native AE consumption. Slice 1b adds MP in-process delivery; visible Orders and Quartermaster behavior still require the operator's test. No game was launched and no installed-game files or `data/` were accessed or changed in this work.

Disassembly details, wrapper arguments, task/cache addresses and remaining gaps are in [ae-internals.md](ae-internals.md). The scheduled issuer is `0x1399C0`, task base `0x60391D0`, group 0. Active challenges call `0x139350`, which reaches the existing `0x139400` page fetch, task base `0x6039A60`, also group 0. Many LUI getters and mutation operations are inlined, not calls to separate engine functions.

### Changes

- Added `src/client/component/achievement_injection.cpp`, enabled only for non-dedicated Multiplayer. Zombies' `achievement_sync.cpp` and its persisted-record gate, refresh behavior and response generation remain unchanged. MP delivery does not require existing Zombies achievements.
- Detours invoke the original user-page/scheduled fetch first. On success for controller 0, they copy the actual native request via string getter `0xA3B850`, preserving Action, ClientTx, filters, account-specific kinds and pagination. The copied JSON and 25-byte task transaction are bounded and checked before queuing. At most one pending response per fetch type is retained. Dispatch rechecks task activity and transaction identity, dropping canceled/replaced tasks.
- The main pipeline processes the copied request with `achievement_engine::dispatch`, then calls `AE_SetResponseString` and `AE_ProcessResponse(0, bridge, 0)`. The bridge is the existing, proven `0x6039B58` string object (`0x6039A60+0xF8`), reused synchronously for both response types. ProcessResponse finds the real task by Action and ClientTx, not by the input object's address. No guessed scheduled response field is written. Native scheduled callback response-object placement remains unknown; `+0xF8` also equals controller stride, so this implementation deliberately supports only controller 0.
- Task 111 explicitly returns an empty SKU result collection and traces its request. `data_types.hpp` has no SKU or SKU-page serializer; the empty `bdTaskResult` collection uses `service_reply::send()` to emit the standard typed uint32 zero count. This is the **same empty wire result as the old stub**, now intentional and bounded; it alone cannot explain a Quartermaster improvement.
- Task 242 now uses `send_struct()` for an empty structured success instead of `send()`. Its body after the standard transaction/error/task header is empty, removing the previous typed uint32 zero count. Captures have prefix `88 17 08 4c 00`, then protobuf-like context, UUID, ClientTx and varint fields. Empty success was the chosen permitted fallback: **no ClientTx echo, field tags, SKU catalog, purchase or entitlement is invented**. Native acceptance of an empty structured body is a guess; this is not a proven Quartermaster fix. Both tasks reject bodies over 64 KiB, tolerate opaque smaller input without parsing/dereferencing it, and retain guarded error handling.
- `hq_protocol::trace` still requires `-demonware_debug` (the original report's unconditional-tracing statement was superseded by commit `f59e47e`). New files are `hq_injected_ae_request_<pid>_<seq>.bin`, `hq_injected_ae_response_<pid>_<seq>.bin`, and `hq_marketplace_111_<pid>_<seq>.bin`; `hq_marketplace_242_*` and Reward tracing remain. Injection console messages report user/active versus scheduled, Tx, byte count and group. A `dispatched` message means ProcessResponse was called, not that its private parser accepted the result.

No new gameplay progression, payroll policy, supply-drop rolling, mutation-response injection, expired-fetch injection, or multiplayer split-screen support is included. Activation/deactivation/claim still use the existing router transport; do not assume they complete native UI tasks just because reads now have an injection path. No native schedule parser/schema changes were guessed.

### Validation

Release/x64 regeneration and the requested full solution build passed after each code stage. Logs: `build/research/hq-slice1b-stage2-build.log` and `hq-slice1b-stage3-build.log`; neither reports a compiler warning or error. Output is `build/bin/x64/Release/s2x.exe`; it was not installed or run.

The standalone production HQ harness passed. Its stale debug-flag linkage and pre-`f59e47e` negative-limit assertion were repaired. Added checks exercise the real service reply serializer before encryption: task 111 has exactly one zero result count; task 242 has no result-count/body fields. Native-shaped scheduled and active requests preserve the 24-character ClientTx and return offers/stored achievements. Existing persistence, corrupt-file, lock, reward replay, malformed JSON, typed-packet and inventory tests pass. Harness build log: `build/research/hq-slice1b-tests.log`. Runs stay under `build/research/hq-tests/run-<pid>`.

These checks do not execute detours, native string objects, native JSON handlers, menu transitions or the game. They cannot establish UI acceptance. `git diff --check` passes.

### Exact operator verification

1. With the game closed, back up the test profile as in Slice 1, install the newly built executable/PDB when ready, and add `-demonware_debug` to the known working launch shortcut. This task did not do those steps. Use the same MP profile/settings as the failed test to isolate the transport change.
2. Enter online Multiplayer, then Headquarters. Wait at least five seconds for the existing catalog-copy loop. Open Major Howard's Orders board and any contracts view that caused the captured scheduled fetch. Look for `[HQ AE injection] dispatched scheduled ... group 0` and `dispatched user/active ... group 0`. Match each injected request and response by ClientTx, rather than adjacent dump sequence numbers.
3. Confirm injected scheduled JSON contains the expected available offers, then record whether they actually appear. Close/reopen the board three times. Verify new successful fetches receive matching responses and the board stays usable. If JSON has offers but the board is still empty, capture the console, both injected files, and the missing handler ranges below; stop changing offer names/fields until the parser is inspected. If no injection message occurs, report which native fetch/Reward request occurred.
4. With an already accepted test record, open the active Orders view; confirm its native get_user_achievements request and injected reply include the persisted HQ record. Close/reopen and restart once. Do not use accept/abandon/claim completion as an assertion of this read-only delivery change; retain their traces if explored, since their native completion transport is still pending.
5. Open Quartermaster with the same empty catalog/inventory as the failed test. Confirm `getSkusPaginated: empty SKU page` and `task 242: provisional empty structured success`, then check whether the menu remains open for at least ten seconds. Close/reopen three times. Record flicker/close/errors and retain `hq_marketplace_111_*` and `hq_marketplace_242_*`. No SKUs or paid entitlements should appear. If it still closes, the empty structured-response guess did not resolve the UI dependency; obtain a native successful task-242 response/schema before inventing a transaction field.
6. Launch Zombies with a profile containing persisted achievements and repeat the previously working achievement/lobby refresh check. Expect the old behavior and no `[HQ AE injection]` messages. Optionally start a dedicated instance during operator testing and confirm it never installs/runs this injection component. This task ran neither mode.

### Exact remaining dump requests

All offsets/sizes are hexadecimal image-relative byte ranges, from the same unpacked build:

| Offset | Size | Needed evidence |
|---|---|---|
| `0x13BD30` | `0x0600` | User, expired and scheduled callbacks through `0x13C220`; establish native response-object layout and completion lifecycle |
| `0x13E8B0` | `0x0AA0` | Native response handlers including scheduled `0x13EF20` and user `0x13E960`; validate schedule containers, activation limits, readiness and pagination |
| `0x676860` | `0x01E0` | Exact Action-to-task mapping used by ProcessResponse |

These investigations stopped at the missing byte boundaries. All requested user/active/scheduled fetch entry points were located and implemented via the proven bridge. No installed-game dump paths were read. The Marketplace UUID's catalog/store meaning remains unverified; no additional binary range is asserted for its decoder because its entry point is not known.

## Slice 2 (2026-09-12)

### Delivery status

This slice implements the AE transport/router/event paths and fixes structured reply
framing. **It does not establish that Quartermaster or Mail works in game.** No game
was launched. XP reward mapping, retail weekly rewards, the AC currency mapping and
the vendor response schemas remain unresolved below. These are not covered by a
passing standalone harness.

Commits before the final report/diagnostics commit:

- f25facd: shared synchronous AE delivery and empty task 4/5 acknowledgements.
- be2016b: filters, native status/reward vocabulary, abandon, weekly offers.
- fa8954b: event-driven kill/headshot progress, payroll, claim replay protection.
- 7094370: empty structured response bodies for MP vendor/Mail, Marketplace tracing.

### What changed

The MP-only bridge hooks native submission at image offset 0x8397E0, after task data
and callbacks have been installed. It calls the original, checks the AE task type,
controller, active data and ClientTx, then dispatches the actual request and calls
AE_ProcessResponse synchronously. It replaces the two fetch hooks and their queued
scheduler path. Controller 0 remains the supported controller. The bdReward worker
no longer dispatches AE mutations or returns mirrored JSON; tasks 4/5 have stock
empty acknowledgements. Debug request and injected response dumps remain enabled.
Unsupported AE actions still receive an error JSON from the router; supply-drop
opening and mission actions have not gained business implementations.

Native action handlers were decompiled; see ae-ghidra-findings.md. Activate reads
optional DetailedInventory, deactivate does nothing with the body, and claim checks
the transaction rather than reading itemsReceived/currenciesReceived. The latter
fields remain diagnostic response fields; they do not update the native wallet by
themselves. User fetches and Marketplace inventory/balance fetches project saved state. Activation
success callback 0x13B0B0 copies the selected scheduled record into the native user
table with status 2 and emits eventType 2; preserving successful task completion is
necessary for all three accepted orders to appear immediately.

The router now filters legacy records as well as local records by kinds/statuses/names.
For-users replies are objects keyed by requested user ID; only the local account gets
local records, and unknown users get empty arrays. Limit applies per user. Single-user
fetches also honor UserIDs. Empty UserIDs means no users. Missing/nonpositive/malformed
Limit retains the existing tolerant 1000-record cap. For-users does not yet implement
continuation pagination; current catalog fits the native 30-record user cache.

Scheduled statuses are available/in_progress/claimable/completed. User statuses are
inactive/inProgress/claimable/finished. Abandon accepts the captured request without
AchievementKind, infers the persisted kind, clears progress/activation/usage and restores
available. A subsequent activation can take the offer again. JSON rewards use lower-case
grant_currency/grant_product with nested currency/product objects. expirationTimestamp,
activationTimestamp, completionTimestamp, fulfilledTimes and usageTimeRemaining are emitted.

The existing semantic daily joins remain: kills=10, headshots=3, 1v1 wins=3, commend=5;
three rotate each UTC day. Weekly offers are kills=100, wins=10 and scorestreak calls=25;
three are offered per seven-day period anchored to Unix epoch. Contract definitions
33/34/35 remain kind 4 with the prior local targets/time limits and no invented prices.
There are three daily, three weekly and three contract slots. Accepting three at once
still needs in-game validation of the native callback/cache flow.

### Reward and event policy: explicit guesses

The copied weeklychallengestable.csv is **zero bytes**. dwgamechallenges.csv identifies
weekly names/kinds/events but not targets/rewards. The three weekly targets above are
local defaults, not a successful join against retail weekly UI data. Their challengeName
uses the AE name until the missing UI table can establish a real UI reference.

The daily UI copy specifies 2000 in its XP column. **XP is not awarded by this slice**:
there is no verified XP currency/product mapping in the supplied tables. Daily offers
instead advertise/grant local currency 2 x25; weekly offers currency 2 x100. These are
local reward policy, not table-derived replacements for XP. Currency 2 is a candidate
Armory Credits ID, not proven: Inventory_ConvertItemToArmoryCredit at 0x11EC10 reaches
0x2764A0, whose pawn path writes a field of 2, but this alone does not identify that
field as a currency ID. Verify the native wallet mapping before treating these values
as real AC. No supply-drop bundle/product mapping is asserted. The generic item grant
path is tested with an explicit numeric fixture, and still assumes product ID equals
item GUID. It is not a complete product-bundle catalog.

Production bdReward tasks 11/12 submit local MP events to the economy; Zombies and
remote users keep their prior event handling. All table event names and parameters
are logged at info level with -demonware_debug. Supported completion predicates:

- event 1 / killed_a_player -> daily_ch_kills and weekly_ch_kills;
- event 1 with selector 6 == 1 -> daily_ch_headshots (definition predicate `(6:1)`);
- event 18 / picked_up_payroll -> payroll_officer, kind 5, target/progress 1.

A matching active order increments by one per event and becomes claimable at target.
The other daily/weekly/contract types have no completion implementation yet. Nonzero
event timestamps plus name/parameters are hashed into persisted replay receipts; zero
timestamps cannot be reliably deduplicated and are counted on each delivery. Receipts
are capped at 2048 independently of permanent claim receipts; this is a bounded replay
window, not lifetime exactly-once event processing. It may collapse indistinguishable
same-timestamp events; capture native timestamps before broadening event coverage.

Payroll grants candidate currency 2 x200 on claim; four hours between settled pickups
is local policy. It does not overwrite an unclaimed reward. Claims are atomic with
currency/inventory writes and reject reuse of a settled transaction for a new cycle,
including another payroll cycle on the same day. Existing accepted orders retain their
saved reward snapshots: abandon/reaccept to take the new local rewards.

Payroll is visible in kind-5 user fetches and eligible for-users queries. The observed
for-users query requests only inProgress and excludes kind 5, so honoring those filters
necessarily excludes claimable payroll. The native for-users handler also has additional
eligibility checks. Do not treat a successful router test as proof that the payroll kiosk
will stop spinning; capture its kind-5 fetch and claim after the common injection fix.

### Quartermaster and Mail findings

Task 242 input is a typed struct containing protobuf-style tags: context, a stable
36-character UUID, a changing transaction string, and bool 1. The previous response
contained only the service header: send_struct() does not automatically add a body.
MP task 242 now validates the outer struct/padding and returns a typed, zero-length
structured body. Its business schema is still unknown; this is a framing correction,
not a proven vendor catalog or purchase response. Task 111 retains an ordinary empty
result page. Tracing was added for 42, 60, 130, 132, 165, 193, 199 and 232.

S2xFull recovered these fragmented SDK blocks (image-relative offsets, not hook targets):

- 0x11CD4551: service 0x50 / task 0xF2, calls 0xA41ABA -> 0xA5DAD0.
  Referenced from 0xA41A99; predecessors 0x20C55F and 0xA4EEF7. The call continuation
  goes to 0x1D9798 via 0xA41A42. Follow its response object and deserialize vtable next.
- 0x118174FD: bdTaskParams(service 0x50, task 0x6F), context/page parameter writes.
  Typed SKU result element parser has not been recovered; zero results need no element.
- 0x11F29DC2: bdTaskParams(service 0x50, task 0x2A), next call 0x14EAF2.
- 0x11817A13: service 0x50 / task 0x3C, next call 0xA438CD.
  Names startExchangeTransaction/steamProcessDurable are repository names; the exact
  reply objects and reason for six repetitions remain unverified.

The captured console does execute bdMarketingComms task 6 (line 107, during startup).
That establishes service use, not that it services the Mail kiosk. Its existing handler
was not an empty stub: it fabricated one protobuf message with ID zero and empty fields.
MP now returns a framed empty collection and traces marketing_6. The old Zombies handler
is preserved. Correlate a new marketing_6 request with a deliberate Mail-only interaction;
if none occurs, search for the actual kiosk service before making another schema change.

### Exact operator verification

1. Launch MP with -demonware_debug. Do not use Zombies for these tests. Wait for assets
   and the five-second catalog load. Run `hqeconomy`, then `aefetch scheduled`, `aecache`.
   Expect nine recognized records (3 kind 1, 3 kind 2, 3 kind 4), native success, ready=1.
   Preserve the console and injected_ae_request/response plus reward_request dumps.
2. Open Major Howard. Accept three daily orders consecutively without leaving. For each,
   require an injected activate request/response before the native UI completion. Fetch
   scheduled again and inspect in_progress statuses. Abandon one, fetch again, require
   available, then reaccept it. Repeat for one weekly order. Check filtered user requests
   no longer receive unrelated kind-5 Zombies records.
3. Accept daily_ch_kills or daily_ch_headshots when offered. For kills, produce ten local
   kill events; for headshots, three events with selector 6=1. Diagnostic alternative:
   run `aeevent kill` ten times or `aeevent headshot` three times. These commands directly
   change the local economy through the same event reducer; they do not test task 11/12
   wire parsing. Run `hqeconomy` and `aefetch user`. Require claimable, then claim at Howard.
   Require one saved reward credit and finished. Re-fetch/reopen and ensure no duplicate.
4. Run `aeevent payroll` or deliberately use payroll. Inspect `hqeconomy`: payroll_officer
   should be claimable. Capture the kiosk's kind-5 fetch and claim request. After claim,
   require +200 currency 2 once; another pickup within four hours must not mint again.
   Compare displayed AC to stored currency 2 to confirm or reject the candidate mapping.
5. Open Quartermaster once. Capture marketplace_242, native success/failure and whether
   the hub still unloads. Task 242 must now have a typed empty struct body on success.
   If it still closes, the next work is response-object/vtable recovery at the offsets
   above, not another blind empty acknowledgement. Inspect 42/60 dumps for transaction
   and durable identifiers before implementing exchanges or entitlements.
6. Interact only with Mail and record whether marketing_6 fires then. Require an empty
   inbox without an error; if not, preserve its request and native completion result.
   Supply Drops may remain grey: this slice does not establish a crate product catalog
   or implement open_supply_drop, and does not claim to fix that flow.
7. Restart and run `hqeconomy` to confirm persistence. Recheck ordinary Zombies achievements
   separately: the dedicated Zombies response bridge, event handling and MarketingComms
   reply branch were retained; game-level regression testing was not performed here.

`aefetch <scheduled|user>` and `aecache` remain. New `aeevent <kill|headshot|payroll>`
submits one diagnostic event and prints the save outcome. It changes local state;
`hqeconomy reload` invalidates the cache and rereads the store, not resets it.

### Validation and remaining work

All stage Release builds and standalone harness runs passed after their fixes. Final
commands use premake vs2022, Release|x64 s2x.sln, Release|x64 hq-tests.vcxproj, and
bin/hq-tests.exe with cwd build/research/hq-tests. Logs: hq-slice2-final-build.log and
hq-slice2-final-tests.log. Tests exercise production router/store/serialization with
three daily and three weekly fixtures, native filters/abandon/status/reward shape,
foreign-user isolation, kill completion/replay/claim, payroll/cooldown/transaction
reuse, empty struct framing, and prior persistence/packet tests. The harness does not
execute native hooks, service handlers, LUI or the vendor reply deserializers.

Before calling Slice 2 fully verified: validate shared-hook timing in game; recover the
weekly UI table through an operator-provided dump; identify XP and AC reward mapping;
resolve product IDs to item GUID/bundle contents; recover task-242 response deserializer;
prove the Mail kiosk service; implement remaining event predicates. No installed-game
files or data/ were read or modified and the game was not run. The pre-existing untracked
run-47992/ directory was left untouched. Source edits are confined to src/client and
research artifacts to build/research.


## Slice 3 � 2026-09-12

**Partial delivery: supply-drop economy support and non-claimable Mail placeholders
are implemented; Quartermaster opening and payroll kiosk claims remain unresolved.**
This section supersedes Slice 2's suggestion that an empty inbox array is safe.
No game was launched. No installed-game or data/ files were modified.

### Changes and evidence

- `da835be`: preserve newest available HQ dumps (PID 55380), decode them, recover
  native SKU readiness, validate SKU query framing, add `hqnative` and SKU callback
  logging. `run-55380/ae-actions.txt`, `decoded.txt`, `console-from-launch.log`, and
  `dw/` hold the evidence. The console slice starts at its last authentication
  request: no S2x startup banner is present for that run. Authentication diagnostics
  are redacted in the saved slice. Later untraced HQ loading follows the traced run;
  those clicks cannot be assigned to the PID's earlier requests.
- `1021eff`: retain at least 14 allocated mail slots, use ID zero (native cleared
  message state), clamp allocation, reject overflowed varints, trace MarketingComms
  task 4. This disables fabricated claims instead of inventing redeemable rewards.
  The mail crash guard and Zombies payload are retained.
- `6d2ab4f`: implement `open_supply_drop` with three uniform collection-member rolls,
  atomic inventory debit/grant and persistent replay receipts; add `hqopendrop`.
  The Orders bridge, task-table membership checks, router acknowledgement behavior,
  and existing payroll achievement/claim policy are preserved.

Established Quartermaster facts: `Inventory_AreSKUsFetched` (0x120610 -> 0x278400)
reads 0x81038A8. FetchAllSKUs (0x120670 -> 0x278E20) issues group 5/type 0x17;
submit thunk 0x1BC1AF, success 0x27B700, failure 0x27B6C0. Success copies returned
0x370-byte SKUs to a 400-entry cache and sets fetched when result count < page
limit. **Zero results is explicitly a terminal page**, not evidence of malformed
paging. A new wrapper around zero records would be speculative. Captured requests
have page 1/limit 100, ID filters, byte type filters and an empty final string.
All three named vendor publisher switches already allow access. The exact Lua
main-menu enable expression is still unknown. Task 242 remains an empty typed
struct: its reply schema and high-level issuer/callback were not recovered, and
this work does not claim to fix vendor opening. Its UUID is absent from
launchitems.csv. Unloading `mp_hub_allies_slim_load` alone is normal load-zone
cleanup, not proof that the vendor caused a hub unload.

Established Mail facts: MarketingRedeemMessageCodes (0x125780 -> 0x3726F0) requires
nonzero message ID and a nonempty redemption code. 0x3721A0 clears the ID to zero.
Queue drain 0x2B2D50 issues group 0/type 0x87 or 0x88, success 0x2B3030 and failure
0x2B2FA0; success applies inventory/currency result arrays. These are not AE JSON
objects and must not be admitted by relaxing achievement_injection's filter.
The exact DW redemption task and payload remain unestablished. No Mail claim,
open_supply_drop, or picked_up_payroll is in the newest captured PID; detailed
tracing is absent from the later walk. Earlier evidence associates payroll with
Reward 11/event 18; existing claimable kind-5 payroll and replay protection remain.
No new payroll grant or native success claim is made here.

Established drop facts: 0x2AEEA0 reads supplyDropTypes column 5 and queries inventory
quantity at 0x279480; 0x2B0850 reads column 4 for SupplyDropID and submits group
0/type 0x7F. Common is item GUID **1 / 0x1**, name **sd_mp**, UI type 0; rare is
item GUID **2 / 0x2**, name **sd_mp_rare**, UI type 1. These IDs are not currency
IDs. 0x2AF7A0 reads **GrantedItems** objects with **id**, optional **GrantedCurrencies**,
and **DetailedInventory** (item_id, item_quantity, collision_field,
expiry_duration, mod_date_time). The reply includes absolute quantities and the
consumed drop, including zero on final use. 0x2B03B0 emits OpenSupplyPackageSuccess.

Local policy rather than retail reconstruction: three rolls with replacement,
uniform over deduplicated member GUIDs from itemscollections.csv (columns 3+,
count in column 2), restricted to IDs present in collections.csv. Collection
completion rewards in column 1 are excluded. Common and rare use the same pool;
there is no claimed retail rarity guarantee, duplicate conversion or paid purchase.
Only common/rare MP drops at collision 0 are supported. A committed receipt
preserves loot selection across replay/restart; replay returns current absolute
quantities so old transactions cannot rewind the native inventory. Different drop
names with the same ClientTx, missing stock/catalog, expiry, overflow and save
failures reject without debit. Native animations/menus still need operator testing.

### Operator verification � console commands first

Start with `-demonware_debug`. Wait at least five seconds after reaching the frontend
for runtime tables to load. Run:

```
hqnative
hqeconomy
aefetch scheduled
aecache
hqgrant item 1 2
hqgrant item 2 1
hqeconomy
```

1. Restart the client to let Marketplace 165 fetch granted inventory; `hqeconomy`
   only prints/reloads local storage and does not fetch native inventory. Confirm
   common/rare counts of two/one if starting from zero. Open the Supply Drops
   shortcut and open one common drop. Require three cards/items, one drop consumed,
   new inventory quantities, and persistence after restart. Extra preexisting stock
   adds to these amounts. No balance grant is required by the recovered count path.
2. To exercise the native drop issuer separately from shortcut enablement, run
   `hqopendrop common` or `hqopendrop rare` after granting. These consume stock and
   create real native tasks through the existing bridge. Inspect injected JSON for
   GrantedItems/GrantedCurrencies/DetailedInventory and matching ClientTx. Require
   OpenSupplyPackageSuccess and verify `hqeconomy` before/after. A new command is a
   new transaction and intentionally consumes another owned drop.
3. Regression-check Major Howard from both menu HQ and in-world: daily/weekly/
   contract lists, accept and abandon immediately. Run `aefetch scheduled` and
   `aecache` again; compare native ready/cache with the known working behavior.
4. Run `hqnative` before and after opening Quartermaster from each entry point.
   Capture `[HQ native] SKU page success/failure`, raw fetched flag, Marketplace
   111 and 242. If fetched=1 but the button is grey, recover the remaining Lua
   gate; do not force this flag. If failure is logged, inspect SDK read-side framing.
   Record the action order and allow a few seconds between each click.
5. Open Mail and require no fabricated claimable messages and no crash. An empty
   visible inbox still has at least 14 allocated protocol slots. If a claim button
   remains for a cleared slot, capture its LUI path before further payload changes.
6. For payroll, run `aeevent payroll`, `aefetch user`, `hqeconomy`. Existing local
   policy makes payroll_officer claimable unless already on cooldown. Separately
   attempt one kiosk pickup and one claim with tracing enabled; record Reward 11
   parameters, injected AE action/group, any Marketplace or MarketingComms requests,
   and the precise error. Require +200 currency 2 once only after a successful
   claim; this native claim behavior is still unresolved, not a passed check.
7. Restart and verify persistence. Check Zombies separately; no game-level Zombies
   test was run here. Its mail branch and existing AE transport remain untouched.

### Validation and precise remaining work

Release builds pass after premake regeneration, using the supplied MSBuild commands.
The standalone harness builds and passes when executed from build/research/hq-tests.
Logs are hq-slice3-stage{1,2,3}-{build,tests,harness}.log. Added tests cover captured
SKU query/truncation, minimum and bounded Mail allocation with zero IDs, native drop
vocabulary, debit/grant, reload replay, transaction conflicts, depletion, malformed
requests, and overflow rollback. Existing Orders/payroll/claim tests still pass.
The harness does not execute native detours, LUI, protobuf deserializers or animations.

Remaining required fixes: recover task 242's read-side result and high-level issuer,
then implement its actual schema; recover the exact menu gating expression; capture
and trace payroll's actual native claim task and implement the missing completion
path. The newest available debug evidence cannot establish those later clicks.
S2xFull task-242 chain: 11CD4551 <- A41A99 <- 20C55F <- 11A28228 <- A41A70,
with incoming external block 11FDE456. The recovered external block starts with
R15=RCX, RDX=RCX+8, RBP=R8+0x10, then traverses context bytes. Resolve its caller
and result vtable; do not install hooks at external trampoline offsets.
SKU cache/readiness is now observable via hqnative, so the next run can distinguish
catalog completion from other UI gates. Keep group-0 AE membership checks intact.

Supporting notes: slice3-quartermaster.md, slice3-mail.md, slice3-supply-drops.md;
Ghidra output in ghidra/decomp-slice3. All source/research changes are confined to
src/client and build/research. Existing untracked root run-47992/ was left untouched.

## Slice 4 - 2026-09-12

Payroll settlement, item metadata persistence/audit replies, a native-schema
conversion acknowledgement and discriminating console diagnostics are delivered.
**Quartermaster enablement and the reported Mail claim error are not claimed fixed
or game-verified.** The owner's working Orders board and native Supply Drop reveal
are the regression baseline. No game was launched and no installed-game or data/
files were modified. Changes are confined to src/client and build/research.

### Evidence and commits

- 9187a22: preserve PID 40144 dumps, decode and list every logged request/reply
  observation in run-40144/actions.txt; slice4-evidence.md summarizes UI sequences.
- 247b801: initial provisional 242 acknowledgement, bounded parser and hqvendor.
  Its store-UUID interpretation is superseded by 3f40910 below.
- c70b620: native payroll settlement and hqmail; trace actual Mail response and
  Reward 12 bytes. Existing non-claimable Mail allocation retained.
- 9ccb818: task 168 putInventoryItemsData, persistent metadata and one audit result.
- 3f40910: recover actual WWII 242 response reader, correct conversion schema,
  add native conversion completion/result diagnostics and correct trace provenance.

There is no startup banner in console.log: the preserved slice starts at the
last authentication boundary before PID 40144. Authentication diagnostics are
redacted. Non-AE reply bytes were not dumped by the installed version; actions.txt
clearly labels source-reconstructed replies and unavailable non-HQ replies.
All three unscoped task168 files match PID 40144 lengths and logged byte previews.
The older PID 57268 168_001 was overwritten by the newer 312-byte file. An initial
comparison with that older console slice was corrected in the final evidence.
PID-scoped HQ dumps are retained unchanged. No exact click timestamps or additional
manual hqnative output appear, so network order is established but click attribution
is limited to the observed load/action sequence and the owner's account.

### Established behavior versus local policy

**Quartermaster / task 242:** It is applyConversionRule, not a store query.
The UUID is a rule ID. Engine.Inventory_ApplyConversionRule registration B39590
points to 121250 -> 278180, group 5. Success 27A4C0, failure 27A460. Response
constructor A4C310 installs vtable C63578; read-side A4C850 consumes field 1
ClientTx string (capacity 25), field 2 uint64, field 3 nested rule descriptor,
fields 4/5/6 repeated objects. Nested reader A4C7B0 expects strings with capacities
16/256/37 and uint32 field 4. Success applies currencies from task-data +210/count
+21C (stride 98), inventory +220/count +22C (stride F0), and emits event 7E.
These arrays are count-guarded; an empty collection is safe here.

Final 242 reply is an 82-byte protobuf body for the captured Tx, enclosed in
bdStructBuffer framing: matching ClientTx, zero scalar, nested context/empty
name/captured UUID/one scalar, zero currency/item/extra records. Types and limits
are established; scalar business meanings and no-op conversion policy are still
provisional. Only the captured UUID with quantity 1 is accepted. Unknown rules
fail instead of granting guessed rewards. The SDK accepts absent fields, so the
old typed empty struct is not proof of parse failure. Native callback counters
now establish whether this step completes regardless of vendor button state.
See slice4-quartermaster.md and ghidra/decomp-slice4.

Task 111 remains unchanged: PID 40144 confirms its terminal empty SKU page
succeeds and sets readiness. Engine.Inventory_AreSKUsFetched (120610 -> 278400)
reads 81038A8 with inventory-enable override. hqvendor also prints inventory
ready/count (80385A8/80385A4, used by flush 27D6B0), pending metadata (819B568),
four vendor/payroll switches, conversion counters and last native result fields.
The complete main-menu Lua expression and entitlement readiness flag remain
unlocated. No readiness flag or vendor gate is forced.

**Mail:** Only MarketingComms 6 is captured; no viewed report, redeem request or
claim_achievement_reward occurs. The 14 allocated ID-zero slots already meet the
native non-claimable contract: MarketingGetMessage 125020 -> 3722F0 checks ready
8A14F84 and message ID +10 through pointer 8A15010, stride 1CA0. ID zero returns
no Lua message; redeem 3726F0 also rejects it before transport. hqmail prints IDs,
content/code lengths without reading/displaying message contents. The response
is now traced. No codes, claimable placeholders, redemption task or reward was
invented. The owner's error remains unexplained until the live slots and the
actual UI claim path are observed. The minimum allocated array and mail_guard
remain intact; Zombies Mail is unchanged.

**Payroll:** The actual flow is Reward 12 picked_up_payroll, first timestamp
1789255507000000, parameters 1=1/2=0, repeatedly retransmitted; a later batch adds
1789256008000000. There is no native AE claim. Native event processing now grants
200 currency 2 and marks payroll finished in one hq_economy::transact. Permanent
payroll:period receipts select the UTC four-hour bucket from the event timestamp.
Same-period different timestamps, aliases, reloads and stale later-period retries
do not grant again. Prior manual claims in that period are respected. Future
or zero timestamps reject; stale periods acknowledge without a grant. Overflow
or save failure rolls back; task12 processing failure returns a task failure.
This fixed UTC-bucket schedule is local policy, not a retail reconstruction.
The synthetic aeevent payroll command retains its older claimable test behavior.
Immediate native wallet push and kiosk success animation are not established;
persisted balance and the next Marketplace 132 fetch must be checked separately.

**Supply Drops / task 168:** Owner verified the native common-drop reveal. The
opening router, generic AE injection, task-table guard and empty Reward AE replies
are unchanged. Task168 is putInventoryItemsData, with an independent ClientTx;
it also runs at startup. Native Inventory_ClearNewFlag -> 27CA90 -> 27A3A0 sets
metadata bit 1. Flush 27D6B0 queues up to 30 records. Success 27BED0 clears pending
write flags; failure 27BCD0 retries. SDK task numbering and audit-log deserializer
corroborate the exact captured request and single-string result.

Task168 validates local owner, known item/collision, bounded record/blob counts,
and stores metadata without modifying quantities/currency. Optional itemData byte
arrays preserve schemaVersion 1 compatibility. Inventory165 returns saved metadata.
Permanent bounded fingerprints reject conflicting Tx reuse and prevent stale
replays from overwriting newer flags. Reply count=1/total=1 followed by the typed
transaction string satisfies bdMarketplaceAuditLogResult (capacity 25). Unknown
items, malformed requests, conflicts and save failure fail safely. Zombies uses
the prior empty-success fallback. See slice4-marketplace-168.md for SDK sources.

### Operator verification - console commands first

Launch the built client with -demonware_debug. Wait five seconds in the frontend.
Before any UI action run these commands and record their output:

```
hqvendor
hqmail
hqnative
hqeconomy
aefetch scheduled
aecache
```

1. **Quartermaster menu:** Attempt Play > HQ > Quartermaster, then run hqvendor.
   Record whether the entry was grey, whether any new 242 request occurred, and
   native conversion success/failure counts. Expect SKU effective/raw=1 and
   inventoryReady=1 after fetching, allow_hub_vendor_menu=1, relevant killswitches
   zero. Require the conversion callback to succeed, responseTx to match the
   traced 242 ClientTx, and zero result-array counts under the no-op policy.
   A successful conversion with a grey button isolates the remaining Lua gate.
2. **Quartermaster world:** Enter full Headquarters, run hqvendor, attempt the
   vendor once, run hqvendor again. Record the visible flicker/error and request
   counter delta separately from the world-load 242. Capture the complete log
   and PID-scoped marketplace_242_response dump; do not equate loading-zone unload
   with vendor failure. If conversion fails, compare the new reply with A4C850.
3. **Mail:** Run hqmail before and after opening Mail. Expect ready=1, a non-null
   allocation and 14 IDs zero with zero code/content lengths. Require no claimable
   message. If a claim button is still shown, record its title/category/index and
   hqmail output; the next code target is that Lua path. Do not keep clicking a
   cleared slot to manufacture a network claim. Keep marketing_6_response and any
   marketing_4/redemption dumps for correlation.
4. **Payroll:** Record currency 2 with hqeconomy, pick up payroll once, and run
   hqeconomy again after the Reward12 request. Expect +200 if this UTC period has
   no native receipt/manual claim; otherwise +0. Repeat pickup/claim attempts and
   wait for at least two repeated event batches: balance must not rise again.
   Restart in the same period and verify persistence and the native balance after
   Marketplace132. In a new UTC four-hour bucket, a fresh pickup may add 200;
   replaying an old timestamp must not. Record kiosk error/animation independently
   of saved balance. Do not use aeevent payroll as proof of native settlement.
5. **Orders regression:** Open Major Howard from both HQ entry points. Fetch lists,
   accept and abandon one order as before; compare aecache readiness and native
   completion. No AE injection/router membership or reply framing was changed.
6. **Drop regression:** With an owned common drop, open one via the working
   shortcut and require three native reveal cards, one consumed drop and persisted
   loot. If stock is needed, hqgrant item 1 1 then restart for inventory165 refresh.
   Do not run hqopendrop as a harmless diagnostic: it consumes an owned drop.
   Task168 should now be handled, have a one-result audit response and persist
   itemData. Restart and verify quantities stay correct and old new-item flags
   stay cleared. hqvendor dirtyMetadata should drain after successful writes.
7. Check Zombies separately if desired; no game-level Zombies test was run.
   Its existing Mail/AE branches and task168 fallback have been preserved.

### Validation and precise remaining work

Premake regenerated with ./tools/premake5.exe vs2022. The requested Release x64
MSBuild solution and standalone harness build/run pass. Logs are
hq-slice4-stage{1,2,3,4}-{build,tests,harness}.log and
hq-slice4-conversion-{build,tests,harness}.log for the final source changes.
Harness covers captured 242/168 framing, all truncated prefixes, wrong owner,
metadata persistence/conflicts/stale replay, one allocated audit result, payroll
period/reload/alias/legacy-claim protection, plus existing Orders/drop/malformed
input/atomic save tests. It cannot execute native hooks, Lua or game animations.

Remaining: establish the exact Quartermaster LUI boolean expression and any
entitlement/onboarding inputs; verify the recovered conversion reply on the native
callback and decide whether the known conversion rule needs real business effects;
identify why a cleared Mail slot still offers the owner's claim interaction;
recover the payroll wallet/UI notification path if persistence succeeds but the
kiosk still errors. Unknown conversion rules and purchase/catalog business logic
remain unsupported. None of these remaining UI outcomes is reported as passed.

Existing untracked root run-47992/ was left untouched. The archived evidence and
final research notes are the reproducible handoff for the next operator walk.


## Slice 5 - 2026-09-12

Payroll persistence is proved by the owner's PID 46420 store and traces. Native
wallet synchronization and a payroll completion notification are implemented.
Quartermaster has a bounded nonempty catalog experiment and broader diagnostics.
Mail now follows an explicit empty-inbox policy at the native accessor as well as
the allocated wire response. **The requested game-level outcomes are not claimed
verified: no game was launched.** The exact Quartermaster menu predicate and the
first payroll/Mail visible error paths were not present in the available evidence.

### Evidence and staged commits

- fd571db: archive PID 46420, native wallet reader/schema recovery, hqwallet,
  absolute balance synchronization and persisted payroll completion push.
- 180b7f2: enumerate bindings/globals, add diagnostic output, filtered display SKU
  and reject native/direct purchases.
- d5500a4: empty native Mail inbox, lookup diagnostics, fetch count/capacity,
  plus delayed RVA resolution, terminated SKU blobs and notification retry safety.
- This report commit updates the owner's build/RUNBOOK.md section 9 as explicitly
  requested. That file is the sole exception to src/client and build/research.

run-46420 contains 72 PID-scoped dumps, other log-referenced dumps preserved as
found, console-from-launch.log, hq_economy.json and actions.txt. The last auth
boundary supplies the launch slice; authentication diagnostics are redacted.
The ordered listing includes captured JSON/hex and labels source-derived replies.
There are no manual hqmail outputs or precise click timestamps. Sequences are
frontend load, slim HQ load, payroll pickup/retries, full HQ load, Orders actions.
Unscoped files are not assumed immutable or sufficient evidence of response bytes.

Store revision 66 has currency2=200 and payroll_officer finished, receipt
payroll:124254  ->  1789259964000000, completionTimestamp1789259963. This establishes
settlement, not the top-right HUD. One Marketplace132 occurs at frontend load;
no 130 or balance refresh follows pickup. No claim_achievement_reward request
occurs. Both conversion callbacks succeed with SKU/inventory ready, switches
correct and zero result arrays. The owner still saw Quartermaster grey/flicker,
Mail claim errors and a first payroll error on integration 8fb25af; these are
current observations, not merely the earlier slice3 symptoms.

### Established versus guessed

**Wallet/payroll:** Engine registration 140AE0 installs table B37F30. Entry B39520
pairs Inventory_GetCurrencyBalance with 120940  -> 279780. It reads 13 currency
records at 7F6FBB8, stride 38, byte ID+20/u32 value+24, count 7F6FE90, ready 7F6FE94,
controller stride 2E0. Fetch 278A50 clears with 20CBA0, completes via 27B230; native
reader A49900 consumes byte ID/u32 balance. Existing132 serialization was correct.
MP130 now shares that serializer and context/limit parser; 130's request schema
is an unobserved compatibility assumption, not a captured success. Each currency
record is now traced. hqwallet prints ready/count, all records and the binding's
currency2 result. The association with the owner's top-right label still needs
an actual menu check; currency2/200/four-hour buckets remain the local policy.

Main-thread synchronization waits for native balance readiness and uses27D510
(absolute setter 27DC10 plus inventory eventType 5) when persisted amounts differ.
No second grant or forced ready flag is involved. Native limits remain: thirteen
slots and signed Lua integer display. This covers post-claim currency changes
without requiring a network fetch that the captured pickup never submitted.

A newly persisted payroll settlement queues a native achievement push. 13C480
reads name/kind/reason/status/progress/type and triggers; reason=completed emits
achievementEngine eventType 0 with success/ID/kind/challengeName/itemsReceived/
currenciesReceived. SET_CURRENCY_BALANCE inventory.currencies uses currency_id,
balance_before and balance_delta, consumed by27C480. The main-thread native
string bridge delivers it; retries/manual claims do not queue another reward.
The push schema is established; missing this push causing the first kiosk error
is an inference. This is a separate notification handler, not a fabricated AE
claim response. The group0 task filter, Orders router and drop opening stay intact.

**Quartermaster:** lui-vendor-bindings.txt records 113 matching registration pairs,
per-function decompiles, direct globals and recovered inventory/store callees.
Unexamined callees are explicitly listed; this is not an exhaustive transitive
analysis. hqvendor prints77 recovered runtime reference bases as raw8, plus
semantic wallet/SKU type/count/prices/items/inventory/conversion/dvar diagnostics.
Read-only string tables and LUI VM pointers are omitted from the raw dump.
Store registration 370500 supplies namespace Store from B655F0; Inventory_* are
Engine members. UserCanAccessStore and FoundPlayerPurchases return true;
ShowEmptyStoreDialog returns false. 27A210 requires inventory and balance ready.
GetAllSKUIDs requires matching type 81038AC, ready 81038A8, and nonzero IDs from
400 fixed records at 81038B0/stride 2E8. None proves the actual menu enable predicate.

Task 111 read-side chain A4A5A0  -> A4A510  -> A4A2C0 is now recovered, including blobs,
price records and type/maxQuantity/soldOut suffix. A76950 confirms typed blob reads.
One local type 100 offer uses SKU1/product1, sd_mp (table itemGUID1), price 200 of
currency2 and maxQuantity 1. It is selected only on page1 with matching filters and
empty token; page2 and collection type 150 stay empty. Both blobs are terminated
for native string consumers. Fixed product item records are initialized with
zero count, not a null dynamic array. SKU/product IDs, pricing and metadata
meaning are provisional. No retail product catalog is claimed. The native
purchase issuer276580 returns an initialized empty transaction (Lua nil), and
DW 106 rejects direct requests. No payment or ownership changes can follow this
offer. A nonempty catalog curing the grey/flicker remains a testable hypothesis.

**Mail:** A50A60 allocates1CA0-byte repeated messages; A70ED0 confirms field 1
uint64 message ID and content/code blob lengths. The existing14 ID-zero slots
are well-formed. 3723B0 returns the cumulative slot count for an unknown category;
3722F0/3726F0 then read it without checking the response count. This establishes
an out-of-range path, not its use during the owner's click. Only MarketingComms6
was captured; no claim request/error response can honestly be identified.

Chosen policy: local MP inbox exposes no claimable message. The native message
accessor returns false/empty output (MarketingGetMessage returns zero Lua values),
unread poll returns false, and stale redemption attempts are suppressed. The14
allocated protocol slots, size and storage remain intact. Native fetch success
logs count/capacity; reads/redeems log category/index/mapped slot/bounds. hqmail
prints these counters and avoids inspecting14 slots when size is smaller.
This makes the known accessor deterministic. A separate static kiosk claim
button can still require Lua investigation; its disappearance is not game-proved.

### Operator verification - console first

Use the new branch build, with -demonware_debug; wait five seconds in frontend.
Run and save this exact sequence before any UI action:

```
hqwallet
hqvendor
hqmail
hqeconomy
```

1. **Wallet:** expect native ready 1 and currency2 equal to hqeconomy (archived
   value200, adjusted for later owner activity). Check the top-right counter in
   both HQ entry routes and record its label/value. Save132_currency dumps and
   hqwallet output if mismatched. Do not infer visibility from the saved store.
2. **Payroll:** in an unreceipted UTC four-hour bucket, record wallet/store, pick
   up once, then repeat the four commands. Require exactly+200 and a finished
   kiosk/countdown without an error. Expect payroll_native_push and the delivered
   completion log; require currenciesReceived amount 200. Wait through two repeated
   Reward12 batches: no additional grant or reward push. Revisit and restart:
   store/native balance must agree. Existing payroll:124254 cannot pay again;
   test a fresh bucket without deleting receipts. Do not use aeevent payroll as
   evidence of native pickup. Record exact on-screen error if it persists.
3. **Quartermaster frontend:** hqvendor, attempt Play > HQ > Quartermaster, then
   hqvendor. In type 100 expect one SKU ID 1 with one price; type 150 may legitimately
   be empty. Preserve111_sku and native SKU callback output. Record whether grey,
   opened, or closed. A purchase attempt must return unavailable with unchanged
   wallet/inventory; this display catalog is not a functioning store.
4. **Quartermaster world:** hqvendor immediately before interacting and after
   the flicker/open. Record click time, SKU count/type, conversion counter deltas
   and any new task independently from world loading. If nonzero catalog and
   all flags still fail, recover the actual menu Lua/onboarding condition next.
5. **Mail:** hqmail before opening and after one attempt at each entry route.
   Require native fetch count >= 14, nonnull allocation, zero IDs/lengths, empty
   visible inbox and no claimable message. Save category/index access logs. If a
   claim control persists, record title/category/index and counter deltas; no
   delta identifies a path outside these MarketingComms bindings. A redeem attempt
   is suppressed and grants nothing. Keep Marketing6 response and any new tasks.
6. **Regressions:** Orders accept/abandon/claim from both routes; Supply Drops
   shortcut reveals three items, consumes one owned drop, and metadata168 drains.
   Use existing stock; hqopendrop consumes stock. Soak frontend/HQ90 seconds. Check
   Zombies independently: hooks and changed service branches are MP-only, but no
   game-level Zombies test was performed. Restart to verify persistence.

### Validation and precise remaining work

Premake regeneration, requested Release x64 solution build, standalone harness
build and harness run all pass. Logs: hq-slice5-premake.log and
hq-slice5-stage{1,2,3}-{build,harness,tests}.log. Final source is the stage3 build.
Tests cover native currency bytes, persisted completion push/replay suppression,
SKU read-order projection and filter/paging/truncated inputs, Mail bounds and all
prior economy/Orders/drop/payroll cases. These do not execute native detours,
SDK deserializers, Lua predicates or kiosk animations. No game/data files changed.
Existing untracked root run-47992/ was preserved.

Remaining required verification/research: exact top-right currency label/binding
argument; first-pickup success after native push; observed130 request if used;
actual Quartermaster menu Lua predicate, full transitive entitlement/onboarding
inputs and product metadata semantics; actual Mail button path if it bypasses
MarketingGetMessage. No missing trace or decompile is represented as a proven
UI fix. Supporting notes: slice5-payroll.md, slice5-quartermaster.md,
slice5-mail.md, lui-vendor-bindings.txt and ghidra/decomp-slice5.


## Slice 6 - 2026-09-12

Implemented currency7 Armory Credits and one-time payroll migration, a full
774-item collection catalog, atomic native Quartermaster purchasing, daily/weekly
roster reconciliation and native inventory refresh after grants/openings. Release
x64 and the rebuilt standalone harness pass. **No game was launched or operated;
Quartermaster entry, purchase animation and Major Howard UI outcomes await the
operator checks below.** No Steam or data/ files were modified. Existing root
run-47992/ and preexisting research artifacts were preserved.

### Commits and evidence

- 07f1e56: currency correction, documented payroll constant and receipt migration.
- 491d370: full catalog, native cache readers and atomic native purchases.
- 6314e17: persisted current-period offers and rollover/abandon tests.
- a61010a: native booster quantity refresh and diagnostics.
- b414220: aligned native SKU storage, logarithmic per-item price lookup and
  rejection of a migration save that would exceed the store receipt limit.
- This report/status commit completes the research handoff.

The operator's lui-trace-quartermaster.txt records AreSKUsFetched=true,
GetAllSKUIDs(100)={}, cached collection prices0/currency0 and hammer balance via
GetCurrencyBalance(0,7). The operator identified currency2's +200 as COD Points.
The trace also identifies conversion242 as grantIdToken_130. Its acknowledged
startup rule and existing response remain unchanged. The empty catalog is the
operator-established Quartermaster gate; successful entry after these changes is
still a live verification requirement, not a result inferred from a C++ test.

At archival time the newest task111 PID was51584. run-51584 contains44 PID-scoped
DW dump files, our console-redacted.log copied as found (may span launches), a
read-only copy of hq_economy.json and slice6-observations.txt. The preexisting
console-from-launch.log was left untouched. The store has two in-progress dailies
and two available dailies dated20708 alongside a20709 order, demonstrating the
stale-roster failure. Captured requests: page1/limit100, zero ID filters, one byte
type150 on initial load and100 on HQ load; empty token, zero padding. All captured
task111 request bytes are retained. New research decompiles are in
ghidra/decomp-slice6; detailed notes: slice6-currency.md,
slice6-quartermaster.md, slice6-rollover.md and slice6-inventory.md.

### Established behavior and explicit local policies

**Currency/payroll.** Armory Credits=7, COD Points=2 are established by operator
binding/output evidence. Native279780 reads thirteen wallet slots;27D510 updates
absolute balances and notifies the UI. All new local AC rewards and pending known
local AC definitions use7. payroll_amount=200 remains a guess: extracted payroll
strings and research tables did not recover a retail amount or currency table.
Four-hour UTC settlement policy is unchanged.

Migration marker migration:payroll-currency7-v1 lives in the transaction ledger
and records the transferred amount. Valid payroll timestamps and manual payroll
claim receipts account for200 each, conservatively taking max(native,manual) per
day to avoid counting manual-claim acknowledgements twice. Ambiguous historical
overlaps can under-recover; arbitrary CP is never inferred as payroll. Transfer
is capped by remaining CP and AC uint32 headroom. No other currencies change.
Marker, balances and corrected pending rewards persist atomically; save failure
preserves the original file. Reload/restart cannot repeat the transfer.

**Catalog.** itemscollections membership joins collections IDs. The generated
client header contains774 distinct purchasable members. It excludes column1
collection-completion rewards, unknown collections and supply-drop GUIDs1/2.
Neither research tables nor data/ are runtime dependencies. Types100 and150 are
supported; unknown types and unmatched IDs yield terminal empty pages. Filtering
precedes pagination, including mixed byte types and duplicate filters. Native
27B700 terminates only on count<limit, so exact multiples receive a final empty
page. Task111 has no NextPageToken result field: appending one would corrupt its
typed records. Native requests use page numbers and empty token; a matching
decimal page token is accepted for explicit callers and other tokens fail.
All blobs/strings terminate within the recovered0x370 layout and fixed price
capacity. No supply-drop sale SKU is fabricated from a drop-type definition.

One guessed price table is used everywhere: native rarity0/1/2/3/4 maps to
50/250/1000/3000/5000 AC. Native652330 reads item column29. Main-thread asset
loading publishes rarity; unavailable/invalid rarity uses common as a documented
fallback. SKU ID/product ID=item GUID and decimal skuData are local metadata
policy. Retail prices/product catalog metadata were not recovered.

Two additional native constraints required changes. Both generic SKU cache and
Lua120760's stack buffer hold400, fewer than774. The original buffer/cache are
left bounded;120760 now creates a GC-rooted Lua table for the full catalog once
the native fetched flag is set.2797E0 supplies stable aligned0x2E8 records with
ten initialized fixed product slots and one populated item/price. Its five
recovered callers consume the output pointer.274970 reads a separate collection
price cache and hard-codes currency6; its MP hook returns the same local price
with established HUD currency7. Increasing task111 alone would not fix these.

**Purchase.** The implemented path is native issuer276580, invoked by Lua11FDF0;
direct DW106 stays explicitly unsupported. No unknown SDK success payload is
fabricated. Native transaction generation8390A0 returns the original25-byte
transaction representation. Next main tick settles one item through transact:
debit7, grant GUID/quantity1, store purchase:<tx> -> GUID:1. Same-tx replay after
reload returns success without a second mutation; conflicting tx, duplicate
ownership, missing SKU or invalid quantity fails. Insufficient funds is BD code
0x1F47 and leaves wallet/inventory/revision unchanged.

Decompiled SDK success27BA60 reads allocated currency count/pointer+320/+328 and
inventory+338/+340, applies native updates, then publishes completion via276220.
The local path applies the corresponding absolute wallet/item updates and
D5F30/2752E0 refresh, then calls their shared event publisher275360. The callback
contract is inventoryEventType4, inventoryTaskType24, success and transaction ID.
Native failure276290 also publishes this boolean event; there is no error-code
field in that Lua completion contract. Numeric errors are logged and traced as
native_purchase. Success is published only after persistence. The operator must
verify UI success and ownership; no game callback was executed by the harness.

**Offers.** Each fetch reconciles current day/week rosters and persists only if
needed. Three live slots per kind count active/claimable plus available; active
progress/activation/rewards survive rollover, with today's offerDay. Old available
rows expire and replacements use today. Abandon resets progress/usage and
reoffers today. NextPeriodStartTimes and weekly expiration use actual UTC epoch
boundaries, independent of daily rollover. Contracts retain their previous policy.
Because the local weekly definition pool has only three entries, exhausted
completed definitions may be reoffered to keep three slots; unused definitions
are preferred. This is explicit local replenishment policy, not retail repeat
limits. Receipt identity persists until reactivation; an old ClientTx cannot
grant a new instance. A preexisting malformed roster with >3 active orders is
preserved rather than silently abandoning earned progress; no offers are added.

**Supply drops.** Registration123870 ->2AEEA0 looks up supplydroptypes column1
(type) to column5(GUID), then279480/279300 reads native quantity+4. Type0 is
GUID1/common, type1 is GUID2/rare. Task165 already returns positive stored drop
quantities; success27B400 uses20C850's projection, identical to20C8B0 used by
purchase updates. New main-thread sync waits for inventoryReady, compares raw
native quantities and sends absolute32-byte updates only when different, including
zero after last-drop opening or expiry. Identical quantities do not redirty168;
metadata acknowledgements and drop reveal/consume logic are unchanged. Native
entitlement/cheat overrides and Zombies behavior remain unchanged.

### Operator verification - console first

Use the branch's new Release executable with -demonware_debug. Installing/running
it is the operator's step; this work did neither. Keep an existing profile/store
backup, retain receipts, and wait for frontend inventory/catalog fetches to finish.
Capture these commands before opening any vendor:

```
hqwallet
hqvendor
hqeconomy
```

1. **Wallet/migration:** hqwallet must show native ready1 and currency7 equal to
   the stored AC balance. Currency2 should fall only by the receipt-accounted
   migration amount; marker appears once. Restart/reload: no second transfer.
   In a fresh four-hour bucket, collect payroll once: +200 currency7, no CP gain;
   native completion push settles the kiosk. Repeat pickup/poll/restart: no extra
   grant. Record any first-pickup error, rather than inferring success from storage.
2. **Quartermaster entry:** Play > HQ > Quartermaster should be enabled and show
   a priced collection list. Also test the in-world Quartermaster. hqvendor prints
   fullCollectionSKUs=774; the bounded raw generic cache may show400, which is
   expected. AreSKUsFetched must end true after all pages. With the tracer,
   GetAllSKUIDs(100) should contain774 IDs and known collection-item price queries
   should return nonzero price/currency7. Save all111 request/reply dumps and
   native SKU callback logs if it remains disabled or prices stay zero.
3. **Buy one unowned item:** record its GUID, displayed price and wallet; ensure
   sufficient AC (earn payroll or explicitly use hqgrant currency 7 <amount> for
   an operator test). Buy quantity1. Expect one price debit, inventory quantity1,
   a successful UI completion and refreshed owned state. Run the three commands,
   revisit/restart and verify persistence. The purchase:<tx> receipt must agree.
   Buying an unaffordable item must show failure and preserve balances/inventory;
   native_purchase should log error8007 (0x1F47). Existing ownership must not charge
   again. Preserve transaction string and click time for callback discrepancies.
4. **Major Howard after abandon:** accept three dailies, abandon one, then reopen
   Orders. Expect two in progress plus one available, and reaccept without an
   empty slot. hqeconomy should show today's offerDay. Across the next UTC day,
   active progress stays, remaining slots use current offers; weekly selection
   stays independent until its boundary. Verify next-reset countdowns. Repeat the
   abandon check for weekly orders. Do not edit the game clock/store to fake this.
5. **Drops/regressions:** hqvendor's type0/common and type1/rare quantities should
   agree with stored GUID1/2 after165. An explicit hqgrant item 1 1 should appear
   without restarting; opening consumes one, reveals three items, and opening the
   last leaves zero. Save inventory_native_refresh and165/168 dumps. Check168
   drains, existing Orders claims/replays, payroll settle and Mail's prior empty
   inbox behavior. Check Zombies separately; no game-level Zombies regression
   test has been performed. Keep exact menu labels/click times on any failure.

### Validation

Requested premake generation and Release x64 MSBuild solution build pass. The
standalone hq-tests.vcxproj rebuild passes; bin/hq-tests.exe was run from inside
build/research/hq-tests and passes. Logs: hq-slice6-premake.log,
hq-slice6-stage{1,2,3,4}-{build,harness,tests}.log and
hq-slice6-final-{build,harness,tests}.log. Final build includes the hardening commit.

Coverage includes migration overlap/spent credits/one-time behavior,774-item
pagination and malformed byte requests, rarity bounds, atomic purchase and
replay/error cases, accept3/abandon1 through the actual router, deterministic
daily/weekly rollovers, current dates/boundaries, native inventory projection and
expiry, plus existing drop/payroll/metadata/Mail/Zombies-storage regressions. A
corrupted HQ store is reloaded in the harness and still cannot hide independent
Zombies records. Tests do not execute detours, Lua callbacks or native SDK readers.
Runtime price fallback, local replenishment policy and outstanding UI verification
are explicit above; no live outcome is represented as tested.

## Slice 7 â€” purchase ownership, Quartermaster catalog, hosted order events (2026-09-13)

Started from `ba06662` on `feat/39-hq-economy`. The pre-existing untracked
`run-47992/` was left alone. No game launch, installation, Steam-directory write,
or data/ change was performed. The newest PID's 136 HQ dumps were archived to
`build/research/run-64176/dw/` before analysis; its last Lua-capture log slice is
`run-64176/console-from-last-capture.log`.

### Purchase ownership: established cause and fix

The archived native purchase receipts prove Crab (GUID 33554731 / 0x200012B)
was granted: `_92.bin` has error=0 and `_93.bin` rejects another purchase with
error=8010. The persistent store already regarded it as owned. The defect was
the native expiration representation, not a missing debit/grant transaction.

`ui_utility_mp_collectionutils.dec.lua` uses
`Engine.Inventory_IsItemGUIDUsableForPlayer` for the collection item and
`Inventory_GetCollectionProgress` for collected totals; reward ownership uses
`Inventory_GetItemQuantity`. The exact binding chain is:

| Binding / helper | Native reader |
|---|---|
| Inventory_GetItemQuantity (11DEB0) | 279480 -> 279300, reads quantity at +4 |
| Inventory_IsItemGUIDUsableForPlayer (123710) | 27A310 -> 279300 and 27A260 |
| Inventory_GetCollectionProgress (120F30) | 274A70 loops collection GUIDs through 27A310 |

All use the GUID hash-indexed inventory at RVA 0x7F78178, 0x68-byte entries,
controller stride 0xC8438. Entry +8 is absolute expiry and +0x10 is duration.
New decompiles in `ghidra/decomp-slice7/` establish that 27A260 treats the old
expiry=0 / duration=-1 pair as expired. Permanent items require UINT32_MAX /
INT64_MAX. Thus quantity could be 1 while usable and collected were false.

`hq_inventory_cache::project` now supplies both permanent sentinels. Task 165
uses the same projection through `fill_result`. The main-thread inventory sync
repairs expiry/duration even when the cached quantity already matches, so an
already purchased Crab is repaired without buying again. Purchase insertion
still uses native 27DD30, collection refresh D5F30, inventory event 2, and
transaction completion event 24; the native absolute wallet setter 27D510 emits
currency event 5 for currency 6 before completion. Supply-drop DetailedInventory
also uses the permanent duration sentinel, avoiding an expired intermediate
record before the periodic repair.

The existing native purchase issuer remains the supported route. Task 106 is
still explicitly rejected in MP: no guessed whole-SDK purchase reply is sent.
Harness coverage serializes the **granted purchase inventory record** in the
bdMarketplaceInventory wire shape consumed by native purchase success 27BA60 /
20C8B0 and task 165, reads every field back, and checks the permanent sentinels.
This is not a live native SDK-deserializer test.

### Contracts, CWL, and promotional fields

The catalog now contains 774 collection entries and 21 leading vendor entries:
the two required drops, three local contracts, and all 16 CWL packs. The drops
retain tags MP/ZM and their 1000 AC prices. Every vendor entry has
`name;description`, under the 64-byte native limit.

Established Lua rules: `QuarterMasterUtils.GetContractCurrencies` scans `c`,
converts it to an achievement ID, and checks the first SKU item's quantity;
`ActivateMissedContracts` activates those IDs. `C` links Quartermaster details
to a scheduled contract. `SKUType.Contracts` is 201, so both task-111 queries
and the native GetAllSKUIDs hook support that filtered view. The general
Quartermaster view also contains the contracts for the shared Lua cache.

| Local SKU/token | c / C | Definition | AC price |
|---|---|---|---|
| 0x0800F021 | 33 | contract_mp_1 | 25 |
| 0x0800F022 | 34 | contract_mp_2 | 50 |
| 0x0800F023 | 35 | contract_mp_3 | 75 |

Token GUIDs, prices and English descriptions are local policy, not recovered
retail offers. Contract-specific menu scripts are not present in the supplied
294 decompiles; tab navigation to `contracts_menu`, the shared helpers, type 201
and definition IDs are established, but live contract rendering/activation is
still an operator check. Existing achievement activation behavior is retained.

`ui_s2_quartermaster_cwl_menu_uc.dec.lua` always builds 16 tiles, looking up
CWL_CWL, CWL_EF, CWL_ENVY, CWL_EPSI, CWL_EU, CWL_EVIL, CWL_FAZE, CWL_LUMI,
CWL_MIND, CWL_OPT, CWL_RED, CWL_RISE, CWL_SPLY, CWL_UNI, CWL_VITA and CWL_KALI.
All tags now exist and use the shipped tag-to-image mapping. Each local pack
costs 1000 AC and grants five actual cosmetic GUIDs grouped in the decompiled
`quartermaster_supply_drop_details_uc` table (emblem, calling card, helmet,
charm, camo). Bundle composition and AC pricing are local policy. The emblem
GUID doubles as the local SKU and ownership limiter. Products, synthesized
native SKU item arrays and atomic purchase grants share the same five-item list.
Repeat/replayed purchases cannot double charge. The CWL tile model calls its
price `CoDPointsPrice`; check the displayed currency icon in the operator walk,
since the local offers deliberately use currency 6 rather than paid CP.

The 0x2E8 native SKU slot layout is established by binding 11FF90:
promotionalText +0x25C (64 bytes), skuData +0x29C (64 bytes), product ID +0x240,
item count +0x244, item IDs +0x30+i*0x38 and quantities +0x34+i*0x38,
currency +0x24C and price +0x250, price count +0x2E1. The inherited payroll
follow-up already wrote promo +0x25C; Slice 7 supplies both text halves and
initializes every advertised bundle item record. No empty advertised array is
introduced.

### Server-to-client reward wire and application

The existing #53 relay owns the shared queue, XUID lookup and
CG_DeployServerCommandString detour. Zombies keeps its original
`s2x_hc <group> <challenge>` handling and 128-entry bound. MP extends it with:

```
s2x_hq 1 <recipient-XUID> <timestamp> <event-name-or-ID> <parameter-count> [<selector> <uint64-value>]...
```

All numbers are decimal; event names are at most 64 lowercase letters, digits
or underscores. Timestamp is nonnegative int64. Limit: 16 parameters, selectors
1..64 with no duplicates, 768 bytes for the whole command. Version, recipient,
numeric overflow, missing/extra fields, oversized input and invalid names are
validated before application. No game command text can be embedded in a token.

The existing bounded task-11 parser accepts at most 48 users x 100 events and
only steam account batches are routed. On dedicated/listen servers, remote
events queue by XUID (4800 commands maximum, 32 drained per server tick).
Party_FindMemberByXUID resolves the current svs_clients index; disconnected or
unready clients are dropped. Delivery uses SV_SendServerCommand with
SV_CMD_RELIABLE. It does not use an unauthenticated connectionless message.
Local listen-host events go straight to submit_hq_event once; remote events
are not applied to the hosting process's HQ store. The receiver rechecks the
recipient against its Steam ID and calls the same submit_hq_event function as
task 12. Zombies and secondary local clients do not apply MP relay messages.
Queue/receiver failures are caught; malformed input cannot apply a partial event.

Trust boundary: the relay trusts the hosting server, so a modified dedicated or
listen server can forge reward events (order progress, payroll) for its connected
clients - the same trust boundary the existing Zombies hidden-challenge relay
already accepts, so only play on servers you trust for economy progress.

The shared event store preserves existing timestamp/parameter replay receipts
(zero timestamps remain intentionally non-deduplicated). Enabled daily/weekly
and contract counters use dwgamechallenges.csv event IDs: kills=1,
headshots=1 with selector 6 equal to 1, multi-kills=2, streaks=4, end-game=5,
1v1=7 and social=10. **weekly_ch_wins maps to event 5 with no predicate in that
table.** Do not claim a winner-only interpretation has been proved: observe
both a win and a loss if that distinction matters. Counters stop at target and
become claimable through the existing store/achievement refresh path.

With -demonware_debug, retain `hq_reward_11`, `hq_relay_forwarded`,
`hq_relay_applied`, `hq_relay_rejected` dumps and the normal `[HQ event]` lines.
The console queue fix and structured task-11/12 acknowledgements are retained.

### Exact operator verification (not performed by this slice)

1. Use this branch's Release build with -demonware_debug. Run `hqwallet`,
   `hqeconomy`, `hqvendor` and `aecache`. Revisit Crab's collection first:
   the existing purchase should be collected without another debit. Buy one
   different unowned affordable item. Expect one price debit, an immediate
   updated hammer counter, collected state and collection total increment.
   Exit/re-enter the menu and restart normally to confirm persistence. An
   unaffordable purchase must leave the wallet and inventory unchanged.
2. Open Quartermaster from the HQ menu and in world. Deals must retain both
   rare drops, their names/descriptions, images and 1000 AC prices. Contracts
   must list the three priced contracts; purchase/activate one and check its
   definition ID. CWL must populate all 16 tiles with names, descriptions and
   team images; inspect a pack's five items and currency icon. If purchasing a
   pack, verify all five grants and a single debit. Retain Lua errors if the
   Contracts menu still fails; its full menu script is not in this archive.
3. Accept daily kills (0/10) and a weekly kills order. Start the owner's own
   dedicated server using the matching build, `s2x.exe -dedicated ...`, with
   the owner's normal server arguments and -demonware_debug. Join it through
   Server Browser as a remote player, get kills/headshots and finish a match.
   Server evidence: task 11 plus relay_forwarded for the player's XUID.
   Client evidence: relay_applied plus `[HQ event] 1`; return to Orders and
   expect kills/headshots to advance, with 10 daily kills becoming claimable.
   Claim once and verify one reward. A different player's kills must not advance
   this player's orders. Other servers need this relay build too.
4. Repeat in a listen match with another client: host-local events must apply
   once, and the joining player's events must arrive by reliable relay. Verify
   the dedicated and listen cases separately. Inspect event-5 progress after a
   completed match and, if possible, compare win/loss reporting.
5. Recheck Orders accept/abandon/weekly countdown, supply-drop reveal and
   consumption, payroll +200 AC once per period and completion notification,
   Mail's allocated empty inbox, vendor opening, and console responsiveness.
   Check Zombies hidden completions and drops separately; no game-level
   regression result is claimed by the harness.

### Validation

Release x64 solution and harness builds pass, followed by hq-tests.exe run from
build/research/hq-tests. Logs are `hq-slice7-stage{1,2,3}-{build,harness,tests}.log`
and `hq-slice7-final-{build,harness,tests}.log`. Premake vs2022 generation was run.
Coverage adds serialized purchase grant records/permanent sentinels, legacy
projection repair inputs, all CWL tags and bundles, contract type/ID/price views,
bundle replay, and the exact client relay validation/apply helper with real HQ
store transitions, headshot isolation, recipient/malformed rejection and replay.
Native detours, reliable delivery and actual Lua rendering require the operator
walk above. The game was not run or installed.


## Slice 8 - full reward events and table predicates (2026-09-13)

Implemented on `feat/39-hq-economy`, starting at `8917ac9`:
`da6bdfe` (relay capacity and task parser) and `5d9a016` (predicate engine).
No game was launched or installed; no game-directory or `data/` files were changed.
Existing untracked `run-47992/` was left untouched. Source edits preserve CRLF/tabs.

### Evidence and capacity

The owner's dedicated match recorded the win but only one kill and no headshots.
The supplied trace description shows small `multi_kill` events reaching the client,
without `killed_a_player`. Inspection found **three** limiting layers: the native
reward parser allowed ten parameters, relay encoding allowed sixteen/selectors
1..64, and the receiving hook rejected more than 38 command tokens.

Read-only inspection of all eight available `hq_reward_11_*.bin` / `bdReward_11_*.bin`
requests in the game dump folder found only `enter_hub`, one parameter, maximum
selector 1. No captured dedicated kill payload was available, so the actual kill
maximum cannot be claimed. The explicit fallback is **256 unique parameters,
selectors 0..255**. MP tasks 11 and 12 opt into this parser capacity and reject
invalid numeric selectors and duplicate selectors. Zombies uses the unchanged
legacy parser limit and completion path. Existing per-request byte limits
(64 KiB task 12, 3 MiB task 11), 48 users and 100 events per batch remain bounded.
Each individual maximum-sized event fits those request limits.

The server now logs, once per task-11 event name (bounded to 128 names):
`[HQ task11 server] killed_a_player: parameters=N max_selector=M`.
This is emitted before local application/remote forwarding, without requiring
`-demonware_debug`; that flag is still needed for request/relay dumps. The first
sample is an observation, not a measured maximum over the entire session.

[Disassembly and dump inventory](hq-slice8-evidence.md) establish the engine limit:
`SV_SendServerCommand` at RVA 0x6E0BA0 formats into 0x20000 bytes, but its downstream
queue at 0x6DDFE0 copies into **0x400-byte text slots**, including NUL. At 0x6DE17E
it passes 0x400 to 0x6745A0, which terminates/truncates the copy. The reliable ring
contains 128 slots of stride 0x408. A command must therefore be at most 1023 bytes.

### Wire format and validation

Every event retains all parameters; no predicate-based filtering is performed.
The inner event remains readable decimal text, now bounded to 8192 bytes:

```text
s2x_hq 1 <XUID> <nonnegative-int64-timestamp> <event-name-or-ID> <count> [<selector> <uint64-value>]...
```

Names allow ASCII letters (including the mixed-case table name
`equippedSomethingInCAC`), digits and underscores, up to the parser's 99-character
name limit. Duplicate selectors, foreign/zero recipients, negative timestamps,
overflow, excess/missing tokens and invalid names fail before application.
The envelope can represent all 256 parameters even at maximum uint64 values.

Only the following version-2 chunks are sent as actual reliable commands:

```text
s2x_hq 2 <XUID> <FNV1a64-of-whole-inner-event> <zero-based-index> <total> <lowercase-hex-data>
```

Each fragment carries at most 400 original bytes (800 hex characters), plus six
header tokens, comfortably below 1023 bytes. At most 21 fragments are accepted
for the 8192-byte envelope. The receiving hook sees exactly seven tokens rather
than hundreds of event parameters. Matching client/server builds are required;
version 1 is now the inner representation, not a directly accepted game command.

Fragments for one event are queued consecutively under the existing queue mutex.
The 4800-command queue admits the complete fragment set or rejects the event;
32 commands drain per server tick. XUID-to-client resolution and connected-state
checks remain in the server path. The client keeps one bounded assembly, requires
consecutive indices and matching recipient/hash/total, and rejects orphan,
duplicate, malformed, oversized or older-than-ten-second continuations. Index 0
starts a fresh assembly. Only the completed, fingerprint-checked, decoded event
calls `submit_hq_event`, the same application path as task 12. No partial event
changes progress. Queue saturation/disconnection remains a bounded delivery
failure, not an unbounded allocation or retry loop.

The fingerprint is an integrity/replay identifier, not authentication; the existing
hosting-server trust boundary is unchanged. The persistent event receipt now
normalizes numeric/named event aliases and parameter order, so equivalent task-11,
task-12 and relayed representations count once within the existing bounded
2048-receipt window. Zero timestamps retain the prior intentionally undeduplicated
behavior. Existing pre-upgrade receipts keep their old hashes; this does not attempt
a store-wide receipt migration.

Completed event dumps remain `hq_relay_applied_<pid>_*.bin` (inner text);
`hq_relay_forwarded_*` now contains chunk commands, and malformed/incomplete
continuations produce `hq_relay_rejected_chunk_*`. Server task-11 request dumps
remain `hq_reward_11_*`.

### Definition semantics and progress

The captured table has 1234 rows, 416 nonempty predicates and 133 distinct
expressions. Enumerated operators: `:` (selector test), `&&`, `||`; parentheses
also group nested expressions. No other operators occur. Referenced selectors
are 1, 2, 3, 5, 6, 7, 8, 9, 128, 129 and 130. The parser supports nested grouping,
AND precedence over OR, uint64 operands, bounded length (2048) and depth (32), and
validates both sides even when a Boolean result could short-circuit. Missing
parameters evaluate false, including a missing parameter tested against zero.
Malformed expressions/events fail closed.

Selectors below 128 compare scalar/enum values for equality. Selectors 128..255
are treated as flag words, requiring the requested bits. This interpretation is
inferred from the table: `(130:4)&&(130:128)` cannot be satisfied by equality,
and all table masks on selectors 128..130 are powers of two. The unused higher
selectors follow that flag convention; actual captured kill flags still require
the operator verification below.

The main-thread catalog loader copies MP definition kinds 1..4, event column 3
and predicate column 4 into the engine's rule map. Rows without a numeric event
or with malformed predicates cannot advance. Persisted order records supply
progress/status, not predicates. Existing offer selection, targets, rewards and
contracts remain intact; this slice does not invent new UI-table joins or offers.
An active order advances only when its definition's event ID matches and its
predicate succeeds, including:

| Definition | Event | Predicate |
|---|---|---|
| daily/weekly kills | 1, killed_a_player | empty/true |
| daily headshots, contract_mp_2 | 1 | `(6:1)` |
| daily dom caps | 3, gamemode_action | empty/true |
| daily killstreak, weekly scorestreak calls | 4, streak | empty/true |
| weekly wins, contract_mp_1 | 5, end_game | empty/true |
| contract_mp_3 | 2, multi_kill | empty/true |
| daily silenced SMG | 1 | `(130:4)&&(130:128)` |
| daily equipment kills | 1 | `(1:8)||(1:9)` |

Each matching event adds **one**, saturating at the target and becoming claimable.
The table has no increment/count-selector column. The observed multi-kill payload
`1=4, 2=1, 3=2` does not establish that an order should gain four progress units;
the event-2 contract remains one multi-kill occurrence. Event 2 never advances
event-1 kill orders, preventing double counting once kill events arrive. This is
the explicit local occurrence-count policy, not a claim that unavailable retail
backend count logic was recovered. Likewise event-5 win definitions have no
winner predicate: winner-only semantics remain unproved; compare a win and a loss.

### Verification completed

Both stages passed the requested Release x64 build and the expanded harness:

```powershell
./tools/premake5.exe vs2022
& "C:/Program Files/Microsoft Visual Studio/2022/Community/MSBuild/Current/Bin/MSBuild.exe" build/s2x.sln -m -v:minimal -nologo -p:Configuration=Release -p:Platform=x64
& "C:/Program Files/Microsoft Visual Studio/2022/Community/MSBuild/Current/Bin/MSBuild.exe" build/research/hq-tests/hq-tests.vcxproj -m -v:minimal -nologo -p:Configuration=Release -p:Platform=x64
# Run from build/research/hq-tests:
./bin/hq-tests.exe
```

Logs: `hq-slice8-stage{1,2}-{build,harness,tests}.log` and
`hq-slice8-final-{build,harness,tests}.log`. `git diff --check` passed.
The harness compiles the production reward parser and checks MP task 11 with 150
parameters, unchanged Zombies bounds, 256-parameter/max-uint64 encode/decode,
chunk sizing, recipients, expiry, duplicate/orphan chunks, whole-event fingerprint
failure, and duplicate selectors. It parses every captured table predicate and
checks every operator, nesting/precedence, flag words, missing selectors, malformed
branches, numeric overflow and depth/length bounds. A 150-parameter headshot goes
through encode/decode and chunk reassembly into the real store, advancing kills
and headshots together. Other checks cover dom caps, streaks, event 5, weapon flags,
equipment OR, ordinary kills, replay aliases/order, and multi-kill non-duplication.
The existing supply-drop, vendor/purchase/CWL, payroll, mail, offer and Zombies
isolation tests also pass. Native delivery/UI behavior is not proven by a harness.

### Exact operator verification still required

1. Use this Release build for **both** the owner's dedicated server and client,
   with their usual arguments plus `-demonware_debug`. Host the dedicated server
   normally; join it through Server Browser. Do not substitute a private/custom
   match, which the owner observed does not report kill events.
2. Accept daily/weekly kills and a headshot order when offered. Record initial
   `hqeconomy`/`aecache` progress. Play the dedicated match: get known ordinary
   kills and headshots, then finish the match. Expected deltas: one per kill,
   one per headshot in addition to its kill; multi-kill notifications do not
   add extra kills. If reaching a target, expect claimable and one reward grant.
3. On the server expect `[HQ task11 server] killed_a_player: parameters=N
   max_selector=M`. Retain its request dump to measure the real maximum and
   verify headshot/flag values. Expect `hq_relay_forwarded_*` version-2 fragments
   for the player's XUID. On the owning client expect `hq_relay_applied_*` with
   a complete `killed_a_player` event and `[HQ event]` logging the full parameters.
   Return to Orders (or refresh `aefetch user`) and confirm both counters advance.
4. Test another player's kills: they must not change this client's counters.
   Repeat with a listen host and joining client; local host delivery is direct,
   remote delivery is chunked. Compare win and loss event-5 behavior, and test
   dom/streak/weapon predicates on active matching orders when available.
5. Recheck Orders/contract slots, one collected Quartermaster purchase, CWL packs,
   a supply-drop reveal, payroll +200 AC once per period and its completion push.
   Check Zombies separately. No game-level result is claimed in this slice.


## Slice 9 — Contracts list/payment and native MP loot ownership (2026-09-13)

Started at `14e8fdc` on `feat/39-hq-economy`, after the required checkout.
Implementation commits: `436f41a` (contracts) and `26a814b` (loot ownership).
Release x64 and the HQ harness pass. **No game was launched or installed, and no
in-game verification was performed in this slice.** Installed integration remains
`71c57ff` per the handoff. The pre-existing untracked `D:/S2x/run-47992/` was left alone.
No Steam-directory or `data/` files were modified. Source edits preserve CRLF.

### Contracts: exact shipped list, price, payment and display conditions

Ground truth is `luafiles/dec/ui_s2_contracts_menu_uc.dec.lua`, not the old
assumption that a `t:CONTRACT` SKU alone creates a tile. The generated menu binds
`contractGrid` to `DataSources.Shared.MP.DailyOrders.contractsList`.
`ui_utility_shared_dwdatautils.dec.lua` fills its Operation cache with:

```lua
GameChallengeList[f16_arg0]._cachedScheduledChallenges = Engine.AE_GetScheduledChallenges( f16_arg0 )
GameChallengeList[f16_arg0]._cachedPlayerActiveChallenges = Engine.AE_GetPlayerActiveChallenges( f16_arg0, GameChallengeType.GameAchievementKind_ALL )
```

The Contracts menu's `f0_local27` iterates the scheduled Operation cache, replaces
a matching entry with the player's active record, and applies these exact gates:

```lua
local f28_local3 = DwDataUtils.GetCachedData[DwDataUtils.Vendor.Operation]( f28_arg1, GameChallengeGroup.Scheduled )
if DwDataUtils.IsPlayerActiveChallenge( f28_arg1, f28_local7.ID ) then
    f28_local7 = DwDataUtils.GetPlayerActiveChallenge( f28_arg1, f28_local7.ID )
end
if CONDITIONS.IsInHubTutorial( f28_arg1 ) then
    if f28_local3[f28_local4].kind == GameChallengeType.GameAchievementKind_FTE and f28_local7.kind == GameChallengeType.GameAchievementKind_Order_Contract then
        f28_local0.periodicContractData.menuContracts[#f28_local0.periodicContractData.menuContracts + 1] = f28_local7
    end
elseif f28_local3[f28_local4].kind ~= GameChallengeType.GameAchievementKind_FTE and f28_local7.kind == GameChallengeType.GameAchievementKind_Order_Contract and AchievementEngineUtils.ShouldDisplayChallengeByID( f28_arg1, f28_local7.ID ) then
    f28_local0.periodicContractData.menuContracts[#f28_local0.periodicContractData.menuContracts + 1] = f28_local7
end
```

`Order_Contract = 4`, `FTE = 6`. Tutorial behavior stays intact. Normal contracts
require a scheduled kind-4 record and `ShouldDisplayChallengeByID`, even when a
SKU exists. The resulting `#menuContracts` is passed to `contractsList:Populate`.
The grid's `isActive`/progress come from a matching player-active ID; status 3/4
means claimable/completed. Fetch completion handlers update both caches before
repopulating; merely changing a catalog SKU cannot fix those gates.

`ui_utility_mp_achievementengineutils.dec.lua` defines
`AEChallengeTable.File = "mp/periodicChallengeTable.csv"`. Columns 15/16/17/18
are DisplayUnlockItem / DisplayLockItem / DisplayExperimentCohort /
DisplayRandomizer. `ShouldDisplayChallengeByID` ANDs four helpers. Their decisive
conditions are, respectively:

```lua
return Engine.Inventory_GetItemQuantity( f29_arg0, f29_local0 ) > 0
return Engine.Inventory_GetItemQuantity( f30_arg0, f30_local0 ) == 0
if HashRangeUtils.IsPlayerInRange( f31_arg0, f31_local1, tonumber( f31_local4 ) ) then
    return true
end
return DailyRewardRandomizer._cachedRandomizerData[f32_arg0].currentRewards[f32_local3] == f32_local4
```

The first two helpers return true for nil/empty cells; the cohort helper returns
true when its cell cannot be split as `name:range.range...`; the randomizer helper
returns true for an empty cell. Valid cohort ranges must match at least once;
valid randomizer `index:choice` must equal the cached daily choice.

The menu's `f0_local8` (price) and `f0_local9` (SKU) do **not** select by tag or by
`c`/`C`. They scan `quartermaster.SKUInfos`, populated with
`Engine.Inventory_GetSKUInfo` over the type-100 Quartermaster list:

```lua
if f8_local4.items[1].guid == f8_arg1 then
    return f8_local4.prices[1].value
end
if f9_local4.items[1].guid == f9_arg1 then
    return f9_local4.skuID
end
```

The argument being matched is column 11, `CostItemGuid`. The selected button
obtains that column before calling `f0_local9`; the description uses:

```lua
local f30_local9 = f0_local2( f30_arg3.ID, AEChallengeTable.Cols.CostItemGuid )
local f30_local10 = Engine.Inventory_GetItemQuantity( f30_arg1, f30_local9 ) > 0
local f30_local11 = Engine.Localize( "@AEC_ARMORY_CREDITS", f0_local8( f30_arg0, f30_local9, f30_arg2 ) )
```

A positive quantity changes the text to `MENU_CONTRACT_ALREADY_PAID`. More than
two active-plus-expired contracts disables buying. A missing button SKU makes the
buy callback return without purchasing. A nonempty column 19 uses a conversion
instead of a purchase. Otherwise, purchase completion invokes AE activation:

```lua
local f16_local7 = Engine.Inventory_PurchaseSKU( f16_arg1, f16_local4, 1 )
if Engine.AE_ActivatePlayerChallenge( f45_local1, f45_local2 ) then
```

The expiry guard rejects an elapsed, nonzero `expirationEpoch` through
`Engine.EpochTimeToGameTime(...) == "0x0"`. Display time starts from
`f30_arg3.timeLimit`; for active/completed records it switches to
`tonumber( f30_local7.timeLeft )`. The native fields are `usageTimeTarget` and
`usageTimeRemaining`. `GetRewardAndIcon(f30_arg3.reward, ID)` needs the reward
published by the native AE reader; the existing contract rewards remain
50/100/150 AC, and usage target remains 3600 seconds. These are local policy,
not recovered retail payouts. Slice 9 does not add a new play-time accounting
system; actual native countdown behavior remains part of the walk.

The Quartermaster utility has a separate recovery path for paid tokens:

```lua
local f7_local5 = QuarterMasterUtils.FindSkuDataByType( Engine.Inventory_GetSKUInfoSKUData( f7_local9 ), QuarterMasterUtils.SKUDataKeys.CONTRACT_ID_CONTRACT )
QuarterMasterUtils.ClearCachedSKUInfoItems()
local f7_local6, f7_local7 = Engine.Inventory_GetSKUInfoItems( f7_local9, QuarterMasterUtils.CachedSKUInfoItems )
if f7_local7 >= 1 and 0 < Engine.Inventory_GetItemQuantity( f7_arg0, f7_local6[1].guid ) then
    f7_local0[f7_local1 + 1] = f7_local5
end
```

`GetContractCurrencies` thus returns **challenge IDs**, not balance currency IDs.
`ActivateMissedContracts` tries `Engine.AE_ActivatePlayerChallenge` for those IDs
not already active, up to three. Relevant SKU data keys from the same utility:

| Key | Exact meaning and condition |
| --- | --- |
| `t` | TAG. `FindSKUIDByType` requires tag equality. Retain `CONTRACT`; the Contracts grid itself does not filter this tag. |
| `c` | CONTRACT_ID_CONTRACT; numeric ID for paid-token recovery. |
| `C` | CONTRACT_ID_QUARTERMASTER; the Quartermaster details' View Contract link. |
| `i` | Image override; keep `s2_challenge_contracts`. |
| `l` | LIMITER_DATA `guid|max`: `return f10_local2 <= Engine.Inventory_GetItemQuantity( f10_arg0, f10_local1 )`; missing/malformed means false (not limited). |
| `u` | UNLOCK_GUID: `return Engine.Inventory_GetItemQuantity( f11_arg0, f11_local0 ) == 0`; absent means false (not locked). |
| `e` | EXPERIMENT_COHORT `name|range`: `return HashRangeUtils.IsPlayerInRange( f12_arg0, f12_local1, f12_local2 )`; absent/malformed means true. |

The three contracts omit `l`/`u`/`e`; these SKU gates are independent of the
periodic-table display gates described above. SKU data stays within the existing
64-byte native field, with `t:CONTRACT;c:33;C:33;i:s2_challenge_contracts` and
corresponding IDs 34/35. Promotional text and type 100 are retained.

### Contract changes and the evidence limit

- The saved assets do **not** include `periodicChallengeTable.csv`. We cannot
  identify which original row/cell excluded the three entries, nor claim that a
  particular retail display gate was observed false. Instead, the new
  `hq_contracts.cpp` defines an explicit local UI policy for IDs 33..35: type
  `AEC_CONTRACT`, matching names/descriptions, target 1, time 3600, cost GUIDs
  `0x5000001..3`, and empty display/conversion gates. A scoped `Engine.TableLookup`
  adapter supplies those 20-column rows; unrelated tables/IDs/columns and Zombies
  delegate unchanged. This is a deliberate local policy, not a recovered table.
- The owner's saved console log explicitly contains
  `Engine.GetItemGUIDFromReference("contract_mp_1") -> "0x5000001"` and equivalent
  mappings for 2/3 (lines 80884..80886 at read time). Those item GUIDs replace the
  fabricated SKU IDs as `items[0]`. Previously the empty item arrays caused
  `granted_items` to publish the SKU ID itself. The cost-token identity now agrees
  across the local UI rows, native SKU items, product replies and persisted grants.
- Purchase debits currency **6** by 25/50/75, grants one token and writes the replay
  receipt atomically. A second purchase while paid/active/claimable, or finished
  today, cannot charge again. Existing collection/drop/CWL behavior is retained.
- The existing AE `activate_user_contract` handler requires and consumes the paid
  token in the same transaction that sets `inProgress`. An already-active retry
  succeeds before checking the token, so a lost completion callback does not
  require another payment. A purchase replay after consumption cannot recreate
  the token. Existing active legacy contracts remain accepted by the retry path.
- Kind-4 scheduled/user serialization and the existing success-reward vocabulary
  remain in use; this is still the native AE Orders path, not a separate UI-only
  contract state. No per-item constructors are called on SKU slots.

### Loot ownership: native source and the compatibility change

`ui_utility_mp_cac_guid_utils.dec.lua` ultimately reads:

```lua
local f15_local4, f15_local5, f15_local3 = Engine.GetItemLockState( f15_arg0, f15_arg1 )
```

It also uses `Engine.IsGuidUnlocked` for equipped/selected GUID decisions. The
competitive/default-item/weapon-specific Lua branches precede or follow this
call and were not changed. `s1cacutils`' `Cac.GetItemLockStateByGuid` falls through
to `return Engine.GetItemLockState( f163_arg0, f163_arg1 )`.
`Cac.PushLootDataToDataModel` only dispatches a category writer:

```lua
local f706_local0 = f0_local95[f706_arg0]
if f706_local0 then
    f706_local0( f706_arg0, f706_arg1, f706_arg2, f706_arg3 )
end
```

Primary/Secondary_Reticle both use `f0_local88`; the loadout builder obtains loot
metadata through `InventoryUtils.GetLootData` / `GetLootDataForController`. This
model is not a persistent source of ownership. `InventoryUtils` reads consumable
quantity/expiry from the Engine inventory functions; `Loot_OpenSupplyPackage` and
`Loot_GetSupplyPackageContent` operate on reveal transactions, not a separate
reticle entitlement list.

New offline Ghidra output is checked in under `ghidra/decomp-slice9/`.
Together with the earlier `decomp-slice6/279300.c` and
`decomp-slice7/27A310.c`, `27A260.c`, it establishes:

| Reader/writer | Recovered path |
| --- | --- |
| `Inventory_GetItemQuantity` | 0x279480 checks the D0980 shortcut, then 0x279300 and record+4 quantity. |
| `Inventory_IsItemGUIDUsableForPlayer` | 0x27A310 checks that shortcut, then the same record's nonzero quantity and `!0x27A260(controller, slot)` expiry. |
| GUID cache | 0x279300 searches the controller's GUID hash index and returns a pointer into the 0x68-stride item array. It is the cache populated by 0x27DD30/0x27CA20. |
| `Engine.GetItemLockState` | 0x11D620 calls 0xCF850. CF850 reaches the existing D0B10 unlock-table hook; for applicable item classes it additionally checks 0x27A310. |
| `Engine.IsGuidUnlocked` | 0x1159C0 resolves the item reference and calls 0x73F9F0, which reaches the existing D1050 unlock-table hook. |
| Purchase/store inventory | `hq_marketplace::purchase` persists GUID quantity. `bdMarketplace` task 165 pages that same state through `hq_inventory_cache::fill_result`. |
| Native insertion/refresh | `refresh_item` calls 0x27DD30 with the same permanent-item projection. Purchase immediately invokes it, then 0xD5F30 and inventory event 0x2752E0(controller, 2), before task-24 purchase completion. The existing 100 ms main-thread reconciler covers supply-drop grants and token consumption. |

0x27A260 requires the permanent sentinels `expires = UINT32_MAX` and
`duration = INT64_MAX`; positive quantity alone is insufficient. HEAD already
had the correct shared projection and immediate insertion/event path, including
legacy-sentinel repair. Slice 9 does not claim those pre-existing fixes as new.
0xD5F30 updates native progression/model state and calls 0xD3720 to reconcile
inventory-driven stat bits; it is not a network task-165 fetch. For immediate
purchases we retain insertion plus the inventory event; the next actual task 165
returns the persisted item without any synthetic inventory-ready flag.

The added MP loot compatibility branch in `unlock_items.cpp` makes **both**
unlock-table readers return unlocked for a `loot` row whose controller-0 native
cache has nonzero quantity and passes the native expiry test. It uses
0x279300 + 0x27A260 directly, avoiding recursion through the D0980 shortcut.
Unowned/expired loot, non-loot rows, other controllers and Zombies use the
existing paths. Both unlock toggles retain their original branches; no global
unlock is enabled. This joins CAC's unlock-table result to the native inventory
source instead of trusting the Collections checkmark.

**Evidence limit:** the packed D0B10/D1050/D0980 internals are not fully recovered
in the saved image; the relevant original thunk targets leave dumped memory.
The exact stock branch producing the owner's lock result has not been observed.
The compatibility rule is explicit and its call sites/cache reader are recovered;
its native execution and the final CAC result still require the game walk.
No claim is made that a new task-165 schema or a second loot cache was needed.

`hqownership <decimal|0xGUID>` is a read-only main-thread diagnostic. It prints
cached quantity, `Inventory_GetItemQuantity` (0x279480), expiration/duration,
native usability, native lock code (0 = unlocked), then actual Lua
`Engine.IsGuidUnlocked` and `Cac.GetItemGuidLockState`. It emits
`hq_ownership_native_*` under `-demonware_debug` through the existing trace helper.
If the inventory or CAC/LUI context is unavailable it reports that rather than
fabricating a result. `refresh_item` now rejects zero GUIDs, collision records and
metadata over 64 bytes before native insertion. The ten-slot SKU constraint is
untouched, and no 0x20D440 call was added.

### Verification performed here

- `./tools/premake5.exe vs2022` succeeded.
- `"C:/Program Files/Microsoft Visual Studio/2022/Community/MSBuild/Current/Bin/MSBuild.exe" build/s2x.sln -m -v:minimal -nologo -p:Configuration=Release -p:Platform=x64` succeeded after each implementation stage, including the final native diagnostic change. The existing build-info `git describe` no-tags message is nonfatal; MSBuild exited 0.
- The equivalent MSBuild command for `build/research/hq-tests/hq-tests.vcxproj`
  succeeded; `bin/hq-tests.exe` was run **inside** `build/research/hq-tests` and
  passed. New coverage exercises unpaid rejection, paid-token persistence,
  AE activation/consumption, replay after consumption, duplicate charging,
  all three active Orders records, and exact 25+50+75 debit on currency 6.
- The harness also buys the morning-log reticle `0x70200d8`, reloads the store,
  pages it through task-165 inventory and checks that immediate/native reply
  projections agree on quantity and permanent sentinels. Every granted item
  from a supply-drop result is checked after reload against that same projection.
  Existing malformed-input, failed-save, expiry, Zombies, payroll, relay and
  event-predicate tests still pass. These are offline persistence/protocol tests,
  not execution of the game's machine-code functions.
- `python build/research/test_slice9_lua.py` passes. It executes the embedded
  policy, the **decompiled** `ShouldDisplayChallengeByID` helpers and the
  **decompiled** Contracts list/cache/price/SKU functions in a mocked Lua 5.1 runtime.
  It verifies three tiles, prices 25/50/75, matching SKU IDs, active substitution,
  malformed arguments, and delegation for Zombies/unrelated tables/IDs.
  Dependency setup, if needed:
  `python -m pip install --target build/research/slice9-python lupa`.
- `git diff --check` is clean. Only allowed source/research/status paths changed.

### Exact in-game verification still required (not executed)

Use the trace shortcut after the owner installs a build containing Slice 9.
Keep `cg_unlockall_loot 0` and `cg_unlockall_items 0` for ownership checks.

1. At a normal MP Headquarters session (outside the tutorial), run `hqcontracts`,
   `aefetch scheduled`, `aefetch user`, `aecache`, `hqwallet`, `hqskutest`.
   Require ready=1, kind-4 IDs 33/34/35, future expiration, timeLimit 3600 and
   non-null rewards. Contract SKUs must be type 100, price 25/50/75, currency 6,
   and their owned/item diagnostics must name `0x5000001..3`, not `0x0800F021..23`.
2. Quartermaster -> Contracts must show three rows with prices. Existing
   active/claimable rows may occupy their slots; do not expect all three to be
   purchasable on the owner's already-progressed store. Buy an available one:
   require `[HQ purchase] ... error=0`, a currency-6 debit of exactly its price,
   `activate_user_contract` success, an active Orders slot, correct reward text
   and time-left display. Re-enter Quartermaster/Orders; no second charge and no
   missed paid contract. Do not reset the owner's store just to create offers.
3. For the already-purchased morning reticles run `hqownership 0x70200d8` and
   `hqownership 0x7020012`. Require `cached>=1 quantity>=1`,
   `expires=4294967295 duration=9223372036854775807 usable=1 lock=0`, followed by
   `IsGuidUnlocked=1 CAC=Unlocked`. If CAC is unavailable at the frontend, open
   Create-a-Class and repeat. Equip a compatible sight and select the reticle;
   verify it saves to the loadout and remains equipped after leaving/reopening.
4. Buy one previously unowned collection reticle. Record its `[HQ purchase]`
   GUID and immediately run `hqownership` for it; require the same results
   without a restart, then verify equipping. An unowned non-default loot reticle
   should remain locked. Record results before/after purchase and after relaunch;
   the startup task-165 inventory must retain the item. Reticle/sight compatibility
   restrictions remain stock and do not mean ownership is missing.
5. Open a supply drop, record the three `GrantedItems` GUIDs, run `hqownership`
   on its equippable cosmetics and verify they can be selected in their relevant
   loadout categories. Repeat after relaunch. A duplicate grant may have quantity
   above 1; it must not become expired or unusable. Check the reveal still shows
   all three results and consumes exactly one drop.
6. Recheck Orders accept/abandon/claim and event progress, Deals/CWL/Collections,
   payroll countdown/claim without banner, and toggle behavior (enable the
   existing unlock toggles briefly, then restore them). Verify Zombies behavior
   separately. Capture the trace/log and any actual failed native/Lua result;
   no test in this report substitutes for that walk.


## Slice 10 — Retail Headquarters catalog, rewards and Inbox (2026-09-13)

Started at `a6ec7b8` on `feat/39-hq-economy`, after the requested checkout.
Ground truth: `retail-economy-2026-09-13.md`, HANDOFF RESUME HERE and 4e–4k,
the Slice 9 report, and the shipped decompiled Lua. No game was launched, no
build was installed, and neither the Steam tree nor `data/` was modified.
The pre-existing untracked `D:/S2x/run-47992/` is untouched. C++ sources retain CRLF.

Implementation commits:

- `e3c1fe6`: nine native contract identities, retail tiers, projected rewards,
  paid AE activation and match-only usage accounting.
- `8a5774b`: Collections pricing by rarity and item type.
- `946fc38`: six daily offers, daily/weekly rewards, period completion limits
  and Above and Beyond redemption counters.
- `f3ec0b1`: correct GUID-column reader RVA and lowercase contract cost GUIDs.
- `6eb0316`: allocated deliverable marketing messages and the Mail kiosk bridge.
- `fa23d73`: retire placeholder state before the initial fetch; Order display
  metadata and immediate Above and Beyond record projection.
- `3c1a585`: cap native unread-Mail economy polling at one check per second.

### Retail versus S2x

| Feature | Retail capture | Slice 10 S2x |
| --- | --- | --- |
| Contracts board | Nine offers | Nine native kind-4 identities; three active at most |
| Low contract tier | 100 AC / 20 minutes / 3000 XP | Same |
| Medium contract tier | 350 AC / 40 minutes / 3000 XP | Same |
| Supply contract tier | 450 AC / 50 minutes / Supply Drop | Same, item GUID 1 |
| Weapon contract | LAD / 5000 AC / 80 minutes / 10 LMG headshots | Same objective/tier; reward resolved from native `lad_mp` reference |
| Contract time | Counts while playing | Persisted usage advances only on consecutive in-match samples, outside virtual lobby and `hub` |
| Collections | Rarity AND type prices | Common 125; Rare 275, camo 250; Legendary 600, camo 550, charm 2275, costume/uniform/weapon 3250; Epic 7300, weapon 8900 |
| Daily offers / active | Six / three | Six / three, independently enforced on the server-side AE transition |
| Daily win reward | 250 Social Score | Currency 7, amount 250, for the native 1v1 win order |
| Rifle Adept | 35 rifle kills, 2x Supply Drops | Two GUID-1 items, with explicit “2x Supply Drops” display text |
| Daily item reward | Door Kicker weapon variant observed | Shotgun order awards existing collection GUID `0x20000d`; local substitute, not Door Kicker |
| Weekly kills | 500 kills / Rare Supply Drop | New offer target 500, GUID 2; all three weeklies award GUID 2 |
| Above and Beyond | Six daily redemptions / three weekly redemptions | Counters `above_beyond_daily` / `above_beyond_weekly`, one bonus GUID 1 / 2 at threshold |
| Mail | Claimable item deliveries | One welcome delivery: 500 AC; table can contain multiple deliveries/reward entries |
| Payroll | 200 AC / four hours | Unchanged |
| Rare MP/ZM drops | 200 CP each | **Owner decision: retain 1000 AC each, currency 6** |
| CWL packs | 500 CP | **Owner decision: retain 1000 AC each, currency 6** |

The rare-drop/CWL deviation is intentional: these purchases remain earnable
without CoD Points. Common drops remain earned/openable only. No CP economy was
introduced and the Zombies execution paths were not changed.

### Contract definitions and predicates

All nine identities exist as kind 4 in `tables/dwgamechallenges.csv`. Kind 11 is
unnecessary. The first four offers are owner-captured; the last five are local
choices using the captured price/time/reward tiers, not recovered retail slots.

| ID / name | Objective | Seconds | AC | Reward | Table predicate |
| --- | --- | --- | --- | --- | --- |
| 162 `contract_4_headshots_tdm` | 4 TDM headshots | 1200 | 100 | 3000 XP | `(2:1)&&(6:1)` |
| 561 `contract_50_kills_smg` | 50 SMG kills | 2400 | 350 | 3000 XP | `(1:2)` |
| 146 `contract_55_kills_tdm` | 55 TDM kills | 3000 | 450 | GUID 1 | `(2:1)` |
| 3048 `contract_ch_lad` | 10 LMG headshots | 4800 | 5000 | LAD | `(1:3)&&(6:1)` |
| 149 `contract_45_kills` | 45 kills | 2400 | 350 | 3000 XP | empty |
| 153 `contract_25_kills_dom` | 25 Domination kills | 1200 | 100 | 3000 XP | `(2:2)` |
| 164 `contract_9_headshots` | 9 headshots | 2400 | 350 | 3000 XP | `(6:1)` |
| 204 `contract_25_kills_lmg` | 25 LMG kills | 1200 | 100 | 3000 XP | `(1:3)` |
| 562 `contract_50_kills_lmg` | 50 LMG kills | 3000 | 450 | GUID 1 | `(1:3)` |

These are killed-a-player event 1 predicates, evaluated by the existing Slice 8
grammar. Selector 2 is gametype, selector 1 weapon class, selector 6 headshot.
The catalog and SKU tiers share native names; no new event grammar or relay wire
format was introduced. `lad_mp` appears in the shipped `s1cacutils` weapon data;
BG_GetItemGUIDFromReference resolves its actual GUID after assets load. The saved
CSV set does not include the LAD loot row, so no guessed numeric weapon GUID was
baked in. A missing weapon reference fails closed rather than granting GUID zero.

`usageTimeTarget` and `usageTimeRemaining` are native AE fields: the parser at
0x13A570 stores them at record +4/+0x3c; Lua exposes `timeLimit`/`timeLeft`.
`ui_s2_contracts_menu_uc.dec.lua` uses `timeLimit`, or the active record's
`timeLeft`, for the detail panel. `tick_contracts` uses CL_IsLocalClientInGame,
the virtual-lobby flag and `g_gametype != hub`. One-second samples advance only
in-progress contracts; reaching the usage target sets expired. Claimable rewards
stop consuming time. Frontend, HQ, disconnects and offline time do not consume
usage. This is conservative sampling, not a claim of recovered retail timer code:
transitions or stalled frames can lose a small amount of chargeable time.

### Empty Rewards panel, price line and stale completions

The owner's 14:05 walk established the three Slice 9 tiles rendered, but rewards
were blank. The shipped detail function `f0_local28` calls
`AchievementEngineUtils.GetRewardAndIcon(record.reward, ID)` and writes
`rewardTop`, `rewardTopIcon`, `contractCost` and `costIcon`. The price helper
matches `SKUInfos[].items[1].guid` **as a string** against periodic-table column
11, then reads `prices[1].value`; it does not price by the SKU tag.

The existing `successRewards` grammar was already consistent with the recovered
0x13E610 reader: lowercase `grant_currency` with `currency.id/amount`, or
`grant_product` with `product.id/items[].id/quantity`. There is no evidence that
inventing a different JSON key would fix the owner's blank panel. Instead,
scoped MP AE accessor adapters populate the exact Lua reward fields from the
current catalog, including when the menu substitutes a completed active record:
`currencyID`, `currencyAmount`, `productID`, `itemID`. XP is currency **1**, as
defined by `Currencies.XP` and rendered by the shipped reward helper. XP is
persisted through GRANT_CURRENCY and projected by the existing absolute wallet
sync; actual rank/XP presentation remains an in-game acceptance check.

The nine local cost tokens are `0x50f0001` through `0x50f0009`, distinct from SKU
IDs `0x0800f021` through `0x0800f029`. These reserved local token choices are not
claimed to be recovered retail CostItemGuid values. Every token agrees between
the periodic row, SKU item, purchase grant and AE consumption. Lowercase hex is
essential to the shipped Lua price comparison. The backend debits currency 6 and
activates through the existing paid-token AE contract transition; replay cannot
charge again or recreate a consumed token.

`migration:retail-contracts-v1` runs during store loading before assets are ready.
It removes `contract_mp_1..3` progress/claims and zeroes their retired paid tokens,
while preserving transaction receipts as replay tombstones and leaving other
inventory, payroll and progression alone. There is no automatic refund for the
retired synthetic contracts. Subsequent catalog reconciliation removes contract
records whose name/target/time definition no longer matches; direct claim requests
also reconcile, preventing a removed achievement from being paid.

### Collections and Orders

Collection prices still feed the shared SKU/product/purchase path. Native
0x652330 reads loot rarity column 29 via GUID-column reader **0xD1BA0**; the same
reader now supplies column 0 (StatsTable Group). The shipped InventoryUtils
defines camo, charm, costume/uniform and weapon group names. Unknown rarity uses
the Common fallback. Epic weapon types receive the 8900 top-weapon tier; the
capture does not establish a finer per-variant distinction. Heroic/noncaptured
combinations use the documented fallback tier, not a claimed retail measurement.

Daily catalog: 1v1 win (250 Social Score), 35 rifle kills (two common drops),
25 kills (one common drop), three headshots (one common drop), one commendation
(250 Social Score), and 100 shotgun kills (collection item `0x20000d`, present in
itemscollections row 27). The latter four choices are local. Weeklies are 500
kills, ten wins and 25 scorestreak calls, each with one rare drop. The saved tables
do not identify Door Kicker's loot GUID; the substitute is explicitly not sold as
that retail weapon variant. No daily/weekly reward is Armory Credits.

Six daily board slots are separate from ActivationLimits=3. Carried active orders
keep their earned progress and accepted targets; their reward definitions are
updated to the current catalog. New offers use the retail-aligned targets. Three
weekly offers and all existing active-slot limits remain. Completed offers occupy
their slot for the rest of the period: the old immediate reoffer/reward loop is
closed. UTC daily/weekly boundaries remain the existing Slice 6 boundaries.

The native Above and Beyond identities are rows 370/371, kind 5. Successful new
claims increment their counters atomically with the order payout. Replayed claims
and the subsequent UI RedeemedDaily/Weekly event 17 cannot increment twice. Six
daily redemptions award one GUID 1; three weekly redemptions award one GUID 2.
The bonus record is included in the claim response for native counter refresh,
marked completed with requiresClaim=false, and resets at the corresponding period.

### Mail delivery implementation and boundaries

`hq_mail::deliveries` holds stable message ID/code, title, description and a list
of currency/item rewards. The shipped starter has ID 1, code
`s2x-mail:welcome-v1`, and grants 500 currency-6 AC. Never reuse a delivery ID for
a different reward. There is room for six Inbox entries in the default 14 slots;
the current table ships one. Claiming one delivery can grant multiple rewards.

Task 6 retains allocated slots for every advertised entry (minimum 14). Slot 8
contains the starter while unclaimed. A70ED0's recovered fields remain: uint64
ID at +0x10, content blob at +0x2c / length +0x102c, metadata JSON at +0x1030 /
length +0x1830, redemption code at +0x1834 / length +0x1c34, optional code signature
at +0x1c38 / length +0x1c78. Fields 3/4 carry JSON content/metadata and field 5 the
local code. Claimed/empty entries have ID zero; the array is never freed or shrunk.

The decompiled `ui_s2_mail_officer_menu_uc` reveals an important distinction:
`f0_local19` builds the Inbox from Inventory_GetVoucherItems plus
InventoryUtils.GetLootData, and its Collect callback calls
Inventory_RedeemVoucherItem. MarketingGetMessage alone cannot populate this kiosk.
A scoped MP adapter exposes pending allocated deliveries as voucher metadata and
routes their Collect operation into the same validated `redeem_slot` used by the
0x3726F0 marketing-redeem detour. Original voucher calls delegate unchanged.
The existing kiosk completion handler expects inventory event 4 / task 126
(ApplyConversionRule); that notification is queued after the popup opens, so the
existing handler refreshes the grid, removes the popup and shows the empty state.

Redemption validates controller, mapped slot, readiness, allocation count/capacity,
all four blob lengths, message ID and exact code. It grants rewards and writes the
permanent `mail:<id>` receipt in one economy transaction; overflow/save failure
cannot partially grant or claim the pack. Success clears only the native message
ID. Replays across reloads cannot pay again. Malformed requests, unknown codes,
bad indices and unavailable stores fail closed. No native remote redemption task
or retail code service is impersonated: settlement is deliberately in-process.
The native unread poll remains allocation guarded; Zombies retains its original
service and accessor behavior, including nil voucher-list results.

### Validation and outstanding owner walk

- Premake `vs2022` succeeded. Release x64 MSBuild succeeded after each stage and
  on the final source (`hq-slice10-final-build.log`).
- The Release x64 harness build succeeded (`hq-slice10-final-harness.log`);
  `bin/hq-tests.exe` was run from `build/research/hq-tests` and passed. Added checks
  cover nine SKUs, 100+350+450 AC payment/activation/replay, timer saturation/expiry,
  retired state, the rarity/type table, six offers/fourth-active rejection,
  redemption bonuses, 14-slot mail framing, overflow, exact codes and reload replay.
- `python build/research/test_slice10_lua.py` passes. It executes the shipped
  contract reward and price readers and Mail kiosk list/collect functions under
  Lua 5.1 mocks, including completed-contract rewards, all nine prices, two-drop
  display, collect-to-empty behavior and Zombies delegation. It is not a screenshot
  or native game execution test. The old Slice 9 three-placeholder Lua fixture is
  historical and superseded by this test.
- Existing persistence, malformed-input, Zombies, drops, payroll, products,
  collections/CWL, relay and predicate harness checks still pass. No constructor
  call at 0x20D440 was introduced, and native SKU/product item limits remain ten.
  `-demonware_debug` protocol tracing remains enabled through the existing helpers.
- The dedicated lobby guard is outside this feature branch, per HANDOFF 4j; it
  was neither edited nor removed. Integration still needs to retain that merge.

**Not established by offline tests:** final visual rendering, native XP/rank
presentation, LAD entitlement usability, exact one-second timer behavior through
real match transitions, and live Mail completion/popup timing. After the owner
installs the build, verify nine priced contracts with visible rewards; buy one,
check AC debit and active slot, wait in HQ then play a match and compare timeLeft;
accept three of six dailies and reject a fourth; redeem daily/weekly rewards and
bonuses; collect Welcome once, reopen/restart and confirm no second 500 AC grant.
Also repeat the working drops/CWL/Collections/payroll/reticle checks and the
dedicated client join/quit test on integration. This slice did not run the game.


## Slice 11 — retail contract tokens, completion-time label, CWL AC icon (2026-09-13)

Implemented on `feat/39-hq-economy`, starting at `b545fbf`:

- `bb83356` — retail contract payment tokens, persisted-token migration, zero contract expiration, retail periodic-table delegation and harness/Lua coverage.
- `edb1622` — CWL preview currency patch and shipped-builder/timer Lua coverage.

Owner baseline: installed integration `e1a0156`, HANDOFF item 4l, passed six Major
Howard dailies and three weeklies with rewards, Collections pricing, AC Deals,
and the 500 AC Welcome Mail. Slice 11 fixes the three remaining reported defects.
The game was not run, installed or modified during this work. Existing untracked
repository-root `run-47992/` was left untouched.

### A. Contracts: known retail payment tokens and localized rows

The owner observed `hqownership 0x50F0001` reporting cached=0, quantity=1,
usable=1, lock=0, while an unowned real StatsTable row reported quantity=0 and
lock=17. The native quantity shortcut treats unknown GUIDs as owned; the nine
synthetic CostItemGuid values therefore selected `MENU_CONTRACT_ALREADY_PAID`.
The Contracts detail's shipped quantity check is in
`luafiles/dec/ui_s2_contracts_menu_uc.dec.lua` around lines 539–545.

`hq_marketplace.hpp` now uses these real StatsTable `contract` group items in
its nine SKU grants. Purchase and AE activation/consumption already derive their
token from the same SKU (`granted_items`), so they now agree without a second map.
`hqcontracts` diagnostics no longer advertise the synthetic tokens.

| ID | Retail CostItemGuid (exact table spelling) | Kept AE target / seconds | Retail target / seconds |
| --- | --- | --- | --- |
| 162 | `0x5000019` | 4 / 1200 | 4 / 1200 |
| 561 | `0x500006c` | 50 / 2400 | 50 / 2400 |
| 146 | `0x5000009` | 55 / 3000 | 40 / 3600 |
| 3048 | `0x50000B9` | 10 / 4800 | 10 / 4800 |
| 149 | `0x500000c` | 45 / 2400 | 25 / 2400 |
| 153 | `0x5000010` | 25 / 1200 | 25 / 1200 |
| 164 | `0x500001b` | 9 / 2400 | 1 / 2400 |
| 204 | `0x5000043` | 25 / 1200 | 25 / 1200 |
| 562 | `0x500006d` | 50 / 3000 | 50 / 2400 |

The nine local periodic rows were removed from `hq_contracts.cpp`. For every
column on these IDs, the TableLookup wrapper falls through to the real table;
retail AEC_* title/description keys, difficulty and other metadata are retained.
All nine rows have empty columns 13–19 (reward overrides, display gates and
purchase conversion override). Their SpecialType values in column 12 are retail
metadata, not display gates. The local Orders rows remain unchanged.
The record reward adapter remains, and its former dependency on `rows[id][11]`
is replaced by a separate contract-limit map so removing those rows cannot
nil-index the wrapper or change the captured limits. AE targets continue to
drive progress and the localized description parameter. ID 162's retail Name
column says `contract_5_headshots_tdm`; the existing captured AE identity
`contract_4_headshots_tdm` is retained, as are the established IDs and predicates.

Case evidence: the raw LAD token is exactly `0x50000B9`. The shipped Contracts
cache initializer lowercases the table fields before its two string-equality
price/SKU readers use them. The native numeric SKU token renders lowercase, so
the cached `0x50000b9` matches. Offline comparisons of raw table and SKU GUIDs
are case-insensitive; the tests execute the actual shipped cache initializer
and price/SKU readers for all nine offers rather than changing retail spelling.

`hq_economy.cpp` adds `migration:retail-contract-tokens-v1`. The previous
`migration:retail-contracts-v1` has already run on Slice 10 stores and is retained.
The new one-time migration zeroes all persisted `0x50F0001`–`0x50F0009` quantities,
including nonzero collision slots, while retaining inventory records and all
purchase/claim receipts as replay tombstones. It grants no replacement token,
refund or duplicate reward, and leaves real contract tokens/progress untouched.
It runs before cached snapshots publish and before transactional mutations;
reload tests verify persistence and no second revision bump.

Read-only evidence copies are committed under `build/research/tables/`:

- `periodicChallengeTable.csv`: 839 rows including header, 21 columns; SHA-256 `9c52b6cb0565372c6c93255f6236c4b6cab948d3c5db24ef8647281821e99f94`.
- `StatsTable.csv`: SHA-256 `a04b96dedf0d8549ebd8bd231baca21f49089e07074e704ee56344feeb328a84`.

Both copies were checked byte-for-byte against
`D:\Program Files\Steam\steamapps\common\Call of Duty WWII\s2x\dump\mp\`.
No file under the Steam installation was written.

### B. Completion Time and activated Orders timers

The shared AE serializer now emits `expirationTimestamp: 0` for kind 4 in
scheduled, user/active and push records. Daily/weekly period expirations and
NextPeriodStartTimes are unchanged. `usageTimeTarget` and `usageTimeRemaining`
retain the captured match-only limits and remaining usage.

`eventEndTimestamp` remains omitted, not emitted as zero: the native parser
maps that unrelated key to the last-completion field at record+0x30, dividing
by 1000. Emitting it would overwrite completion data. The relevant parser
(`ghidra/decomp-payroll/13A605.c`, same record parser at 0x13A570) writes the uint64
expiration directly to record+0x18 without rejecting zero. The scheduled/active
accessors (`ghidra/decomp-quick/121A00.c`, `121F40.c`) publish its decimal string;
the active accessor filters by record ID/kind, not by a nonzero expiration.
The shipped `DwDataUtils.IsContractExpired` uses the recently-expired ID list,
not a zero-epoch test.

Executing the shipped selector at
`luafiles/dec/ui_s2_daily_orders_descriptions_uc.dec.lua:74–140` verifies that
string `"0"` selects `ShowContractUnactivatedTime` and
`@MENU_CONTRACT_COMPLETION_TIME`; active records select
`ShowContractActivatedTime`. A nonzero epoch selects the prior expiration
countdown branch. Native game rendering remains an owner check.

### C. CWL preview currency image and installation requirement

`data/ui_scripts/mp/patches/cwl_currency.lua`, required by that folder's
`__init__.lua`, wraps the registered `cwl_preview` builder and
BuildRegisteredType path using the existing patch style. A per-element guard
prevents duplicate subscriptions. It refreshes on creation, SKU `id` model
changes and `CoDPointsPrice` model changes. The selected model ID is passed to
`Engine.Inventory_GetSKUInfo`; currency 6 in `prices[1]` selects
`s2_armory_credits_icon`, otherwise `cod_points`. The existing Cost subscription
and its value are untouched. Missing elements/models/prices and teardown are
nil-safe; Zombies delegates without changing the icon.

**Install the data as well as the executable.** The installed patches live at
`<game>\s2x\ui_scripts\mp\patches\`; the exe install does not update that folder.
The orchestrator must copy the updated `data/` payload (including
`cwl_currency.lua` and `patches/__init__.lua`) to the corresponding installed
`s2x` paths when integrating. This work did not perform that copy.

### Validation and exact owner verification

Passed:

- `./tools/premake5.exe vs2022`.
- Release x64 solution build using the requested VS2022 Community MSBuild command; `hq-slice11-stage1-build.log`.
- Release x64 `build/research/hq-tests/hq-tests.vcxproj` build; `hq-slice11-stage1-harness.log`.
- `bin/hq-tests.exe` from inside `build/research/hq-tests`; `hq-slice11-stage1-tests.log`. Coverage includes all nine retail grants, 100+350+450 AC debit once, token consumption/replay, three activated contracts in both board replies with zero expiration and intact usage timers, idle/match usage expiry/saturation, migration of every synthetic token/collision, real-token/receipt preservation and reload idempotence. The owner-store assertion now counts the additional migration receipt.
- `python build/research/test_slice10_lua.py`: real retail table fallthrough for every column of all nine IDs, known StatsTable contract items, shipped cache/price/SKU readers including uppercase LAD, rewards/limits, Orders two-drop display, Mail collection and Zombies delegation.
- `python build/research/test_slice11_lua.py`: shipped timer selector and actual shipped CWL preview builder under Lua 5.1 model stubs, AC/CP switching, Cost retention, malformed/missing data and elements, both builder paths and Zombies isolation.
- Existing harness checks for malformed input, Orders, drops, Collections/CWL, Mail, payroll, relay/predicates and Zombies still pass. No new native hook, no 0x20D440 call, no native item-capacity or 64-byte SKU-string change. Edited existing sources retained their detected CRLF endings.

In-game verification is pending; these are offline results, not a claimed owner
walk. After integrating both code and data:

1. Open Quartermaster → Contracts. Select ID 162, the four TDM headshots offer.
   Require a localized title/description and reward, **Contract Cost 100 AC**
   (not Already Paid), and **Completion Time 20m 00s** (not Contract Expires).
   Check all nine offers; in particular LAD must resolve its 5000 AC price/SKU.
   `hqownership 0x5000019` should report quantity 0 before a fresh purchase.
2. Record the AC balance, buy ID 162 once, and require exactly 100 AC debited.
   The contract must appear in Orders with its active match-only timer. Reopen
   both boards to confirm it remains listed and no second debit occurs.
3. Wait in HQ and compare `hqcontracts` timeLeft: it must not decrease from idle
   wall-clock time. Play an MP match (owner only), then return to Orders: only
   match time should have been consumed; progress should follow the existing
   TDM/headshot predicate. Reload to verify persisted remaining time and receipt.
4. Open Quartermaster → CWL Packs front screen, move among tiles and return from
   a pack detail. Require the **AC icon** beside the existing **1000** price on
   the front preview; the detail must continue to show AC. A currency-5 SKU, if
   supplied for a separate test, must retain the CP coin.
5. Spot-check the owner-confirmed baseline: six dailies/three weeklies and their
   rewards, Collections prices/ownership, AC Deals, drops, payroll and Mail.
   A previously claimed Welcome must not pay another 500 AC. Keep integration's
   existing dedicated/relay fixes; confirm Zombies remains unchanged.


## Slice 12 — redeemed Order slots and Above and Beyond (2026-09-13)

Code and regression tests: `10508f7` on `feat/39-hq-economy`, based on
`674a41d`. The owner verified Slice 11 installed as integration `740e39e`:
contracts display Contract Cost 100 Armory Credits and Completion Time 20m 00s,
purchase debits and activates, CWL packs display Armory Credits, and payroll
claims cleanly. This slice addresses the remaining redeemed Order slot and
Above and Beyond counter defects. No game was run, installed, or modified.

### Changes and evidence

- Both `get_user_achievements_for_users` and `get_user_achievements` omit kind
  1/2/4 records only when status is `finished` and `claimTransaction` is nonempty.
  Unclaimed finished and claimable records remain visible. Scheduled replies
  retain the current-period completed Howard tile. The existing activation
  count already counts only `inProgress`/`claimable`, with ActivationLimits 3;
  regressions now prove three real active orders fit after redemption and a
  fourth is rejected. Same-period reacceptance and abandoning redeemed records
  remain rejected.
- Retail `tables/dwgamechallenges.csv:367-368` contains
  `370,above_beyond_daily,5,17,,Gold` and
  `371,above_beyond_weekly,5,17,,Gold`. No rename is needed. The harness checks
  those mappings and both user replies' counter progress/targets (6 daily,
  3 weekly), `status: in_progress`, and `requiresClaim: false`. Only these two
  MP counter identities receive that status projection; stored bonus completion
  still prevents duplicate grants. Weekly counter expiration follows the weekly
  boundary, while `reconcile_offers` resets each counter at its own period.
- `migration:above-beyond-recount-v1` is written atomically through the existing
  reconciliation transaction, after the MP counter catalog becomes available.
  Before offers can replace older definitions, it recounts redeemed dailies
  completed today and weeklies completed this UTC week using completion time,
  including carried orders. Counts saturate at 6/3, exclude missing receipts,
  zero completion times and older periods, and do not replay historical rewards.
  The marker persists across reload; new claims increment once and replay does
  not increment. A threshold already reached is retained as paid bookkeeping.
- Retail UI evidence: `luafiles/dec/ui_s2_periodicchallengeinventory_uc.dec.lua`
  lines 330-350 fill active slots, lines 598-616 complete the local redeemed
  record pending refetch, and lines 537-550 read the Above and Beyond counters.
  `ui_utility_shared_dwdatautils.dec.lua:188-190` fetches active challenges;
  `ui_utility_mp_achievementengineutils.dec.lua:217-218` specifies IDs 370/371.
  These establish the expected native consumer; rendering still needs the owner
  verification below.

### Offline validation

Passed `./tools/premake5.exe vs2022`, the requested Release x64 solution build,
the Release x64 `build/research/hq-tests/hq-tests.vcxproj` build, and
`bin/hq-tests.exe` run from `build/research/hq-tests`. Logs:
`hq-slice12-stage1-build.log`, `hq-slice12-stage1-harness.log`, and
`hq-slice12-stage1-tests.log` (PASS).

New regressions reproduce redeemed daily/weekly records, Howard's completed tick,
three accepted daily slots, the fourth-order limit, same-period reaccept/abandon
rejection, visible unclaimed completions, hidden redeemed contracts, retail
counter IDs, 1/6 and 1/3 recounts, reload idempotence, a fresh claim reaching 2/6,
claim replay, and daily/weekly rollover. Existing malformed-input, Zombies,
contract token/debit/timer, drops, Collections, Mail, payroll, and relay/predicate
checks also pass. The earlier assertion expecting a redeemed record in a native
active reply now expects its absence. Source files retained detected CRLF/tab
style. The pre-existing untracked root `run-47992/` was left untouched.

### Exact owner verification after install

1. Install the Slice 12 executable through the normal integration process,
   retaining the already-installed Slice 11 data. Open Orders after a fresh
   achievement fetch. The redeemed `daily_ch_headshots` must leave its active
   slot: no stuck 3/3 tile or Abandon Orders prompt. The third daily already
   accepted must now be visible. Major Howard must keep the redeemed offer's
   tick until the period rolls over, and it must not be acceptable again in that
   period.
2. On the same UTC day as the reported redemption (completion `1789324252`,
   offer day `20709`), require **Daily Orders Completed 1/6**. Reopen the screen
   and restart to confirm the count remains 1/6, not 2/6. If installation occurs
   after daily rollover, the correct initial count is 0/6; the migration must
   not carry yesterday's claim into today.
3. Complete and redeem a fresh daily once. Require the tile to leave its active
   slot, the reward to grant once, and **Daily Orders Completed 2/6** (or 1/6
   when starting after rollover). Reopen/retry and confirm no second increment.
   Check the weekly equivalent and 3-order target when redeeming a weekly.
4. Accept into the freed slot, confirm up to three active dailies are visible,
   and check ordinary abandon/reaccept still works. On rollover, require daily
   and weekly counters to reset at their respective boundaries and the prior
   period's Howard tick to disappear.
5. Spot-check the owner-confirmed Slice 11 baseline: 100 AC contract cost,
   20m completion timer, one debit and activation, CWL Armory Credits, and clean
   payroll pickup. Retain the established Orders, drops, Collections, Mail and
   relay behavior. Zombies game-level verification remains an owner check;
   this slice changes no Zombies handler or native hook.
