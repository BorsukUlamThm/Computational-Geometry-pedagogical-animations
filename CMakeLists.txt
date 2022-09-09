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
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/libs/geometry/include
        ${CMAKE_SOURCE_DIR}/libs/graphics/include
        ${CMAKE_SOURCE_DIR}/libs/utils/include
)
add_subdirectory(libs/geometry)
add_subdirectory(libs/graphics)
add_subdirectory(libs/utils)

# Includes and sources
file(GLOB_RECURSE includes ${CMAKE_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE sources ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Test
add_executable(tests tests.cpp ${includes})
set_target_properties(tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${bin})
target_link_libraries(tests
        CGPA_utils
        CGPA_graphics
        CGPA_geometry)

# Examples
file(GLOB examples ${CMAKE_SOURCE_DIR}/examples/*.cpp)
foreach (example ${examples})
    get_filename_component(example_name ${example} NAME_WE)
    add_executable(${example_name} ${example})
    set_target_properties(${example_name} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${bin}/examples)
    target_link_libraries(${example_name}
            CGPA_utils
            CGPA_graphics
            CGPA_geometry)
endforeach ()

# All other executables
file(GLOB chapters ${CMAKE_SOURCE_DIR}/animations/*)
foreach (chapter ${chapters})
    get_filename_component(chapter_name ${chapter} NAME_WE)
    file(MAKE_DIRECTORY ${log}/${chapter_name})
    file(GLOB animations ${chapter}/*.cpp)

    foreach (animation ${animations})
        get_filename_component(animation_name ${animation} NAME_WE)
        add_executable(${animation_name} ${animation} ${sources})
        set_target_properties(${animation_name} PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY ${bin}/${chapter_name})
        target_link_libraries(${animation_name}
                CGPA_utils
                CGPA_graphics
                CGPA_geometry)
    endforeach ()
endforeach ()
