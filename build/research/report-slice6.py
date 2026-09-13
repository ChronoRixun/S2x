from pathlib import Path
import subprocess
def write(p,s): Path(p).write_bytes(s.replace('\r\n','\n').replace('\n','\r\n').encode())
p=Path('build/research/hq-economy-slice1-report.md')
report='''

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
- HARDENING: aligned native SKU storage, logarithmic per-item price lookup and
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
'''
head=subprocess.check_output(['git','rev-parse','--short','HEAD'],text=True).strip()
p.write_bytes(p.read_bytes()+report.replace("HARDENING",head).replace("\n","\r\n").encode("utf-8"))
p=Path('build/RUNBOOK.md'); s=p.read_text(encoding="utf-8")
anchor='# 9. `feat/39-hq-economy` — issue [#39](https://github.com/Brentdevent/S2x/issues/39)'
s=s.replace(anchor,anchor+'''

**Slice 6 status (2026-09-12):** currency7 AC/migration, full774-item catalog,
native purchases, current-period Orders and booster refresh implemented; Release
and rebuilt harness pass. Game/UI verification pending. Current operator steps:
`research/hq-economy-slice1-report.md`, Slice6; these supersede the older slice4/5
instructions below. This branch build was not installed or run by the agent.''')
s=s.replace('| Orders: Abandon | **works in the latest owner walk**; regression check on slice 5 |','| Orders: Abandon | Slice6 current-day reoffer and accept3/abandon1 harness pass; Major Howard check pending |')
s=s.replace('| Weekly orders | offered by the router; previously showed empty in the UI — re-check |','| Weekly orders | Slice6 independent rollover/current offers implemented and tested; UI re-check pending |')
s=s.replace('| Payroll | **+200 persisted in PID 46420**, receipt `payroll:124254`; slice 5 wallet/push implemented, visible success awaiting walk |','| Payroll | Slice6 uses established AC currency7; receipt-only CP migration and +200 local amount tested; kiosk check pending |')
s=s.replace('| Quartermaster | **grey/flickers on integration `8fb25af`, PID 46420** despite native conversion success; slice 5 nonempty catalog experiment unverified |','| Quartermaster | Slice6 full774-item types100/150 catalog, native price readers and purchases implemented; UI entry/buy verification pending |')
s=s.replace('| Supply Drops | **works** end to end — native reveal, 3 items, drop consumed |','| Supply Drops | Prior native reveal works; Slice6 post-fetch quantity refresh implemented/tested, live verification pending |')
s=s.replace('- [ ] Payroll: one pickup grants +200 currency 2 once; repeats do not','- [ ] Payroll: one pickup grants +200 currency 7 (AC) once; repeats do not; migration moves only receipt-accounted CP')
s=s.replace('- [ ] Quartermaster: SKU count/type, conversion callbacks, 111 and 242 dumps kept; purchases rejected without mutation','- [ ] Quartermaster: full774-item catalog/prices, buy one item with one debit/grant, insufficient funds unchanged; retain111/242/native_purchase traces')
s=s.replace('- **ASK OWEN:** Currency 2 in the HQ economy is a *candidate* Armory Credits ID, never proven. If you\n  ever see a UI currency change by exactly the granted amount, note it — that would settle the\n  mapping.','- **Resolved in Slice6:** currency7 is Armory Credits (Lua hammer balance); currency2 is COD Points (owner observation). Payroll corrected with receipt migration.')
write(p,s)
