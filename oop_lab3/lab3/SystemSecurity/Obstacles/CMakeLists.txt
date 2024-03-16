cmake_minimum_required(VERSION 3.16)
project(Obstacles)

set(CMAKE_CXX_STANDARD 20)

add_library(Obstacles STATIC source/Obstacles.cpp)

target_include_directories(Obstacles PUBLIC include)

target_link_libraries(Obstacles PUBLIC Object)