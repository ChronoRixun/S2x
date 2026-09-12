# Slice 3: Quartermaster investigation

S2xFull, -noanalysis, decomp-slice3. Offsets relative to 0x7ff7a3190000.

Established: Lua Inventory_AreSKUsFetched at 0x120610 calls 0x278400;
it tests the SKU fetched byte 0x81038A8 (with an inventory-enable dvar override).
FetchAllSKUs at 0x120670 calls 0x278E20, group 5/type 0x17 (confirmed in slice3-sku-group.txt), submit thunk 0x1BC1AF,
success 0x27B700, failure 0x27B6C0. Success gets the SDK result count,
copies up to 100 SKU records of stride 0x370 into the 400-entry cache
(stride 0x2E8), and sets fetched when count < requested limit. Otherwise it
requests the next page. Thus zero results is a valid terminal page, and an
extra page wrapper would be incorrect. Individual SKU vtable 0xC63438;
size A4AA10 (0x370). A4A990 calls write helpers and is a serializer,
not an established deserializer. A4A220 is a destructor. The individual
SKU deserialize entry remains unresolved.
Captured 111 query: context, page=1, limit=100, bool=false, zero ID filters,
one byte type filter (150 at startup, 100 later), empty string, zero padding.
Added bounded parsing and native success/failure diagnostics plus hqnative.

Unresolved: exact main-menu Lua enable expression and task 242 reply schema,
issuer group/type and success callback. Fragmented SDK code has task constant
242 at 0x11CD4551, via A41A99/A41ABA. A typed empty struct is still sent;
this is not a vendor fix. No fake SKU record or arbitrary protobuf fields added.
The UUID is absent from the read-only launchitems.csv. Its meaning is unknown.
The supplied run does not establish that 242 is the vendor-open request:
mp_hub_allies_slim_load unloading is normal loading-zone cleanup.

Next: run hqnative before/after Quartermaster with -demonware_debug, correlate
SKU callback and readiness with actual menu failure. Recover the read-side vtable entry for nonempty
SKU records, and reconstruct the fragmented caller above A41A99 before changing 242.
