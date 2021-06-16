cmake_minimum_required(VERSION 3.19)
project(Alpha)
set(CMAKE_CXX_STANDARD 14)

set(Drawer_dir "${CMAKE_SOURCE_DIR}/Drawer")
file(GLOB_RECURSE drawer_sources "${Drawer_dir}/*.h")

add_executable(Alpha main.cpp ${drawer_sources})