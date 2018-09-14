cmake_minimum_required(VERSION 3.12)
project(lucky_labs_test_task)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -DDEBUG")

if (CMAKE_BUILD_TYPE MATCHES "Other[A-z]*")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DOTHER")
endif (CMAKE_BUILD_TYPE MATCHES "Other[A-z]*")

if (CMAKE_BUILD_TYPE MATCHES "[A-z]*Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -DDEBUG")
    set(CMAKE_CXX_DEBUG_FLAGS "${CMAKE_CXX_DEBUG_FLAGS} -g -DDEBUG")
endif (CMAKE_BUILD_TYPE MATCHES "[A-z]*Debug")

add_subdirectory(bombs)
add_subdirectory(sea-battle)
