# Combat Simulator (C++)

A modular, real-time combat simulation written in modern C++, focused on correctness, concurrency, and clean system design.

This project was built to explore time-based simulation, multi-entity interaction, and state-driven logic in a controlled environment. While the domain is game-inspired, the emphasis is on engineering fundamentals rather than presentation.

---

## Overview

The simulator models real-time combat between autonomous entities with abilities, items, and AI-driven decision-making. It operates on a fixed update loop, processes asynchronous user input, and enforces strict state transitions to maintain consistency.

Key goals of the project:
- Build a deterministic, testable simulation core
- Handle concurrent input safely
- Maintain clear separation between systems
- Support extensibility without fragile coupling

---

## Core Features

### Real-Time Simulation Loop
- Fixed-step update loop (~60 FPS)
- Time tracking using `std::chrono`
- Global cooldown and cast-time mechanics enforced via timestamps
- Explicit state transitions for actions and abilities

### Concurrency & Input Handling
- Dedicated input thread for non-blocking command collection
- Thread-safe command queue using `std::mutex` and `std::atomic`
- Clean startup and shutdown with well-defined ownership
- No unsynchronised shared state

### Entity & State Management
- Shared `Entity` abstraction for players and NPCs
- Encapsulated stat systems (health, armor, damage ranges, crit chance)
- Defensive checks to prevent invalid state transitions
- Clear lifecycle handling (death, fleeing, combat end)

### AI System
- NPC behaviour implemented as a state-driven update loop
- Decisions based on current combat state, cooldowns, and health thresholds
- Designed for extensibility without modifying the combat engine

---

## Inventory & Loot System

- Inventory abstraction with typed item access
- Consumables and equipment modeled via stat modifiers
- Loot generation supports:
  - Weighted probability distributions
  - Guaranteed drops
  - Unique item constraints
  - Randomized value attributes

Random sampling is isolated from state mutation to allow deterministic testing and reproducibility.

---

## Testing & Build System

- Unit tests written with Catch2
- Test coverage includes:
  - Stat calculations
  - Entity interactions
  - Inventory and equipment logic
  - Resource systems
- Dependency management handled via CMake `FetchContent`
- No reliance on system-installed libraries

---

## Build Instructions

### Requirements
- CMake 3.14+
- C++17 compatible compiler

### Build And Run
```bash
rm -rf build
mkdir build && cd build
cmake ..
make -j


./combat_sim


ctest