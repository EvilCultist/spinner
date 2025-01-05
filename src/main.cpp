#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
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



int main()
{
    if(!glfwInit()) return -1;

    glfwHints();

    GLFWwindow* window = glfwCreateWindow(1200, 700, "OpenGL", nullptr, nullptr);
    // GLFWwindow* window = glfwCreateWindow(1200, 700, "OpenGL", glfwGetPrimaryMonitor(), nullptr);

    if(!window) return -1;

    glfwMakeContextCurrent(window);

    glewExperimental = true;
    // if (!glewInit()) return -1;
    glewInit();

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    printf("%u\n", vertexBuffer);

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
