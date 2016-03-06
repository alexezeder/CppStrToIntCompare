cmake_minimum_required(VERSION 3.2)
project(sprintfTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -O3")

set(SOURCE_FILES main.cpp)
add_executable(sprintfTest ${SOURCE_FILES})
