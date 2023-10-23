cmake_minimum_required(VERSION 3.25)
project(MiniCraft)

set(CMAKE_CXX_STANDARD 20)

find_package(glfw3 CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.hpp src/**/*.cpp src/**/*.hpp)

add_executable(MiniCraft ${SOURCES})
target_link_libraries(MiniCraft PRIVATE glfw)
