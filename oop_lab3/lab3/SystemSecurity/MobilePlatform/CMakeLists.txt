cmake_minimum_required(VERSION 3.16)
project(MobilePlatform)

set(CMAKE_CXX_STANDARD 20)

add_library(MobilePlatform STATIC source/MobilePlatform.cpp)

target_include_directories(MobilePlatform PUBLIC include)
target_link_libraries(MobilePlatform PUBLIC StationaryPlatform)