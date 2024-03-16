cmake_minimum_required(VERSION 3.16)
project(Cell)

set(CMAKE_CXX_STANDARD 20)

add_library(Cell STATIC source/Cell.cpp)

target_include_directories(Cell PUBLIC include)

target_link_libraries(Cell PUBLIC  Point Object )