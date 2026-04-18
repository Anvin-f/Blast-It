# BlockBlast: Dungeon Grids

A text-based C++ game that combines BlockBlast-style puzzle mechanics with a
turn-based RPG dungeon crawl. Place block shapes on an 8×8 grid to clear rows
and columns, earn Action Points, then spend them fighting monsters.

Group project for COMP2113.

## Team and modules

| Member | Files | Responsibility |
|--------|-------|----------------|
| A | `board.{h,cpp}`, `block.{h,cpp}` | Grid, shapes, placement, line clearing |
| B | `player.{h,cpp}`, `combat.{h,cpp}`, `fileio.{h,cpp}` | RPG stats, combat, save/load |
| C | `main.cpp`, `game.{h,cpp}`, `Makefile` | Game loop, integration, build |

## Requirements

- A C++ compiler supporting **C++11** (`g++` recommended)
- GNU `make`
- A Unix-like shell so `make clean` works (`rm -f` is not a Windows command)

## Setup

### macOS

Install the Xcode Command Line Tools if you don't have them:

```
xcode-select --install
```

That gives you `g++` and `make`. Done.

### Windows

`cmd.exe` and PowerShell do not include `make` or `g++`. Pick **one** of the
following environments and use it consistently:

**MSYS2 (recommended)**
1. Install from https://www.msys2.org/
2. Open the "MSYS2 MinGW 64-bit" shell
3. Run: `pacman -S mingw-w64-x86_64-gcc make`
4. Add `C:\msys64\mingw64\bin` to your PATH

**WSL (Windows Subsystem for Linux)**
1. In an admin PowerShell: `wsl --install`
2. Reboot, finish Linux setup
3. Inside WSL: `sudo apt update && sudo apt install build-essential`

Either option works. Agree with teammates on one so "works on my machine"
stories are easier to debug.

## Build

From the project root:

```
make
```

This produces an executable named `blockblast` (`blockblast.exe` on Windows).

## Run

On macOS / WSL / MSYS2:

```
./blockblast
```

Press `q` then Enter to quit.

## Clean

Removes the executable and all `.o` object files:

```
make clean
```

Run this if a build seems to behave weirdly after a header change — it forces
a full rebuild.

## Project structure

```
.
├── main.cpp        # Entry point
├── game.cpp        # Main game loop
├── game.h          # Game class
├── Makefile        # Build rules
├── README.md       # This file
└── .gitignore
```

Planned files not yet implemented: `board.{h,cpp}`, `block.{h,cpp}`,
`player.{h,cpp}`, `combat.{h,cpp}`, `fileio.{h,cpp}`.

When you add a new `.cpp` file, remember to add a matching rule in the
`Makefile` and list the new `.o` in both the link step and the `clean` rule.

## How to play

*Gameplay is under active development. This section will be filled in once
the puzzle and combat layers are implemented.*

## Troubleshooting

**`make: command not found`**
`make` is not installed. See the Setup section for your OS.

**`Makefile:N: *** missing separator. Stop.`**
The indented lines under a rule must start with a **tab**, not spaces. Open
the Makefile in an editor that shows whitespace and fix the offending line.

**`'g++' is not recognized ...` (Windows)**
You're running from `cmd` or PowerShell without MSYS2's `bin` on your PATH.
Either fix the PATH or run `make` from the MSYS2 / WSL shell.

**`./blockblast: No such file or directory` (Windows)**
On Windows the file is `blockblast.exe`. Run it as `./blockblast.exe` or
just `blockblast`.

**Changed a `.h` file but the bug didn't go away**
Run `make clean` and then `make` again. If it goes away after that, one of
the `.o` rules in the Makefile is missing a header dependency — fix it.