#include "shaders.h"
#include "utils.h"
#include <iostream>

void shaders::checkShader(GLuint shader) {
  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) {
    char buffer[512];
    glGetShaderInfoLog(shader, 512, NULL, buffer);
    std::cout << buffer << std::endl;
    std::cerr << "vertex shader failed to compile" << std::endl;
    throw -1;
  }
}

GLuint shaders::makeShader(std::string path, GLenum type) {
  std::string vertexSourceString = utils::readFile(path);
  // std::cout << "\n---" << path << "---\n"
  //           << vertexSourceString << "\n\t---\n"
  //           << std::endl;
  const char *vertexSource = vertexSourceString.c_str();
  GLuint vertexShader = glCreateShader(type);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);
  checkShader(vertexShader);
  return vertexShader;
}

// std::string fragmentSourceString =
//     utils::readFile("src/shaders/triangle.frag");
// // std::cout << fragmentSourceString << std::endl;
// const char *fragmentSource = fragmentSourceString.c_str();
// GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
// glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
// glCompileShader(fragmentShader);
// glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
// if (status != GL_TRUE) {
//   char buffer[512];
//   glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
//   std::cout << buffer << std::endl;
//   std::cerr << "fragment shader failed to compile" << std::endl;
//   return -1;
// }

// std::string vertexSourceString =
// utils::readFile("src/shaders/triangle.vert"); const char *vertexSource =
// vertexSourceString.c_str(); GLuint vertexShader =
// glCreateShader(GL_VERTEX_SHADER); glShaderSource(vertexShader, 1,
// &vertexSource, NULL); glCompileShader(vertexShader); GLint status;
// glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
// if (status != GL_TRUE) {
//   char buffer[512];
//   glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
//   std::cout << buffer << std::endl;
//   std::cerr << "vertex shader failed to compile" << std::endl;
//   return -1;
// }
