from pathlib import Path
report='''

## Slice 5 - 2026-09-12

Payroll persistence is proved by the owner's PID46420 store and traces. Native
wallet synchronization and a payroll completion notification are implemented.
Quartermaster has a bounded nonempty catalog experiment and broader diagnostics.
Mail now follows an explicit empty-inbox policy at the native accessor as well as
the allocated wire response. **The requested game-level outcomes are not claimed
verified: no game was launched.** The exact Quartermaster menu predicate and the
first payroll/Mail visible error paths were not present in the available evidence.

### Evidence and staged commits

- fd571db: archive PID46420, native wallet reader/schema recovery, hqwallet,
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

Store revision66 has currency2=200 and payroll_officer finished, receipt
payroll:124254 -> 1789259964000000, completionTimestamp1789259963. This establishes
settlement, not the top-right HUD. One Marketplace132 occurs at frontend load;
no 130 or balance refresh follows pickup. No claim_achievement_reward request
occurs. Both conversion callbacks succeed with SKU/inventory ready, switches
correct and zero result arrays. The owner still saw Quartermaster grey/flicker,
Mail claim errors and a first payroll error on integration8fb25af; these are
current observations, not merely the earlier slice3 symptoms.

### Established versus guessed

**Wallet/payroll:** Engine registration140AE0 installs tableB37F30. EntryB39520
pairs Inventory_GetCurrencyBalance with120940 ->279780. It reads 13 currency
records at7F6FBB8, stride38, byte ID+20/u32 value+24, count7F6FE90, ready7F6FE94,
controller stride2E0. Fetch278A50 clears with20CBA0, completes via27B230; native
readerA49900 consumes byte ID/u32 balance. Existing132 serialization was correct.
MP130 now shares that serializer and context/limit parser; 130's request schema
is an unobserved compatibility assumption, not a captured success. Each currency
record is now traced. hqwallet prints ready/count, all records and the binding's
currency2 result. The association with the owner's top-right label still needs
an actual menu check; currency2/200/four-hour buckets remain the local policy.

Main-thread synchronization waits for native balance readiness and uses27D510
(absolute setter27DC10 plus inventory eventType5) when persisted amounts differ.
No second grant or forced ready flag is involved. Native limits remain: thirteen
slots and signed Lua integer display. This covers post-claim currency changes
without requiring a network fetch that the captured pickup never submitted.

A newly persisted payroll settlement queues a native achievement push. 13C480
reads name/kind/reason/status/progress/type and triggers; reason=completed emits
achievementEngine eventType0 with success/ID/kind/challengeName/itemsReceived/
currenciesReceived. SET_CURRENCY_BALANCE inventory.currencies uses currency_id,
balance_before and balance_delta, consumed by27C480. The main-thread native
string bridge delivers it; retries/manual claims do not queue another reward.
The push schema is established; missing this push causing the first kiosk error
is an inference. This is a separate notification handler, not a fabricated AE
claim response. The group0 task filter, Orders router and drop opening stay intact.

**Quartermaster:** lui-vendor-bindings.txt records113 matching registration pairs,
per-function decompiles, direct globals and recovered inventory/store callees.
Unexamined callees are explicitly listed; this is not an exhaustive transitive
analysis. hqvendor prints77 recovered runtime reference bases as raw8, plus
semantic wallet/SKU type/count/prices/items/inventory/conversion/dvar diagnostics.
Read-only string tables and LUI VM pointers are omitted from the raw dump.
Store registration370500 supplies namespace Store fromB655F0; Inventory_* are
Engine members. UserCanAccessStore and FoundPlayerPurchases return true;
ShowEmptyStoreDialog returns false. 27A210 requires inventory and balance ready.
GetAllSKUIDs requires matching type81038AC, ready81038A8, and nonzero IDs from
400 fixed records at81038B0/stride2E8. None proves the actual menu enable predicate.

Task111 read-side chain A4A5A0 ->A4A510 ->A4A2C0 is now recovered, including blobs,
price records and type/maxQuantity/soldOut suffix. A76950 confirms typed blob reads.
One local type100 offer uses SKU1/product1, sd_mp (table itemGUID1), price200 of
currency2 and maxQuantity1. It is selected only on page1 with matching filters and
empty token; page2 and collection type150 stay empty. Both blobs are terminated
for native string consumers. Fixed product item records are initialized with
zero count, not a null dynamic array. SKU/product IDs, pricing and metadata
meaning are provisional. No retail product catalog is claimed. The native
purchase issuer276580 returns an initialized empty transaction (Lua nil), and
DW106 rejects direct requests. No payment or ownership changes can follow this
offer. A nonempty catalog curing the grey/flicker remains a testable hypothesis.

**Mail:** A50A60 allocates1CA0-byte repeated messages; A70ED0 confirms field1
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

1. **Wallet:** expect native ready1 and currency2 equal to hqeconomy (archived
   value200, adjusted for later owner activity). Check the top-right counter in
   both HQ entry routes and record its label/value. Save132_currency dumps and
   hqwallet output if mismatched. Do not infer visibility from the saved store.
2. **Payroll:** in an unreceipted UTC four-hour bucket, record wallet/store, pick
   up once, then repeat the four commands. Require exactly+200 and a finished
   kiosk/countdown without an error. Expect payroll_native_push and the delivered
   completion log; require currenciesReceived amount200. Wait through two repeated
   Reward12 batches: no additional grant or reward push. Revisit and restart:
   store/native balance must agree. Existing payroll:124254 cannot pay again;
   test a fresh bucket without deleting receipts. Do not use aeevent payroll as
   evidence of native pickup. Record exact on-screen error if it persists.
3. **Quartermaster frontend:** hqvendor, attempt Play > HQ > Quartermaster, then
   hqvendor. In type100 expect one SKU ID1 with one price; type150 may legitimately
   be empty. Preserve111_sku and native SKU callback output. Record whether grey,
   opened, or closed. A purchase attempt must return unavailable with unchanged
   wallet/inventory; this display catalog is not a functioning store.
4. **Quartermaster world:** hqvendor immediately before interacting and after
   the flicker/open. Record click time, SKU count/type, conversion counter deltas
   and any new task independently from world loading. If nonzero catalog and
   all flags still fail, recover the actual menu Lua/onboarding condition next.
5. **Mail:** hqmail before opening and after one attempt at each entry route.
   Require native fetch count>=14, nonnull allocation, zero IDs/lengths, empty
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
'''
p=Path('build/research/hq-economy-slice1-report.md');p.write_bytes(p.read_bytes()+report.replace('\n','\r\n').encode('utf-8'))
p=Path('build/RUNBOOK.md');s=p.read_text(encoding='utf-8')
s=s.replace('(sections Slice 1, 1b, 2, 3, 4), `ae-ghidra-findings.md`, `slice3-*.md`, `slice4-*.md`.','(sections Slice 1, 1b, 2, 3, 4, 5), `ae-ghidra-findings.md`, `slice3-*.md`, `slice4-*.md`, `slice5-*.md`.')
s=s.replace('- Current store state (leftover from testing): 1 common drop (guid `0x1`, quantity 0 after the last\n  open), three loot items, three in-progress dailies, a claimable payroll, no currency.','- PID 46420 archived store: currency 2 = 200, payroll finished with receipt `payroll:124254`,\n  common-drop quantity 0. Use `hqeconomy` for current state; do not assume that old snapshot is live.')
s=s.replace('| `hqvendor` | SKU flag, 242/conversion counters, inventory ready/count, dirty metadata, vendor killswitches |','| `hqwallet` | native wallet ready/count, all 13 slots, currency-2 balance from the Lua reader |\n| `hqvendor` | wallet, SKU type/count/records, 77 recovered runtime references, conversion counters, inventory and switches |').replace('| `hqmail` | mail ready flag, slot pointer, the first 14 slot IDs with content/code lengths |','| `hqmail` | empty-inbox policy, read/redeem/index counters, ready/count/capacity, allocation and first 14 slot IDs/lengths |')
s=s.replace('```text\nhqvendor\nhqmail\nhqnative\nhqeconomy','```text\nhqwallet\nhqvendor\nhqmail\nhqeconomy\nhqnative',1)
a=s.index('## 9.3 Payroll');b=s.index('## 9.4 Quartermaster',a)
s=s[:a]+'''## 9.3 Payroll — **+200 persisted; slice 5 native visibility/UI awaiting walk**

The traced owner walk on integration `8fb25af` (PID 46420) proves currency 2 = 200 and
`payroll_officer` finished, receipt `payroll:124254` for timestamp `1789259964000000`.
The first pickup showed an error; a revisit showed claimed/countdown, but no visible credits.
Only the frontend Marketplace 132 balance fetch occurred; no refresh or AE claim followed pickup.
Slice 5 adds `hqwallet`, main-thread absolute balance updates and a native achievement completion
push after a new persisted settlement. The missing push causing the error is an inference; no
visible kiosk error text was captured. Currency 2 / 200 / UTC four-hour buckets are local policy.

**Test:**

1. Run `hqwallet`, `hqvendor`, `hqmail`, `hqeconomy`; record native and stored currency 2.
2. In a fresh UTC four-hour bucket without a receipt, pick up once. Require +200 once, the native
   balance matching the store/top-right counter, and a claimed kiosk/countdown without an error.
3. Expect `hq_payroll_native_push_*` and `[HQ payroll] delivered persisted completion push`.
   Repeated Reward 12 batches must not grant or animate a second reward.
4. Revisit and restart in the same period; balance must persist and remain visible.
5. Existing receipts cannot pay again. Do not delete receipts to manufacture a passing result.
6. Record the exact visible error separately if it persists. The harness does not prove the kiosk.
7. `aeevent payroll` uses the older synthetic path and is not a native-pickup test.

''' + s[b:]
a=s.index('## 9.4 Quartermaster');b=s.index('**Test:**',a)
s=s[:a]+'''## 9.4 Quartermaster — **still grey/flickering on slice 4; slice 5 catalog experiment**

The owner re-walked integration `8fb25af` with tracing (PID 46420): the main-menu entry was grey
and the in-world vendor flickered/closed. Both conversion callbacks succeeded with SKU/inventory
ready and switches correct. These are current observations, not just the earlier slice 3 walk.
The actual Lua enable expression remains unresolved. Slice 5 enumerates 113 matching binding pairs,
prints 77 recovered runtime references, and supplies one filtered type-100 `sd_mp` display SKU at
200 currency 2. Native and direct purchases are rejected with no grant/debit. Type 150 remains empty.
The nonempty catalog is a hypothesis to test; it is not a verified Quartermaster fix or retail store.

''' + s[b:]
a=s.index('**Do not** assume this is fixed',s.index('## 9.4'));b=s.index('## 9.5 Mail',a)
s=s[:a]+'''6. In the type-100 catalog expect `nonzeroSKUs=1`, SKU ID 1 and one price. Keep `111_sku` dumps.
   Compare before/after each interaction; type 150 may legitimately have zero records. A purchase
   must be unavailable and leave wallet/inventory unchanged. If it still greys/closes with a nonzero
   catalog and healthy flags, the next target is the actual menu Lua/onboarding gate.

''' + s[b:]
a=s.index('## 9.5 Mail');b=s.index('**Test:**',a)
s=s[:a]+'''## 9.5 Mail — **slice 5 empty-inbox policy; kiosk verification pending**

The owner still saw claim errors on integration `8fb25af` (PID 46420), but only MarketingComms 6
was captured; there was no redemption request or manual `hqmail` output. Slice 5 confirms the
14 allocated ID-zero messages are valid. It also found that an unknown category maps one past the
valid slots, which native message/redeem readers fail to bounds-check; use during the owner's click
is unproved. MP now returns no message from the native accessor, reports no unread mail and suppresses
stale redemptions. The wire allocation remains at least 14 entries. Reads/redeems log category/index
and bounds; native fetch success logs count/capacity. Zombies behavior is unchanged.

''' + s[b:]
s=s.replace('`hqmail` before opening Mail. Expect:', '`hqmail` before opening Mail. Expect empty-inbox policy, native count >= 14, and:')
s=s.replace('`hqmail` again. **Do not keep clicking it to force a network claim.** That Lua path is the next\n   code target.', '`hqmail` again. Compare read/redeem counters and category/index logs. No counter change means\n   the control uses a path outside these MarketingComms accessors; that Lua path is the next target.')
import re
states={
'Orders: Abandon':'**works in the latest owner walk**; regression check on slice 5',
'Payroll':'**+200 persisted in PID 46420**, receipt `payroll:124254`; slice 5 wallet/push implemented, visible success awaiting walk',
'Quartermaster':'**grey/flickers on integration `8fb25af`, PID 46420** despite native conversion success; slice 5 nonempty catalog experiment unverified',
'Mail':'**claim errors on integration `8fb25af`, PID 46420**; slice 5 native empty-inbox policy and bounds diagnostics implemented, kiosk verification pending',
'Task 168 metadata':'served during traced PID 46420; retain metadata/persistence regression checks'
}
for name,state in states.items():s=re.sub(r'^\| '+re.escape(name)+r' \|.*$',f'| {name} | {state} |',s,flags=re.M)
s=s.replace('- [ ] Payroll: persists across restart; kiosk behaviour recorded separately','- [ ] Payroll: `hqwallet` agrees with `hqeconomy` and top-right counter; no first-pickup error; persists across restart')
s=s.replace('- [ ] Quartermaster: conversion callback success/failure recorded, 242 dumps kept','- [ ] Quartermaster: SKU count/type, conversion callbacks, 111 and 242 dumps kept; purchases rejected without mutation')
p.write_bytes(s.replace('\n','\r\n').encode())
