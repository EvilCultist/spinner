#include <GL/glew.h>
#include <chrono>
#include <ios>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <cmath>
#include <utils.h>

int main() {
  if (!glfwInit())
    return -1;

  utils::glfwHints();

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

  std::string vertexSourceString = utils::readFile("src/shaders/triangle.vert");
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

  std::string fragmentSourceString =
      utils::readFile("src/shaders/triangle.frag");
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

  auto timer = new utils::Timer();

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");

    float time = timer->now();
    glUniform3f(uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);

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
