cmake_minimum_required(VERSION 2.8)

set(SOURCE_EXE test.cpp)
set(GAME_SOURCE test_game.cpp)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(3d-drawer ${SOURCE_EXE})
add_executable(3d-game ${GAME_SOURCE})
target_compile_definitions(3d-drawer PUBLIC SFML-STATIC)
target_compile_definitions(3d-game PUBLIC SFML-STATIC)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

target_link_libraries(3d-drawer my3dframework)
target_link_libraries(3d-drawer sfml-system sfml-window sfml-graphics)

target_link_libraries(3d-game my3dframework)
target_link_libraries(3d-game sfml-system sfml-window sfml-graphics)
