# Slice 6 currency correction

Established by operator Lua trace: Inventory_GetCurrencyBalance(0,7) is the
hammer/Armory Credits counter; currency 2 is COD Points (owner observed +200 CP).
Native reader 279780 has 13 slots; sync uses the existing absolute setter27D510
on the main thread, now including ID7. Payroll and local Orders rewards use7.
The amount constant payroll_amount=200 remains a guess. Extracted payroll
strings and tables did not provide a retail amount or a currency-name table.

Migration marker transactions[id=migration:payroll-currency7-v1] stores amount
moved. Valid native payroll receipts and manual payroll claim receipts account
for 200 each, conservatively max(native,manual) per day to avoid counting native
acknowledgements of manual claims twice. Ambiguous historical overlaps can
under-recover; unrelated CP is not inferred as payroll. Transfer is capped by
remaining CP and uint32 AC headroom. Only2->7 changes; no negative balance or
reissued reward. Pending known local AC definitions are corrected. Marker,
wallet and rewards persist atomically before snapshot is published; failed save
preserves the original. New stores get the marker before new grants.

Release solution and rebuilt harness/run pass (hq-slice6-stage1-*.log).
Tests: receipt overlap, unrelated balances, spent credits, one-time marker,
payroll persistence/replay and existing suite. No game launched.
