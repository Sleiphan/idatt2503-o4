cmake_minimum_required(VERSION 3.7...3.26)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(edu_ntnu_inft2503
    VERSION 0.1
    DESCRIPTION "An example project."
    LANGUAGES C CXX)

set(AFL_COMPILER "afl-gcc")
set(AFL_COMPILER_PP "afl-g++")

add_subdirectory(Exercise_4)
# add_subdirectory(Exercise_5)
add_subdirectory(Exercise_6)
add_subdirectory(Exercise_7)
add_subdirectory(Exercise_8)