cmake_minimum_required(VERSION 3.14)
project(psds_cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_EXAMPLES "Build examples" OFF)
option(BUILD_EXAMPLES_01_WEEK "Build examples for week_01" OFF)
option(BUILD_EXAMPLES_02_WEEK "Build examples for week_02" OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
find_package(GoogleTest REQUIRED)

set(CMAKE_BINARY_TASKS_DIR ${CMAKE_BINARY_DIR}/tasks)

include(cmake/TestSolution.cmake)
include(cmake/AsanFlags.cmake)

function(add_week NAME)
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${NAME})
        add_subdirectory(${NAME})
    endif()
endfunction()

add_executable(psds_cpp main.cpp)

add_week(week_01)
#add_week(week_02)
#add_week(week_03)
#add_week(week_04)
#add_week(week_05)
#add_week(week_06)
#add_week(week_07)
#add_week(week_08)
#add_week(week_09)
#add_week(week_10)