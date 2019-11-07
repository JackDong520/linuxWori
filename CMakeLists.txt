cmake_minimum_required(VERSION 3.15)
project(linuxWori)

set(CMAKE_CXX_STANDARD 14)

add_executable(linuxWori main.cpp main.h BPlusTree.cpp BPlusTree.h Tree.h struct.h Context.h BTree.h BTree.cpp)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Wconversion")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
find_package(Threads REQUIRED)
target_link_libraries(linuxWori Threads::Threads)