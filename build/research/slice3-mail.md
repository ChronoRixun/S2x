# Slice 3: Mail and payroll

Established from S2xFull: MarketingRedeemMessageCodes binding 0x125780 ->
0x3726F0(controller, category, index). Requires ready mail, a nonzero message
ID at entry+0x10, and code length at +0x1C34. Code is at +0x1834;
a second code at +0x1C38/+0x1C78 selects 0x2B3590 rather than 0x2B3420.
These enqueue redemptions, drained by 0x2B2D50: group 0 type 0x87 or 0x88,
success 0x2B3030, failure 0x2B2FA0, submit 0x1B988D or 0x20DD70.
Success applies inventory from data+0x830/count+0x83C (stride 0x3B0) and
currency deltas from +0x840/count+0x84C (stride 0x30). This is not a normal AE
JSON task and must not be added to achievement_injection's type filter.
Exact DW task IDs for these fragmented SDK issuers remain unresolved.

0x3721A0 removes a message by zeroing its ID. MP placeholder IDs now use zero:
no invented redeemable code/reward and no fabricated claim. The 14 minimum
allocated entries and mail_guard remain. Excessive requests are bounded at
4096 slots; overflowed varints are rejected. Zombies payload unchanged.
MarketingComms 4 now has raw request tracing without changing its reply.

Payroll: prior evidence establishes Reward 11 picked_up_payroll, but this
latest traced PID contains no such event or claim request. Existing local
200 AC / four-hour claimable achievement and permanent claim receipts are
preserved. No invented new reply or automatic double grant. Payroll kiosk
success is unresolved; capture a debug run with one pickup followed by
one claim. Compare aeevent payroll; aefetch user; hqeconomy to distinguish
local event generation from native claim submission. A0 rejection in PID
55380 is from a non-group-0 task; do not weaken the crash-prevention filter.
