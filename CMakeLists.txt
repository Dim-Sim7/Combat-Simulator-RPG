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
add_library(combat_core
    src/entities/statblock.cpp
    src/entities/pointwell.cpp
    src/entities/entity.cpp
    src/entities/player.cpp
    src/entities/npc.cpp
    src/entities/npc_ai.cpp

    src/items/item.cpp
    src/items/armor.cpp
    src/items/weapon.cpp 
    src/items/inventory.cpp
    src/items/equipslots.cpp
    src/items/item_database.cpp 
    src/items/item_factory.cpp 

    src/loot/enemy_loot_filler.cpp 
    src/loot/gold.cpp 
    src/loot/lootable_value.cpp 

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

add_executable(test_stat_block
    tests/test_stat_block.cpp
)
target_link_libraries(test_stat_block PRIVATE combat_core Catch2::Catch2WithMain)

add_executable(test_pointwell
    tests/test_pointwell.cpp
)
target_link_libraries(test_pointwell PRIVATE combat_core Catch2::Catch2WithMain)

add_executable(test_entity
    tests/test_entity.cpp
)
target_link_libraries(test_entity PRIVATE combat_core Catch2::Catch2WithMain)

add_executable(test_armor
    tests/test_armor.cpp
)
target_link_libraries(test_armor PRIVATE combat_core Catch2::Catch2WithMain)

add_test(NAME StatBlockTests COMMAND test_stat_block)
add_test(NAME PointwellTests COMMAND test_pointwell)
add_test(NAME EntityTests COMMAND test_entity)
add_test(NAME ArmorTests COMMAND test_armor)
