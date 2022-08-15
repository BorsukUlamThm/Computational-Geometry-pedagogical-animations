cmake_minimum_required(VERSION 3.0)
project(CGPA)
set(CMAKE_CXX_STANDARD 20)

# Some directories
set(bin ${CMAKE_SOURCE_DIR}/bin)
set(data ${CMAKE_SOURCE_DIR}/data)
set(log ${data}/log)
file(MAKE_DIRECTORY ${bin})
file(MAKE_DIRECTORY ${log})
file(MAKE_DIRECTORY ${data}/saved_figures)
file(MAKE_DIRECTORY ${data}/saved_inputs)

# Libs setup
include_directories(
        ${CMAKE_SOURCE_DIR}/libs/geometry/include
        ${CMAKE_SOURCE_DIR}/libs/graphics/include
        ${CMAKE_SOURCE_DIR}/libs/utils/include
)
add_subdirectory(libs/geometry)
add_subdirectory(libs/graphics)
add_subdirectory(libs/utils)

# Includes
file(GLOB_RECURSE includes ${CMAKE_SOURCE_DIR}/include/*.h)

# Test executable
add_executable(tests tests.cpp ${includes})
set_target_properties(tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${bin})
target_link_libraries(tests
        CGPA_utils
        CGPA_graphics
        CGPA_geometry)

# All other executables
file(GLOB chapters ${CMAKE_SOURCE_DIR}/src/*)
foreach (chapter ${chapters})
    get_filename_component(chapter_name ${chapter} NAME_WE)
    file(MAKE_DIRECTORY ${log}/${chapter_name})
    file(GLOB sources ${chapter}/*.cpp)

    foreach (source ${sources})
        get_filename_component(source_name ${source} NAME_WE)
        add_executable(${source_name} ${source} ${includes})
        set_target_properties(${source_name} PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY ${bin}/${chapter_name})
        target_link_libraries(${source_name}
                CGPA_utils
                CGPA_graphics
                CGPA_geometry)
    endforeach ()
endforeach ()
