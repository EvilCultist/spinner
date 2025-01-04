cmake_minimum_required(VERSION 3.20)
project(spinner)

set(CMAKE_CXX_STANDARD 20)

add_executable(spinner src/main.cpp)
add_subdirectory(glfw)
target_link_libraries(spinner glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(spinner OpenGL::GL)
