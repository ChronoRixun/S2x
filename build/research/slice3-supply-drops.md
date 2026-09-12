# Slice 3: Supply drops

Established using S2xFull and instruction operands (decomp-slice3 and
slice3-drop-lookup.txt): 0x2AEEA0 looks up column 1 (UI drop type) and returns
column 5, converts it with atoi, then calls inventory quantity 0x279480.
0x2B0850 uses the same column-1 lookup, returns column 4 into SupplyDropID,
and submits group 0 type 0x7F, data stride 0xF8, submit 0xA5793B thunk,
success 0x2B03B0, failure 0x2B02D0. The task is already covered by the existing
AE injection bridge; no generic hook/filter or bdReward acknowledgement changed.
Common UI type 0 -> sd_mp -> inventory item 1 (0x1).
Rare UI type 1 -> sd_mp_rare -> inventory item 2 (0x2).
These are inventory GUIDs, not currency IDs. Native quantity reads inventory;
there is no balance requirement in that function. Broader Lua gating is unverified.

Handler 0x2AF7A0 requires GrantedItems, reads each object's id (up to 50),
optionally reads GrantedCurrencies through 0x27C480, and DetailedInventory
through 0x27C1D0. The latter reads item_id, item_quantity, collision_field,
expiry_duration and mod_date_time. Zero quantity explicitly removes the item.
Native success emits OpenSupplyPackageSuccess with the same transactionID.

Implemented two drop types only, using inventory collision 0. The economy
transaction consumes one unexpired owned drop, rolls three items with replacement,
grants those quantities, and saves a permanent drop:ClientTx receipt atomically.
Replay returns the same items but CURRENT absolute DetailedInventory quantities,
so it neither grants again nor rewinds the native quantity cache. Same ClientTx
with a different drop type fails. Missing stock/catalog, expiry, overflow and
save failure reject the transaction without debit. Malformed requests fail.

Loot is a local policy: uniform rolls from member GUIDs (columns 3 onward,
count in column 2) of mp/itemscollections.csv, restricted to collection IDs
present in mp/collections.csv. Deduplicated/sorted pool, no collection completion
reward from column 1, no paid purchases, no retail odds or rare guarantee.
Runtime assets are copied on the main thread; service code never reads assets.
No source CSV needs to be installed. Zombies types are unsupported here and
its existing transport/bridge branches remain unchanged.

Operator commands (after at least five seconds in the frontend):
    hqgrant item 1 2
    hqgrant item 2 1
    hqeconomy
Restart to fetch the new inventory through Marketplace 165, then use the shortcut.
For a direct native task test without relying on the shortcut cache:
    hqopendrop common
    hqopendrop rare
    hqeconomy
These commands submit the actual native task, not just the local JSON router.
Expect three GrantedItems, a consumed drop in DetailedInventory (zero on last
use), OpenSupplyPackageSuccess, and persisted loot after restart. In-game
animation, UI cards, immediate cache updates and shortcut enablement remain
operator verification gates. The harness cannot run native binary code.
