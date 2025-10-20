# CMakeList.txt
cmake_minimum_required(VERSION 3.10)
project(Project CXX)

# Packages
find_package(OpenGL REQUIRED)
# find_package(OpenCV REQUIRED)
find_package(glfw3 REQUIRED)

# Source
file(GLOB SRC "src/*.cpp")
file(GLOB IMGUI "src/imgui/*.cpp")

add_executable(Project src/main.cpp
                       src/glad.c
                       ${SRC}
                       ${IMGUI})

# Include
target_include_directories(Project PUBLIC include)
target_link_libraries(Project glfw)


