include_guard(GLOBAL)

set(graphics ${CMAKE_SOURCE_DIR}/libs/graphics)
set(utils ${CMAKE_SOURCE_DIR}/libs/utils)

add_subdirectory(${CMAKE_SOURCE_DIR}/libs/utils graphics/bin)
include_directories(${graphics}/include ${utils}/include)

file(GLOB_RECURSE graphics_sources ${graphics}/src/graphics/*.cpp)
add_library(CGPA-graphics ${graphics_sources})

target_link_libraries(CGPA-graphics
        CGPA-utils
        -lsfml-graphics -lsfml-window -lsfml-system
        )