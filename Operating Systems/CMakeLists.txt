cmake_minimum_required(VERSION 3.9)
project(OS)

SET(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_CXX_STANDARD 11)

add_executable(OS main.cpp)