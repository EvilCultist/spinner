#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <filesystem>
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
std::string readFile(const std::string& filePath) {

    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file at " << filePath << std::endl;
        return "";
    }

    std::string temp="";
    std::string buffer="";
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
  // GLFWwindow* window = glfwCreateWindow(1200, 700, "OpenGL",
  // glfwGetPrimaryMonitor(), nullptr);

  if (!window)
    return -1;

  glfwMakeContextCurrent(window);

  glewExperimental = true;
  if (glewInit() != GLEW_OK)
    return -1;
  // printf("glewInit - %u\n", glewInit());

  float vertices[] = {0.0f, 0.5f, 0.5f, -0.5f, -0.5f, -0.5f};

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // printf("%u\n", vbo);
  // std::cout << readFile("src/shaders/triangle.vert") << std::endl;
  std::string vertexSourceString = readFile("src/shaders/triangle.vert");
  const char* vertexSource = vertexSourceString.c_str();
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);
  GLint status;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
  if( status != GL_TRUE){
      std::cerr << "vertex shader failed to compile" << std::endl;
      char buffer[512];
      glGetShaderInfoLog(vertexShader, 512, NULL, buffer);
      return -1;
  }

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);
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
