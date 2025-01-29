#include <GL/glew.h>
#include <chrono>
#include <climits>
#include <cstdint>
#include <ios>
#define GLFW_DLL
#include "shaders.h"
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <cmath>
#include <utils.h>

// TODO : make this one shader

// #define WINDOW_HEIGHT 1200
#define WINDOW_HEIGHT 1200
// #define WINDOW_WIDTH 2200
#define WINDOW_WIDTH 1200

int main() {
  if (!glfwInit())
    return -1;

  utils::glfwHints();

  GLFWwindow *window =
      glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGL", nullptr, nullptr);

  if (!window)
    return -1;

  glfwMakeContextCurrent(window);

  glewExperimental = true;
  if (glewInit() != GLEW_OK)
    return -1;

  float vertices[] = {
      //  Position   Color            Texcoords
      1.0f,  -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // 2 Bottom-right
      -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // 3 Bottom-left
      1.0f,  1.0f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // 4 Top-right
      -1.0f, 1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f  // 5 Top-left
  };

  GLuint elements[] = {0, 1, 2, 1, 2, 3};

  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  GLuint ebo;
  glGenBuffers(1, &ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements,
               GL_STATIC_DRAW);

  auto vertexShader =
      shaders::makeShader("src/shaders/aio.vert", GL_VERTEX_SHADER);
  auto fragmentShader =
      shaders::makeShader("src/shaders/aio.frag", GL_FRAGMENT_SHADER);

  GLuint shaderProg = glCreateProgram();
  glAttachShader(shaderProg, vertexShader);
  glAttachShader(shaderProg, fragmentShader);

  glBindFragDataLocation(shaderProg, 0, "outColor");
  glLinkProgram(shaderProg);
  glUseProgram(shaderProg);

  GLuint posAttrib = glGetAttribLocation(shaderProg, "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);

  GLuint tex;
  glGenTextures(1, &tex);

  utils::getImage("res/spinner.png", GL_TEXTURE0, tex);

  glUniform1i(glGetUniformLocation(shaderProg, "texSpinner"), 0);

  auto timer = new utils::Timer();
  long double time;

  while (!glfwWindowShouldClose(window)) {

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    time = (timer->now(1) / 10000.0);
    GLint uniTime = glGetUniformLocation(shaderProg, "time");
    glUniform1f(uniTime, time);

    glUseProgram(shaderProg);

    glBindVertexArray(vao);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }
  }

  // std::cout << time << std::endl;

  glDeleteTextures(1, &tex);

  glDeleteProgram(shaderProg);
  glDeleteProgram(fragmentShader);
  glDeleteProgram(vertexShader);

  glDeleteBuffers(1, &ebo);
  glDeleteBuffers(1, &vbo);

  glDeleteVertexArrays(1, &vao);

  // std::this_thread::sleep_for(std::chrono::seconds(10));

  glfwTerminate();
  return 0;
}
