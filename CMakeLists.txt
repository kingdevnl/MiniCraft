cmake_minimum_required(VERSION 3.25)
project(MiniCraft)

set(CMAKE_CXX_STANDARD 20)


add_subdirectory(quickjs)


find_package(glfw3 CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.hpp src/**/*.cpp src/**/*.hpp)

add_executable(MiniCraft ${SOURCES})
target_include_directories(MiniCraft PRIVATE src/ quickjs/)
target_link_libraries(MiniCraft PRIVATE glfw GLEW::GLEW glm::glm spdlog::spdlog spdlog::spdlog_header_only imgui::imgui nlohmann_json::nlohmann_json quickjs)

add_custom_command(TARGET MiniCraft POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:MiniCraft>/assets)
