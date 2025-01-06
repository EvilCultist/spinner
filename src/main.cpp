#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <iostream>
// #include <iostream>
// #include <thread>

void glfwHints(){
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
}

const char* getShaderByPath(char* path){
    FILE *fp;
    long size = 0;
    char* shaderContent;

    /* Read File to get size */
    fp = fopen(path, "rb");
    if(fp == NULL) {
        return "";
    }
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp)+1;
    fclose(fp);

    /* Read File for Content */
    fp = fopen(path, "r");
    // shaderContent = memset(std::malloc(size), '\0', size);
    // fread(shaderContent, 1, size-1, fp);
    // fclose(fp);

    return shaderContent;
}



int main()
{
    if(!glfwInit()) return -1;

    glfwHints();

    GLFWwindow* window = glfwCreateWindow(1200, 700, "OpenGL", nullptr, nullptr);
    // GLFWwindow* window = glfwCreateWindow(1200, 700, "OpenGL", glfwGetPrimaryMonitor(), nullptr);

    if(!window) return -1;

    glfwMakeContextCurrent(window);

    glewExperimental = true;
    if (glewInit() != GLEW_OK) return -1;
    // printf("glewInit - %u\n", glewInit());

    float vertices[] = {
        0.0f, 0.5f,
        0.5f, -0.5f,
        -0.5f, -0.5f
    };

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // printf("%u\n", vbo);
    std::ifstream vertex_s;
    vertex_s.open("src/shaders/triangle.vert");
    if (!vertex_s.is_open()){
        std::cout << "file not open" << std::endl;
        return -1;
    }
    std::string temp;
    std::string vertexSource = "";
    while(getline(vertex_s, temp)) vertexSource += temp + '\n';
    vertex_s.close();
    printf("shader src - %s\n", vertexSource.c_str());

    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }


    // std::this_thread::sleep_for(std::chrono::seconds(10));

    glfwTerminate();
    return 0;
}
