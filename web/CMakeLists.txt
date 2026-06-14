cmake_minimum_required(VERSION 3.13)

project(3d-framework-wasm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/../src")

add_executable(rasterizer
    wasm_app.cpp
    "${SRC_DIR}/camera.cpp"
    "${SRC_DIR}/loader.cpp"
    "${SRC_DIR}/point.cpp"
    "${SRC_DIR}/renderer.cpp"
    "${SRC_DIR}/screen.cpp"
    "${SRC_DIR}/surface_object.cpp"
    "${SRC_DIR}/triangle.cpp"
    "${SRC_DIR}/wire_object.cpp"
)

target_include_directories(rasterizer PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}"
    "${SRC_DIR}"
)

if(EMSCRIPTEN)
    set_target_properties(rasterizer PROPERTIES
        OUTPUT_NAME "rasterizer"
        SUFFIX ".js"
        LINK_FLAGS "--bind -s MODULARIZE=0 -s EXPORTED_RUNTIME_METHODS=['cwrap'] -s EXPORTED_FUNCTIONS=['_raster_init','_raster_frame','_raster_width','_raster_height','_raster_pixels','_raster_angle','_malloc','_free'] --preload-file ${CMAKE_CURRENT_LIST_DIR}/../models/teapot.off@/models/teapot.off"
    )
endif()
