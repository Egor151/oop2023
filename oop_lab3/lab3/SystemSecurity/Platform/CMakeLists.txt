cmake_minimum_required(VERSION 3.16)
project(Platform)

add_library(Platform INTERFACE)

target_include_directories(Platform INTERFACE include)

target_link_libraries(Platform INTERFACE Object Module Network Armament Sensor)