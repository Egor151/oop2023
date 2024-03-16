cmake_minimum_required(VERSION 3.16)
project(Xray)

set(CMAKE_CXX_STANDARD 20)

add_library(Xray STATIC source/Xray.cpp)

target_include_directories(Xray PUBLIC include)

target_link_libraries(Xray PUBLIC Sensor Plan Violator)