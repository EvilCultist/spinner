#include <GL/glew.h>
#include <chrono>
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
      0.8f,  0.8f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // Top-right
      -0.8f, 0.8f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Top-left
      0.8f,  -0.8f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // Bottom-right
      -0.8f, -0.8f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f  // Bottom-left
  };

  GLuint elements[] = {3, 2, 1, 2, 1, 0};

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

  // GLuint tex;
  // glGenTextures(1, &tex);
  // glActiveTexture(GL_TEXTURE0);
  // glBindTexture(GL_TEXTURE_2D, tex);

  GLuint tex[3];
  glGenTextures(3, tex);
  // glBindTexture(GL_TEXTURE_2D, tex);
  // auto image = utils::getImage("res/spinner.png");
  utils::getImage("res/spinner.png", GL_TEXTURE0, tex[0]);
  utils::getImage("res/mask.png", GL_TEXTURE1, tex[1]);
  utils::getImage("res/glass.png", GL_TEXTURE2, tex[2]);

  // int width, height;
  // unsigned char *image =
  //     SOIL_load_image("res/spinner.png", &width, &height, 0, SOIL_LOAD_RGBA);
  // // SOIL_load_image("sample.png", &width, &height, 0, SOIL_LOAD_RGBA);
  // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
  //              GL_UNSIGNED_BYTE, image);
  // // for (int i = 0; i <= 300; i++) {
  // //   std::cout << image[i];
  // // }
  // // std::cout << std::endl;
  // SOIL_free_image_data(image);
  glUniform1i(glGetUniformLocation(shaderProgram, "texSpinner"), 0);
  glUniform1i(glGetUniformLocation(shaderProgram, "texMask"), 1);
  glUniform1i(glGetUniformLocation(shaderProgram, "texGlass"), 2);

  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // glGenerateMipmap(GL_TEXTURE_2D);
  // auto timer = new utils::Timer();

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // GLint uniColor = glGetUniformLocation(shaderProgram, "triangleColor");

    // float time = timer->now();
    // glUniform3f(uniColor, (sin(time * 4.0f) + 1.0f) / 2.0f, 0.0f, 0.0f);

    glUseProgram(shaderProgram);

    glBindVertexArray(vao);

    // glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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

  // utils::removeImage(image);

  // std::this_thread::sleep_for(std::chrono::seconds(10));

  glfwTerminate();
  return 0;
}
