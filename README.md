<div align="center">

# cub3D

### 42 Madrid — Graphics Branch

![42 School](https://img.shields.io/badge/42-Madrid-000000?style=for-the-badge&logo=42&logoColor=white)
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![miniLibX](https://img.shields.io/badge/miniLibX-Linux-4a4a4a?style=for-the-badge)
![RayCasting](https://img.shields.io/badge/RayCasting-Engine-e11d48?style=for-the-badge)

</div>

---

## Table of Contents

- [Description](#description)
- [Features](#features)
- [Instructions](#instructions)
- [Controls](#controls)
- [Map format](#map-format)
- [Resources](#resources)
- [Team](#team)

---

## Description

cub3D is a raycasting engine written in C, inspired by Wolfenstein 3D — the game Id Software released in 1992 and widely considered the first true FPS. The goal is to render a first-person view inside a maze defined by a `.cub` scene file, with different wall textures per cardinal direction and configurable floor and ceiling colors.

The theme chosen for this implementation is the Backrooms — an endless labyrinth of empty rooms, which fits the raycaster aesthetic well. The project was completed with all five bonuses: wall collisions, minimap, doors, animated sprites, and mouse rotation.

---

## Features

**Mandatory**

| Feature | Details |
|---|---|
| Raycasting engine | DDA algorithm, full first-person perspective |
| Directional textures | Different textures for N / S / E / W walls |
| Floor & ceiling | Solid RGB color per surface |
| Keyboard input | WASD to move, arrow keys to rotate, ESC to quit |
| Scene parser | `.cub` file with strict format validation |
| Error handling | `Error\n` + message on any misconfiguration |

**Bonus**

![Wall Collisions](https://img.shields.io/badge/Wall_Collisions-done-22c55e?style=flat-square)
![Minimap](https://img.shields.io/badge/Minimap-done-22c55e?style=flat-square)
![Doors](https://img.shields.io/badge/Doors-done-22c55e?style=flat-square)
![Animated Sprites](https://img.shields.io/badge/Animated_Sprites-done-22c55e?style=flat-square)
![Mouse Rotation](https://img.shields.io/badge/Mouse_Rotation-done-22c55e?style=flat-square)

| Bonus | Description |
|---|---|
| Wall collisions | Player cannot walk through walls |
| Minimap | Overhead map overlay showing player position and orientation |
| Doors | `D` character on map — open and close with interaction key |
| Animated sprites | Frame-based sprite animation rendered in 3D space |
| Mouse rotation | Horizontal mouse movement rotates the camera |

---

## Instructions

**Requirements**

- Linux
- miniLibX — bundled in `minilibx-linux/`, no separate install needed
- `libXext` and `libX11` — `sudo apt install libxext-dev libx11-dev`
- `gcc`, `make`

**Compilation**

```bash
git clone git@github.com:T-D-A-H/Cub3D.git
cd Cub3D

# Mandatory
make

# With bonuses
make bonus
```

**Run**

```bash
# Mandatory
./cub3D maps/your_map.cub

# Bonus
./cub3D_bonus maps/your_map.cub
```

**Cleanup**

| Command | Description |
|---|---|
| `make clean` | Remove object files |
| `make fclean` | Remove object files and binary |
| `make re` | Full recompile |

---

## Controls

| Key | Action |
|---|---|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` / `→` | Rotate camera |
| Mouse X | Rotate camera (bonus) |
| `E` | Interact with door (bonus) |
| `ESC` | Quit |
| Red cross | Quit |

---

## Map format

Scene files use the `.cub` extension. Elements can appear in any order except the map, which must always be last.

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

1111111111
1000000001
10N000D001
1000000001
1111111111
```

**Map characters**

| Character | Meaning |
|---|---|
| `1` | Wall |
| `0` | Empty space |
| `N` / `S` / `E` / `W` | Player start position and orientation |
| `D` | Door (bonus) |
| ` ` | Space — valid, treated as void |

The map must be fully enclosed by walls. Any misconfiguration exits with `Error\n` followed by an explicit message.

---

## Resources

**Raycasting**

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — the main reference for the DDA algorithm and texture mapping
- [Game Engine Black Book: Wolfenstein 3D](https://fabiensanglard.net/gebbwolf3d/) — deep dive into the original engine
- [Binary Space Partitioning (Wikipedia)](https://en.wikipedia.org/wiki/Binary_space_partitioning)

**miniLibX**

- [miniLibX Linux documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [42 Docs — MiniLibX](https://42docs.com/libs/minilibx/getting_started.html)

**Math**

- [Ray-Plane intersection](https://en.wikipedia.org/wiki/Line%E2%80%93plane_intersection)
- [DDA algorithm](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm))

**AI usage**

AI was used during this project for the following tasks:

- Generating boilerplate and repetitive C structures (getter/setter patterns, error message formatting)
- Explaining DDA algorithm edge cases and helping debug texture offset calculations
- Reviewing and suggesting improvements to the map parser logic
- Writing this README

All AI-generated code was reviewed, tested, and understood before being integrated. Nothing was copy-pasted without verification.

---

## Team

| Login | GitHub |
|---|---|
| ctommasi | [@vikingokvist](https://github.com/vikingokvist) |
| jaimesan | [@Ja1m3st](https://github.com/Ja1m3st) |

---

<div align="center">
42 Madrid
</div>
