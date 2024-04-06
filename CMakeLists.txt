cmake_minimum_required(VERSION 3.28)
project(GameLogiXpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(GameLogiX main.cpp
        src/game.h
        src/game.cpp
        src/helper.hpp)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(GameLogiX PRIVATE imgui::imgui)
find_package(glfw3 CONFIG REQUIRED)
target_link_libraries(GameLogiX PRIVATE glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(GameLogiX PRIVATE OpenGL::GL)
