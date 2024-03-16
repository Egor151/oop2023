cmake_minimum_required(VERSION 3.16)
project(Optical)

set(CMAKE_CXX_STANDARD 20)

add_library(Optical STATIC source/Optical.cpp)

target_include_directories(Optical PUBLIC include)

target_link_libraries(Optical PUBLIC Sensor Violator Obstacles)