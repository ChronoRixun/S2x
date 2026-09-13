# bdMarketplace task 99 and the reward-event acknowledgement (Fable, 2026-09-13)

Branch `feat/39-hq-economy`: `4a877c6` (task 99 product query), `5fc9591` (bdReward
struct acknowledgement). Release x64 solution build: 0 errors. Harness
(`build/research/hq-tests`, Release x64): PASS. Nothing installed, nothing merged.
Evidence run: pid 25248 on 6560cdc, archived in `build/research/run-25248/`
(console slice from line 97707, 97 `hq_*_25248_*.bin` dumps). Ghidra artefacts:
`build/research/ghidra/decomp-task99b/`, `task99-*.txt`, new scripts `CallersImm.java`,
`DumpPtrs.java`, `Listing.java`, `CallersPrev.java`, `FindCalls.java`.

Offsets are S2x image offsets (address - 0x7ff7a3190000).

## 1. What task 99 is

**bdMarketplace task 99 = "get products by product id"**: the query that fills the
product record of every cached SKU. It is issued by the game's per-frame marketplace
pump, not by the supply-drop reward commit that slice 5 assumed.

### Issuer chain

| step | offset | evidence |
|---|---|---|
| Per-frame pump | `0x27D160` | `decomp-task99b/27D160.c`. Runs for controllers 0..1. Once the SKU fetched flag `0x81038A8` is set it walks the 400-slot SKU cache `0x81038B0` (stride 0x2E8) and collects every slot whose product id (`+0x08`) is non-zero and whose cached product id (`+0x240`) is zero, deduplicated, **stopping at 100 ids** (`CMP R9D,0x190` / `CMP RCX,0x64` in `task99-callers.txt` at `27D44C`). With a non-empty list it allocates a group-5 task slot via `0x2081B0(5, controller)` and sets type `0xA` (`MOV R8D,0xa`). |
| Explicit issuer | `0x278C30` | same params block, same callbacks; `(controller, ids*, count, flag)`. |
| Params block | `0x816A6E0` | `decomp-task99b/20CF90.c` (constructor): 100 result records of 0x2A8 bytes at +0, ids at `+0x109A0` (100 x u32), count at `+0x10B30`, mode byte at `+0x10B34` (1 = fill SKU slots, 0 = fill the 20-entry product table `0x8100C40`). |
| Submit thunk | `+0x30 = 0x11F846A3` -> `0x20C658` -> relocated SDK method | `decomp-task99b/11F846A3.c`, `20C658.c`. |
| SDK prologue | `0x9605` | `task99-listing.txt`: `MOV R8B,0x63 ; MOV DL,0x50 ; LEA RCX,[RBP-0x29] ; JMP 0xA42728` -> `CALL 0xA6B930` = bdTaskParams(service 0x50, **task 0x63**), then `0xA6BB50` addContext. The only `MOV R8B,0x63` in the whole image (`task99-imm-all.txt`). |
| Success callback | `+0x38 = 0x27B4D0` | `decomp-task99b/27B4D0.c`: takes the SDK result count into `+0x10B30`; for each 0x2A8 record, mode 1: finds the SKU slot whose `+0x08` equals the record's product id (`+0x10`) and copies the record into the slot via `0x20C1A0`; then, if **every** slot with a SKU id has `+0x240 == +0x08`, raises inventory event `0x17` success=1 through `0x275360` (`inventoryEventType=4, inventoryTaskType=23`). Mode 0 copies into the 20-entry table and raises event 3. |
| Failure callback | `+0x40 = 0x27B4C0` | empty function (`27B4C0.c`). |

### Why it fired every frame

The pump has no pending flag and no backoff: each frame it recomputes "slots without a
product" and re-issues while the list is non-empty. Our status-only reply (5565a6f)
completed the task with zero results, `0x27B4D0` copied nothing, `+0x240` stayed zero
in all 400 slots, so the next frame asked again (5,715 times in run-25248; 1,989 in
run-51584 when the catalog had one SKU). The vendor UI never received event 0x17.

### Request (wire, captured `run-25248/dw/hq_marketplace_99_25248_61.bin`, 538 bytes)

```
03 63                       typed task id (99)
10 "s2_steam" 00            context string
08 01000000                 u32 page = 1
08 64000000                 u32 count = 100      (ids that follow)
08 64000000                 u32 limit = 100      (= count in both captures)
08 <id> x100                u32 product ids, sorted (0x20000D, 0x20001F, ... 0x40000E)
00 x16                      AES padding
```
The slice-5 40-byte capture (one-SKU catalog) is `1, 1, 1, [1]`: same shape.

### Result record (SDK object 0x2A8 bytes, vtable `0xB4B298`, deserializer `0xA488C0`)

Read order (helpers: `0xA77030` readUInt32, `0xA76FD0` readUInt16, `0xA76950` readBlob
with capacity, `0xA76F70` readUInt8):

| # | field | stored at | note |
|---|---|---|---|
| 1 | u32 productId | `+0x10` | |
| 2 | blob, capacity 135 | stack temp, discarded | name |
| 3 | blob, capacity 240 | stack temp, discarded | description |
| 4 | blob, capacity 64 | stack temp, discarded | product data |
| 5 | u16 | `+0x14` | unused by the cache copy |
| 6 | u32 | `+0x18` | unused by the cache copy |
| 7 | u32 itemCount | `+0x1C` (byte) | vtable[4] `0xA48B40`; capacity 10, extra items overwrite slot 9 |
| 7a | per item: u32 itemId, u32 quantity | item `+0x20`, `+0x24` | item vtable `0xC63298`[0] = `0xA486F0` (confirmed decompile); items at `+0x68 + i*0x38` |
| 8 | u32 count (<= 4) then u32/u32 pairs | `+0x1D`, `+0x20..`, `+0x30..` | |
| 9 | u32 count (<= 4) then u32/u32 pairs | `+0x40`, `+0x44..`, `+0x54..` | |

Cache copy `0x20C1A0` (SDK record -> SKU slot + 0x10): product id -> slot `+0x240`,
item count byte -> slot `+0x244`, item i -> slot `+0x10 + i*0x38` (`+0x20` id,
`+0x24` quantity), so item 0's id/quantity live at slot `+0x30/+0x34`, exactly the
fields `hq_native::sku_lookup` was already synthesising for its own copies.

### Reply implemented (`hq_products.hpp`, `bdMarketplace::getProducts`)

Standard count-framed reply (`send()`; task 111 uses the same framing and is accepted):
`u64 tx, u32 error=0, u8 99, u32 n, u32 n, n x record`, each record:

```
08 <productId>  13 <len> "<id>\0"  13 01 00  13 01 00  05 0000  08 00000000
08 01000000  08 <productId> 08 01000000   08 00000000  08 00000000
```
i.e. product = requested id, one item {id, quantity 1} (SKU id = product id = item GUID,
the local policy of the task 111 catalog), zero pairs. Every requested id is answered:
the pump only asks for ids it took from our own catalog, and any unanswered id would
keep the per-frame loop alive. `page`/`limit` bound the page; `count` must equal the
number of ids; > 100 ids, a foreign context, a zero id or a truncated request are
rejected with `BD_PARAM_PARSE_ERROR`. Logging: first 8 requests in full, then a
counter line every 1024 (a regression can no longer flood the console).

Harness: parses both captures, serialises the 100-id page through `service_reply` and
re-reads it field by field in the native order, checks paging/limits, truncation, count
mismatch, >100 ids, and that logging stops.

Confidence: high on the identity, the request layout, the record layout and the
callbacks (all decompiled, item deserializer confirmed at `0xA486F0`). Medium on two
details only an in-game run proves: that the blob helper `0xA76950` accepts our
1-byte blobs (it accepted the same framing for the task 111 SKU records), and that
the vendor UI opens once event 0x17 arrives (the Lua consumer of that event was not
traced; it is the only remaining native gate we know of).

### Slice-5 assumption corrected

`0x2AF560` (called from the open_supply_drop handler `0x2AF7A0`) writes `99`, the
granted item ids and the currency pairs into a 0x3FC-byte message buffer with the
engine's MSG_* writers (`0x326C720/0x326DAD0/0x326DD60`) and hands it to
`0x31F0740`; it is a client/LUI message, not a Demonware task, and it never touches
`0x2081B0`, the task-slot allocator every marketplace issuer goes through
(`task99-callers.txt` lists all 90 issuers with their group/type). There is only one
task-99 request shape, so no dispatch by shape is needed.

## 2. Payroll banner: bdReward 11/12 are struct tasks

`hq_reward_12_25248_77.bin` starts `17 08 50000000 0A 08 "s2_steam" 12 2A ...`: a typed
StructBuffer (0x17) carrying a protobuf `RewardGameEvents` message, i.e. task 12 (and
11, same `read_payload`) is a **struct task**, like bdMarketplace 242 and
bdMarketingComms 6. Both were answered with `send()` (count-framed). The SDK cannot
deserialise that as a struct reply, the task fails client-side, and the game's event
queue re-sends the whole batch with exponential backoff:

- task 11 `enter_hub` (same timestamp 1789271739000000) at transactions 184, 341, 658, 1289;
- task 12 `picked_up_payroll` at 1039, 1080, 1157, 1316, 1630, 2257, 3436, 4620, 5805,
  6986, 8170 (intervals 41, 77, 159, 314, 627, then ~1180 frames), the second pickup
  (1789272064000000) joining the same batch from 1630 on.

The economy side was already idempotent: the first batch paid 200 Armory Credits
(`[HQ payroll] delivered persisted completion push`), every replay hit
`hq_payroll::settle`'s "already settled this period" branch and returned success (no
`economy update failed` line in the slice). The banner came from the client-side task
failure, not from the batch content.

Fix (`5fc9591`): tasks 11 and 12 reply with `send_struct()` and
`hq_protocol::empty_struct_result` (typed empty body) on success; the failure path
uses `send_struct()` too and is reached only when the store transaction itself fails.
Harness: second `picked_up_payroll` in the same period -> `submit_event` true, wallet
unchanged; a task-12 reply through `service_reply::send_struct` reads back as
`tx, error 0, task 12, struct(0 bytes)`.

Open point: the game-side reader of the task-12 response was not located (the struct
constructors for service 0x8B carry no immediates; only task 5 `0x1195568B` showed
up). An empty protobuf body is what the SDK accepted for MarketingComms 6 (its success
callback ran); if the Lua kiosk still complains after a single, non-repeated task 12,
the next target is that reader.

## 3. In-game verification (next walk, trace shortcut, no tracer)

1. Hub entry: `[DW] bdMarketplace: executing task '99'` at most **4 times** in a row
   (400 slots / 100 ids) followed by
   `[HQ marketplace] task 99 product query page 1 count 100 limit 100 [...]` lines; no
   further task-99 lines for the rest of the session. A `[HQ marketplace] task 99: N
   product requests so far` warning means the loop is still alive.
2. `hqvendor` -> `[HQ vendor] catalogType=100 nonzeroSKUs=400 productsLoaded=400/400
   (task 99 queries=4) ...` and `hqtask99` -> `native SKU slots with product 400/400`.
   Before the fix these read `product=0 items=0` per slot.
3. `hqvendor full` -> `SKU slot=0 id=2097165 ... product=2097165 items=1`.
4. Quartermaster (Play > HQ > Quartermaster and in-world): conversion success callback
   still < 1000 ms; the vendor should now stay open with the priced list. If it still
   closes with products loaded and a fast success callback, dump `[LUI]` lines around
   the close: the Lua handler of inventory event 0x17/0x7E is the next target.
5. Payroll: one `bdReward: executing task '12'` per pickup, **no** repeats at growing
   intervals, no `Unable to get payroll` banner; `hqwallet` currency 6 unchanged on a
   second pickup in the same 4-hour period, +200 in the next one. `enter_hub` (task
   11) should likewise appear once per hub entry.
6. `-demonware_debug` dumps `hq_marketplace_99_<pid>_*.bin` (first 8 requests) and
   `hq_marketplace_99_product_<pid>_*.bin` (first 4 records) for a byte check against
   section 1.
