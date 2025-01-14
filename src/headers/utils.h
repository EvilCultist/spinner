#pragma once
#include <chrono>
#include <string>
#define GLFW_DLL
#include <GL/glew.h>
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
void getImage(std::string filePath, GLenum tex, GLint loc);
// void removeImage(unsigned char *image);
// void mkImage(const std::string &filepath);
} // namespace utils
