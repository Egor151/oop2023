cmake_minimum_required(VERSION 3.16)
project(Environment)

set(CMAKE_CXX_STANDARD 20)

add_library(Environment STATIC source/Environment.cpp)

target_include_directories(Environment PUBLIC include)

target_link_libraries(Environment PUBLIC  AI Violator Plan)