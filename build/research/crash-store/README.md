# Startup fail-fast (0xC0000409) with the owner's HQ store

## Artefacts

| File | What it is |
|---|---|
| `hq_economy.json` | byte-for-byte copy of `<game>\players2\user\hq_economy.json.crashbak2` (6233 bytes, revision 72). The original is never modified. |
| `bdMarketplace_99_request.bin` | one of the 1989 identical task 99 requests from run 51584. |

Both are harness fixtures; `build/research/hq-tests/tests.cpp` loads them.

## What the fault address actually is

Windows Application Error, 2026-09-12 21:01:52 and 21:02:48:

```
Faulting application name: s2x.exe, version: 0.0.0.250
Faulting module name: s2_mp64_ship.exe, version: 2.0.0.1
Exception code: 0xc0000409   Fault offset: 0x0000000000ab656d
```

Image offset `0xAB656D` in `build/research/ghidra/s2_mp64_ship_unpacked.exe` (file offset
`0xAB5B6D`) decodes to:

```
00AB6550  48 89 4C 24 08        mov   [rsp+8], rcx          ; __report_gsfailure
00AB6555  48 83 EC 38           sub   rsp, 38h
00AB6559  B9 17 00 00 00        mov   ecx, 17h              ; PF_FASTFAIL_AVAILABLE
00AB655E  FF 15 54 59 7B 10     call  IsProcessorFeaturePresent
00AB6564  85 C0                 test  eax, eax
00AB6566  74 07                 je    short 00AB656F
00AB6568  B9 02 00 00 00        mov   ecx, 2                ; FAST_FAIL_STACK_COOKIE_CHECK_FAILURE
00AB656D  CD 29                 int   29h                   <-- reported fault offset
```

So the fail-fast is **`__report_gsfailure` inside the game module**: a `/GS` stack cookie
check failed, i.e. a *game* function's stack buffer was overrun. It is **not** the CRT
invalid-parameter path (`FAST_FAIL_INVALID_ARG` = 5) and not `abort()`
(`FAST_FAIL_FATAL_APP_EXIT` = 7), and an S2x-side `abort()` would fault in `s2x.exe`,
not in `s2_mp64_ship.exe`.

The same offset and exception code were already logged on 2026-09-12 00:45:48 with
s2x.exe **0.0.0.195** - before `hq_economy.json` existed at all (`hq_economy.lock` was
first created at 01:56). Whatever smashes that cookie predates the HQ store.

## Was the store itself to blame?

No parsing or migration defect was found, and the A/B is not clean:

* Run 51584 (20:32-20:36, same installed build 0.0.0.250 = slice 5, same store file,
  file unmodified since 20:23) loaded it successfully -
  `[HQ economy] revision 72: 1 currencies, 10 items, 8 achievements` in
  `build/research/run-51584/console-redacted.log`.
* The two crashing launches wrote **zero** lines to `s2x\logs\console.log` and produced
  no `s2x\dump\dw` payloads, so they died before the first `Com_Frame` (the
  `g_consoleLog` dvar is registered from a `scheduler::main` task). Nothing in S2x reads
  the store that early: every `snapshot()`/`transact()` caller is either a
  `scheduler::pipeline::main` loop gated on a native ready flag, a console command, or a
  Demonware transport handler, and all of those run after the console log opens.
* The harness now loads this exact file through the production `hq_economy`,
  `achievement_engine`, `hq_payroll` and `hq_marketplace` code (snapshot, slice 6
  migration, offer rollover, payroll settle, native projection, catalog/wallet
  invariants) and passes.

The hardening in the same commit therefore targets the *class* of fault rather than a
single reproduction: every store-loading entry point now catches, logs and falls back to
defaults, the secure-CRT formatters truncate instead of fail-fasting, the wallet sync
cannot exceed the 13 native currency slots, and store identifiers are bounded at 128
characters before they are handed to native code.

If it reproduces, capture it with a debugger attached at launch (`s2x.exe` + WinDbg,
break on `ntdll!RtlFailFast2`/`int 29h`): the stack trace names the game function whose
cookie died, which is the one piece of evidence no static analysis can supply here.

## bdMarketplace task 99

See `src/client/game/demonware/hq_proxy_rewards.hpp` for the full chain. Summary:

* `2AF7A0` parses our AE reply (`GrantedItems`, `GrantedCurrencies`,
  `DetailedInventory`) into the per-controller block at `87E3B30 + controller * 0x154`
  and then calls `2AF560`.
* `2AF560` opens a `bdByteBuffer` over a **0x3FC-byte stack buffer**, writes `99` first,
  then the pending item ids and `(currency, amount)` pairs, then submits.
* The LUI trace shows `Rank.RewardMasterPrestigeSupplyDrops` /
  `Rank.ConvertProxyRewards` immediately before the first request.

So task 99 is the client committing rewards it was just granted. The captured payload is
`"s2_steam"` plus four `uint32(1)` fields, which does not line up with `2AF560`'s field
order, and the transport plus both completion callbacks are in the Arxan-protected
region (`31F0740`, `326DAD0`, `326DD60`, `326C720` all fail to decompile), so the result
schema is **not** established.

Note that `service::exec_task` already answered unknown tasks with a well-formed
task-level success (`create_reply(id).send()`, result count 0) and the client still
re-issued the request every frame - a bare success does not stop the loop. The handler
therefore registers the task, validates the request, replies with a status only, and
logs the payload once instead of once per frame (the measurable harm was 1989 console
lines plus 1989 payload dumps in a single run). `hqtask99 fail` switches the reply to
`BD_HANDLE_TASK_FAILED` at runtime so the failure branch can be A/B tested in one
session without a rebuild.
