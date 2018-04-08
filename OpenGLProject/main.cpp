#include <iostream>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* videoMode = glfwGetVideoMode(primaryMonitor);
    GLFWwindow* window = glfwCreateWindow(videoMode->width, videoMode->height, "OpenGL Project", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    double lastTime = glfwGetTime();
    int nbFrames = 0;

    while (!glfwWindowShouldClose(window))
    {
        // fps counter
        double currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0) {
            printf("%f ms/frame, %i fps\n", 1000.0 / double(nbFrames), nbFrames);
            nbFrames = 0;
            lastTime += 1.0;
        }

        glfwPollEvents();

        glClearColor(0.2f, 0.4f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}