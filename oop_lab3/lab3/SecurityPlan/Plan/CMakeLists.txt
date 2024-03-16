cmake_minimum_required(VERSION 3.16)
project(Plan)

set(CMAKE_CXX_STANDARD 20)

add_library(Plan STATIC source/Plan.cpp)

target_include_directories(Plan PUBLIC include)

target_link_libraries(Plan PUBLIC Cell)