include_directories("Catch2/src")

add_executable(lab3_test  source/ViolatorTest.cpp source/CheckNumTest.cpp source/CreateTabTest.cpp source/SecurityPlanTest.cpp source/SystemSecurityTest.cpp)  # Adjust the path to Violator.cpp if necessary

#target_link_libraries(lab3_test Catch2::Catch2WithMain)
target_link_libraries(lab3_test PUBLIC Violator Plan Point Cell CheckNum CreateTab Armament MobilePlatform Module Network Obstacles Optical Platform Sensor StationaryPlatform Xray Catch2::Catch2WithMain)