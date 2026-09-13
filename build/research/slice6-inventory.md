# Slice 6 booster inventory

Established native chain: Engine.Loot_GetNumBoosterPacksOfType registration
B39760 ->123870(controller,type) ->2AEEA0. It resolves supplydroptypes.csv
column1(type) to column5(item GUID), then279480(controller,GUID). For normal MP,
type0=sd_mp=GUID1 and type1=sd_mp_rare=GUID2.279480 looks up279300 and reads
quantity+4 (apart from existing entitlement/cheat overrides). It does not count
unopened drop receipts or infer stock from the catalog. The existing binding's
cheat fallback is unchanged. The full decompile and table establish this path.

Task165 already serializes persisted positive inventory quantities. Confirmed by
harness: a remaining common drop appears after opening one; opening the last
leaves quantity0. Native display after165 remains operator verification, not a
claim of an executed game check.

New main-thread sync waits for native inventoryReady80385A8, compares persisted
collision0 quantities against279300's raw cache, and calls27DD30 with absolute
32-byte20C8B0-projected records only on differences. This handles hqgrant, open,
purchase and expiry after the initial fetch, including explicit zero quantities.
It shares the purchase refresh helper, uses the same expiry-duration=-1 as165,
then D5F30/2752E0 notify inventory users. No ready flags or metadata acknowledgements
are reset; identical quantities do not repeatedly dirty task168. Foreign collision
records are not collapsed into the GUID-only cache. No native SDK array invented.

hqvendor now prints full catalog count and both native booster quantities.
-demonware_debug captures inventory_native_refresh GUID:before->after.
Release and rebuilt harness/run pass in hq-slice6-stage4-*.log. Tests cover165
remaining stock, absolute refresh projection, final-drop zero and expiration,
plus the existing atomic consume/grant/replay and metadata168 regression suite.
No game launched; no writes to Steam or data/.
