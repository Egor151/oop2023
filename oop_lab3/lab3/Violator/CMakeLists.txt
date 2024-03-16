cmake_minimum_required(VERSION 3.16)
project(Violator)

set(CMAKE_CXX_STANDARD 20)

add_library(Violator STATIC source/Violator.cpp)

target_include_directories(Violator PUBLIC include)

target_link_libraries(Violator PUBLIC Plan)