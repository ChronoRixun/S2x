# Slice 4 evidence: PID 40144

`run-40144/actions.txt` lists every logged service request, raw decode and injected
JSON response in console order. Non-AE replies are reconstructed from 384073d,
not observed wire captures. The console has no startup banner; the last auth
boundary before PID 40144 is used. Authentication diagnostics are redacted.

Quartermaster: frontend load issues Reward 4 user/scheduled fetches (49/50),
Marketplace 111 (51: page 1, limit 100, type 100), Marketplace 242 (52), Reward 4
kind-5 user fetch (53), Marketplace 168 (54). SKU success reports fetched=1.
World load later repeats user/scheduled (122/123), 242 (124), kind-5 user (125),
168 (126), pump (127). 242 body is fields 1=context s2_steam,
2=3cf6ce39-7313-4bd0-1fcf-c8ba7b0eecd6, 3=24-byte ClientTx, 4=1.
Its reply is only typed empty struct `17 08 00 00 00 00` after the task header.
111 empty terminal page succeeds; first unresolved point is 242's absent business
result and the unobserved remaining LUI gate. Click timestamps and separate
operator hqnative prints are absent; load sequences cannot prove click causation.

Mail: only MarketingComms 6 at transaction 43, requesting 14 slots; reply has 14
allocated ID-zero records. No task 4 viewed report, redemption service request,
or claim_achievement_reward occurs. Owner reports claim error, so divergence
precedes network redemption (cleared message ID/code guards or UI visibility).
Keep allocated slots; recover MarketingGetMessage visibility instead of inventing
an uncaptured redemption task.

Payroll: Reward 12 transaction 80 reports picked_up_payroll timestamp
1789255507000000, parameters 1=1, 2=0. Transactions 81,83,85,86,88,91,96,98,
101,104,107,117 replay it. 131 and 134 carry that event and timestamp
1789256008000000. Empty transport success is already sent, but local code only
creates a claimable achievement; there is no subsequent native AE claim request.
That is the first economy divergence: pickup must settle the local payroll once,
with persistent protection against these repeated batches and later-period replay.

Supply drop: Reward 4 transaction 84, open_supply_drop ClientTx
KxJ3GwAAAADokvCXoAEAAA==, sd_mp; injected response 39 is Status ok with three
GrantedItems and absolute DetailedInventory. Owner verified native reveal.
Task 168 also runs at startup and after world loading, with a DIFFERENT ClientTx;
its repeated {user, empty account, item ID, 64-byte metadata, collision} records
indicate item-data updates (new-item flag), not a drop receipt lookup.
The missing handler replies zero results. Do not alter successful AE opening.

Unscoped request_trace dumps are overwritten across launches: 168_000/001 bytes
now disagree with their logged previews (ClientTx and lengths). They are archived
as found but must not be attributed to this PID. 168_002 matches the log (312
bytes, three items 4194366/4194540/100728853). PID-scoped HQ dumps are reliable.
