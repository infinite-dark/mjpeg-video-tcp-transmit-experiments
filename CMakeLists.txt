cmake_minimum_required(VERSION 3.26)
project(CameraTransmitter)

set(CMAKE_CXX_STANDARD 11)

add_executable(CameraTransmitter main.cpp
        src/server.cpp
        src/server.h
        src/camserver.cpp
        src/camserver.h)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(CameraTransmitter ${OpenCV_LIBS})
