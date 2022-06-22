cmake_minimum_required(VERSION 2.8)
file(GLOB SRC_FILES "*.cpp")
set(SOURCE_LIB ${SRC_FILES})
add_library(my3dframework STATIC ${SOURCE_LIB})
