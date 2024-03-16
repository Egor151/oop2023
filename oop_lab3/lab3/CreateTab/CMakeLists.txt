cmake_minimum_required(VERSION 3.16)
project(CreateTab)

set(CMAKE_CXX_STANDARD 20)

add_library(CreateTab STATIC source/CreateTab.cpp)

target_include_directories(CreateTab PUBLIC include)

target_link_libraries(CreateTab PUBLIC  Plan AI Violator)