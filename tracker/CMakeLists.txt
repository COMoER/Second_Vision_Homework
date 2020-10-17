cmake_minimum_required(VERSION 3.17)
project(tracker)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
find_package(Eigen3 REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(tracker main.cpp tracker.h tracker.cpp)

target_link_libraries(tracker Eigen3::Eigen)
target_link_libraries(tracker ${OpenCV_LIBS})