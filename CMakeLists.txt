cmake_minimum_required(VERSION 3.1)
project(AirForce)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp)
add_executable(AirForce ${SOURCE_FILES})