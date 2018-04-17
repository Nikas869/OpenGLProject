#include "stdafx.h"
#include "application.h"

Application::Application(HINSTANCE hInstance, int nCmdShow) : hInstance_(hInstance), nCmdShow_(nCmdShow)
{
}

bool Application::Initialize()
{
    return true;
}

int Application::Start()
{
    // The main window class name.
    std::wstring szWindowClass = (L"OpenGLApp");

    // The string that appears in the application's title bar.
    std::wstring szTitle = (L"OpenGL project");
    WindowClass windowClass = WindowClass::GetDefaultWindowClass(hInstance_, szWindowClass);
    Window window(hInstance_, windowClass, szTitle, 1280, 720);

    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
        PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
        32,                   // Colordepth of the framebuffer.
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24,                   // Number of bits for the depthbuffer
        8,                    // Number of bits for the stencilbuffer
        0,                    // Number of Aux buffers in the framebuffer.
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    HDC hdc = GetDC(window.GetHandler());
    int pixelFormat = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, pixelFormat, &pfd);

    HGLRC hglrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, hglrc);
    typedef BOOL(APIENTRY * PFNWGLSWAPINTERVALPROC)(int);
    PFNWGLSWAPINTERVALPROC wglSwapIntervalEXT = reinterpret_cast<PFNWGLSWAPINTERVALPROC>(wglGetProcAddress("wglSwapIntervalEXT"));
    wglSwapIntervalEXT(0);
    window.Show(nCmdShow_);
    UpdateWindow(window.GetHandler());

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
            window.SetTitle(std::to_wstring(1000.0 / double(nbFrames)) + L" ms/frame, " + std::to_wstring(nbFrames) + L" fps");
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
        SwapBuffers(hdc);
    }

    return 0;
    //glfwMakeContextCurrent(window);
    //glfwSetKeyCallback(window, key_callback);

    //glewExperimental = GL_TRUE;
    //if (glewInit() != GLEW_OK)
    //{
    //    std::cout << "Failed to initialize GLEW" << std::endl;
    //    return -1;
    //}

    //int width, height;
    //glfwGetFramebufferSize(window, &width, &height);
    //glViewport(0, 0, width, height);

    //glfwSwapInterval(0);

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

Application::~Application()
{
}