cmake_minimum_required(VERSION 3.22)
project(Contest_10 C)

set(CMAKE_C_STANDARD 99)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lm")

include_directories(gdb-1-task)

add_executable(Contest_10 gdb-3-task/cJSON.c gdb-3-task/task3.c)

target_link_libraries(Contest_10 m)