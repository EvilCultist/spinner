#include "utils.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <chrono>
#include <cstddef>
#include <fstream>

utils::Timer::Timer() {
  auto start = std::chrono::high_resolution_clock::now();
}
// has some issue, returns a constant
float utils::Timer::now() {
  auto end = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::duration<float>>(end - start)
      .count();
}

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

void utils::getImage(std::string filePath, GLenum tex, GLint loc) {
  glActiveTexture(tex);
  glBindTexture(GL_TEXTURE_2D, loc);
  int width, height;
  unsigned char *image =
      SOIL_load_image(filePath.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, image);
  // settings functions
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  GLfloat textureBackground[] = {1.0f, 1.0f, 1.0f, 1.0f};
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, textureBackground);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // import texture before this
  glGenerateMipmap(GL_TEXTURE_2D);
  SOIL_free_image_data(image);
}

// void utils::removeImage(unsigned char *image) {}

// void utils::mkImage(const std::string &filepath) {
//   // wait for it
//   auto image = getImage(filepath);
//   GLuint tex;
//   glGenTextures(1, &tex);
//   glBindTexture(GL_TEXTURE_2D, tex);
//   // settings functions
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
//   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
//   GLfloat textureBackground[] = {1.0f, 0.5f, 1.0f, 0.0f};
//   glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR,
//   textureBackground); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
//   GL_NEAREST); glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
//   GL_LINEAR); GLfloat pixels[] = {0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//                       0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f};
//   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels);
//   // import texture before this
//   glGenerateMipmap(GL_TEXTURE_2D);
//   removeImage(image);
// }
