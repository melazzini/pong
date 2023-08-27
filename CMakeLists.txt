cmake_minimum_required(VERSION 3.25)
project(Pong)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules/")

find_package(SDL2 REQUIRED)

add_subdirectory(test)

add_executable(app main.cpp src/BoxDrawablePrimitiveSDL.cpp src/Renderer.cpp src/Window.cpp src/BackendContextSDL.cpp)

target_include_directories(app PRIVATE ${SDL2_INCLUDE_DIRS})

target_link_libraries(app ${SDL2_LIBRARIES})
