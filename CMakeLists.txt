cmake_minimum_required(VERSION 3.26)
project(Pong)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules/")

add_subdirectory(test)

add_executable(Pong main.cpp
        src/Paddle.cpp
        include/Paddle.h)
