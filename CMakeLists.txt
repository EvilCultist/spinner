cmake_minimum_required(VERSION 3.20)
project(spinner)

set(CMAKE_CXX_STANDARD 20)

add_executable(spinner src/main.cpp)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)


if(glfw3_FOUND)
    target_link_libraries(spinner glfw)
endif()

if(OpenGL_FOUND)
    target_link_libraries(spinner OpenGL::GL)
    # link_libraries(OpenGL::GL)
endif()

if(GLEW_FOUND)
    target_link_libraries(spinner GLEW::GLEW)
endif()
