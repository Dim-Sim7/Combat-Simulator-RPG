cmake_minimum_required(VERSION 3.10)
project(warcraft_roguelike)

set(CMAKE_CXX_STANDARD 17)

# Add main source folder
include_directories(src)

# Add your main source files (if you have an executable)
# add_executable(warcraft_roguelike src/main.cpp src/statblock.cpp)

# --- Tests ---
# Define the test executable
add_executable(test_stat_block
    tests/test_stat_block.cpp
    src/statblock.cpp
)

add_executable(test_pointwell
    tests/test_pointwell.cpp
    src/pointwell.cpp
)

add_executable(test_entity
    tests/test_entity.cpp
    src/entity.cpp
    src/pointwell.cpp
    src/statblock.cpp
)   

add_executable(test_armor
    tests/test_armor.cpp
    src/armor.cpp
    src/item.cpp
    src/pointwell.cpp
)

# Link with Catch2 (if installed system-wide)
find_package(Catch2 3 REQUIRED)
target_link_libraries(test_stat_block PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_pointwell PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_entity PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_armor PRIVATE Catch2::Catch2WithMain)

#COMMANDS I NEED TO KNOW
#rm -rf build
#cmake ..
#make
# /test_....
