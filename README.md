<img width="1200" height="350" alt="s2x-readme-banner" src="https://github.com/user-attachments/assets/733e21a4-2703-4ba7-ab07-151b0f17e94a" />

# S2x ⭐

> [!WARNING]
> S2x is actively being developed, and several features are already implemented, but the project is not yet feature-complete.
>
> Expect bugs, crashes, missing features, and general instability.
>
> Dedicated servers, modding support, online functionality, and further gameplay stability are still in development.

S2x is a custom client project for **Call of Duty®: WWII**, focused on preserving and extending functionality for campaign, multiplayer, and zombies.

Join the S2x community on [Discord](https://discord.gg/wdC8Jpc2cC).

The project is inspired by the work of the former XLabs community, but S2x is an independent project and is not affiliated with XLabs, Activision, Sledgehammer Games, Microsoft, or any related publisher, developer, or trademark holder.

## Requirements

You must own a legitimate Steam copy of **Call of Duty®: WWII** to use S2x.

S2x does **not** provide game files, cracked executables, or any method to obtain the game without purchasing it. Please support the original developers and publishers by owning a legal copy of the game.

## Compile from source code

- Clone the Git repository using [Git](https://git-scm.com/install/windows) or [GitHub Desktop](https://desktop.github.com/download/). **Do not download it as a ZIP**, as that will not include the required submodules.
- Run the `generate.bat` script to generate the project solution.
- Build the project using the generated solution file at `build\s2x.sln`.

## Combat Training

Start Multiplayer, open the console with the tilde/backtick key and load a map with a
gametype:

```text
map mp_shipment_s2 dom
```

Once the map has loaded, add bots:

```text
spawnBot 6
```

`bot_fill` does that on every map start, so changing map does not mean retyping
`spawnBot`. It is saved with your profile:

```text
bot_fill 6
map mp_shipment_s2 war
```

Set `bot_fill 0` to disable it again. The value is a number of bots from 0 to the
multiplayer player limit of 18; a value outside that range is rejected and the previous
one is kept. Bots count toward the match's player limit, and the console reports how many
the engine actually added. Progression works in these matches.

One trap worth knowing: a dedicated server started from this game folder reads the same
profile, so `+set bot_fill N` there also changes the value for your own matches. Set it
back to `0` afterwards if you do not want bots in them.

## Credits

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
