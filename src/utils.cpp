#include "utils.h"

void utils::glfwHints() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
}

// const char* readFile(const std::string& filePath) {
std::string utils::readFile(const std::string &filePath) {

  std::ifstream file(filePath);

  if (!file.is_open()) {
    std::cout << "Error: Could not open file at " << filePath << std::endl;
    return "";
  }

  std::string temp = "";
  std::string buffer = "";
  while (getline(file, temp))
    buffer += temp + '\n';
  // while (getline(vertex_s, temp))
  //     vertexSource += temp + '\n';
  file.close();
  // std::cout << buffer << std::endl;

  return buffer;
}
