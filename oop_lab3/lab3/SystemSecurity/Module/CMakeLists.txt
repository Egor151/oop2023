cmake_minimum_required(VERSION 3.16)
project(Module)

add_library(Module INTERFACE)

target_include_directories(Module INTERFACE include)
