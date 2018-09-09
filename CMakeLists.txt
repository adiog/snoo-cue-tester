cmake_minimum_required(VERSION 3.0)
project(snoo-cue-tester CXX)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/abseil)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/sensor-fusion)

include_directories(source)
include_directories(deps/abseil)
include_directories(deps/udpbox/include)
include_directories(deps/sensor-fusion/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/sensor-fusion/variant/imu-kalman)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/sensor-fusion/variant/imu-static)

file(GLOB_RECURSE sources source/**.cpp)
file(GLOB_RECURSE headers source/**.h)
add_executable(snoo-cue-tester ${sources} ${headers})
target_link_libraries(snoo-cue-tester sensorFusion GL glut GLU absl_strings pthread)

add_executable(template_test test/template_test.cpp)
target_link_libraries(template_test gtest pthread)
