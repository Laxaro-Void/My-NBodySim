# CMakeList.txt
cmake_minimum_required(VERSION 3.12)
project(Project VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

# Packages
find_package(OpenGL REQUIRED)
# find_package(OpenCV REQUIRED)
find_package(glfw3 REQUIRED)

# Source
file(GLOB SRC "src/*.cpp")
file(GLOB COMP "src/components/*.cpp")
file(GLOB CONT "src/controller/*.cpp")
file(GLOB SHDRS "src/shaders/*.cpp")
file(GLOB SYS "src/systems/*.cpp")
file(GLOB VIEW "src/view/*.cpp")
file(GLOB IMGUI "src/imgui/*.cpp")

add_executable(Project
    src/main.cpp
    src/glad.c
    ${SRC}
    ${COMP}
    ${CONT}
    ${SHDRS}
    ${SYS}
    ${VIEW}
    ${IMGUI}
)

# Include
target_include_directories(Project
    SYSTEM PUBLIC 
    include
)

target_link_libraries(Project
    glfw
    OpenGL::GL
)
