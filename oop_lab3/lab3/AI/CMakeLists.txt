cmake_minimum_required(VERSION 3.16)
project(AI)

set(CMAKE_CXX_STANDARD 20)

add_library(AI STATIC source/AI.cpp)

target_include_directories(AI PUBLIC include)

target_link_libraries(AI PUBLIC Platform Plan Violator Module  Point Sensor Object StationaryPlatform MobilePlatform Optical Xray )