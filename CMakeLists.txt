cmake_minimum_required(VERSION 2.8)

project(3d-drawer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)
add_subdirectory(src)

if(BUILD_TEST)
    add_subdirectory(test)
endif()
