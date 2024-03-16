cmake_minimum_required(VERSION 3.16)
project(CheckNum)

set(CMAKE_CXX_STANDARD 20)

add_library(CheckNum INTERFACE)

target_include_directories(CheckNum INTERFACE include)