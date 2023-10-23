cmake_minimum_required(VERSION 3.27)
project(MiniCraft)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.hpp src/**/*.cpp src/**/*.hpp)

add_executable(MiniCraft ${SOURCES})
