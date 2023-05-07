include_guard(GLOBAL)

set(utils ${CMAKE_SOURCE_DIR}/libs/utils)

include_directories(${utils}/include/utils)

file(GLOB_RECURSE utils_sources ${utils}/src/utils/*.cpp)
add_library(CGPA-utils ${utils_sources})

# Boost include
FIND_PACKAGE(Boost 1.71 COMPONENTS program_options REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

target_link_libraries(CGPA-utils ${Boost_LIBRARIES})