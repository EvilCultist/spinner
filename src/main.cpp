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

  // float vertices[] = {0.0f, 0.5f,  1.0f, 0.0f,  0.0f,  0.5f, -0.5f,
  //                     0.0f, 1.0f,  0.0f, -0.5f, -0.5f, 0.0      -0.5f,
  //                     0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // Top-left
  // f, 0.0f,
  //                     1.0f, -1.0f, 0.5f, 0.0f,  0.0f,  0.0f};
  float vertices[] = {
      //  Position   Color            Texcoords
      0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 2.0f,  1.0f,  // Middle-right
      -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, -1.0f, 1.0f,  // Middle-left
      0.5f,  -1.0f, 0.0f, 0.0f, 1.0f, 2.0f,  -1.0f, // Top-right
      -0.5f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, // Top-left
      0.5f,  1.0f,  0.0f, 1.0f, 1.0f, 2.0f,  -1.0f, // Bottom-right
      -0.5f, 1.0f,  1.0f, 1.0f, 0.0f, -1.0f, -1.0f  // Bottom-left
  };

  GLuint elements[] = {3, 2, 1, 2, 1, 0, 5, 4, 1, 4, 0, 1};

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

  // auto vertexShader =
  //     shaders::makeShader("src/shaders/triangle.vert", GL_VERTEX_SHADER);
  // auto fragmentShader =
  //     shaders::makeShader("src/shaders/triangle.frag", GL_FRAGMENT_SHADER);

  // GLuint shaderProgram = glCreateProgram();
  // glAttachShader(shaderProgram, vertexShader);
  // glAttachShader(shaderProgram, fragmentShader);

  // glBindFragDataLocation(shaderProgram, 0, "outColor");
  // glLinkProgram(shaderProgram);
  // glUseProgram(shaderProgram);

  // GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  // glEnableVertexAttribArray(posAttrib);
  // glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
  // 0);

  // GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
  // glEnableVertexAttribArray(colAttrib);
  // glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
  //                       (void *)(2 * sizeof(float)));

  // GLint texAttrib = glGetAttribLocation(shaderProgram, "texCord");
  // glEnableVertexAttribArray(texAttrib);
  // glVertexAttribPointer(texAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
  //                       (void *)(5 * sizeof(float)));

  // auto vertexShaderRefl =
  //     shaders::makeShader("src/shaders/refl.vert", GL_VERTEX_SHADER);
  // auto fragmentShaderRefl =
  //     shaders::makeShader("src/shaders/refl.frag", GL_FRAGMENT_SHADER);

  // GLuint shaderProgramRefl = glCreateProgram();
  // glAttachShader(shaderProgramRefl, vertexShaderRefl);
  // glAttachShader(shaderProgramRefl, fragmentShaderRefl);

  // posAttrib = glGetAttribLocation(shaderProgramRefl, "position");
  // glEnableVertexAttribArray(posAttrib);
  // glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
  // 0);

  // colAttrib = glGetAttribLocation(shaderProgramRefl, "color");
  // glEnableVertexAttribArray(colAttrib);
  // glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
  //                       (void *)(2 * sizeof(float)));

  // texAttrib = glGetAttribLocation(shaderProgramRefl, "texCord");
  // glEnableVertexAttribArray(texAttrib);
  // glVertexAttribPointer(texAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
  //                       (void *)(5 * sizeof(float)));
  auto vertexShader =
      shaders::makeShader("src/shaders/aio.vert", GL_VERTEX_SHADER);
  auto fragmentShader =
      shaders::makeShader("src/shaders/aio.frag", GL_FRAGMENT_SHADER);

  GLuint shaderProg = glCreateProgram();
  glAttachShader(shaderProg, vertexShader);
  glAttachShader(shaderProg, fragmentShader);

  GLuint posAttrib = glGetAttribLocation(shaderProg, "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);

  GLuint colAttrib = glGetAttribLocation(shaderProg, "color");
  glEnableVertexAttribArray(colAttrib);
  glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
                        (void *)(2 * sizeof(float)));

  GLuint texAttrib = glGetAttribLocation(shaderProg, "texCord");
  glEnableVertexAttribArray(texAttrib);
  glVertexAttribPointer(texAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
                        (void *)(5 * sizeof(float)));

  glBindFragDataLocation(shaderProg, 0, "outColor");
  glLinkProgram(shaderProg);
  glUseProgram(shaderProg);

  GLuint tex[3];
  glGenTextures(3, tex);
  // glBindTexture(GL_TEXTURE_2D, tex);
  // auto image = utils::getImage("res/spinner.png");
  utils::getImage("res/spinner.png", GL_TEXTURE0, tex[0]);
  utils::getImage("res/mask.png", GL_TEXTURE1, tex[1]);
  utils::getImage("res/glass.png", GL_TEXTURE2, tex[2]);

  glUniform1i(glGetUniformLocation(shaderProg, "texSpinner"), 0);
  glUniform1i(glGetUniformLocation(shaderProg, "texMask"), 1);
  glUniform1i(glGetUniformLocation(shaderProg, "texGlass"), 2);

  // glUseProgram(shaderProgram);

  // glUniform1i(glGetUniformLocation(shaderProgram, "texSpinner"), 0);
  // glUniform1i(glGetUniformLocation(shaderProgram, "texMask"), 1);
  // glUniform1i(glGetUniformLocation(shaderProgram, "texGlass"), 2);

  auto timer = new utils::Timer();
  long double time;

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    time = (timer->now(1) / 10000.0);
    // std::cout << time << std::endl;
    // glUniform3f(uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);
    GLint uniTime = glGetUniformLocation(shaderProg, "time");
    glUniform1f(uniTime, time);

    glUseProgram(shaderProg);

    glBindVertexArray(vao);

    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,
                   (void *)(sizeof(GLuint) * 6));

    // GLint uniTimeRef = glGetUniformLocation(shaderProgramRefl, "time");
    // glUniform1f(uniTimeRef, time);

    // glUseProgram(shaderProgramRefl);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }
  }

  // std::cout << time << std::endl;

  glDeleteTextures(3, tex);

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
