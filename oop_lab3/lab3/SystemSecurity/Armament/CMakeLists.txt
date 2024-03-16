cmake_minimum_required(VERSION 3.16)
project(Armament)

set(CMAKE_CXX_STANDARD 20)

add_library(Armament STATIC source/Armament.cpp)

target_include_directories(Armament PUBLIC include)

target_link_libraries(Armament PUBLIC Module  Plan Violator)