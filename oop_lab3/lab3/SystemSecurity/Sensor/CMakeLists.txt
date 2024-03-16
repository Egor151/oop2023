cmake_minimum_required(VERSION 3.16)
project(Sensor)

add_library(Sensor INTERFACE)

target_include_directories(Sensor INTERFACE include)

target_link_libraries(Sensor INTERFACE Module)
target_link_libraries(Sensor INTERFACE Plan Violator)