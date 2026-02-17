cmake_minimum_required(VERSION 3.14)
project(combat_simulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------
# Fetch Catch2 (no system install required)
# -----------------------------
include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.5.2
)

FetchContent_MakeAvailable(Catch2)

# -----------------------------
# Core library
# -----------------------------
set(ENTITY_SOURCES
    src/entities/statblock.cpp
    src/entities/pointwell.cpp
    src/entities/entity.cpp
    src/entities/player.cpp
    src/entities/npc.cpp
    src/entities/npc_ai.cpp
)

set(ITEM_SOURCES
    src/items/item.cpp
    src/items/armor.cpp
    src/items/weapon.cpp
    src/items/inventory.cpp
    src/items/equipslots.cpp
    src/items/item_database.cpp
    src/items/item_factory.cpp
)

set(LOOT_SOURCES
    src/loot/enemy_loot_filler.cpp
    src/loot/gold.cpp
    src/loot/lootable_value.cpp
)

add_library(combat_core
    ${ENTITY_SOURCES}
    ${ITEM_SOURCES}
    ${LOOT_SOURCES}
    src/battlesystem.cpp
)

target_include_directories(combat_core PUBLIC src)

# -----------------------------
# Main executable
# -----------------------------
add_executable(combat_sim
    src/main.cpp
)

target_link_libraries(combat_sim PRIVATE combat_core)

# -----------------------------
# Tests
# -----------------------------
enable_testing()

add_executable(combat_tests
    tests/test_stat_block.cpp
    tests/test_pointwell.cpp
    tests/test_entity.cpp
    tests/test_items.cpp
    tests/test_consumable.cpp
    tests/test_itemfactory.cpp
    tests/test_enemy_loot_filler.cpp
    tests/test_loot_table.cpp
    tests/test_lootable_value.cpp
)

target_link_libraries(combat_tests
    PRIVATE
        combat_core
        Catch2::Catch2WithMain
)

# Let Catch2 register tests with CTest automatically
include(Catch)
catch_discover_tests(combat_tests)