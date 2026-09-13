# S2x test runbook — verify every branch before opening upstream PRs

**Written:** 2026-09-12
**Repo:** `D:\S2x` (fork `ChronoRixun/S2x`, upstream `Brentdevent/S2x`, `master` == upstream `b4ae6e7`)
**Game:** `D:\Program Files\Steam\steamapps\common\Call of Duty WWII`

## Purpose and how to use this

Every change in this pass lives on its own branch off `master`, and the plan is one upstream pull
request per branch. Before any PR is opened you want to have personally seen the fix work and seen
that it did not break anything else. This runbook is the script for that. Work through it in order:
first build and run the `integration` branch (which merges every branch) and do the **general
regression pass** in "Before you start" — that catches anything that broke across the whole set in
one launch. Then work down the per-branch sections. Each section tells you what the fix does, which
commits it is, exactly what to type, what the console should print, what else the change touches
(the regression checks), and what I already verified versus what has never been run. Each section
ends with a tick-box checklist. **A branch is not ready for a PR until every box in its section is
ticked.** If something fails, don't fix it in the moment — capture the evidence listed in that
section and note it, so the failure can be diagnosed from the log rather than from memory.

Where I know the exact console wording it is quoted verbatim (most of these are copied out of
`<game>\s2x\logs\console.log` from real runs). Where the exact wording was never observed the
runbook says "look for a line mentioning ..." instead of inventing text.

---

# Before you start

## 0.1 Branch state (as of 2026-09-12 20:30)

| Branch | Tip | Pushed to `origin`? | Upstream issue |
|---|---|---|---|
| `chore/search-path-logging` | `5302cbe` | yes | none (local finding) |
| `chore/dev-diagnostics` | `d4c150c` | yes | none (supports #53/#48/#49) |
| `fix/44-rotation-settings` | `84258e1` | yes | [#44](https://github.com/Brentdevent/S2x/issues/44) |
| `fix/40-party-host-slot` | `4c52aa4` | yes | [#40](https://github.com/Brentdevent/S2x/issues/40) |
| `feat/52-stringtable-override` | `8d45c0d` | yes | [#52](https://github.com/Brentdevent/S2x/issues/52) |
| `feat/22-bot-fill` | `3dd9655` | yes | [#22](https://github.com/Brentdevent/S2x/issues/22) |
| `fix/53-zombies-progression` | `af0dbcd` | yes | [#53](https://github.com/Brentdevent/S2x/issues/53) |
| `feat/48-rank-prestige` | `f28ff88` | yes | [#48](https://github.com/Brentdevent/S2x/issues/48) |
| `feat/39-hq-economy` | `5a6d86f` | yes | [#39](https://github.com/Brentdevent/S2x/issues/39) |
| `integration` (merges all nine) | `8fb25af` | yes | — |
| `fix/49-local-play-unlocks` | **never created** | — | [#49](https://github.com/Brentdevent/S2x/issues/49) |

`fix/49-local-play-unlocks` was planned (plan section 9: instrument with `cg_unlock_debug 1` in
Local Play, then `luidump Engine Lock|Unlock|Item` and `luidump Cac` to find the binding) but the
investigation was never started and the branch does not exist. There is nothing to test for #49 and
nothing to open a PR for. Say so on the issue or leave it alone.

Both `feat/39-hq-economy` (`5a6d86f`) and `integration` (`8fb25af`) are already pushed to `origin`
(confirmed against `origin/feat/39-hq-economy` and `origin/integration` as of 2026-09-12 20:55). No
push is needed before testing.

## 0.2 Build and install a branch

From Git Bash in `D:\S2x`. Close the game first — the exe cannot be overwritten while it runs.

```bash
git checkout <branch>
MSYS_NO_PATHCONV=1 ./tools/premake5.exe vs2022
MSYS_NO_PATHCONV=1 "/c/Program Files/Microsoft Visual Studio/2022/Community/MSBuild/Current/Bin/MSBuild.exe" build/s2x.sln -m -v:minimal -nologo -p:Configuration=Release -p:Platform=x64
cp build/bin/x64/Release/s2x.exe build/bin/x64/Release/s2x.pdb "/d/Program Files/Steam/steamapps/common/Call of Duty WWII/"
cp data/ui_scripts/mp/patches/unlocks.lua "/d/Program Files/Steam/steamapps/common/Call of Duty WWII/s2x/ui_scripts/mp/patches/"
```

Notes:

- `premake5.exe vs2022` is required after **every** branch switch: branches add new `.cpp` files and
  the solution is generated from a glob.
- The dash-style MSBuild switches (`-m -v:minimal`) are required under Git Bash; `/m` style breaks.
- The last line only matters for `fix/53-zombies-progression`, `feat/48-rank-prestige` and
  `integration` (they are the branches that change `unlocks.lua`). Copying it on other branches is
  harmless but will leave the newest Lua in place — if you want a truly clean branch test, copy the
  `unlocks.lua` from the branch you are on.
- The currently installed `s2x.exe` is already `integration` at `8fb25af` (slice 4 reviewed and
  merged, built and installed at 20:55 on 2026-09-12 — HANDOFF item 3h). A rebuild/reinstall before
  the regression pass is **not required**, but doing one is harmless if you want a from-scratch
  confirmation.

## 0.3 Back up and restore your profile

Your pre-test progression backup already exists: **`D:\S2x\build\backups\players2-234709\`** — a copy
of `<game>\players2` taken before anything wrote stats.

Take a fresh backup before each risky test (anything that writes stats: `setrank`,
`unlockzmeastereggs`, HQ grants):

```powershell
$game = "D:\Program Files\Steam\steamapps\common\Call of Duty WWII"
$stamp = Get-Date -Format "HHmmss"
Copy-Item "$game\players2" "D:\S2x\build\backups\players2-$stamp" -Recurse
```

Restore (game closed):

```powershell
$game = "D:\Program Files\Steam\steamapps\common\Call of Duty WWII"
Remove-Item "$game\players2" -Recurse -Force
Copy-Item "D:\S2x\build\backups\players2-234709" "$game\players2" -Recurse
```

Targeted undo, if you don't want to roll the whole profile back:

- Zombies achievement records written by `unlockzmeastereggs confirm`: delete
  `<game>\players2\user\achievements.json`. That file did **not** exist before this pass, so deleting
  it restores the original state exactly.
- No `setrank` has ever been run on this profile. The first time you run it, take a fresh backup
  first.

## 0.4 Reset the HQ economy store

The Headquarters economy store is `<game>\players2\user\hq_economy.json` (plus a lock file
`hq_economy.lock`). It is not part of stock progression — deleting it only resets the HQ features.
It currently holds leftover test state (a common supply drop, three loot items, three in-progress
daily orders, a claimable payroll).

```powershell
$game = "D:\Program Files\Steam\steamapps\common\Call of Duty WWII"
# game closed
Remove-Item "$game\players2\user\hq_economy.json" -Force
Remove-Item "$game\players2\user\hq_economy.lock" -Force -ErrorAction SilentlyContinue
```

If you hand-edit the file while the game is running, type `hqeconomy reload` in the console to drop
the cache and re-read from disk. `hqeconomy reload` does **not** reset anything — only deleting the
file does.

## 0.5 Launching the game

Launch **only** by double-clicking a shortcut (a direct `s2x.exe` launch from a terminal crashes with
`0xC0000005` inside the game image). **Steam must be running** before you start, or you get
"S2x Error: Steam must be running to play this game!" and a stuck process.

| Shortcut | Arguments | Use for |
|---|---|---|
| `C:\Users\Owen\Desktop\S2x Development.lnk` | `-noupdate -multiplayer` | normal MP testing |
| `C:\Users\Owen\Desktop\S2x MP Trace.lnk` | above + `-demonware_debug` | every HQ economy test, and any failure you need evidence for |
| `D:\S2x\build\backups\S2x Zombies Dev.lnk` | `-noupdate -zombies` | Zombies testing |
| `D:\S2x\build\backups\S2x MP Trace NoSteam.lnk` | trace + `-nosteam` | only if Steam sign-in is broken; online features are degraded |

Dedicated server (for #44 and #40) is started from a **cmd** window in the game folder — that route
does work directly:

```bat
cd /d "D:\Program Files\Steam\steamapps\common\Call of Duty WWII"
start "" s2x.exe -dedicated +set net_port 27017 +set party_maxplayers 4 +set party_matchStartDelay 15 +set scr_dm_scorelimit 55 +set sv_maprotation "gametype dom map mp_shipment_s2 gametype war map mp_shipment_s2 gametype dm map mp_shipment_s2" +exec server.cfg +map_rotate
```

## 0.6 Sending console commands

- Client: the separate console window titled **`S2x Console`** — click it, the input box is focused
  on activation, type the command and press Enter. The in-game console (backtick in
  `S2x - Multiplayer` / `S2x - Zombies`) also works but is less reliable.
- Dedicated server: its window is titled **`S2x Dedicated Server`**, not `S2x Console`.
- If a command sequence is long, put it in a cfg file instead and run one line. Cfg files live in
  `<game>\s2x\` and are run with `exec <name>.cfg` (loose cfg exec works). Existing examples in that
  folder: `server.cfg`, `capture_hq.cfg`, `capture_strings.cfg`.
- Helper scripts, if you'd rather automate: `D:\S2x\build\backups\syscon.ps1` posts commands into the
  console window without stealing focus; `D:\S2x\build\backups\rotation-test2.ps1` drives the
  dedicated-server rotation test end to end.

## 0.7 Reading the console log

One shared log for client and server: **`<game>\s2x\logs\console.log`** (dvar `g_consoleLog`). It is
appended to, not rotated, so note the line count before a test and only read the tail.

```powershell
$log = "D:\Program Files\Steam\steamapps\common\Call of Duty WWII\s2x\logs\console.log"
# before the test
$before = (Get-Content $log).Count; $before
# after the test — only the new lines
Get-Content $log | Select-Object -Skip $before
# look for problems in the new lines only
Get-Content $log | Select-Object -Skip $before | Select-String -Pattern 'error|FAILED|exception|assert'
```

Crash dumps land in `<game>\minidumps\`. **Baseline: three zips already exist** from 2026-09-12
16:38, 16:49 and 16:53 — those are the Mail crash that commit `e19ae2f` fixed. Only a dump newer than
the moment you started testing counts as a new crash.

```powershell
Get-ChildItem "D:\Program Files\Steam\steamapps\common\Call of Duty WWII\minidumps" |
  Sort-Object LastWriteTime -Descending | Select-Object -First 5 Name, LastWriteTime
```

## 0.8 General regression pass (run this first, on `integration`)

`integration` (`8fb25af`) is already built and installed (see 0.2's note). Confirm that (or rebuild
it if you want a clean baseline), then:

1. Note the console.log line count (0.7).
2. Launch `S2x Development.lnk`. The MP frontend reaches the main menu; the S2x server browser and
   the UNLOCKS tab are present.
3. Quit. Launch `S2x Zombies Dev.lnk`. The Zombies frontend reaches the main menu; the UNLOCKS tab is
   present with the Zombies rows.
4. Back in MP: `map mp_shipment_s2 tdm`, then `spawnBot 6`, play a couple of minutes, get a few kills,
   let the match end or `endMatch`.
5. In Zombies: start a private match on `mp_zombie_descent` (The Final Reich) or Groesten Haus, play
   one full round, quit to the lobby.

**Clean-log criteria** for the new lines from steps 2–5:

- [ ] No line containing `error` (case-insensitive) other than known-benign ones you have seen before
      — read each one, don't skip.
- [ ] No line containing `FAILED`.
- [ ] No new file in `<game>\minidumps` newer than the start of the test.
- [ ] The game reached the frontend, loaded a map and quit cleanly in both modes.

If the pass is clean you can trust per-branch testing to be about the branch. If it is not, find out
which branch owns the failure before continuing.

### Baseline checklist

- [ ] `integration` (`8fb25af`) built and installed (exe, pdb, `unlocks.lua`)
- [ ] Profile backed up
- [ ] MP frontend clean
- [ ] Zombies frontend clean
- [ ] Local bot match played, clean
- [ ] One Zombies round played, clean
- [ ] No new minidump

---

# 1. `chore/search-path-logging`

**Upstream issue:** none. This came out of a local incident — UI scripts silently were not loaded
from `%LOCALAPPDATA%\s2x` and there was no way to tell from the log. (Root cause turned out to be
that `%LOCALAPPDATA%\s2x` does not exist on this machine at all; the game-local
`<game>\s2x\ui_scripts` is what loads.)

**What it does:** at filesystem startup the client now prints the resolved AppData path and the
ordered list of loose-file search paths, and if *no* `ui_scripts` directory was found in any search
path it says so once instead of failing silently. No behaviour change beyond the logging; the
`ui_scripts` loader was refactored to return whether the directory existed and to compute the
`mp`/`sp` subfolder once.

**Commits:**

- `5302cbe` Log loose file search paths and missing UI script directories

## What to test

1. Build and install this branch (0.2). Launch `S2x Development.lnk`.
2. In `console.log`, near the top of the run, find the two startup lines:

   ```text
   [FS] AppData path: C:/Users/Owen/AppData/Local/s2x
   [FS] Loose file search paths (highest priority first): <path>; <path>
   ```

   Confirm the search-path list actually contains
   `D:/Program Files/Steam/steamapps/common/Call of Duty WWII/s2x` — that is the folder that really
   loads on this machine.
3. Confirm custom UI still loads: the S2x server browser entry exists in the MP menu and the UNLOCKS
   tab is present. (Those come from `<game>\s2x\ui_scripts\mp\...`.)
4. Negative test for the "missing directory" line. Close the game, then:

   ```powershell
   $game = "D:\Program Files\Steam\steamapps\common\Call of Duty WWII"
   Rename-Item "$game\s2x\ui_scripts" "ui_scripts_off"
   ```

   Launch again and look for:

   ```text
   [LUI] No ui_scripts directory was found in N loose file search path(s); custom UI scripts are not loaded.
   ```

   The S2x server browser and UNLOCKS tab should be gone in this state — that is the point of the
   message. `lui_restart` in the console re-runs the loader and should print the line again.
5. Restore the folder:

   ```powershell
   Rename-Item "$game\s2x\ui_scripts_off" "ui_scripts"
   ```

   Relaunch, confirm the S2x menus are back and the `[LUI]` line is gone.

## Regression checks

- Custom UI scripts still load in **both** MP and Zombies (the refactor touched the mp/sp branch of
  the loader). Check the UNLOCKS tab in the Zombies frontend too.
- Campaign (`sp`) UI scripts: not testable here beyond "the code path is symmetric" — the loader now
  picks `sp` for the non-MP binary the same way it always did.
- No effect on dedicated servers, gameplay or Demonware.

## Status so far

Already verified in-game: both `[FS]` lines appear. The `[LUI]` missing-directory line and the
restore step have **not** been run — step 4 and 5 are new work for you.

## Checklist

- [ ] `[FS] AppData path:` line present
- [ ] `[FS] Loose file search paths` line present and lists the game-local `s2x` folder
- [ ] S2x server browser + UNLOCKS tab present (MP)
- [ ] S2x UNLOCKS tab present (Zombies)
- [ ] `[LUI] No ui_scripts directory was found ...` appears with `ui_scripts` renamed away
- [ ] Folder restored, menus back, `[LUI]` line gone
- [ ] No new errors / no minidump

---

# 2. `chore/dev-diagnostics`

**Upstream issue:** none directly. This is the instrumentation that made #53, #48 and the HQ economy
work possible: Release builds compile out `console::debug`, so every existing progression diagnostic
was invisible.

**What it does:** adds developer-only commands and logging with no behaviour change —
`luidump` (enumerate a LUI global table and print each key, its type and, for C closures, its name
and RVA), `findstrings` / `dumpcode` (scan and dump the loaded, unpacked game image — this is how the
Achievement Engine JSON vocabulary was found), a `[DW-trace]` one-liner plus payload files for stubbed
`bdReward` and `bdMarketplace` tasks, unhandled-action logging in the glutton HTTP server, and a
`cg_unlock_debug` dvar that prints a 2-second summary of the unlock hooks. It also fixes a real crash:
`console.cpp` now uses `_TRUNCATE` in `_vsnprintf_s`, so long trace lines cannot blow up the console.

**Commits:**

- `8951b10` Add developer diagnostics for progression and UI investigation
- `f4ca462` Write traced Demonware payloads to files and truncate long console lines
- `1b8d131` Add findstrings and trace unknown Demonware tasks
- `073a608` Add a range mode to findstrings
- `d4c150c` Add dumpcode for copying unpacked image bytes

## What to test

1. Build and install this branch. Launch `S2x MP Trace.lnk` (you want `-demonware_debug` on for the
   trace part).
2. `luidump` with no arguments prints its usage:

   ```text
   Usage: luidump <table[.subtable]> [filter] [output file]
   Example: luidump Engine Dvar, luidump Lobby S2x lobby-functions
   ```

3. `luidump Engine Dvar` — expect a summary line of the form
   `luidump: 'Engine' has N matching entries` followed by one line per entry with the key, its type
   and, for C closures, the binding name and RVA. Spot-check that known bindings are listed:
   `Engine.IsItemUnlocked` (RVA `0x1158D0`), `Engine.IsGuidUnlocked` (`0x1159C0`),
   `Engine.GetItemLockState` (`0x11D620`).
4. `luidump Engine Order` and `luidump Engine Hub` — used for the HQ work; they should not error even
   when they match nothing.
5. `luidump Engine Dvar engine-dvars` writes the output to a file instead; expect
   `luidump: wrote N entries of 'Engine' to 'engine-dvars'` and the file under `<game>\s2x\`.
6. `cg_unlock_debug 1`, then open Create-a-Class. Every 2 seconds while the hooks are being called:

   ```text
   [unlock_items] last 2s: 128 table calls, 0 local-client calls, 0 overridden | cg_unlockall_items=0 local_play=0 has_stats=1 last_table=mp/...
   ```

   Confirm `cg_unlock_debug 0` silences it and that the counters are zero-cost when off (no lines).
7. `findstrings open_supply_drop` — expect
   `findstrings: N string(s) containing 'open_supply_drop' (image size 0x...) -> <path>` and a file
   under `<game>\s2x\dump\strings\`. Range form: `findstrings @B40600-B41800`.
8. `dumpcode 13EF20 600` — expect
   `dumpcode: wrote 0x600 bytes from image offset 0x13EF20 to <path>` and the file under
   `<game>\s2x\dump\code\`.
9. `[DW-trace]` lines: with `-demonware_debug`, go online and enter Headquarters (or just reach the
   frontend). Look for lines of this shape (this exact one is from a real run):

   ```text
   [DW-trace] bdMarketplace::168 request: 136 bytes | 10 73 32 5F 73 74 65 61 6D 00 10 74 5A 53 49 44 ...
   [DW-trace] wrote s2x/dump/dw/bdMarketplace_168_001.bin
   ```

   and for unhandled HTTP actions, a line mentioning
   `[DW]: [glutton]: unhandled action '<name>' (N bytes)`.
10. Long-line crash regression: with `-demonware_debug` on, stay in the frontend for a minute while
    traces are being written. Before `f4ca462` this crashed. Expect no crash and no minidump.

## Regression checks

- **Everything here must be inert when the commands are not used.** Play a normal bot match with
  `cg_unlock_debug 0` (the default) and confirm no `[unlock_items]` spam and no frame-time change.
- Unlock behaviour itself must be unchanged: with `cg_unlockall_items 1`, items are still unlocked;
  with it `0`, they are still locked. The diagnostics only count calls.
- `-demonware_debug` off (the plain `S2x Development.lnk`) must produce **no** `[DW-trace]` lines and
  no files in `<game>\s2x\dump\dw\`.
- Zombies unaffected (no Zombies-specific code touched).

## Status so far

Already verified: `luidump`, the `[DW-trace]` lines and the `cg_unlock_debug` counters all work.
`findstrings` and `dumpcode` were used extensively for the Ghidra work, so they are proven in
practice. The "inert when off" regression checks have not been done as a deliberate test.

## Checklist

- [ ] `luidump` usage + a real table dump with correct RVAs
- [ ] `luidump ... <file>` writes the file
- [ ] `cg_unlock_debug 1` prints the 2s summary; `0` silences it
- [ ] `findstrings <text>` and `findstrings @<start>-<end>` both work
- [ ] `dumpcode <rva> <size>` writes the file
- [ ] `[DW-trace]` lines and `.bin` payloads appear with `-demonware_debug`
- [ ] Nothing traced without `-demonware_debug`
- [ ] Normal bot match unaffected with all diagnostics off
- [ ] No new minidump

---

# 3. `fix/44-rotation-settings` — issue [#44](https://github.com/Brentdevent/S2x/issues/44)

**What it does:** on a dedicated server, admin gameplay settings (`scr_dom_scorelimit` and friends)
were lost after `map_rotate`. `prepare_match_settings()` execs `default_xboxlive.cfg` on every
rotation and only replayed the `+exec` launch file — never `+set` values, never anything typed at the
console, and nothing at all in Zombies; re-exec'ing a cfg that ends in `map_rotate` also loops. The
fix adds an **admin settings ledger** (`dedicated_settings.cpp`): every dvar the admin sets — from
`+set` on the command line, from the `+exec` config and any config it execs, and from text typed into
the server console — is recorded, and the whole ledger is re-applied synchronously right before GSC
reads the values (inside `G_InitGame`, via the already-detoured `scr_begin_load_scripts_stub`), plus
once at lobby time. Lifecycle keys (`mapname`, `g_gametype`, `sv_maxclients`, `sv_maprotation`, ...)
are on a denylist and never recorded. As a side effect it also makes `+set` work at all on dedicated
servers (the engine ignores `+set` under S2x) and seeds `sv_maprotation` from `+set`.

**Commits:**

- `30e0d62` Keep admin gameplay settings across dedicated map rotations
- `84258e1` Apply +set arguments on dedicated servers

## What to test

1. Build and install this branch.
2. Confirm `<game>\s2x\server.cfg` contains (it already does):

   ```text
   set sv_hostname "S2x settings test"
   set scr_dom_scorelimit 300
   set scr_war_scorelimit 111
   ```

3. Start the dedicated server from a cmd window:

   ```bat
   cd /d "D:\Program Files\Steam\steamapps\common\Call of Duty WWII"
   start "" s2x.exe -dedicated +set net_port 27017 +set party_maxplayers 4 +set party_matchStartDelay 15 +set scr_dm_scorelimit 55 +set sv_maprotation "gametype dom map mp_shipment_s2 gametype war map mp_shipment_s2 gametype dm map mp_shipment_s2" +exec server.cfg +map_rotate
   ```

4. In the startup log, expect:

   ```text
   Dedicated settings: recorded scr_dm_scorelimit "55" (command line).
   Dedicated settings: tracking config 'server.cfg'.
   Dedicated settings: recorded scr_dom_scorelimit "300" (server.cfg).
   Dedicated settings: recorded scr_war_scorelimit "111" (server.cfg).
   Dedicated settings: restored N of M value(s) (command line).
   ```

   (The trailing source label is `command line`, the normalised cfg name, or `console`.)
5. `dedicatedSettings` (or `dedicatedSettings list`) in the **`S2x Dedicated Server`** window prints:

   ```text
   Dedicated settings: N recorded value(s), M tracked config(s).
     scr_dm_scorelimit "55"
     scr_dom_scorelimit "300"
     scr_war_scorelimit "111"
   ```

6. At the start of each match, look for the live-values line and the restore line:

   ```text
   Dedicated settings: restored N of M value(s) (script load).
   Dedicated settings: live scr_dom_scorelimit=300 scr_dom_timelimit=...
   ```

   For the DOM match it must show `300`, for WAR `111`, for DM `55`.
7. **Console-typed value survives rotation.** During an intermission type
   `scr_dom_scorelimit 250` in the server window; expect
   `Dedicated settings: recorded scr_dom_scorelimit "250" (console).` Then `endMatch` through the
   rotation twice so DOM comes back around, and confirm the `live` line now shows
   `scr_dom_scorelimit=250`.
8. **Client-visible check.** Launch a second instance (`S2x Development.lnk`), then in its console:

   ```text
   connect 127.0.0.1:27017
   ```

   The scoreboard / match rules should show the configured limit, not the stock default.
9. **Zombies path.** Repeat with `-dedicated -zombies`, a `set` line in the cfg (e.g.
   `set scr_zm_...` for whatever limit you want to prove), and after a rotation run `dvarDump` (or
   just read the value back by typing the dvar name) to confirm the value survived. Zombies used to
   replay nothing at all, so this is the important half of the fix.
10. **Loop check.** Since `queue_server_config()` was deleted, a `server.cfg` that ends with
    `map_rotate` must no longer cause a rotation loop. Add `map_rotate` as the last line of a test cfg
    and confirm the server rotates once per match, not continuously. Remove it afterwards.

## Regression checks

- **Clients are unaffected**: the component is `multiplayer_component` and returns early unless
  `game::environment::is_dedicated()`. Launch a normal client and confirm no `Dedicated settings:`
  lines appear at all.
- Denylisted keys must not be recorded — `dedicatedSettings list` must **not** contain `mapname`,
  `g_gametype`, `sv_maxclients`, `net_port`, `sv_maprotation`, `dedicated`.
- Read-only dvars are skipped rather than warned about repeatedly; if you see
  `Dedicated settings: Dvar_SetCommand did not apply <name> ...; using typed setters.` note which dvar
  it was — that is the fallback path and it is worth reporting in the PR.
- The console-input hook (`console::on_input`) now runs on every typed line — confirm normal console
  commands still work on a client (where the callback is not registered) and on the server.
- Rotation itself still works: three maps, three gametypes, in order, repeatedly.

## Status so far

**Fully verified once already** on a local dedicated server: cfg value 111, `+set` value 55 and a
console-typed 250 all survived rotations. Not yet done: the Zombies dedicated variant (step 9), the
client-connect scoreboard check (step 8), and the `map_rotate`-in-cfg loop check (step 10).

## Checklist

- [ ] `recorded` lines for `+set`, cfg and console sources
- [ ] `dedicatedSettings list` shows the full ledger, no denylisted keys
- [ ] `live` line shows the right limit for DOM / WAR / DM
- [ ] Console-typed 250 survives two rotations
- [ ] Client connects and sees the configured limit
- [ ] Zombies dedicated: value survives a rotation
- [ ] cfg ending in `map_rotate` does not loop
- [ ] A plain client prints no `Dedicated settings:` lines
- [ ] No new errors / no minidump

---

# 4. `fix/40-party-host-slot` — issue [#40](https://github.com/Brentdevent/S2x/issues/40)

**What it does:** a dedicated server was eating one of its own player slots. The dedicated frontend
owner is party member 0, so setting `5321` (party_maxPrivatePartyPlayers) and `Party_SetMaxClients`
to `party_maxplayers` meant N really allowed host + N-1 remote players (in Zombies, 3 of 4). The
reporting code already subtracted the host, so a full server never even showed "Full", and the join
rejection came from the engine's party-full check. The fix introduces the rule *native party/session
capacity = `party_maxplayers` + 1*: `sv_maxclients` and everything advertised stay at N, while `5321`
and both `Party_SetMaxClients` calls get N+1, applied through a helper that widens the dvar's
integer domain first so the engine's clamp cannot silently drop the value. The client mirror does the
same for the hosted party while keeping the advertised N for LUI.

**Commits:**

- `4c52aa4` Reserve the dedicated host's party slot on top of the player limit

## What to test

1. Build and install this branch.
2. Start a **Zombies** dedicated server with a limit of 1:

   ```bat
   cd /d "D:\Program Files\Steam\steamapps\common\Call of Duty WWII"
   start "" s2x.exe -dedicated -zombies +set net_port 27017 +set party_maxplayers 1 +exec server.cfg +map_rotate
   ```

3. In the server log expect the capacity line (this exact shape was already observed with
   `party_maxplayers 4`):

   ```text
   Dedicated party: capacity 5 (host + 4 players), min 1, session limit 5, host limit N.
   ```

   With `party_maxplayers 1` it must read `capacity 2 (host + 1 players) ... session limit 2`.
   Crucially the line must **not** end in `(clamped)` — if it does, `5321`'s domain rejected the
   value and the fix did not take. You may also see, once:

   ```text
   Dedicated party: widening 5321 domain [0, 4] to [0, 2].
   ```

4. **The actual join test — this is the part that has never been run.** Launch a client
   (`S2x Zombies Dev.lnk`), find the server in the browser and join.
   - Before the fix, one client was rejected (reason 46). Now it must **join**.
   - The browser should show `1/1` and the server marked **Full**.
   - Start a second client and confirm it is rejected — the capacity must not have become unlimited.
5. Repeat with `+set party_maxplayers 2`: one client joins, the browser shows `1/2` and
   **Joinable**; a second client joins and it becomes `2/2` Full.
6. Repeat in **MP** with `+set party_maxplayers 1`. The joining player must get a real gameplay slot:
   at match start the log should show the match starting with the player in it and **no** error line
   about the local client occupying a gameplay slot.

## Regression checks

- Normal capacities are not broken: run `party_maxplayers 4` and confirm four clients can be in the
  match and a fifth is rejected (or at least that the browser count matches reality).
- `sv_maxclients` must still read N, not N+1 — check with `dvarDump` or by typing `sv_maxclients` in
  the server console. The advertised/browser number must be the player count, not the party capacity.
- The client-side mirror (`dedicated_party_client.cpp`) affects a client hosting its own party.
  Confirm a normal private MP lobby with friends-count limits still behaves (or, minimally, that a
  client can host a local match and invite nobody without an error).
- The domain-widening helper writes into `dvar->domain.integer.max`. Confirm no dvar-related warning
  or assert appears at startup on either client or server.
- Zombies and MP both need checking — the bug was worse in Zombies (3 of 4).

## Status so far

Implemented and building; the capacity log line was verified on a server
(`capacity 5 (host + 4 players) ... session limit 5`, no clamp). **The client join test has never
been done** — that is the entire point of the issue, so steps 4–6 are mandatory before the PR.

## Checklist

- [ ] `Dedicated party: capacity N+1 (host + N players) ... session limit N+1` with no `(clamped)`
- [ ] Zombies, `party_maxplayers 1`: one client joins successfully
- [ ] Browser shows `1/1` Full; a second client is rejected
- [ ] `party_maxplayers 2`: `1/2` Joinable, then `2/2` Full
- [ ] MP, `party_maxplayers 1`: the player gets a gameplay slot, no slot error at match start
- [ ] `sv_maxclients` still equals `party_maxplayers`
- [ ] `party_maxplayers 4` behaves sanely
- [ ] No new errors / no minidump

---

# 5. `feat/52-stringtable-override` — issue [#52](https://github.com/Brentdevent/S2x/issues/52)

**What it does:** lets you replace (or add) any string table with a loose `.csv` file, the same way
GSC and LUI overrides already work. A detour on `DB_FindXAssetHeader` fast-paths anything that is not
`ASSET_TYPE_STRINGTABLE`; for string tables it looks for a loose file at the asset path under
`%LOCALAPPDATA%\s2x\data\` and `<game>\s2x\`, parses the CSV into a `game::StringTable` and caches it.
The cell hash formula is not guessed: on the first packaged table it sees, it self-checks candidate
formulas (the IW one is `tolower(c) + 31*h`) against real cells and **disables overrides entirely with
a warning** if none match. Adds `dumpstringtable` and `reloadstringtables` commands and a README
section.

**Commits:**

- `8d45c0d` Add loose file string table overrides

## What to test

1. Build and install this branch. Launch MP and reach the frontend.
2. Confirm the hash self-check passed — look for:

   ```text
   [stringtable] cell hash formula '<name>' verified against '<asset>'
   ```

   If instead you see
   `[stringtable] no known cell hash formula matches '<asset>'; loose string table overrides are disabled`
   then the feature is off and nothing below will work — capture that line, it is a blocker.
3. Find the pool and the table name:

   ```text
   listassetpool 59
   listassetpool 59 bot
   ```

   Expect the STRINGTABLE pool index to be **59** and asset names to be lowercase, e.g.
   `mp/botdivisiontable.csv`.
4. Dump a table:

   ```text
   dumpstringtable mp/botDivisionTable.csv
   ```

   Expect:

   ```text
   dumpstringtable: wrote 'mp/botDivisionTable.csv' (11 rows x 7 columns) to '<game>/s2x/dump/mp/botDivisionTable.csv'
   ```

   (11x7 is what was observed for this table.)
5. **Override test.** Copy the dump into a loose folder and edit it:

   ```powershell
   $game = "D:\Program Files\Steam\steamapps\common\Call of Duty WWII"
   New-Item -ItemType Directory -Force "$game\s2x\mp" | Out-Null
   Copy-Item "$game\s2x\dump\mp\botDivisionTable.csv" "$game\s2x\mp\botDivisionTable.csv"
   ```

   Edit `$game\s2x\mp\botDivisionTable.csv` and change the division weapons to something obvious.
   Then in game:

   ```text
   map mp_shipment_s2 dom
   spawnBot 6
   ```

   Expect the load line:

   ```text
   [stringtable] loaded 'mp/botDivisionTable.csv' from '<path>' (11 rows x 7 columns)
   ```

   and the bots to carry the edited weapons. **This "loose bot table in a real match" step is the one
   thing that was never tested.**
6. **Definitive hash test** (proves the cell hash, independent of what the bot table consumer does).
   Create `<game>\s2x\mp\s2x_test.csv` containing:

   ```text
   a,hello
   ```

   and read it from GSC with `tablelookup("mp/s2x_test.csv", 0, "a", 1)` in a test script, printing the
   result. Expect `hello`.
7. **Reload behaviour.** Edit the CSV in place and `map_restart` — the new values must be picked up.
   `reloadstringtables` should print:

   ```text
   [stringtable] cache cleared; loose tables are reloaded on their next lookup
   ```

8. **Revert behaviour.** Delete the loose CSV, `map_restart`, and confirm the stock table is back
   (bots carry stock weapons).

## Regression checks

- **Stock behaviour when no loose file exists** — this is the important one, because the detour runs
  on every `DB_FindXAssetHeader` call. With no loose CSVs present at all, play a normal match and a
  Zombies round and confirm nothing changed and no `[stringtable]` lines appear except the hash
  verification.
- Malformed CSV must fall back to the packaged table, not crash: put a deliberately broken file
  (unbalanced quotes, a 2000-column row) in place and confirm a `[stringtable]` error line and the
  stock table being used.
- Size caps: 8 MiB, 65535 rows, 1024 columns. A too-big file should log
  `[stringtable] '<name>' exceeds N bytes; using the packaged table`.
- Zombies uses string tables heavily (`mp/zombiedlc3mapinfotable.csv` etc.) — one Zombies round with
  no overrides in place is a required check.
- Dedicated server: unaffected in principle, but the detour is global. One dedicated match is a cheap
  sanity check.

## Status so far

Verified: the hash formula (`lowercase * 31`), `dumpstringtable` works, the STRINGTABLE pool is 59,
asset names are lowercase, `mp/botdivisiontable.csv` is 11x7. **Never tested: an actually edited loose
bot table taking effect in a match** (step 5), the GSC `tablelookup` test (step 6), reload/revert
(steps 7–8) and the malformed-file fallback.

## Checklist

- [ ] Hash formula verified line present (not the "disabled" warning)
- [ ] `listassetpool 59` lists tables; names are lowercase
- [ ] `dumpstringtable mp/botDivisionTable.csv` writes 11x7
- [ ] Edited loose bot table changes bot weapons in a real match
- [ ] `mp/s2x_test.csv` + GSC `tablelookup` returns `hello`
- [ ] Edit in place + `map_restart` picks up changes; `reloadstringtables` prints its line
- [ ] Deleting the loose file reverts to stock
- [ ] Malformed / oversized CSV falls back with an error line, no crash
- [ ] Normal MP match and Zombies round unaffected with no overrides present
- [ ] No new errors / no minidump

---

# 6. `feat/22-bot-fill` — issue [#22](https://github.com/Brentdevent/S2x/issues/22)

**What it does:** the Combat Training request. The other half of the issue ("map always loads the hub
gametype") was already fixed upstream by `47e7bca` — `map <map> <gametype>` works. This branch adds a
saved `bot_fill` dvar (0 .. the mode's max players, default 0): on every map start a small state
machine on the server scheduler waits for the local client to be in game (listen servers, up to ~30 s),
waits a 2 s grace (5 s on dedicated) and then spawns `min(bot_fill - current bots, free slots)`. A
level generation counter invalidates stale tasks so `map_restart` doesn't double-spawn. `spawnBot` and
`bot_fill` now share one capped spawn helper, and `party::get_bot_count()` was exported. MP only. A
README "Playing against bots" section documents `map`, `spawnBot` and `bot_fill`.

Explicitly out of scope and stated as such: a Combat Training LUI menu and a `bot_kick` command
(no `SV_DropClient` symbol).

**Commits:**

- `3dd9655` Add bot_fill to spawn bots automatically on map start

## What to test

1. Build and install this branch. Launch MP.
2. Set the dvar and load a map:

   ```text
   bot_fill 6
   map mp_shipment_s2 tdm
   ```

   Expect, a few seconds after the map loads:

   ```text
   bot_fill: spawning 6 bot(s) (0 present, target 6)
   ```

   and 7 players on the scoreboard (you + 6).
3. `map_restart` — expect no double-spawn:

   ```text
   bot_fill: 6/6 bots already present
   ```

4. `spawnBot 3` on top — three more bots, if slots allow. If the match is full, expect:

   ```text
   spawnBot: cannot spawn bots, match player limit reached
   ```

5. `bot_fill 0`, then `map mp_shipment_s2 dom` — no bots spawn and no `bot_fill:` line appears.
6. **Persistence**: `bot_fill 6`, quit the game entirely, relaunch, and confirm `bot_fill` still reads
   6 (it is a saved dvar) and bots spawn on the next `map`.
7. **Clamping**: `bot_fill 99` should clamp to the mode's max players rather than trying to spawn 99;
   confirm the spawn line reports a sane number and the match doesn't break.
8. Play a couple of minutes with bots and confirm **progression still works** (XP is awarded), which
   is what the README claims.

## Regression checks

- `spawnBot N` on its own (the pre-existing command) must behave exactly as before, including in a
  match started without `bot_fill`.
- With `bot_fill 0` (the default) there must be **zero** behaviour change on any map start — this is
  the "stock behaviour when the feature is off" check.
- **Zombies**: `bot_fill` is MP-only (`get_fill_target()` returns 0 unless
  `environment::is_multiplayer()`). Start a Zombies match and confirm no bots and no `bot_fill:`
  lines.
- **Dedicated server**: the state machine has a 5 s dedicated grace path. Start a dedicated MP server
  with `+set bot_fill 4` and confirm bots fill in after the match starts and clients can still join
  (bots count toward the player limit — check the interaction with `party_maxplayers` and
  `fix/40-party-host-slot` if you're testing the merged `integration` build).
- `party.cpp` was refactored to export `get_bot_count()`; confirm the server browser / lobby player
  counts still look right.

## Status so far

Builds; **never runtime tested at all**. Everything above is new work.

## Checklist

- [ ] `bot_fill 6` + `map mp_shipment_s2 tdm` → `bot_fill: spawning 6 bot(s)`, 7 players
- [ ] `map_restart` → `bot_fill: 6/6 bots already present`
- [ ] `spawnBot 3` adds bots / reports the limit correctly
- [ ] `bot_fill 0` → no bots, no lines
- [ ] Value persists across a full game restart
- [ ] `bot_fill 99` clamps sanely
- [ ] XP is awarded in a bot match
- [ ] Zombies: no bots, no `bot_fill` lines
- [ ] Dedicated MP: bots fill and clients can still join
- [ ] No new errors / no minidump

---

# 7. `fix/53-zombies-progression` — issue [#53](https://github.com/Brentdevent/S2x/issues/53)

**What it does:** two dead ends in Zombies progression.

*Groesten Haus* is gated behind the tutorial progression loot item; the loot override deliberately
left that item on stock ownership and the marketplace inventory that would grant it isn't emulated,
so the map could never unlock. New saved bool `cg_unlock_zm_progression` makes the loot and
consumable-quantity hooks treat that item as owned, with an "Unlock Groesten Haus" row in the Zombies
UNLOCKS tab. It is deliberately separate from `cg_unlockall_loot`, which is mostly used for MP
cosmetics and whose carve-out preserved the tutorial gating.

*Tortured Path chapters* are gated by achievement 1112, driven by the `zombies_map_won` reward event,
which the hidden-challenge processor was dropping. The processor now handles the main-quest events
(41 map won, 42 DLC3 survival, 43 Easter egg, 44 red skull), resolves the chapter from the current map
via `mp/zombieDlc3MapInfoTable.csv` (windmill = 1, dnk = 2, dig_02 = 3) instead of guessing from map
names, and records chapter bits, Easter eggs and skull completions into the persisted achievements.
The local player's task 11 events now reach the processor, unmapped events are logged at info level,
and the supplemental unlock writes the three chapter bits instead of `1`. A new
`unlockzmeastereggs confirm` command (and an "Unlock All Easter Eggs" row) marks those main-quest
achievements complete.

**Commits:**

- `18539cc` Track Zombies main quest progression and expose the Groesten Haus unlock
- `af0dbcd` Resolve Tortured Path chapters from the DLC3 map info table

## What to test

**Take a fresh profile backup first** (0.3) — this branch writes to
`players2\user\achievements.json`.

1. Build and install this branch, **including `unlocks.lua`** (the Lua rows live there).
2. Launch `S2x Zombies Dev.lnk`, open the UNLOCKS tab. Three relevant rows must be present:
   - "Unlock All Zombies Loot" (pre-existing)
   - **"Unlock All Easter Eggs"** (GenericButton, opens a confirmation modal, runs
     `unlockzmeastereggs`)
   - **"Unlock Groesten Haus"** (scrollable toggle bound to `cg_unlock_zm_progression`)
   If a row is missing or the grid does not scroll, the installed `unlocks.lua` is stale.
3. **Groesten Haus toggle — never visually verified.** Note whether Groesten Haus is selectable in a
   ZM private match *before* toggling. Then set the toggle on (or type
   `cg_unlock_zm_progression 1`), return to the private match map list, and confirm Groesten Haus is
   now selectable and actually loads. Toggle back off and confirm it locks again.
4. `unlockzmeastereggs` with no argument must refuse and explain:

   ```text
   unlockzmeastereggs: this permanently marks the Zombies main quests (Tortured Path chapters and Easter eggs) as completed and cannot be automatically undone. Run "unlockzmeastereggs confirm" to continue.
   ```

5. `unlockzmeastereggs confirm` in **Zombies** must print:

   ```text
   unlockzmeastereggs: 6 Zombies main quest entries marked as completed. Return to the lobby for the change to apply.
   ```

   and write 6 records to `<game>\players2\user\achievements.json`. If any entry cannot be resolved
   you get a warning line naming how many of how many failed.
6. Run `unlockzmeastereggs confirm` in **Multiplayer** — it must refuse:

   ```text
   unlockzmeastereggs: this command is only available in Zombies.
   ```

7. Return to the lobby and confirm the Easter-egg / main-quest state is reflected in the UI.
8. **Chapter progression logging.** In a Zombies match, the reward-event path now logs. With
   `-demonware_debug`, look for lines of the form:

   ```text
   [reward] <event description>
   [zombies_progression] <event name> on map '<map>' (chapter <n>)
   ```

   and for maps outside the chapter set:

   ```text
   [zombies_progression] map won outside the Tortured Path chapters; nothing recorded
   ```

   Also expect `[hidden_challenges]` lines for group loading and mask changes, e.g.
   `[hidden_challenges] <name>: 0x00 -> 0x01`.
9. **Undo:** delete `<game>\players2\user\achievements.json` (it did not exist before this pass) or
   restore the profile backup.

## Regression checks

- **TTP chapter tracking cannot be tested on this machine.** You own no DLC Zombies maps — only
  `mp_zombie_descent` / `house` / `nest_01` / `training` zones exist, and the chapter maps are
  `mp_zombie_windmill`, `mp_zombie_dnk`, `mp_zombie_dig_02`. The chapter code path can only be
  exercised through the `unlockzmeastereggs` command and the log lines above, not by actually
  finishing a chapter. Say this in the PR rather than claiming it was verified.
- Existing Zombies unlock toggles must be unchanged: `cg_unlockall_loot` on/off behaves as before, and
  with `cg_unlock_zm_progression 0` the tutorial gating is back exactly as stock.
- `unlimited_zombies_consumables` was touched — confirm `cg_unlimited_zm_consumables` still behaves
  (quantities stay topped up) and that with the progression toggle *off* the tutorial item's quantity
  is stock.
- `hidden_challenges.cpp` was substantially rewritten and `bdReward.cpp` touched: play a normal
  Zombies round and confirm ordinary hidden challenges / character challenges still progress, and
  that MP is unaffected (play one MP bot match).
- `stats.cpp` gained the new command only; `setrank`/`setprestige` live on the other branch.

## Status so far

Verified: `unlockzmeastereggs confirm` wrote 6 records to `players2/user/achievements.json`.
Never verified: the Groesten Haus toggle actually making the map selectable (step 3 — the visual
check), the UI rows being present and usable, the MP refusal, and any chapter tracking (impossible
here).

## Checklist

- [ ] Fresh profile backup taken
- [ ] Three UNLOCKS rows present in the Zombies tab
- [ ] Groesten Haus locked before, selectable after toggling `cg_unlock_zm_progression 1`, locked
      again after toggling off
- [ ] `unlockzmeastereggs` without `confirm` refuses with the warning
- [ ] `unlockzmeastereggs confirm` reports 6 entries and writes `achievements.json`
- [ ] `unlockzmeastereggs confirm` refuses in Multiplayer
- [ ] `[zombies_progression]` / `[hidden_challenges]` lines appear during a Zombies match
- [ ] Normal Zombies round: hidden/character challenges still progress
- [ ] `cg_unlockall_loot` and `cg_unlimited_zm_consumables` unchanged
- [ ] One MP bot match unaffected
- [ ] TTP chapter tracking documented as untestable here (no DLC maps)
- [ ] Profile restored / `achievements.json` deleted if you want the original state
- [ ] No new errors / no minidump

---

# 8. `feat/48-rank-prestige` — issue [#48](https://github.com/Brentdevent/S2x/issues/48)

**What it does:** lets you choose your prestige and rank. `setrank <level> [prestige]` and
`setprestige <prestige>` write the prestige and the rank's minimum XP, looked up from
`mp/rankTable.csv` (Multiplayer) or `mp/cp_rankTable.csv` (Zombies), into the player stats using the
existing `set_stat`/`set_ranked_stat` primitives, clamped to the table's caps. (Known table facts: MP
maxrank 54 = level 55, master prestige runs to 999 = level 1000, maxprestige 10; ZM maxrank 44. Rank
rows are keyed by zero-based rank index with column 2 = min XP.) The UNLOCKS tab gains Prestige, Rank
and Rank Step steppers plus an "Apply Prestige and Rank" action with a confirmation modal, seeded from
current stats where the stock player-data bindings expose them; a small `S2xStats` Lua table provides
`GetRankCaps()` and `GetLevelForExperience()`.

**Commits:**

- `f28ff88` Add setrank and setprestige with a rank chooser in the UNLOCKS tab

## What to test

**Take a fresh profile backup first** (0.3). No `setrank` has ever been run on this profile — the
first run is the risky one.

1. Build and install this branch **including `unlocks.lua`**.
2. Launch MP. Confirm the Lua bridge exists:

   ```text
   luidump S2xStats
   ```

   (This needs `chore/dev-diagnostics` or the `integration` build for `luidump`.) Expect the table to
   list `GetRankCaps` and `GetLevelForExperience`.
3. Command usage:

   ```text
   setrank
   ```

   → `Usage: setrank <level> [prestige]`

   ```text
   setprestige
   ```

   → `Usage: setprestige <prestige>`

4. Apply a rank:

   ```text
   setrank 55 3
   ```

   Expect:

   ```text
   setrank: prestige 3, level 55 applied (experience = <xp>). Re-open the Soldier menu to refresh the display.
   ```

   Re-open the Soldier / player-card screen and confirm it shows level 55, prestige 3.
5. `setprestige 5` on its own — expect the level-only variant of the message
   (`setrank: level N applied (...)` shape, with the prestige applied) and the UI to follow.
6. **Persistence**: quit the game entirely, relaunch, and confirm the rank/prestige survived.
7. **Clamping**: `setrank 999 0` and `setrank 1 99` must clamp and warn:

   ```text
   setrank: values were clamped to prestige 0-10 and level 1-55.
   ```

   Master prestige should be the only path to levels above 55 (up to 1000).
8. **UI steppers — never tested.** In the UNLOCKS tab, use the Prestige, Rank and Rank Step rows:
   - Rank Step changes how far one press of Rank moves.
   - Prestige is capped at `maxPrestige`; the display reads `N / 10`.
   - At the final prestige the Rank row must allow the higher cap.
   - "Apply Prestige and Rank" opens a confirmation modal and then runs `setrank <rank> <prestige>` —
     confirm the same console line as step 4 appears and the values take.
   - If the grid does not scroll far enough to show all rows, that is the known
     `OptionsGrid_maxVisibleRows` issue mentioned in the plan — note it.
9. **Zombies path**: launch Zombies, run `setrank 44` and confirm the ZM table (`cp_rankTable.csv`) is
   used and the ZM rank display follows. `setrank 99` in Zombies should clamp to 44.
10. Error paths: run `setrank 10` before stats are loaded (immediately at startup) — expect
    `setrank: player stats are not available.` Run it in a mode that supports neither →
    `setrank: only available in Multiplayer or Zombies.`
11. **Restore your real progression** from the backup when finished, unless you want to keep the
    changed rank.

## Regression checks

- The `unlocks.lua` rows are additive: confirm every pre-existing UNLOCKS row (unlock all items, loot,
  Zombies rows) still works after installing this Lua.
- `stats.cpp` gained commands only; no existing stat write path changed. Play a bot match and confirm
  normal XP still accrues on top of the set rank.
- Zombies and MP use different tables — a wrong lookup would show as a nonsense XP value in the
  console line. Sanity-check the XP number against `mp/rankTable.csv` (dump it with
  `dumpstringtable mp/rankTable.csv` on a build that has `feat/52`).
- Dedicated server: unaffected (the commands need player stats).

## Status so far

Builds; the `S2xStats` Lua table was verified via `luidump S2xStats`. **`setrank`, `setprestige` and
the UI steppers have never been runtime tested** — steps 3–11 are all new.

## Checklist

- [ ] Fresh profile backup taken
- [ ] `luidump S2xStats` lists `GetRankCaps` and `GetLevelForExperience`
- [ ] `setrank` / `setprestige` usage lines
- [ ] `setrank 55 3` applies and the Soldier menu shows it after re-open
- [ ] Survives a full game restart
- [ ] Clamping warns and caps correctly (prestige 0-10, level 1-55, master prestige to 1000)
- [ ] UNLOCKS steppers: Prestige, Rank, Rank Step all move correctly
- [ ] "Apply Prestige and Rank" confirmation modal runs the command
- [ ] Zombies: `setrank 44` uses `cp_rankTable.csv`, clamps at 44
- [ ] Error paths behave (no stats / wrong mode)
- [ ] Pre-existing UNLOCKS rows still work
- [ ] Profile restored (or the new rank deliberately kept)
- [ ] No new errors / no minidump

---

# 9. `feat/39-hq-economy` — issue [#39](https://github.com/Brentdevent/S2x/issues/39)

**Upstream issue:** [#39](https://github.com/Brentdevent/S2x/issues/39) (supply drops / daily
challenges). This started as a "reply only, not feasible" item and grew into 32 commits across four
slices. **It is the only branch that is not finished**, and it should be treated differently from the
others: some features work end to end, some are implemented but unverified, and one (the
Quartermaster) is known to still be broken.

**What it does, in one paragraph:** Headquarters' Orders, contracts, payroll, supply drops and the
vendor/mail kiosks all run over the Achievement Engine JSON protocol (bdReward tasks 4/5 plus the
glutton HTTP endpoint) and the bdMarketplace inventory/balance tasks, all of which stock S2x answers
with empty stubs. This branch adds a shared AE action router, a persistent local economy store
(`players2/user/hq_economy.json`) with atomic writes and replay protection, MP in-process response
injection (the native task must complete *successfully* before the LUI will read the cache — the
original bug was that a structured JSON reply made bdReward task 4 fail), Marketplace
inventory/balance/metadata handlers, supply-drop opening with real loot rolls, payroll settlement from
the native `picked_up_payroll` event, a mail-poll crash guard, and a set of `hq*`/`ae*` console
diagnostics.

**Commits (newest first):**

```text
5a6d86f Make the native conversion counters atomic and widen the harness banner
95c7650 docs: report slice 4 findings and console-first verification steps
3f40910 fix: match recovered conversion response and observe native completion
9ccb818 fix: persist inventory metadata and return task 168 audit result
c70b620 fix: settle native payroll pickups once per period and inspect cleared mail
247b801 feat: add provisional store acknowledgement and hqvendor diagnostics
9187a22 research: preserve slice 4 trace and reconstruct HQ action sequences
384073d Name the new HQ test categories in the harness PASS line
4c55979 Document Slice 3 findings, verification steps and unresolved vendor claims
6d2ab4f Open owned MP supply drops with atomic loot grants and replay receipts
1021eff Make allocated Mail placeholders non-redeemable and bound parsing
da835be Trace native SKU readiness and validate terminal catalog requests
e19ae2f Fix the frontend mail-poll crash by never sending an empty getMessages reply
60a4df5 Restrict the AE task hook to real Achievement Engine tasks
48b9471 Add AE event diagnostics, harden claim replay and document Slice 2 verification gaps
7094370 Frame empty structured vendor and mail replies and trace marketplace requests
fa8954b Advance kill orders and payroll from Reward events with replay-safe claims
be2016b Match native AE filters, status vocabulary and abandon transitions; add weekly offers
f25facd Deliver all native AE tasks through the synchronous response bridge
cc12559 Fill the scheduled-order cache before the native task completes and keep task 4 replies stock
fa22d25 Keep transact() validating the on-disk economy store
826b1f4 Cache the HQ economy store, match failure framing per task and hoist AE symbols
3f1939e docs(hq): report slice 1b delivery and operator verification
bbe9d2d test(hq): repair standalone harness and verify empty reply framing
f85307e fix(hq): return empty SKU pages and structured marketplace acknowledgements
ec53678 feat(hq): inject multiplayer achievement fetch responses in process
c79b7bf docs(hq): map native achievement fetches and response dispatch
f59e47e Tolerate missing or zero AE limits and gate raw HQ protocol dumps
69245b2 docs(hq): report slice one protocol assumptions and verification steps
a723e3e feat(hq): serve marketplace inventory and balances with bounded request parsing
0c62bb3 feat(hq): persist economy transactions atomically and add grant commands
c041381 feat(hq): route Achievement Engine actions through shared handlers
```

Full design notes and per-slice verification steps: `D:\S2x\build\research\hq-economy-slice1-report.md`
(sections Slice 1, 1b, 2, 3, 4, 5), `ae-ghidra-findings.md`, `slice3-*.md`, `slice4-*.md`, `slice5-*.md`.

## 9.0 Ground rules for this section

- **Always launch with `C:\Users\Owen\Desktop\S2x MP Trace.lnk`** (`-demonware_debug`). Without it
  there are no payload dumps and a failure cannot be diagnosed.
- Wait at least **five seconds** in the frontend before typing anything: the catalog copy loop reads
  the string tables on a 5 s cadence.
- **Console first, UI second.** Run the diagnostics before touching any menu, then again after each
  interaction, so the delta is attributable.
- `hqopendrop` is **not** a harmless diagnostic — it consumes an owned supply drop.
- Back up `players2` first (0.3) and know how to reset the store (0.4).
- PID 46420 archived store: currency 2 = 200, payroll finished with receipt `payroll:124254`,
  common-drop quantity 0. Use `hqeconomy` for current state; do not assume that old snapshot is live.

### The diagnostic command set

| Command | What it prints |
|---|---|
| `hqeconomy` / `hqeconomy reload` | the local store: currencies, items, achievements. `reload` re-reads from disk |
| `hqgrant currency <id> <amount>` / `hqgrant item <guid> <qty>` | grants into the local store (dev only) |
| `aeevent <kill\|headshot\|payroll>` | submits one synthetic reward event into the reducer |
| `aefetch <scheduled\|user>` | issues a real native AE fetch and reports the transaction |
| `aecache` | dumps the native scheduled-order cache (controller 0) |
| `hqnative` | raw `Inventory_AreSKUsFetched` flag |
| `hqwallet` | native wallet ready/count, all 13 slots, currency-2 balance from the Lua reader |
| `hqvendor` | wallet, SKU type/count/records, 77 recovered runtime references, conversion counters, inventory and switches |
| `hqmail` | empty-inbox policy, read/redeem/index counters, ready/count/capacity, allocation and first 14 slot IDs/lengths |
| `hqopendrop <common\|rare>` | issues a real native open-supply-drop task (**consumes a drop**) |

### The console-first opening sequence

Run this before any UI action and keep the output:

```text
hqwallet
hqvendor
hqmail
hqeconomy
hqnative
aefetch scheduled
aecache
```

Expected (these are copied from a real run):

```text
[HQ AE] aefetch scheduled -> issued, Tx=ZDq_CgAAAADYfuqUoAEAAA==
[HQ AE injection] native scheduled task SUCCEEDED: 9 cached record(s), ready=1
[HQ AE] scheduled cache controller 0: ready=1, 9 record(s)
  [0] id 10 kind 1 target 10 status 2 requiresClaim 1 usageTimeTarget 0 expires 1789257600 reward 00007FF6E8145F20
  [1] id 11 kind 1 target 3 status 2 requiresClaim 1 usageTimeTarget 0 expires 1789257600 reward ...
  [2] id 5 kind 1 target 3 status 2 requiresClaim 1 usageTimeTarget 0 expires 1789257600 reward ...
  [3] id 29 kind 2 target 100 status 1 ...
  [4] id 25 kind 2 target 25 status 1 ...
  [5] id 30 kind 2 target 10 status 1 ...
  [6] id 35 kind 4 target 1 status 1 usageTimeTarget 3600 ...
  [7] id 33 kind 4 target 1 status 1 usageTimeTarget 3600 ...
  [8] id 34 kind 4 target 1 status 1 usageTimeTarget 3600 ...
```

`ready=1` and a non-zero record count are the pass condition. Nine records = 3 dailies (kind 1,
ids 10/11/5), 3 weeklies (kind 2, ids 29/25/30), 3 contracts (kind 4, ids 33/34/35). `hqeconomy`
prints, for example:

```text
[HQ economy] revision 29: 0 currencies, 4 items, 7 achievements
  item 0x1 collision 0 = 1 (expires 0)
  item 0x400060 collision 0 = 1 (expires 0)
  daily_ch_kills kind 1: inProgress 2/10 activated 1789201074 claimed ''
  payroll_officer kind 5: claimable 1/1 activated 1789204857 claimed ''
```

## 9.1 Orders board — **working**, regression only

Verified working on 2026-09-12: Major Howard shows the daily orders, activation works, `aefetch`
reports the native task succeeding and the cache filling. The root cause was found with Ghidra: the
scheduled handler `0x13EF20` only fills the cache at `0x5C94C60`; whether the LUI reads it is decided
by the bdReward task-4 completion callbacks (`0x13C220` success → ready byte 1, `0x13C120` failure →
0). The old structured JSON reply made the task **fail**, and the deferred injection ran after the
callback. `cc12559` moved injection inside the fetch hooks, synchronously, and returned stock empty
replies for the two hook-handled fetch actions.

**Test:**

1. Run the opening sequence. `aefetch scheduled` → `SUCCEEDED`, `ready=1`, 9 records.
2. Walk to Major Howard **in world** (Play → online Multiplayer → Headquarters). Confirm three daily
   orders are listed with the targets from the cache (kills 10, headshots 3, 1v1 wins 3).
3. Accept one. Re-run `aefetch scheduled` and `aecache`: its status must move to `in_progress`
   (status 2). `hqeconomy` must show it as `inProgress` with a nonzero activation timestamp.
4. Accept a second and a third **without leaving the board**. A previously observed bug was that the
   third only appeared after re-entering — check whether that still happens and note it either way.
5. Abandon one. Expect it back to `available` (status 1) in `aecache` and `inactive` in `hqeconomy`.
   **A previously observed failure: Abandon returned a router error `invalid_achievement`.** If that
   recurs, capture the `hq_injected_ae_request_*` / `hq_injected_ae_response_*` pair and the console
   lines around it.
6. Re-accept the abandoned order — it should be takeable again.
7. Weekly slots: check whether weekly orders now show (they were empty on the earlier build). Accept
   and abandon one.
8. Progress and claim: `aeevent kill` ten times (or get ten real kills with `daily_ch_kills`
   accepted), then `hqeconomy` — the record must be `claimable 10/10`. Claim it at Howard, then
   `hqeconomy` again: exactly one reward credit and status `finished`. Re-open and re-claim: **no**
   second credit.
9. Also check the menu route: Play → HQ → Orders equivalent, and confirm `[HQ AE injection]` lines
   appear for both entry points.

**Regression:** this is the part that already works, so the goal is only to prove nothing else in the
branch broke it. Also confirm the group-0 task-table guard still rejects non-AE tasks — the benign
line `[HQ AE injection] task type 0xA0 rejected: not an entry of the group 0 task table` is expected
and is not an error.

## 9.2 Supply Drops — **working**, regression only

Verified end to end on 2026-09-12 (Owen's traced walk): the native reveal plays and three items are
granted. Implementation: common = item GUID `1` / `sd_mp`, rare = GUID `2` / `sd_mp_rare`; three
uniform rolls (with replacement) over deduplicated member GUIDs from `mp/itemscollections.csv`
restricted to IDs in `mp/collections.csv`; atomic debit + grant with a persisted replay receipt.

**Test:**

1. Grant stock and restart so the native inventory fetch (Marketplace 165) picks it up:

   ```text
   hqgrant item 1 2
   hqgrant item 2 1
   hqeconomy
   ```

   Then quit and relaunch. `hqeconomy` should show `item 0x1 ... = 2` and `item 0x2 ... = 1`.
2. Open the Supply Drops shortcut in HQ and open one common drop. Require: three reveal cards, one
   drop consumed, new items in `hqeconomy`, and persistence after another restart.
3. Native-issuer test (bypasses the UI enablement):

   ```text
   hqopendrop common
   ```

   Expect:

   ```text
   [HQ native] open drop issued, Tx=<24-char base64>
   [HQ economy] revision N: 0 currencies, 4 items, 7 achievements
   ```

   with three new loot GUIDs (a real run produced `0x400060`, `0x24001DE`, `0x701E015`).
4. Note the known follow-up: right after a drop opens you will see

   ```text
   [DW] bdMarketplace: missing task '168'
   ```

   in older builds. Slice 4 (`9ccb818`) implements task 168 (`putInventoryItemsData`) with a
   one-result audit reply; the `8fb25af` self-test (pid 17124) confirmed task 168 is now served (no
   missing-task line) at the console-diagnostic level. Confirm it stays gone in your own UI walk, and
   check `hqvendor`'s `dirtyMetadata` drains to 0 after the write.
5. Restart and confirm quantities are right and "new item" flags stay cleared.

## 9.3 Payroll — **+200 persisted; slice 5 native visibility/UI awaiting walk**

The traced owner walk on integration `8fb25af` (PID 46420) proves currency 2 = 200 and
`payroll_officer` finished, receipt `payroll:124254` for timestamp `1789259964000000`.
The first pickup showed an error; a revisit showed claimed/countdown, but no visible credits.
Only the frontend Marketplace 132 balance fetch occurred; no refresh or AE claim followed pickup.
Slice 5 adds `hqwallet`, main-thread absolute balance updates and a native achievement completion
push after a new persisted settlement. The missing push causing the error is an inference; no
visible kiosk error text was captured. Currency 2 / 200 / UTC four-hour buckets are local policy.

**Test:**

1. Run `hqwallet`, `hqvendor`, `hqmail`, `hqeconomy`; record native and stored currency 2.
2. In a fresh UTC four-hour bucket without a receipt, pick up once. Require +200 once, the native
   balance matching the store/top-right counter, and a claimed kiosk/countdown without an error.
3. Expect `hq_payroll_native_push_*` and `[HQ payroll] delivered persisted completion push`.
   Repeated Reward 12 batches must not grant or animate a second reward.
4. Revisit and restart in the same period; balance must persist and remain visible.
5. Existing receipts cannot pay again. Do not delete receipts to manufacture a passing result.
6. Record the exact visible error separately if it persists. The harness does not prove the kiosk.
7. `aeevent payroll` uses the older synthetic path and is not a native-pickup test.

## 9.4 Quartermaster — **still grey/flickering on slice 4; slice 5 catalog experiment**

The owner re-walked integration `8fb25af` with tracing (PID 46420): the main-menu entry was grey
and the in-world vendor flickered/closed. Both conversion callbacks succeeded with SKU/inventory
ready and switches correct. These are current observations, not just the earlier slice 3 walk.
The actual Lua enable expression remains unresolved. Slice 5 enumerates 113 matching binding pairs,
prints 77 recovered runtime references, and supplies one filtered type-100 `sd_mp` display SKU at
200 currency 2. Native and direct purchases are rejected with no grant/debit. Type 150 remains empty.
The nonempty catalog is a hypothesis to test; it is not a verified Quartermaster fix or retail store.

**Test:**

1. Run the opening sequence. Expect from `hqvendor`:

   ```text
   [HQ vendor] Engine.Inventory_AreSKUsFetched=1; 242 requests=N replies=N rejected=0 (conversion rule)
   [HQ vendor] allow_hub_vendor_menu=1
   [HQ vendor] inventoryReady=1 inventoryCount=N dirtyMetadata=0
   [HQ vendor] conversion successes=N failures=0 responseTx=... scalar=... currencyCount=0 inventoryCount=0 extraCount=0
   [HQ vendor] entitlement fetched flag and final LUI enable expression unresolved
   ```

   The three vendor/payroll killswitches must read `0` and `allow_hub_vendor_menu` must read `1`.
2. **Menu route:** Play → HQ → Quartermaster. Then `hqvendor` again. Record: was the entry grey? Did
   a new 242 request occur (counter delta)? Did the conversion callback succeed?
   `[HQ vendor] conversion-rule native success callback` is the line to look for.
3. **World route:** enter Headquarters, `hqvendor`, walk to the vendor once, `hqvendor` again. Record
   the visible flicker/error and the request-counter delta **separately** from the 242 that the world
   load itself issues. Note: `Unloading zone mp_hub_allies_slim_load` after the attempt is normal
   load-zone cleanup, **not** proof the vendor caused the unload.
4. Interpretation: **a successful conversion with a grey button isolates the remaining Lua gate** —
   that is a useful result, not a failure. If the conversion *fails*, that is a protocol problem and
   the reply needs comparing against the reader at `A4C850`.
5. Capture in either case: the complete console slice, the PID-scoped
   `s2x\dump\dw\hq_marketplace_242_*` request and response dumps.

6. In the type-100 catalog expect `nonzeroSKUs=1`, SKU ID 1 and one price. Keep `111_sku` dumps.
   Compare before/after each interaction; type 150 may legitimately have zero records. A purchase
   must be unavailable and leave wallet/inventory unchanged. If it still greys/closes with a nonzero
   catalog and healthy flags, the next target is the actual menu Lua/onboarding gate.

## 9.5 Mail — **slice 5 empty-inbox policy; kiosk verification pending**

The owner still saw claim errors on integration `8fb25af` (PID 46420), but only MarketingComms 6
was captured; there was no redemption request or manual `hqmail` output. Slice 5 confirms the
14 allocated ID-zero messages are valid. It also found that an unknown category maps one past the
valid slots, which native message/redeem readers fail to bounds-check; use during the owner's click
is unproved. MP now returns no message from the native accessor, reports no unread mail and suppresses
stale redemptions. The wire allocation remains at least 14 entries. Reads/redeems log category/index
and bounds; native fetch success logs count/capacity. Zombies behavior is unchanged.

**Test:**

1. `hqmail` before opening Mail. Expect empty-inbox policy, native count >= 14, and:

   ```text
   [HQ mail native] ready=1 slots=<pointer>; first 14 advertised slots
   [HQ mail native] slot 0 id=0 contentLength=0 codeLength=0
   ... (14 slots, all id=0)
   ```

   A null `slots` pointer with `ready=1` is exactly the crash condition the guard protects against.
2. Open Mail (Play → HQ → Mail, and the in-world kiosk). Expect in the log:

   ```text
   [HQ mail] getMessages: 14 non-claimable slot(s) for 14 advertised slot(s)
   ```

3. Require: no crash, no minidump, an empty visible inbox, and **no claimable message**.
4. If a claim button is still shown for a cleared slot: record its title, category and index, and run
   `hqmail` again. Compare read/redeem counters and category/index logs. No counter change means
   the control uses a path outside these MarketingComms accessors; that Lua path is the next target.
5. Keep `s2x\dump\dw\marketing_6_response*` and any `marketing_4` / redemption dumps.
6. Soak test for the crash fix: stay in the frontend and the hub for 90 seconds without touching Mail
   and confirm no crash (this is how `e19ae2f` was verified).

## 9.6 What to capture when something fails

Every failure report needs all four:

1. **Relaunch with the trace shortcut** if you were not already using it
   (`C:\Users\Owen\Desktop\S2x MP Trace.lnk`).
2. The **console.log slice** from launch to the failure (`Get-Content $log | Select-Object -Skip N`).
   Include the `[HQ ...]`, `[DW]`, `[DW-trace]` and `Unloading zone` lines — the ordering matters.
3. The **dump folder** `<game>\s2x\dump\dw\` — specifically the PID-scoped files:
   `hq_injected_ae_request_<pid>_<n>.bin`, `hq_injected_ae_response_<pid>_<n>.bin`,
   `hq_reward_request_<pid>_<n>.bin`, `hq_marketplace_242_*`, `bdMarketplace_<task>_*.bin`.
   Match request to response by **ClientTx**, not by adjacent sequence numbers.
4. Any new zip in `<game>\minidumps\`.

Decode the dumps with:

```powershell
python D:\S2x\build\research\decode_dw.py --summary "D:\Program Files\Steam\steamapps\common\Call of Duty WWII\s2x\dump\dw"
```

## 9.7 Regression checks for the whole branch

- **Zombies is the big one.** The AE transport, the achievement response bridge, the MarketingComms
  reply branch and the task-168 fallback all have separate Zombies paths that were deliberately
  preserved, and **no game-level Zombies test has been run on any slice**. Launch Zombies with a
  profile that has persisted achievements, do the lobby achievement/refresh check, play a round, and
  confirm no `[HQ AE injection]` messages appear at all (the injection component is MP,
  non-dedicated only).
- **Dedicated servers** must never install the injection component. Start a dedicated MP instance and
  confirm no `[HQ ...]` lines in its log.
- **Frontend and hub stability**: 90 s soak in the frontend and 90 s in the hub, no crash, no
  minidump.
- **Store integrity**: delete `hq_economy.json`, restart, confirm the game starts with an empty store
  and nothing errors; then `hqgrant item 1 1` and confirm the file is recreated correctly.
- **Corrupt store**: truncate the JSON deliberately and confirm the game preserves the original and
  rejects writes rather than crashing (this is covered by the standalone harness but not in game).
- MP progression, XP and normal challenges must be unaffected — play one bot match.

## 9.8 Optional: run the standalone harness

The branch ships a standalone test project that compiles the *production* store, router, serializers
and marketplace core. It does not touch the game.

```powershell
& 'C:/Program Files/Microsoft Visual Studio/2022/Community/MSBuild/Current/Bin/MSBuild.exe' build/research/hq-tests/hq-tests.vcxproj -m -v:minimal -nologo -p:Configuration=Release -p:Platform=x64
Push-Location build/research/hq-tests
./bin/hq-tests.exe
Pop-Location
```

Expect a final line beginning `PASS: store, atomic failure, lock, rotation, activation, claim/replay`
and naming the newer categories. This proves the local logic, **not** anything about the game.

## Status so far

| Feature | State |
|---|---|
| Orders board (daily) | **works** — verified in world and via `aefetch`/`aecache` |
| Orders: third accept without re-entering | previously flaky — re-check |
| Orders: Abandon | **works in the latest owner walk**; regression check on slice 5 |
| Weekly orders | offered by the router; previously showed empty in the UI — re-check |
| Supply Drops | **works** end to end — native reveal, 3 items, drop consumed |
| Payroll | **+200 persisted in PID 46420**, receipt `payroll:124254`; slice 5 wallet/push implemented, visible success awaiting walk |
| Quartermaster | **grey/flickers on integration `8fb25af`, PID 46420** despite native conversion success; slice 5 nonempty catalog experiment unverified |
| Mail | **claim errors on integration `8fb25af`, PID 46420**; slice 5 native empty-inbox policy and bounds diagnostics implemented, kiosk verification pending |
| Task 168 metadata | served during traced PID 46420; retain metadata/persistence regression checks |
| Zombies regression | **never tested at game level on any slice** |

## Checklist

- [ ] Profile + `hq_economy.json` backed up
- [ ] Launched with `S2x MP Trace.lnk`, 5 s wait, opening sequence captured
- [ ] Orders: 3 dailies listed, accept x3 without re-entering, abandon, re-accept
- [ ] Orders: weekly slots checked
- [ ] Orders: `aeevent kill` x10 → claimable → claim credits once, no duplicate
- [ ] Supply Drops: shortcut opens a drop, 3 items, drop consumed, persists
- [ ] Supply Drops: `hqopendrop common` issues and grants
- [ ] `[DW] bdMarketplace: missing task '168'` no longer appears; `dirtyMetadata` drains
- [ ] Payroll: one pickup grants +200 currency 2 once; repeats do not
- [ ] Payroll: `hqwallet` agrees with `hqeconomy` and top-right counter; no first-pickup error; persists across restart
- [ ] Quartermaster: `hqvendor` before/after from both entry points, counters recorded
- [ ] Quartermaster: SKU count/type, conversion callbacks, 111 and 242 dumps kept; purchases rejected without mutation
- [ ] Mail: `hqmail` shows 14 id=0 slots, kiosk opens, no crash, no claimable message
- [ ] Mail: any remaining claim button documented (title/category/index)
- [ ] 90 s frontend + hub soak, no crash, no minidump
- [ ] Zombies: achievements/lobby refresh OK, round played, no `[HQ AE injection]` lines
- [ ] Dedicated MP: no `[HQ ...]` lines
- [ ] Store delete/recreate works; corrupt store does not crash
- [ ] MP bot match: XP and challenges unaffected
- [ ] Standalone harness PASS (optional)

---

# Not fixed (reply only)

Draft reply text lives in **`D:\S2x\build\research\github-replies.md`**. Review it, then post it on
the issues. Gist:

**[#23](https://github.com/Brentdevent/S2x/issues/23) — bots in offline Zombies.** WWII's bots are
Multiplayer test clients driven by MP bot GSC/engine logic; the Zombies maps have navmeshes but no bot
AI that could use them, so "3 bots in offline Zombies" would need a complete bot AI written in GSC.
Not planned; `bot_fill`/`spawnBot` stay MP-only. Suggest closing as "not planned" or long-term.

**[#39](https://github.com/Brentdevent/S2x/issues/39) — supply drops & daily challenges.** The draft
in the file is the *old* status ("work in progress, first slice targets Orders and payroll"). **It is
now out of date** — Orders and Supply Drops actually work and there is a branch with 32 commits. Rewrite
the reply before posting, using the status table in section 9. This one is not a reply-only issue any
more; it is a draft-PR candidate.

**[#12](https://github.com/Brentdevent/S2x/issues/12) — campaign modding.** GSC and LUI overrides
already work in campaign: `<game>\s2x\scripts\sp\` (and `scripts\sp\<mapname>\`) and
`<game>\s2x\ui_scripts\sp\<folder>\__init__.lua`. String tables can now be overridden too
(`<game>\s2x\<asset path>.csv`, see the README section added by `feat/52`) — so the reply should be
posted **after** #52 is merged, or it should say "in an open PR". Texture/model swaps are not
supported: no loose-asset loader or fastfile tooling.

**[#22](https://github.com/Brentdevent/S2x/issues/22)** also has a reply drafted for the "map loads
hub gametype" half, which upstream `47e7bca` already fixed — post it with the `feat/22-bot-fill` PR.

**Checklist**

- [ ] #23 reply reviewed and posted
- [ ] #39 reply **rewritten** to match the real state, then posted
- [ ] #12 reply posted (after or alongside the #52 PR)
- [ ] #22 comment posted with the PR

---

# Upstream contribution order and PR notes

**Rule: nothing is opened upstream until that branch's section in this runbook is fully ticked.**
Open them one at a time, in this order, and wait for feedback on the first one or two before pushing
the rest — as a first-time contributor you'll learn the maintainer's preferences from #44 and can
apply them to the others.

Each PR: base `Brentdevent/S2x:master`, head `ChronoRixun/S2x:<branch>`, title = the commit subject,
and reference the issue in the body. Before opening, rebase onto the latest upstream master if it has
moved:

```bash
git fetch upstream
git rebase upstream/master <branch>
git push --force-with-lease origin <branch>
```

### 1. `fix/44-rotation-settings` → #44

```text
Fixes #44.

Problem: on a dedicated server the admin's gameplay settings (scr_<gametype>_scorelimit and friends)
were lost after every map_rotate. prepare_match_settings() execs default_xboxlive.cfg on each rotation
and only replayed the +exec launch file; +set values and console-typed values were never replayed, and
Zombies replayed nothing. Re-exec'ing a cfg that ends in map_rotate also loops.

Fix: a dedicated-only settings ledger records every admin dvar write (from +set, from the exec'd
config and configs it execs, and from the server console) and re-applies it synchronously in
G_InitGame before the GSC reads it, plus once at lobby time. Lifecycle keys are denylisted. As a side
effect +set now works on dedicated servers, which the engine otherwise ignores under S2x.

How tested: local dedicated server with a three-gametype rotation; a cfg value (111), a +set value
(55) and a console-typed value (250) all survived repeated rotations, with the live limits logged at
each match start; verified from a connecting client; Zombies dedicated checked separately.
```

### 2. `fix/40-party-host-slot` → #40

```text
Fixes #40.

Problem: the dedicated frontend owner is party member 0 but never a player, so setting the native
party/session capacity to party_maxplayers meant N really allowed host + N-1 remote players (3 of 4 in
Zombies) and the last joiner was rejected by the engine's party-full check.

Fix: native party/session capacity is now party_maxplayers + 1, while sv_maxclients and every
advertised/compared value stay at N. The int dvar helper widens the registered domain first so the
engine's clamp cannot silently drop the value, and one info line reports the applied capacity.

How tested: dedicated Zombies and MP servers at party_maxplayers 1 and 2 — the client now joins, the
browser shows the right count and Full state, and one more client than the limit is still rejected.
```

### 3. `feat/52-stringtable-override` → #52

```text
Closes #52.

Problem: there was no way to override a string table; only GSC and LUI loose files were supported.

Fix: DB_FindXAssetHeader is detoured for ASSET_TYPE_STRINGTABLE only and looks for a loose .csv at the
asset path in the existing loose-file folders. The cell hash formula is self-checked against a real
packaged table on first use and overrides are disabled with a warning if no candidate matches. Adds
dumpstringtable and reloadstringtables plus a README section.

How tested: hash formula verified in game; dumped mp/botDivisionTable.csv, edited it loose and
confirmed bots carried the edited weapons in a match; a custom mp/s2x_test.csv read back through GSC
tablelookup; edit-in-place + map_restart reloads, deleting the file reverts to stock; malformed and
oversized files fall back to the packaged table.
```

### 4. `feat/22-bot-fill` → #22

```text
Closes #22 (the remaining half; the "map loads the hub gametype" part was fixed by 47e7bca).

Problem: bots had to be added by hand with spawnBot after every map load, which makes an offline
Combat Training-style match tedious.

Fix: a saved bot_fill dvar (0..max players) tops the match up to that many bots on every map start,
once the server is ticking and the local client is in game. spawnBot and bot_fill share one capped
spawn helper so neither can exceed the free slots. MP only; README section added.

How tested: bot_fill 6 + map mp_shipment_s2 tdm spawns 6 bots; map_restart reports them already
present instead of doubling; spawnBot still works on top; bot_fill 0 restores stock behaviour; the
value persists across restarts; Zombies is unaffected.
```

### 5. `fix/53-zombies-progression` → #53

```text
Addresses #53.

Problem: Groesten Haus is gated by the Zombies tutorial progression loot item, which the loot override
deliberately left on stock ownership and which the unemulated marketplace inventory can never grant.
Separately, Tortured Path chapter progression is driven by the zombies_map_won reward event, which the
hidden-challenge processor dropped.

Fix: a saved cg_unlock_zm_progression toggle (with an UNLOCKS row) treats the tutorial item as owned;
the reward-event processor now handles the main-quest events, resolves the chapter from
mp/zombieDlc3MapInfoTable.csv instead of guessing from map names, and records chapter bits, Easter
eggs and the red skull into the persisted achievements. Adds unlockzmeastereggs.

How tested: unlockzmeastereggs confirm writes the expected records; the Groesten Haus toggle makes the
map selectable and locks it again when turned off. Tortured Path chapter completion could not be
tested — I own none of the DLC Zombies maps, so only the table lookup and the recording path are
covered.
```

*(Be explicit about the untested part — it is better to say it than to have a maintainer find it.)*

### 6. `feat/48-rank-prestige` → #48

```text
Closes #48.

Problem: there was no way to pick a rank or prestige.

Fix: setrank <level> [prestige] and setprestige <prestige> write the prestige and the rank's minimum
XP from mp/rankTable.csv (MP) or mp/cp_rankTable.csv (Zombies) through the existing stat primitives,
clamped to the table caps. The UNLOCKS tab gains Prestige / Rank / Rank Step steppers and an Apply
action with a confirmation modal, backed by a small S2xStats Lua bridge.

How tested: setrank 55 3 applied and displayed correctly after re-opening the Soldier menu and
persisted across a restart; clamping warns at the caps; the Zombies table path checked separately; the
UI steppers and Apply action drive the same command.
```

### 7. Diagnostics and logging — one or two small PRs

Suggested split, because they have different audiences:

- **PR A — `chore/search-path-logging`** (tiny, uncontroversial): "Log the resolved AppData path and
  the ordered loose-file search paths at startup, and say so once when no ui_scripts directory is
  found in any of them. Diagnosing a silently unloaded ui_scripts folder currently requires a
  debugger. No behaviour change."
- **PR B — `chore/dev-diagnostics`**: "Release builds compile out console::debug, so the existing
  progression and Demonware diagnostics are invisible. Adds luidump (enumerate a LUI global table),
  cg_unlock_debug counters, one-line [DW-trace] logging plus payload files for stubbed Demonware
  tasks, unhandled-action logging in the glutton server, and fixes a console crash on long trace lines
  (_vsnprintf_s now uses _TRUNCATE). No behaviour change when the commands and dvar are unused."

  If the maintainer pushes back on scope, the `findstrings` / `dumpcode` image-scanning commands
  (`1b8d131`, `073a608`, `d4c150c`) are the obvious part to drop or split into a PR C — they are
  reverse-engineering tools, not general dev diagnostics.

### 8. `feat/39-hq-economy` → #39, **last, as a draft PR**

Open it as a **draft** and say plainly what works and what does not. Do not open it until the branch
is pushed, sections 9.1–9.8 are ticked as far as they can be, and #52 is at least open (the loot roll
depends on string tables conceptually, though not in code).

```text
Draft — addresses #39. Not ready to merge; opening early for direction.

Problem: Headquarters' Orders, contracts, payroll, supply drops, the Quartermaster and Mail all run
over the Achievement Engine JSON protocol (bdReward tasks 4/5 and the glutton HTTP endpoint) plus the
bdMarketplace inventory/balance tasks, all of which S2x answers with empty stubs.

Fix so far: a shared AE action router, a persistent local economy store with atomic writes and replay
protection, in-process response injection for MP fetches (the native task must complete successfully
before the LUI reads its cache), Marketplace inventory/balance/metadata handlers, supply-drop opening
with atomic loot grants, payroll settlement from the native picked_up_payroll event, a fix for a
frontend crash in the unread-mail poll, and console diagnostics.

Working in game: the Orders board (daily/weekly/contract offers, accept/abandon/claim) and Supply
Drops (native reveal, three items, drop consumed). Not working: the Quartermaster menu still greys or
closes — the network side succeeds, the remaining gate is a LUI enable expression I have not located.
Payroll settles in the store but the kiosk UI path is unverified. Mail opens without crashing but a
cleared slot still offers a claim. Reward amounts, the currency ID and the payroll schedule are local
policy, not recovered retail values, and are called out as such in the code and notes.

Happy to split this into smaller PRs (store, AE router, supply drops, diagnostics) if that is easier
to review.
```

### PR checklist

- [ ] All branches rebased on current `upstream/master` and force-pushed to the fork
- [ ] #44 PR opened, section 3 fully ticked
- [ ] #40 PR opened, section 4 fully ticked
- [ ] #52 PR opened, section 5 fully ticked
- [ ] #22 PR opened, section 6 fully ticked
- [ ] #53 PR opened, section 7 fully ticked (with the DLC caveat stated)
- [ ] #48 PR opened, section 8 fully ticked
- [ ] Diagnostics PR(s) opened, sections 1 and 2 fully ticked
- [ ] #39 draft PR opened, section 9 as complete as it can be
- [ ] Reply-only comments posted on #23, #12 (and the rewritten #39 comment)
- [ ] #49: comment that it was investigated but not started, or leave it

---

# Known gaps and open questions

## Never tested (carried over from the handoff)

- `feat/22-bot-fill`: no runtime test of any kind.
- `feat/48-rank-prestige`: `setrank` / `setprestige` and every UI stepper.
- `fix/40-party-host-slot`: the client-join test, which is the whole issue.
- `feat/52-stringtable-override`: a loose bot table actually taking effect in a match.
- `fix/53-zombies-progression`: the Groesten Haus toggle visually; TTP chapters cannot be tested at
  all here (no DLC Zombies maps installed — only `mp_zombie_descent`, `house`, `nest_01`, `training`).
- `fix/49-local-play-unlocks`: never started; branch does not exist.
- HQ economy: the Quartermaster Lua gate, the Mail claim path, the payroll kiosk UI, task 168 in game,
  and **any** Zombies game-level regression test across all four slices.

## ASK OWEN — things I could not determine from the sources

- **ASK OWEN:** What are the exact upstream issue titles and current status (open/closed, any
  maintainer replies since 2026-09-11)? The plan file summarises them but I have not read GitHub. If
  #44 or #40 has been fixed upstream in the meantime, the PRs need rebasing or dropping.
- **ASK OWEN:** Is `D:\S2x\build\backups\S2x Zombies Dev.lnk` still valid, and do you want a copy on
  the Desktop next to the other two? Only the two MP shortcuts are on the Desktop.
- **ASK OWEN:** For the #44 Zombies dedicated test — which gametype/limit dvar do you want to prove?
  The MP test uses `scr_dom_scorelimit`; the Zombies equivalent was never named in the plan or the
  handoff, so step 9 of section 3 is deliberately vague.
- **ASK OWEN:** The `bot_fill` × `party_maxplayers` interaction on a dedicated server (do bots occupy
  slots that the party capacity fix now accounts for?) was never reasoned about. Worth one deliberate
  test on the `integration` build.
- **ASK OWEN:** Whether `%LOCALAPPDATA%\s2x` should be created for testing. It does not exist on this
  machine, which means the AppData half of the search-path and stringtable-override features has never
  been exercised. Creating `%LOCALAPPDATA%\s2x\data\mp\` would let you test the higher-priority path.
- **ASK OWEN:** Is the untracked `D:\S2x\run-47992\` directory at the repo root wanted? It has been
  deliberately left alone by every agent. It should probably be moved under `build/research/` or
  deleted before any PR, so it cannot be committed by accident.
- **ASK OWEN:** The GSC test for `feat/52` step 6 (a script calling `tablelookup("mp/s2x_test.csv", ...)`)
  needs a script file written to `<game>\s2x\scripts\mp\`. No such test script exists yet and the plan
  did not give one — do you want it written, or is the bot-table test enough for you?
- **ASK OWEN:** Currency 2 in the HQ economy is a *candidate* Armory Credits ID, never proven. If you
  ever see a UI currency change by exactly the granted amount, note it — that would settle the
  mapping.

## Unresolved technical questions (documented, not blocking the other PRs)

- The Quartermaster's main-menu LUI enable expression and any entitlement/onboarding readiness input.
- Why a cleared (ID zero) Mail slot still offers a claim interaction.
- The payroll wallet / UI notification path when persistence succeeds but the kiosk errors.
- **Resolved at the console-diagnostic level, unconfirmed in the UI:** the recovered task-242
  conversion reply is accepted by the native callback — the `8fb25af` self-test (pid 17124) showed
  `[HQ vendor] conversion-rule native success callback` firing. What's still open is whether that
  translates into a working Quartermaster menu/vendor for Owen (see section 9.4).
- Ghidra chain for task 242 if it needs more work:
  `11CD4551 <- A41A99 <- 20C55F <- 11A28228 <- A41A70`, external block `11FDE456`. Do not install
  hooks at external trampoline offsets.

## Push and build state at the time of writing

- All ten existing branches, including `feat/39-hq-economy` (`5a6d86f`) and `integration` (`8fb25af`),
  are pushed to `origin` — confirmed against `origin/feat/39-hq-economy` and `origin/integration` as
  of 2026-09-12 20:55 (HANDOFF item 3h). An earlier draft of this runbook read the repo mid-build and
  reported both as behind; that was stale even at the time and has been corrected throughout.
- The installed `s2x.exe` is `integration` at `8fb25af`, i.e. **with** the HQ economy slice 4 commits
  (built and installed at 20:55 on 2026-09-12). No rebuild/reinstall is required before testing,
  though one is harmless if you want a from-scratch confirmation.
- What has **not** happened yet, on this installed `8fb25af` build: Owen's in-world/menu walk of the
  Quartermaster and Mail, and a real in-world payroll pickup. The only testing done on `8fb25af` so far
  is the automated self-test (pid 17124) at the console-diagnostic level — see sections 9.3-9.5.
