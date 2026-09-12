# Slice 4 Mail and payroll

Native MarketingGetMessage 125020 calls 3722F0: ready at 8A14F84, array pointer
8A15010, stride 1CA0, ID +10. It returns no Lua value when ID is zero. Thus the
current 14 allocated cleared slots already implement a non-claimable inbox by
the recovered native contract. There is no captured Mail claim request to answer.
No redemption codes or rewards are invented. Mail reply bytes are now traced;
hqmail prints readiness and IDs/content/code lengths without printing contents.
The owner's remaining claim button/error is unresolved pending these live values
and its actual Lua entry point. This is not a claimed Mail kiosk fix.

Reward 12 pickup is now a settlement in hq_economy::transact. Local policy is 200
currency 2 per UTC four-hour bucket (00/04/08/12/16/20 UTC), selected from the
native event's microsecond timestamp. Permanent payroll:period receipts survive
event receipt eviction, aliases, reload and different pickup timestamps. Old
period batches acknowledge without grants; future timestamps beyond five minutes
and zero timestamps reject. A legacy manual claim in the same period also blocks
a second grant. Failed save/overflow rolls back; task 12 gets a failed task reply
if event processing fails. No additional native claim is needed or captured.

The synthetic aeevent command retains its old claimable-achievement behavior;
native DW event delivery selects settlement explicitly. This preserves existing
harness coverage and avoids pretending the synthetic command tests the kiosk.
A task12 success acknowledges the event; immediate wallet push/UI notification
has not been recovered. Verify persisted balance and next Marketplace 132 fetch.

Tests cover captured repeated timestamps, alias replay after reload, legacy manual
claim protection, next period, stale batch and invalid timestamps. Release and
standalone harness pass. No native/game-level test was run.
