include_guard(GLOBAL)

set(geometry ${CMAKE_SOURCE_DIR}/libs/geometry)
set(graphics ${CMAKE_SOURCE_DIR}/libs/graphics)
set(utils ${CMAKE_SOURCE_DIR}/libs/utils)

add_subdirectory(${CMAKE_SOURCE_DIR}/libs/graphics geometry/bin)
include_directories(${geometry}/include ${graphics}/include ${utils}/include)

file(GLOB_RECURSE geometry_sources ${geometry}/src/geometry/*.cpp)
add_library(CGPA-geometry ${geometry_sources})

target_link_libraries(CGPA-geometry CGPA-graphics)