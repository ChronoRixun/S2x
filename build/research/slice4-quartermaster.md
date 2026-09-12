# Slice 4 Quartermaster

PID 40144 proves the terminal empty SKU page is accepted. Task 111 is unchanged.
242 now validates the captured context/UUID/ClientTx/mode layout and answers a
single typed struct with field 1 ClientTx and field 2 store UUID. This is an
explicit hypothesis, not a recovered SDK schema. It introduces no SKUs, purchases,
entitlements or economy mutations. Bad framing returns a structured parse error.
Request and exact serialized response bodies remain under -demonware_debug.

S2xFull string search (slice4-strings.txt) locates Engine.Inventory_AreSKUsFetched
at registration B394F0 -> 120610 -> 278400. The effective result also reads the
inventory enable dvar (pointer 7F6F108); raw readiness is 81038A8. No IsStoreReady
binding or full main-menu enable expression was found in defined strings. These
are native binding names, not proof of the Lua call site's boolean expression.

hqvendor prints raw/effective SKU readiness, 242 request/reply/rejection counters,
and four registered vendor/payroll switches. Inventory and entitlement fetched
flags remain explicitly unknown. This command does not force any gate. Compare
before/after menu and world attempts: a new 242 counter identifies actual traffic;
fetched=1 plus allowed switches excludes the already-working SKU completion.

Harness validates the bounded request and every truncated prefix. It does not
validate the game's protobuf deserializer. Native UI verification remains needed.
