#include <GL/glew.h>
#include <chrono>
#include <climits>
#include <cstdint>
#include <ios>
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <cmath>
#include <utils.h>

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
      0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // Middle-right
      -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Middle-left
      0.5f,  -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // Top-right
      -0.5f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // Top-left
      0.5f,  1.0f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // Bottom-right
      -0.5f, 1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f  // Bottom-left
  };

  GLuint elements[] = {3, 2, 1, 2, 1, 0, 5, 4, 0, 4, 0, 1};

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
  glUseProgram(shaderProgram);

  GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
  glEnableVertexAttribArray(posAttrib);
  glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);

  GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
  glEnableVertexAttribArray(colAttrib);
  glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
                        (void *)(2 * sizeof(float)));

  GLint texAttrib = glGetAttribLocation(shaderProgram, "texCord");
  glEnableVertexAttribArray(texAttrib);
  glVertexAttribPointer(texAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float),
                        (void *)(5 * sizeof(float)));

  GLuint tex[3];
  glGenTextures(3, tex);
  // glBindTexture(GL_TEXTURE_2D, tex);
  // auto image = utils::getImage("res/spinner.png");
  utils::getImage("res/spinner.png", GL_TEXTURE0, tex[0]);
  utils::getImage("res/mask.png", GL_TEXTURE1, tex[1]);
  utils::getImage("res/glass.png", GL_TEXTURE2, tex[2]);

  glUniform1i(glGetUniformLocation(shaderProgram, "texSpinner"), 0);
  glUniform1i(glGetUniformLocation(shaderProgram, "texMask"), 1);
  glUniform1i(glGetUniformLocation(shaderProgram, "texGlass"), 2);

  auto timer = new utils::Timer();

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLint uniTime = glGetUniformLocation(shaderProgram, "time");

    long double time = (timer->now(1) / 10000.0);
    // std::cout << time << std::endl;
    // glUniform3f(uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);
    glUniform1f(uniTime, time);

    glUseProgram(shaderProgram);

    glBindVertexArray(vao);

    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, &elements[0] + 6);

    glfwSwapBuffers(window);
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, GL_TRUE);
    }
  }

  glDeleteTextures(3, tex);

  glDeleteProgram(shaderProgram);
  glDeleteProgram(fragmentShader);
  glDeleteProgram(vertexShader);

  glDeleteBuffers(1, &ebo);
  glDeleteBuffers(1, &vbo);

  glDeleteVertexArrays(1, &vao);

  // std::this_thread::sleep_for(std::chrono::seconds(10));

  glfwTerminate();
  return 0;
}
