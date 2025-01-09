#pragma once
#include <chrono>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <iostream>

namespace utils {
class Timer {
public:
  Timer();
  float now();

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start;
};
void glfwHints();
std::string readFile(const std::string &filepath);
} // namespace utils
