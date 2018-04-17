#include "stdafx.h"
#include "application.h"

#pragma comment(lib, "opengl32.lib")

//auto polygonMode = GL_FILL;
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

//const GLchar* vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 position;\n"
//"void main()\n"
//"{\n"
//"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
//"}\0";

//const GLchar* fragmentShaderSource = "#version 330 core\n"
//"out vec4 color;\n"
//"void main()\n"
//"{\n"
//"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//"}\n\0";

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    Application app = Application(hInstance, nCmdShow);

    if (app.Initialize())
    {
        return app.Start();
    }
}

//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
//{
//    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//    {
//        glfwSetWindowShouldClose(window, GL_TRUE);
//    }
//    else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
//    {
//        polygonMode = polygonMode == GL_LINE ? GL_FILL : GL_LINE;
//        glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
//    }
//}