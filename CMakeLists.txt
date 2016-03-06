cmake_minimum_required(VERSION 3.2)
project(stoiTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -O3")

set(SOURCE_FILES main.cpp)
add_executable(stoiTest ${SOURCE_FILES})
