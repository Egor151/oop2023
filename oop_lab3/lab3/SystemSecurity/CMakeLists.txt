cmake_minimum_required(VERSION 3.16)

project(SystemSecurity)

add_subdirectory(Platform)
add_subdirectory(MobilePlatform)
add_subdirectory(StationaryPlatform)
add_subdirectory(Obstacles)

add_subdirectory(Module)
add_subdirectory(Armament)
add_subdirectory(Sensor)
add_subdirectory(Optical)
add_subdirectory(Xray)
add_subdirectory(Network)

