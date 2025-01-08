#pragma once
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <cstring>
#include <fstream>
#include <iostream>

namespace utils {
void glfwHints();
std::string readFile(const std::string &filepath);
} // namespace utils
