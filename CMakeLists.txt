cmake_minimum_required(VERSION 2.8)

project(3d-drawer)

set(SOURCE_EXE test/test.cpp)

include_directories(src)

add_executable(3d-drawer ${SOURCE_EXE})

target_compile_definitions(3d-drawer PUBLIC SFML-STATIC)
add_subdirectory(src)

SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++17")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

target_link_libraries(3d-drawer src)
target_link_libraries(3d-drawer sfml-system sfml-window sfml-graphics)
