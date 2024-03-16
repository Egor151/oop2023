cmake_minimum_required(VERSION 3.16)
project(Network)

set(CMAKE_CXX_STANDARD 20)

add_library(Network STATIC source/Network.cpp)

target_include_directories(Network PUBLIC include)

target_link_libraries(Network PUBLIC Module Platform  Point Plan Object)