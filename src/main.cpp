#include <GL/glew.h>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdio.h>
// #include <iostream>
// #include <thread>

void glfwHints() {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
  glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
}

// const char* readFile(const std::string& filePath) {
std::string readFile(const std::string &filePath) {

  std::ifstream file(filePath);

  if (!file.is_open()) {
    std::cerr << "Error: Could not open file at " << filePath << std::endl;
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

int main() {
  if (!glfwInit())
    return -1;

  glfwHints();

  GLFWwindow *window = glfwCreateWindow(1200, 700, "OpenGL", nullptr, nullptr);

  if (!window)
    return -1;

  glfwMakeContextCurrent(window);

  glewExperimental = true;
  if (glewInit() != GLEW_OK)
    return -1;

  float vertices[] = {0.0f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f};

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  std::string vertexSourceString = readFile("src/shaders/triangle.vert");
  const char *vertexSource = vertexSourceString.c_str();
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);
  GLint status;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) {
    char buffer[512];
    glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
    std::cout << buffer << std::endl;
    std::cerr << "vertex shader failed to compile" << std::endl;
    return -1;
  }

  std::string fragmentSourceString = readFile("src/shaders/triangle.frag");
  // std::cout << fragmentSourceString << std::endl;
  const char *fragmentSource = fragmentSourceString.c_str();
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) {
    char buffer[512];
    glGetShaderInfoLog(fragmentShader, 512, NULL, buffer);
    std::cout << buffer << std::endl;
    std::cerr << "fragment shader failed to compile" << std::endl;
    return -1;
  }

  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);

  glBindFragDataLocation(shaderProgram, 0, "outColor");
  glLinkProgram(shaderProgram);

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(posAttrib);

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }
  }

  // std::this_thread::sleep_for(std::chrono::seconds(10));

  glfwTerminate();
  return 0;
}
