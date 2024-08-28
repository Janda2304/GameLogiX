cmake_minimum_required(VERSION 3.28)
project(GameLogiXpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GLFW_DIR "include/GLFW")

file(GLOB IMGUI_SOURCES
        include/imgui/imgui.cpp
        include/imgui/imgui_impl_glfw.cpp
        include/imgui/imgui_impl_opengl3.cpp
        include/imgui/imgui_util.cpp
        include/imgui/imgui_tables.cpp
        include/imgui/imgui_demo.cpp
        include/imgui/imgui_widgets.cpp
        include/imgui/imgui_draw.cpp
)

add_executable(GameLogiX 
        main.cpp
        src/game.cpp
        ${IMGUI_SOURCES}
)

target_include_directories(GameLogiX PRIVATE
        include/GLFW
        include/imgui
        include/json

)

# Link GLFW
find_package(OpenGL REQUIRED)

if (WIN32)
    find_library(GLFW_LIBRARY NAMES glfw3 HINTS ${CMAKE_SOURCE_DIR}/lib)
else()
    find_package(PkgConfig REQUIRED)
    pkg_search_module(GLFW REQUIRED glfw3)
endif()

target_link_libraries(GameLogiX PRIVATE
        ${GLFW_LIBRARY}
        OpenGL::GL
        gdi32
)


#find_package(glfw3 3.3 REQUIRED)
#find_package(OpenGL REQUIRED)
#find_package(imgui REQUIRED)

#target_link_libraries(GameLogiX PRIVATE glfw OpenGL::GL imgui::imgui)
