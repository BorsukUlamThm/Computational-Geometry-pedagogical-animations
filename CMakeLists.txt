cmake_minimum_required(VERSION 3.0)
project(Alpha)
set(CMAKE_CXX_STANDARD 20)

# Some variables for the includes
set(Graphics_dir ${CMAKE_SOURCE_DIR}/src/Graphics)
set(Algorithms_dir ${CMAKE_SOURCE_DIR}/src/Algorithms)
file(GLOB_RECURSE graphics_sources ${Graphics_dir}/*.h)
file(GLOB_RECURSE algorithms_sources ${Algorithms_dir}/*.h)
include_directories(${CMAKE_SOURCE_DIR}/src)

# Executables directory
set(bin ${CMAKE_SOURCE_DIR}/bin)

# Test executable
add_executable(tests tests.cpp ${graphics_sources} ${algorithms_sources})
set_target_properties(tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${bin})
target_link_libraries(tests -lsfml-graphics -lsfml-window -lsfml-system)

# All other executables
file(GLOB chapters ${CMAKE_SOURCE_DIR}/src/Algorithms/Sources/*)
foreach(chapter ${chapters})
    get_filename_component(chapter_name ${chapter} NAME_WE)
    file(GLOB sources ${chapter}/*.cpp)

    foreach(source ${sources})
        get_filename_component(source_name ${source} NAME_WE)
        add_executable(${source_name} ${source} ${graphics_sources} ${algorithms_sources})
        set_target_properties(${source_name} PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY ${bin}/${chapter_name})
        target_link_libraries(${source_name} -lsfml-graphics -lsfml-window -lsfml-system)
    endforeach()
endforeach()
