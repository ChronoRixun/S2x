from pathlib import Path
p=Path('build/research/slice5-payroll.md');p.write_text('''# Slice 5 payroll and evidence

PID 46420 archived in run-46420: 72 PID-scoped dumps, matching console slice,
ordered actions.txt with raw/JSON decode, and read-only live economy copy.
Store revision 66: currency 2 = 200; payroll_officer finished; receipt
payroll:124254 -> 1789259964000000; completionTimestamp 1789259963.
This establishes +200 settlement. The clock is one second ahead in the event.
One Marketplace132 at frontend load, no 130 and no balance refresh after pickup.
No AE claim request, redemption request, logged UI error, or manual hqmail output.
Conversion native success twice; readiness/switches healthy. No exact click markers.

Balance path (S2xFull image-relative offsets): Engine registration B39520 pairs
Inventory_GetCurrencyBalance with 120940 -> 279780. Cache 7F6FBB8, 13 records of
38 bytes, ID +20, value +24; count 7F6FE90, ready 7F6FE94, controller stride 2E0.
278A50 clears cache with 20CBA0 and submits group5 balance task. Success 27B230
sets ready and SDK count; result deserializer A49900 reads ubyte then uint32.
Existing task132 serializer was correct. Task130 MP now shares that response;
its request is the same context/limit assumption and was not observed this run.
Zombies130 remains empty; Zombies132 behavior is retained.
27DC10 sets absolute cached values; 27D510 wraps it with inventory eventType5,
currency/newBalance/difference. Main-thread sync waits for native balance ready,
compares stored currencies every 100ms and uses that wrapper only on differences.
No raw readiness flags or ownership grants are forced. Native has 13 slots;
unknown/out-of-retail-range currency IDs and uint32-to-Lua signed display remain
native limits. hqwallet prints all 13 slots plus ready/count and Lua-reader AC.

13C480 is the independent achievement push handler, not AE_ProcessResponse.
It reads name/kind/reason/status/progress/type. reason=completed emits
achievementEngine eventType0 success=1, ID/kind/challengeName, itemsReceived and
currenciesReceived. SET_CURRENCY_BALANCE -> inventory.currencies entries with
currency_id/balance_before/balance_delta -> 27C480 -> 27D510. A newly persisted
payroll settlement queues this exact push on the main thread using the existing
native string bridge. No new claim task is fabricated. Retries/manual claims do
not queue it. This is an established parser schema, but the absent push causing
the owner's first error is an inference, not a captured error-path diagnosis.

Release/harness pass: hq-slice5-stage1-{build,harness,tests}.log. Harness verifies
push identity/reward inputs and replay suppression, serializer bytes and prior
Orders/drop/payroll tests. It does not execute native callbacks or Lua.
''')
