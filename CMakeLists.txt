cmake_minimum_required(VERSION 3.0)
project(CGPA)
set(CMAKE_CXX_STANDARD 20)

# Some directories
set(bin ${CMAKE_SOURCE_DIR}/bin)
set(data ${CMAKE_SOURCE_DIR}/data)
set(log ${data}/log)
file(MAKE_DIRECTORY ${bin})
file(MAKE_DIRECTORY ${log})
file(MAKE_DIRECTORY ${log}/tests)
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

# Tests
file(GLOB tests ${CMAKE_SOURCE_DIR}/tests/*.cpp)
foreach (test ${tests})
    get_filename_component(test_name ${test} NAME_WE)
    add_executable(${test_name} ${test})
    set_target_properties(${test_name} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${bin}/tests)
    target_link_libraries(${test_name}
            CGPA-utils
            CGPA-graphics
            CGPA-geometry)
endforeach ()

# Examples
file(GLOB examples ${CMAKE_SOURCE_DIR}/examples/*.cpp)
foreach (example ${examples})
    get_filename_component(example_name ${example} NAME_WE)
    add_executable(${example_name} ${example})
    set_target_properties(${example_name} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${bin}/examples)
    target_link_libraries(${example_name}
            CGPA-utils
            CGPA-graphics
            CGPA-geometry)
endforeach ()

# All other executables
file(GLOB chapters ${CMAKE_SOURCE_DIR}/animations/*)
foreach (chapter ${chapters})
    get_filename_component(chapter_name ${chapter} NAME_WE)
    file(MAKE_DIRECTORY ${log}/${chapter_name})
    file(GLOB animations ${chapter}/*.cpp)

    foreach (animation ${animations})
        file(GLOB_RECURSE sources
                ${CMAKE_SOURCE_DIR}/animations/${chapter_name}/src/*.cpp)
        get_filename_component(animation_name ${animation} NAME_WE)
        add_executable(${animation_name} ${animation} ${sources})
        set_target_properties(${animation_name} PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY ${bin}/${chapter_name})
        target_link_libraries(${animation_name}
                CGPA-utils
                CGPA-graphics
                CGPA-geometry)
    endforeach ()
endforeach ()
