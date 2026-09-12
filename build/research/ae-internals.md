# Achievement Engine internals — Slice 1b

All addresses below are image offsets, not absolute pointers. Evidence is the supplied unpacked x86-64 byte ranges and string tables; no game was run. Capstone 5.0.9 was used, restarting at known function entries (padding contains invalid instructions and must not be decoded as function bodies). RIP targets are `instruction end + signed displacement`; rel32 calls use the same calculation.

## Calling convention and LUI entry points

Windows x64: RCX/ECX, RDX/EDX, R8/R8D, R9/R9D are the first four arguments; bool returns in AL. Every LUI wrapper takes `lua_State*` in RCX and returns its Lua result count in EAX. Numeric Lua arguments are converted through `0x2D9AA0`/`cvttss2si`. Contrary to the initial premise, many engine operations are **inlined in the LUI wrapper**, with no separate engine call.

`c` below means controller index, `id` numeric achievement ID, `kind` achievement kind. Getter/reset rows have no task/response object and no ProcessResponse group: they read/write caches synchronously.

| LUI binding / entry | Lua arguments; native operation / target | Task or cache (image offset) |
|---|---|---|
| FetchScheduledChallenges `0x121760` | `(c)`; generates Tx at `0x8390A0`; call at `0x1217DE` to `bool 0x1399C0(ECX=c, RDX=Tx)`; returns bool, Tx string | Task `0x60391D0 + c*0xF8`; task type `0x8F`, group 0 |
| GetScheduledChallenges `0x121A00` | `(c)`; inlined cache-to-Lua table | `0x5C94C60 + c*0x1908`; ready byte `+0x1900`, up to 100 records of `0x30`, ID sentinel at `+0xC` |
| GetNextPeriodStart `0x121870` | `(kind)`; inlined indexed read, valid kinds 0..13; formats uint64 via `0x76A3D0` | `0x60CB1A0 + kind*8` |
| GetActivationLimit `0x121950` | `(kind)`; inlined uint32 read, valid kinds 0..13; returns Lua number | `0x6039198 + kind*4` |
| FetchPlayerActiveChallenges `0x121D00` | `(c)`; call at `0x121D7E` to `bool 0x139350(ECX=c, RDX=Tx)`; tail-calls `0x139400(c, emptyPage, Tx, 0)`; returns bool, Tx string | Task `0x6039A60 + c*0xF8`; type `0x84`, group 0 |
| ArePlayerAchievementsFetched `0x121E90` | `(c)`; inlined ready-byte read | `0x60A4080 + c*0x13890` |
| GetPlayerActiveChallenges `0x121F40` | `(c)`; inlined cache filtering and Lua table construction | `0x60A4080 + c*0x13890`; records start `+0x10`, stride `0x40`, capacity 1000 |
| GetPlayerAchievementInfo `0x1213B0` | `(c,id)`; inlined search of 1000 records, returns default table if absent | Same active cache; IDs at `0x60A409C + c*0x13890 + i*0x40` |
| ActivatePlayerChallenge `0x1222C0` | `(c,id)`; request construction is inlined; kind helper `0x139DC0(ECX=id)`; kinds 4/11 select `activate_user_contract`, others `activate_scheduled_user_achievement` | Task `0x603A030 + c*0xF8`, type `0x99`/`0x8D`, group 0; callbacks `0x13AF60`, `0x13B0B0` |
| DeactivatePlayerChallenge `0x122700` | `(c,id)`; inlined request; name helper `0x13A020(ECX=id)` | Task `0x60393C0 + c*0xF8`, type `0x8E`, group 0; callbacks `0x13B630`, `0x13B760` |
| ClaimChallengeReward `0x122AA0` | `(c,id)`; inlined request, requires matching active record with state 3; name helper `0x13A020(ECX=id)` | Task `0x60395B0 + c*0xF8`, type `0x9E`, group 0; callbacks `0x13B370`, `0x13B4A0` |
| FetchPlayerExpiredAchievementsSinceTimestamp `0x123440` | `(c,timestamp)`; second argument via `0xCCD40`; call at `0x1234C8` to `bool 0x139750(ECX=c, RDX=uint64 timestamp)` | Task `0x6039C50 + c*0xF8`, type `0x72`, group 0; callbacks `0x13C000`, `0x13C090` |
| GetPlayerExpiredAchievementsSinceTimestamp `0x123500` | `(c)`; inlined table plus timestamp | `0x5C98070 + c*0x1A0`, count `+0x190`, timestamp `+0x198` |
| GetNewlyCompletedAchievements `0x122E80` / ResetNewlyCompletedAchievements `0x122F50` | `(c)`; inlined list read/reset | `0x5C97E70 + c*0x7C`, count `+0x78` |
| GetRecentlyExpiredAchievements `0x123000` / ResetRecentlyExpiredAchievements `0x1230D0` | `(c)`; inlined list read/reset | `0x5C97F70 + c*0x7C`, count `+0x78` |
| ResetRecentlyExpiredAchievementByID `0x123180` | `(c,id)`; `0x13D900(RCX=list, EDX=id)` | Same recently-expired list |
| GetCommunityAchievementCounterTotal `0x123250` / IsCommunityAchievementCounterKnown `0x123300` | `(counterID)`; inlined lookup | IDs `0x5C983D0`, count `0x5C98684` |

## Scheduled request and response delivery

`0x1399C0` is conclusively the scheduled issuer: `0x139B09` loads string `0xB414F0` (`get_scheduled_user_achievements`) into R9 for the Action formatter. `0x1399EB` resolves task base `0x60391D0`; `0x1399F2` applies controller stride `0xF8`. It registers type `0x8F` through `0x2081B0(0,c,0x8F)` at `0x139A16`.

Task layout observed for user, scheduled, expired, activation, deactivation and claim: request string object at `+0`; active uint32 at `+0xC0`; 25-byte transaction at `+0xD0`; auxiliary pointer at `+0xF0`. Scheduled writes active/Tx at `0x139B68..0x139B98`, then calls `AE_SetResponseString(task, requestJSON)` at `0x139B9E`. User does the equivalent at `0x13968F..0x1396BD`. The name of this setter is historical: it also stores **requests**.

`AE_SetResponseString` at `0xA3B8F0` adds `0x28` to RCX and calls `0xA75500`; getter `0xA3B850` adds `0x28` and tail-calls `0xA756D0`. Thus the string member is `object+0x28`.

The existing, runtime-proven Zombies bridge uses input object `0x6039A60+0xF8 = 0x6039B58`, string member `0x6039B80`. **The supplied issuer bytes do not prove that +0xF8 is a per-task native response field.** It is also exactly the controller task stride. Do not mechanically apply it to every task or extend this bridge to controller 1.

The native scheduled completion response object's address is **not established** by these dumps. Its success/failure callbacks are `0x13C120` / `0x13C220`, registered at `0x139BBD..0x139BD2`, outside supplied ranges. Slice 1b uses the already-proven user bridge object as a shared, synchronous JSON input for controller 0, including scheduled responses. It does not write a guessed scheduled response field.

`AE_ProcessResponse(ECX=controller, RDX=stringObject, R8D=group)` at `0x676A40` immediately reads JSON with `0xA3B850`. It resolves Action to task types through `0x676860`, finds the task with `0x208270(group,controller,type)` at `0x676B80`, gets task data with `0x839390`, and compares ClientTx to `task+0xD0` at `0x676BA2..0x676BB8`. It does not locate the pending task by its input object's address. Group **0** follows directly from issuer registration and is also explicit in the native ingress shim at `0x676E73..0x676E80`.

The jump table at `0x676D9C` and byte map at `0x676DD4` dispatch type `0x84` to handler `0x13E960`, `0x8F` to `0x13EF20`, `0x72` to `0x13EC20`, `0x8D`/`0x99` to `0x13E8B0`, and `0x9E` to `0x13E910`. Handler signatures are `(ECX=controller, RDX=JSON parser, R8=root, R9=task transaction pointer)`. Their bodies are absent; native schedule JSON shape acceptance remains unverified.

## Exact additional dumps requested

Stop investigation of these callees until the operator provides:

| Offset | Size | Purpose |
|---|---|---|
| `0x13BE30` | `0x0500` | User callbacks `0x13BE30`/`0x13BEA0`, expired callbacks, scheduled callbacks `0x13C120`/`0x13C220`; establish native completion response layout |
| `0x13E8B0` | `0x0AA0` | User/scheduled/expired and mutation response handlers; recover JSON containers, cache readiness, pagination and completion behavior |
| `0x676860` | `0x01E0` | Exact Action-to-task mapping |

These missing ranges do not block controller-0 user/active/scheduled delivery through the proven bridge. Mutation/expired injection is outside this slice's requested fetch delivery and is not installed.
