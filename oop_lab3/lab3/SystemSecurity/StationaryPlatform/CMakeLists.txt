cmake_minimum_required(VERSION 3.16)
project(StationaryPlatform)

set(CMAKE_CXX_STANDARD 20)

add_library(StationaryPlatform STATIC source/StationaryPlatform.cpp)

target_include_directories(StationaryPlatform PUBLIC include)

target_link_libraries(StationaryPlatform PUBLIC Platform Module Plan Object)