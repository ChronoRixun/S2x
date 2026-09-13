# Slice 4 Quartermaster and conversion rule (final, supersedes provisional stage 2)

Task **242 = applyConversionRule**. The UUID is a conversion-rule ID, not a store.
The cross-version SDK maps service 0x50/task 0xF2 to this call:
https://github.com/0xLogic/OpenIW8/blob/main/workspace/iw8/code_source/libs/demonwareclient/bdlobby/bdmarketplace/bdmarketplace.cpp

That name led to the actual WWII binding: registration B39590,
Engine.Inventory_ApplyConversionRule -> 121250 -> 278180 (group 5). Request
reset 20CB80 calls A4CAC0 and response reset A4CAF0; response constructor A4C310
installs vtable C63578. **A4C850 is the native response deserializer.**

It reads field 1 string (capacity 25) at response+10, field 2 uint64 at +30,
field 3 nested object at +38, then repeated objects in fields 4/5/6. Nested
reader A4C7B0 reads string fields 1/2/3 (capacities 16/256/37), uint32 field 4.
Native success 27A4C0 applies task-data +210/count +21C currencies (stride 98),
+220/count +22C inventory (stride F0), then emits event type 7E with request Tx.
Failure is 27A460. Empty collections here are count-guarded and valid; there is
no Mail-like blind array walk. Missing fields are accepted by SDK helpers, so
this also establishes that the old typed empty response was not necessarily a
parse failure. Quartermaster causality is not proved by a 242 load-time request.

Final reply: typed struct with field 1 matching ClientTx, field 2 zero, field 3
{1:s2_steam, 2:empty, 3:captured rule UUID, 4:1}, no fields 4..6. Field types are
established; the scalar meanings, rule descriptor contents and no-op business
policy remain provisional. Only the captured startup UUID with quantity 1 is
accepted; unknown rules get parse error. No rewards, purchases or entitlements
are invented. This supersedes the earlier incorrect field-2 UUID experiment.
The native response body is 82 bytes for the captured 24-byte transaction.

PID 40144 proves the terminal empty SKU page succeeds. Task 111 is unchanged.
Engine.Inventory_AreSKUsFetched at B394F0 -> 120610 -> 278400 reads raw flag
81038A8, with an inventory-enable dvar override (pointer 7F6F108). Defined-string
search found no full menu Lua enable expression or IsStoreReady binding.

hqvendor prints raw/effective SKU readiness, four vendor/payroll switches, 242
request/reply/rejection counters, conversion native success/failure counters,
last response Tx/scalar/array counts. Inventory-ready byte 80385A8 and item count
80385A4 are used by flush 27D6B0; pending metadata count is 819B568. Entitlement
readiness and the complete LUI expression remain unlocated. No gate is forced.
Callbacks preserve their original functions and install only for MP clients.

Next walk: compare hqvendor before/after both entry points. Success counter plus
Tx/scalar/zero arrays establishes deserialization/completion independently from
button enablement. If the button is still grey with all captured inputs ready,
the next target is the Lua caller and remaining entitlement/onboarding inputs.
