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
