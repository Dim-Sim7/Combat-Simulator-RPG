# CMake generated Testfile for 
# Source directory: /home/dim-sim/workspace/Combat-Simulator-RPG
# Build directory: /home/dim-sim/workspace/Combat-Simulator-RPG/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(StatBlockTests "/home/dim-sim/workspace/Combat-Simulator-RPG/build/test_stat_block")
set_tests_properties(StatBlockTests PROPERTIES  _BACKTRACE_TRIPLES "/home/dim-sim/workspace/Combat-Simulator-RPG/CMakeLists.txt;83;add_test;/home/dim-sim/workspace/Combat-Simulator-RPG/CMakeLists.txt;0;")
add_test(PointwellTests "/home/dim-sim/workspace/Combat-Simulator-RPG/build/test_pointwell")
set_tests_properties(PointwellTests PROPERTIES  _BACKTRACE_TRIPLES "/home/dim-sim/workspace/Combat-Simulator-RPG/CMakeLists.txt;84;add_test;/home/dim-sim/workspace/Combat-Simulator-RPG/CMakeLists.txt;0;")
add_test(EntityTests "/home/dim-sim/workspace/Combat-Simulator-RPG/build/test_entity")
set_tests_properties(EntityTests PROPERTIES  _BACKTRACE_TRIPLES "/home/dim-sim/workspace/Combat-Simulator-RPG/CMakeLists.txt;85;add_test;/home/dim-sim/workspace/Combat-Simulator-RPG/CMakeLists.txt;0;")
add_test(ArmorTests "/home/dim-sim/workspace/Combat-Simulator-RPG/build/test_armor")
set_tests_properties(ArmorTests PROPERTIES  _BACKTRACE_TRIPLES "/home/dim-sim/workspace/Combat-Simulator-RPG/CMakeLists.txt;86;add_test;/home/dim-sim/workspace/Combat-Simulator-RPG/CMakeLists.txt;0;")
subdirs("_deps/catch2-build")
