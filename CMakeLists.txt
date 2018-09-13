cmake_minimum_required(VERSION 3.12)
project(lucky_labs_test_task)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -DDEBUG")

add_subdirectory(bombs)
add_subdirectory(sea-battle)
