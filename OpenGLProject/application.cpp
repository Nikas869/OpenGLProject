#include "stdafx.h"
#include "application.h"

Application::Application(HINSTANCE hInstance, int nCmdShow) : hInstance_(hInstance), nCmdShow_(nCmdShow)
{
    window_ = Window();
    openGLWrapper_ = OpenGLWrapper();
}

bool Application::Initialize()
{
    // The main window class name.
    std::wstring szWindowClass = (L"OpenGLApp");

    if (!window_.Initialize(openGLWrapper_, hInstance_, WndProc, szWindowClass))
    {
        return false;
    }
    hWnd_ = window_.GetHandler();

    return true;
}

int Application::Start()
{
    openGLWrapper_.wglSwapIntervalEXT(0);

    /*int major = 0, minor = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    printf("OpenGL context created.\nVersion %d.%d\nVendor %s\nRenderer %s\n",
    major, minor,
    glGetString(GL_VENDOR),
    glGetString(GL_RENDERER));*/

    MSG msg{};
    int nbFrames = 0;
    auto lastTime = std::chrono::time_point_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now());
    while (msg.message != WM_QUIT)
    {
        // fps counter
        auto currentTime = std::chrono::time_point_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now());
        nbFrames++;
        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastTime).count() >= 1) {
            SetWindowText(hWnd_, (std::to_wstring(1000.0 / double(nbFrames)) + L" ms/frame, " + std::to_wstring(nbFrames) + L" fps").c_str());
            nbFrames = 0;
            lastTime += (std::chrono::seconds)1;
        }
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        glClearColor(0.2f, 0.4f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        SwapBuffers(openGLWrapper_.hdc_);
    }

    return 0;
    //glfwMakeContextCurrent(window);
    //glfwSetKeyCallback(window, key_callback);

    //int width, height;
    //glfwGetFramebufferSize(window, &width, &height);
    //glViewport(0, 0, width, height);

    //double lastTime = glfwGetTime();
    //int nbFrames = 0;

    //GLint success;
    //GLchar infoLog[512];

    //GLuint vertexShader;
    //vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    //glCompileShader(vertexShader);

    //glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    //if (!success)
    //{
    //    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    //    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    //}

    //GLuint fragmentShader;
    //fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    //glCompileShader(fragmentShader);

    //glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    //if (!success)
    //{
    //    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    //    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    //}

    //GLuint shaderProgram;
    //shaderProgram = glCreateProgram();

    //glAttachShader(shaderProgram, vertexShader);
    //glAttachShader(shaderProgram, fragmentShader);
    //glLinkProgram(shaderProgram);

    //glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    //if (!success) {
    //    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    //    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    //}
    //glDeleteShader(vertexShader);
    //glDeleteShader(fragmentShader);

    GLfloat triangle[] = {
        0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    //GLuint indices[] = {
    //    0, 1, 3,
    //    1, 2, 3
    //};

    //GLuint VBO, VAO, EBO;
    //glGenBuffers(1, &VBO);
    //glGenVertexArrays(1, &VAO);
    //glGenBuffers(1, &EBO);

    //glBindVertexArray(VAO);

    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    //glEnableVertexAttribArray(0);

    //glBindVertexArray(0);

    //while (!glfwWindowShouldClose(window))
    //{
    //    // fps counter
    //    double currentTime = glfwGetTime();
    //    nbFrames++;
    //    if (currentTime - lastTime >= 1.0) {
    //        printf("%f ms/frame, %i fps\n", 1000.0 / double(nbFrames), nbFrames);
    //        nbFrames = 0;
    //        lastTime += 1.0;
    //    }

    //    glfwPollEvents();

    //    glClearColor(0.2f, 0.4f, 0.1f, 1.0f);
    //    glClear(GL_COLOR_BUFFER_BIT);

    //    glUseProgram(shaderProgram);
    //    glBindVertexArray(VAO);
    //    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    //    glBindVertexArray(0);

    //    glfwSwapBuffers(window);
    //}

    //glfwTerminate();
}

LRESULT CALLBACK Application::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    default:
    {
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    }
}

Application::~Application()
{
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY | WM_KEYDOWN:
    {
        PostQuitMessage(0);
        break;
    }
    default:
    {
        return ApplicationHandle->MessageHandler(hWnd, message, wParam, lParam);
    }
    }

    return 0;
}