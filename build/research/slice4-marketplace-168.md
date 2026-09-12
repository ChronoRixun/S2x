# Slice 4 Marketplace 168

Identified as **putInventoryItemsData**, not a supply-drop result lookup.
The cross-version SDK implementation selects service 0x50/task 0xA8 and binds
exactly one bdMarketplaceAuditLogResult. Its deserializer reads one string with
capacity 0x19. Sources (read 2026-09-12):

- https://github.com/0xLogic/OpenIW8/blob/main/workspace/iw8/code_source/libs/demonwareclient/bdlobby/bdmarketplace/deprecated/bdmarketplacedeprecated.cpp
- https://github.com/0xLogic/OpenIW8/blob/main/workspace/iw8/code_source/libs/demonwareclient/bdlobby/bdmarketplace/bdmarketplaceauditlog.cpp

PID 40144 _002 exactly matches context, independent ClientTx, count=3 and repeated
owner, account, GUID, blob, collision. The metadata is 64 bytes starting 02 and
then zeros. Native confirmation: Inventory_ClearNewFlag (11E4F0 -> 27CA90 ->
27A3A0) sets bit 1 and marks metadata dirty. Flush 27D6B0 copies up to 30 dirty
records, success 27BED0 clears pending flags, failure 27BCD0 retries. Result
arrays are not read by this callback, but the SDK binds an audit result.

Implementation validates all records before transaction, requires local owner,
known inventory GUID/collision, <=30 records and <=64 metadata bytes. Atomic save
updates metadata only. Inventory 165 now returns it. Optional itemData byte arrays
extend schemaVersion 1 compatibly; old stores load with empty metadata. A bounded
fingerprint receipt prevents an old transaction from rewinding newer flags and
rejects conflicting reuse. No quantity, currency or drop roll changes occur.

Reply has result count=1, total=1, and typed transaction string; malformed input
gets parse error, unknown inventory/conflict/save failure gets task failure.
Zombies retains the prior generic empty-success fallback. PID-scoped request and
response traces prevent the overwrite ambiguity seen in request_trace filenames.

Harness checks the real 312-byte request, all truncated record prefixes, wrong
owner, persistence, later update + old replay, conflicting reuse, unknown item
rollback, unchanged quantity, and exact SDK result framing. Release/harness pass.
