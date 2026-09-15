<img width="1200" height="350" alt="s2x-readme-banner" src="https://github.com/user-attachments/assets/733e21a4-2703-4ba7-ab07-151b0f17e94a" />

# S2x ⭐ — ChronoRixun's fork

This is a fork of [Brentdevent/S2x](https://github.com/Brentdevent/S2x), the custom client for **Call of Duty®: WWII**. It carries a set of fixes and features on top of upstream `master`, each on its own branch so it can be offered upstream as a pull request, and an `integration` branch where all of them are merged, built and tested together. If you want everything at once, build `integration`.

> [!NOTE]
> Everything here is offered to the upstream project. The first pull request, [#61](https://github.com/Brentdevent/S2x/pull/61), is open; the rest follow one at a time. Until they land, this fork is the place to get them.

> [!WARNING]
> S2x is actively being developed and is not feature-complete. Expect bugs, crashes, missing features, and general instability. Dedicated servers, modding support, online functionality, and further gameplay stability are still in development.

S2x is a custom client project for Call of Duty®: WWII, focused on preserving and extending functionality for campaign, multiplayer, and zombies. Join the S2x community on [Discord](https://discord.gg/wdC8Jpc2cC). The project is inspired by the work of the former XLabs community, but S2x is an independent project and is not affiliated with XLabs, Activision, Sledgehammer Games, Microsoft, or any related publisher, developer, or trademark holder.

## What this fork adds

| Branch | What it does | Upstream |
|---|---|---|
| `fix/44-rotation-settings` | Admin gameplay settings survive dedicated map rotations | [#44](https://github.com/Brentdevent/S2x/issues/44), PR [#61](https://github.com/Brentdevent/S2x/pull/61) |
| `fix/dedicated-lobby-null-clients` | Fixes a dedicated-server crash in the lobby party walk | crash found while testing #44 |
| `feat/22-bot-fill` | `bot_fill`: bots added automatically on every map start, on clients and dedicated servers | [#22](https://github.com/Brentdevent/S2x/issues/22) |
| `feat/52-stringtable-override` | Loose `.csv` string-table overrides, `dumpstringtable`, `reloadstringtables` | [#52](https://github.com/Brentdevent/S2x/issues/52) |
| `feat/48-rank-prestige` | `setrank` / `setprestige` and a Prestige and Rank chooser in the UNLOCKS tab | [#48](https://github.com/Brentdevent/S2x/issues/48) |
| `fix/53-zombies-progression` | Groesten Haus unlock, Tortured Path chapter tracking, `unlockzmeastereggs` | [#53](https://github.com/Brentdevent/S2x/issues/53) |
| `chore/search-path-logging` | The loose-file search paths printed once at startup, without user names | housekeeping |
| `chore/dev-diagnostics` | Opt-in developer diagnostics: `luidump`, Demonware traces, `findstrings`, `dumpcode` | housekeeping |
| `fix/scheduler-drop-throwing-tasks` | A scheduled task that throws is contained and dropped instead of taking the game down | found during the #39 review, PR to follow |
| `feat/39-hq-economy` | Headquarters economy: Orders, contracts, payroll, supply drops, Quartermaster, Mail | [#39](https://github.com/Brentdevent/S2x/issues/39), PR to follow the smaller ones |

### Dedicated server settings that stick

On upstream, `scr_dom_scorelimit` and friends set from the command line or `server.cfg` lasted exactly one map: the next rotation put every gametype back to its defaults. This fork keeps a ledger of every setting a server admin writes, from `+set`, from any config it executes (nested `exec` included) and from the server console, and restores them when the engine resets them at each map change. Values are recorded when the engine actually executes them, so ordering is exactly what the admin wrote; passwords and tokens are redacted in the log; `dedicatedSettings list` shows what is tracked.

### Bots that fill the match

```text
bot_fill 6
map mp_shipment_s2 war
```

`bot_fill` is saved with your profile and works on dedicated servers too (`+set bot_fill 17`). The value is clamped to the player limit, and a listen host no longer gives up waiting for the level to be ready.

### Loose string tables

Drop a `.csv` at the asset path under `%LOCALAPPDATA%\s2x\data\` or `<game folder>\s2x\` (for example `mp/botDivisionTable.csv`) and the game loads it instead of the packaged one. `dumpstringtable mp/botDivisionTable.csv` exports the packaged table to edit, `listassetpool 59 <filter>` lists table names and `reloadstringtables` drops the cache. Tables are parsed RFC 4180 style; a file over 8 MiB, with more than 65,535 rows or 1,024 columns, or that pads to more than 1,048,576 cells is reported and the packaged table is used instead.

### Rank and prestige

`setrank <level> [prestige]` and `setprestige <prestige>` write the prestige and the rank's minimum XP from the game's own rank tables, in Multiplayer and in Zombies. The UNLOCKS tab of the Soldier menu gains a Prestige and Rank group with steppers and an Apply action behind a confirmation. The stats are written the same way `unlockstatsmp` writes them; the engine uploads them a few seconds later or at the next map load, so load any map before quitting if you want the rank to stick.

### Zombies progression

A saved `cg_unlock_zm_progression` toggle (also an UNLOCKS row) makes the tutorial map Groesten Haus available. Tortured Path chapters, the DLC3 survival unlock, the Easter eggs and the red skull are recorded into the persisted achievements from the game's own reward events, including for remote players on a listen or dedicated server. `unlockzmeastereggs confirm` marks the main-quest achievements complete outright.

### Headquarters economy

Orders, contracts, payroll, supply drops, the Quartermaster and Mail all run over the Achievement Engine protocol that upstream stubs. This fork answers those requests from a local economy store (`players2/user/hq_economy.json`), with retail-shaped Orders, nine contracts priced in Armory Credits, payroll, supply drops that open, and a Quartermaster whose purchases are usable in Create-a-Class. It is the largest branch and is offered upstream as a draft. The Zombies Supplies screens are out of scope for now. It has been through a six-slice Codex review and three fix rounds, each re-reviewed until clean: receipt ids and the store are validated on both load and save, nothing from a request reaches the console log, contract time is counted per activation from a monotonic clock while playing, purchases check eligibility before any debit, the server-to-client relay is queued and batched off the command thread, and task 11 answers a failure honestly instead of acknowledging dropped events.

Headquarters balances, inventory, Orders, contracts, Mail and reward receipts are saved in `players2/user/hq_economy.json`; `hqeconomy reload` in the console reloads it. If two game instances share one profile, each sees the other's saved changes only after its own next successful economy change or an `hqeconomy reload`; the file lock prevents lost writes. The receipt ledger holds at most 10,000 entries and is never pruned, so after enough play new claims, purchases and payroll stop saving and the console says so once. Deleting `players2/user/hq_economy.json` with every instance closed resets the Headquarters economy and nothing else.

### Developer diagnostics

All inert unless used: `luidump <table> [filter]` enumerates a LUI global table with binding names and RVAs; `cg_unlock_debug` summarises the unlock hook calls; `-demonware_debug` writes `[DW-trace]` payload files for stubbed Demonware tasks; `findstrings` and `dumpcode` scan the unpacked game image. Also a real fix: a long console line no longer crashes the console.

### Headquarters economy

Headquarters balances, inventory, Orders, contracts, Mail and reward receipts are saved in `players2/user/hq_economy.json`; `hqeconomy reload` in the console reloads it. If two game instances share one profile, each sees the other's saved changes only after its own next successful economy change or an `hqeconomy reload`; the file lock prevents lost writes. The receipt ledger holds at most 10,000 entries and is never pruned, so after enough play new claims, purchases and payroll stop saving and the console says so once. Deleting `players2/user/hq_economy.json` with every instance closed resets the Headquarters economy and nothing else.

## Requirements

You must own a legitimate Steam copy of **Call of Duty®: WWII** to use S2x. S2x does **not** provide game files, cracked executables, or any method to obtain the game without purchasing it.

## Compile from source code

- Clone the repository with [Git](https://git-scm.com/install/windows) or [GitHub Desktop](https://desktop.github.com/download/). **Do not download it as a ZIP**, as that will not include the required submodules.
- Check out the branch you want: `integration` for everything, or one of the branches above for a single change.
- Run `generate.bat` to generate the project solution, then build `build\s2x.sln` (Release, x64).
- Copy `build\bin\x64\Release\s2x.exe` (and the `.pdb` if you want readable crash reports) into the game folder, and the Lua patches from `data\ui_scripts\` into `<game folder>\s2x\ui_scripts\`.

## How it is tested

Every branch is built into `integration`, installed and exercised in the game before it is offered upstream: dedicated servers through full rotations with bots and a connected client, the console commands with their error paths, the menus in Multiplayer and Zombies, and the persisted files afterwards. Each commit also gets an independent code review before it is pushed. The details of what was run for each change are in the pull request descriptions.

## Playing against bots

Start Multiplayer, open the console with the tilde/backtick key and load a map with a gametype:

```text
map mp_shipment_s2 dom
```

Once the map has loaded, add bots with `spawnBot 6`, or set `bot_fill 6` once to have them added on every map start.

## Modding: loose file overrides

S2x loads loose files from `%LOCALAPPDATA%\s2x\data\` and `<game folder>\s2x\` before the packaged game assets.

- **GSC scripts**: `scripts\mp\*.gsc` (multiplayer and zombies) or `scripts\sp\*.gsc` (campaign), plus `scripts\mp\<mapname>\` and `scripts\mp\<gametype>\` subfolders.
- **UI scripts**: `ui_scripts\mp\<folder>\__init__.lua` or `ui_scripts\sp\<folder>\__init__.lua`.
- **String tables (`.csv`)**: place the file at the asset path, for example `%LOCALAPPDATA%\s2x\data\mp\botDivisionTable.csv` replaces `mp/botDivisionTable.csv`. Tables that do not exist in the game can be added the same way and read from GSC with `tablelookup`.

The search paths in use are printed once at startup as an `[FS]` line.

## Credits

- [Brentdevent](https://github.com/Brentdevent) and the S2x contributors - the upstream project this fork builds on.
- [momo5502](https://github.com/momo5502) - Former lead developer of [XLabsProject](https://github.com/XLabsProject), research, codebase, and Sogen.
- [Auroramod](https://github.com/auroramod) - Multiple components, int 2d patching, and Demonware emulation.
- [Mallgrab](https://github.com/mallgrab/CWHook) - Cold War Arxan research.
- [Wanted](https://github.com/WantedDV) - `find_lea_target` helper and feedback on VirtualAlloc hook research.

## Disclaimer

S2x is an independent community project created for educational, research, preservation, and interoperability purposes.

This project is not affiliated with, endorsed by, sponsored by, or approved by Activision Publishing, Inc., Sledgehammer Games, Microsoft, Steam, Valve, XLabs, or any related companies.

Call of Duty, Call of Duty: WWII, and all related names, logos, assets, and trademarks are property of their respective owners.

S2x does not include or distribute copyrighted game files. Users are required to own a legitimate copy of the game.

The maintainers are not responsible for misuse of this software. Use responsibly.
