cmake_minimum_required(VERSION 3.0)
project(CGPA)
set(CMAKE_CXX_STANDARD 20)

# Boost include
FIND_PACKAGE(Boost 1.74 COMPONENTS program_options REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

# Some variables for the executables
file(GLOB_RECURSE includes ${CMAKE_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE sources ${CMAKE_SOURCE_DIR}/src/*.cpp)
include_directories(${CMAKE_SOURCE_DIR}/include)
add_library(lib_CGPA ${includes} ${sources})

# Some directories
set(bin ${CMAKE_SOURCE_DIR}/bin)
set(data ${CMAKE_SOURCE_DIR}/data)
set(log ${data}/log)
file(MAKE_DIRECTORY ${bin})
file(MAKE_DIRECTORY ${log})
file(MAKE_DIRECTORY ${data}/saved_figures)
file(MAKE_DIRECTORY ${data}/saved_inputs)

# Test executable
add_executable(tests tests.cpp ${includes} ${sources})
set_target_properties(tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${bin})
target_link_libraries(tests -lsfml-graphics -lsfml-window -lsfml-system ${Boost_LIBRARIES})
target_link_libraries(tests ${lib_CGPA})

# All other executables
file(GLOB chapters ${CMAKE_SOURCE_DIR}/animations/*)
foreach(chapter ${chapters})
    get_filename_component(chapter_name ${chapter} NAME_WE)
    file(MAKE_DIRECTORY ${log}/${chapter_name})
    file(GLOB animation_sources ${chapter}/*.cpp)

    foreach(source ${animation_sources})
        get_filename_component(source_name ${source} NAME_WE)
        add_executable(${source_name} ${source} ${includes} ${sources})
        set_target_properties(${source_name} PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY ${bin}/${chapter_name})
        target_link_libraries(${source_name} -lsfml-graphics -lsfml-window -lsfml-system ${Boost_LIBRARIES})
        target_link_libraries(${source_name} ${lib_CGPA})
    endforeach()
endforeach()
