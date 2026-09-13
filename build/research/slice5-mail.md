# Slice 5 Mail

PID46420 contains MarketingComms6 and the 14-slot response only. There is no
MarketingComms4, redemption request, native AE claim, manual hqmail output or
logged UI error. Therefore no network claim task/error can honestly be attributed
to the owner's button. The old return packets were not a successful mail claim.

New S2xFull evidence: A50A60 response reader allocates repeated field1 objects of
1CA0 bytes; capacity grows geometrically and size is response+1C. A70ED0 message
reader consumes field1 uint64 -> +10 message ID; field2 string20; fields3/4/5/6
blobs4096/2048/1024/64, with lengths +102C/+1830/+1C34/+1C78; field7 uint64,
field8 uint32. Existing 14 ID-zero messages are valid and allocated. Allocation
and wire framing are unchanged. No reward/code or successful claim is fabricated.

3723B0 maps category/index with marketingcomms.csv. An unknown category returns
the cumulative count, not -1; missing table returns 0. 3722F0 and 3726F0 fail to
check mapped index against response size before reading ID/code. This establishes
an out-of-range path but does NOT prove it caused this owner's button/error.

Chosen authorized policy: MP local inbox exposes nothing claimable. 3722F0 now
returns false with an empty output, so 125020 MarketingGetMessage returns zero Lua
values, regardless of category/index. 3726F0 suppresses stale redeem attempts;
unread poll returns false while preserving the original null-array diagnostic.
No native response array is emptied, freed or replaced. All hooks are MP-only.
Read/redeem attempts log controller/category/index/mapped slot/count/bounds;
repeated identical reads are bounded. Native fetch success logs size/capacity and
allocation. hqmail includes counters/size/capacity and reads slots only when >=14.
The no-message accessor is deterministic; kiosk layout and any separate static
claim button remain operator verification. If no accessor/redeem counter changes
when that button is used, its Lua/native entry path is outside MarketingComms.

Stage3 also explicitly terminates the SKU/promotional blobs (native cache copies
read them as strings), fixes diagnostic RVA resolution to occur after image mapping and
retains a queued payroll push if native string allocation fails. Release/harness
pass in hq-slice5-stage3-*.log; bounds tests cover exact last/one-past slot, invalid
controllers, null-size and excessive counts. Native detours are not game-tested.
