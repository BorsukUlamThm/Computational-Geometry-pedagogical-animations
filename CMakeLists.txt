cmake_minimum_required(VERSION 3.19)
project(Alpha)
set(CMAKE_CXX_STANDARD 14)

set(Graphics_dir "${CMAKE_SOURCE_DIR}/src/Graphics")
set(Algorithms_dir "${CMAKE_SOURCE_DIR}/src/Algorithms")
file(GLOB_RECURSE graphics_sources "${Graphics_dir}/*.h")
file(GLOB_RECURSE algorithms_sources "${Algorithms_dir}/*.h")

add_executable(Alpha main.cpp ${graphics_sources} ${algorithms_sources})
target_link_libraries(Alpha -lsfml-graphics -lsfml-window -lsfml-system)