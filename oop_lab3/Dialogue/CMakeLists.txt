cmake_minimum_required(VERSION 3.16)
project(Dialogue)

set(CMAKE_CXX_STANDARD 20)

add_executable (Dialogue source/main.cpp)

target_include_directories(Dialogue PUBLIC lab3)

target_link_libraries(Dialogue PUBLIC  AI Plan Violator Obstacles CheckNum CreateTab)