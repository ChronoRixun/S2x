# Slice 5 Quartermaster

S2xFull 140AE0 registers Engine from B37F30 via 2E37B0. Each registration
is a name pointer followed by a C-function pointer. Inventory_* are Engine
members, not a distinct Inventory namespace. lui-vendor-bindings.txt inventories
113 matching defined-string pairs across all namespaces (a superset); each C
function was decompiled, direct runtime globals recorded, and recovered direct
27xxxx inventory/store callees included. Unexamined callees are listed explicitly;
this is not exhaustive transitive dependency recovery or recovered menu Lua.
77 runtime reference bases are printed as raw8 by hqvendor, with semantic wallet,
SKU type/count/items/prices, inventory readiness/count, conversion, and dvar output.
Pointers are printed as bytes, not dereferenced. Read-only data/string tables and
LUI VM pointers are excluded from the runtime value dump.

Established: UserCanAccessStore 10DCA0 returns true. FoundPlayerPurchases 36FCF0
returns true; ShowEmptyStoreDialog 36FD10 returns false. Inventory readiness
27A210 requires balanceReady 7F6FE94 and inventoryReady 80385A8 (dvar override).
AreSKUsFetched tests 81038A8. GetAllSKUIDs 120760 -> 278FB0 requires requested type
==81038AC and ready, then scans 400 fixed records at 81038B0, stride 2E8, for
nonzero IDs. GetSKUInfo 11FF90 -> 2797E0 exposes metadata, prices and cached items.
UserOnlineDataFetched also consults broader online-data readiness and resetstats
popup; its direct callees are listed. No entitlement or overall store flag was
proved responsible for the observed closure.

PID46420: two conversion native successes, both with ready SKU/inventory and
vendor switches enabled. No click markers. No request can be assigned to the
flicker independently of HQ loading. Main-menu grey condition is not recovered.
Empty SKU contents are the leading remaining catalog hypothesis, not a proved
Lua predicate. The added record is an explicitly provisional local display offer.

Task111 read-side vtable C63438: A4A5A0 -> A4A510 -> A4A2C0, native size370.
Fields in order: u32 SKU/product; u8; blob64; u8; three u32; u8; blob135;
u32; u16; u32; u8; u32 price count; repeated currency(ubyte/u32); ubyte type;
u32 maxQuantity; bool soldOut. This differs from write-side serializer offsets.
Cache conversion 20C250 copies known fields and 20D440 initializes fixed product
item records/count to zero, so no unallocated variable array is introduced.

Local offer SKU1/product1 uses sd_mp from supplydroptypes.csv (item GUID1),
price200 currency2, type100, maxQuantity1, soldOut=false. SKU ID/product/price and
skuData semantics are local assumptions. Product cache has zero items pending
any native product fetch; this is not a claim of complete retail catalog support.
Only page1, matching SKU/type filters and empty token receives it; page2 and
collection type150 are empty terminal pages. This preserves collection behavior.
Purchases are rejected before native submission at 276580 (11FDF0 returns nil
from an empty initialized bdString), plus task106 rejects direct requests.
Neither credits nor items are granted/debited. Zombies keeps its prior branches.

Validation: Release and harness logs hq-slice5-stage2-*.log. Tests project the
native typed read order, price, filter/page/token selection and every truncated
query. Native deserialization, UI enablement and metadata interpretation still
require operator verification; no game was launched.
