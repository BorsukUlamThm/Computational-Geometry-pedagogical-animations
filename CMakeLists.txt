cmake_minimum_required(VERSION 3.19)
project(Alpha)
set(CMAKE_CXX_STANDARD 14)

set(Graphics_dir "${CMAKE_SOURCE_DIR}/src/Graphics")
file(GLOB_RECURSE graphics_sources "${Graphics_dir}/*.h")

add_executable(Alpha main.cpp ${graphics_sources})
target_link_libraries(Alpha -lsfml-graphics -lsfml-window -lsfml-system)