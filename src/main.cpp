#include <GL/glew.h>
#include <chrono>
#include <climits>
#include <cstdint>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/trigonometric.hpp>
#include <ios>
#define GLFW_DLL
#include "shaders.h"
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utils.h>

// #define WINDOW_HEIGHT 1200
#define WINDOW_HEIGHT 1200
// #define WINDOW_WIDTH 2200
#define WINDOW_WIDTH 1200

#define acceler 0.01f  // degrees per frame per frame
#define deaccel 0.005f // degrees per frame per frame

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
      1.0f,  -1.0f, // 2 Bottom-right
      -1.0f, -1.0f, // 3 Bottom-left
      1.0f,  1.0f,  // 4 Top-right
      -1.0f, 1.0f,  // 5 Top-left
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
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

  GLuint tex;
  glGenTextures(1, &tex);

  utils::getImage("res/spinner.png", GL_TEXTURE0, tex);
  glUniform1i(glGetUniformLocation(shaderProg, "texSpinner"), 0);

  glm::mat4 trans = glm::mat4(1.0f);
  trans = glm::rotate(trans, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));

  glm::mat4 model = glm::mat4(1.0f);

  glm::mat4 view =
      glm::lookAt(glm::vec3(0.0f, 2.0f, 1.0f),  // I am at
                  glm::vec3(0.0f, 0.0f, 0.0f),  // point to be centered
                  glm::vec3(0.0f, 0.0f, 1.0f)); // up axis

  glm::mat4 proj =
      glm::perspective(glm::radians(45.0f),                   // fov
                       (WINDOW_WIDTH * 1.0f) / WINDOW_HEIGHT, // aspect ratio
                       1.0f,                                  // near plane
                       20.0f                                  // far plane
      );

  GLint uniModel = glGetUniformLocation(shaderProg, "model");
  glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
  GLint uniView = glGetUniformLocation(shaderProg, "view");
  glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
  GLint uniProg = glGetUniformLocation(shaderProg, "projection");
  glUniformMatrix4fv(uniProg, 1, GL_FALSE, glm::value_ptr(proj));

  GLint uniRot = glGetUniformLocation(shaderProg, "rotation");
  glUniformMatrix4fv(uniRot, 1, GL_FALSE, glm::value_ptr(trans));

  GLint uniTime = glGetUniformLocation(shaderProg, "time");
  auto timer = new utils::Timer();
  long double time;
  float velocity = 0.0f;

  while (!glfwWindowShouldClose(window)) {

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    time = (timer->now(1) / 10000.0);
    glUniform1f(uniTime, time);

    // if (((long long int)(time * 100000) % 10) == 0) {
    //   trans =
    //       glm::rotate(trans, glm::radians(000.1f), glm::vec3(0.0f,
    //       0.0f, 1.0f));
    //   glUniformMatrix4fv(uniRot, 1, GL_FALSE, glm::value_ptr(trans));
    // }

    trans =
        glm::rotate(trans, glm::radians(velocity), glm::vec3(0.0f, 0.0f, 1.0f));
    glUniformMatrix4fv(uniRot, 1, GL_FALSE, glm::value_ptr(trans));

    glUseProgram(shaderProg);

    glBindVertexArray(vao);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
      velocity += acceler;
      if (velocity > 180.0f) {
        velocity = 180.0f;
      }
    } else {
      velocity -= deaccel;
      if (velocity < 0) {
        velocity = 0;
      }
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
