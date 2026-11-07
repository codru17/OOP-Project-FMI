# game2d — simple 2D platformer engine

C++17 OOP project: a small 2D game engine (scenes, entities, physics, collisions, input, resources) and a platformer game built on top of it. Graphics/audio/input via [SFML 3](https://www.sfml-dev.org/).

## Build

Requirements: g++ with C++17 (tested with MinGW-w64 GCC 16), CMake 3.24+, Ninja, internet on first configure (SFML is downloaded automatically).

```bash
cd game2d
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug   # first time: downloads + builds SFML (a few minutes)
cmake --build build                                     # compile
./build/game2d                                          # run
```

## Structure

| Folder | Content |
|---|---|
| `include/engine`, `src/engine` | Reusable engine code (game loop, scenes, entities, physics, resources) |
| `include/game`, `src/game` | The platformer itself, built on top of the engine (player, enemies, levels) |
| `assets/textures`, `fonts`, `sounds` | Images, fonts, sounds (copied next to the .exe on build) |
| `assets/levels` | Level files (text-based tile maps) |
| `docs/` | UML diagrams, notes |
