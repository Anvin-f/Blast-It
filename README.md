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

BlockBlast: Dungeon Grids combines a block-placement puzzle with turn-based RPG
combat. Clear lines on the grid to earn Action Points, then spend them fighting
monsters.

### Objective

Survive as long as possible by placing blocks, clearing lines, and defeating
monsters. The game ends when your HP reaches 0.

### Difficulty

At the start you choose a difficulty, which sets your starting stats and the
enemy pool:

| Difficulty | HP  | Attack | Defense | Special unlock |
|------------|-----|--------|---------|----------------|
| Easy       | 150 | 10     | 5       | Always         |
| Normal     | 100 | 10     | 3       | After 3 kills  |
| Hard       | 70  | 8      | 1       | After 5 kills  |

### Controls

| Key | Action |
|-----|--------|
| `1` `2` `3` | Select which of the three available blocks to place |
| `W` `A` `S` `D` | Move the selected block up / left / down / right |
| `R` | Place (confirm) the block on the grid |
| `Q` | Quit the game |

### Placing blocks

Each round you are offered three random block shapes. Select one with `1`, `2`,
or `3`, position it with WASD, and press `R` to place it. Blocks cannot overlap
existing tiles or go out of bounds. A used block is consumed — you cannot place
the same block twice in a round.

### Clearing lines and earning points

After every placement the game checks all 8 rows and all 8 columns. Any row or
column that is completely filled is cleared simultaneously.

**Scoring formula:**

```
base  = max(0, 30 × lines_cleared − 20)
score = base × multiplier
```

The multiplier starts at 1 and increases by 1 for each consecutive move where
you clear at least one line. It resets to 1 the moment a placement clears
nothing.

*Example:* clearing 2 lines on your second consecutive clearing move →
`(30×2 − 20) × 2 = 80 points`.

Points are converted directly into **Action Points (AP)** for the next combat
phase.

### Combat

After earning AP from line clears you fight the current monster. Each combat
turn you may spend AP on any combination of the following actions:

| Action | Cost | Effect |
|--------|------|--------|
| **Attack** | Any AP | Deals `base_attack + AP_spent` damage to the monster |
| **Special Attack** | 20 AP fixed | Deals 2–3× base attack (random); unlocks at kill threshold |
| **Heal** | Any AP | Restores HP equal to AP spent (capped at max HP) |
| **Defend** | Any AP | Reduces incoming monster damage by AP spent that turn |

Unused AP carries over to the next combat round — saving AP between fights is a
valid strategy.

Monster damage per turn: `monster_attack − your_defense − defend_AP_spent`
(minimum 0).

### Monsters

Monsters scale with the number of kills you have accumulated:

| Difficulty | Type   | HP (base + per kill) | Attack (base + per kill) | Bounty |
|------------|--------|----------------------|--------------------------|--------|
| Easy       | Goblin | 30 + 10 × kills      | 8 + 3 × kills            | 30 pts |
| Normal     | Orc    | 50 + 15 × kills      | 12 + 5 × kills           | 50 pts |
| Hard       | Dragon | 70 + 25 × kills      | 16 + 8 × kills           | 70 pts |

Defeating a monster awards its bounty points and spawns a stronger one
immediately.

### Win / loss

- **Game over** — your HP drops to 0.
- There is no fixed end state; the goal is to maximise your score before dying.

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