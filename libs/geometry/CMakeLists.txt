set(geometry ${CMAKE_SOURCE_DIR}/libs/geometry)
set(utils ${CMAKE_SOURCE_DIR}/libs/utils)

add_subdirectory(${CMAKE_SOURCE_DIR}/libs/utils geometry/bin)

include_directories(${geometry}/include ${utils}/include)

file(GLOB_RECURSE geometry_sources ${geometry}/src/geometry/*.cpp)
add_library(CGPA_geometry ${geometry_sources})

target_link_libraries(CGPA_geometry CGPA_utils)