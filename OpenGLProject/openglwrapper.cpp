#include "stdafx.h"
#include "openglwrapper.h"

OpenGLWrapper::OpenGLWrapper()
{
}

bool OpenGLWrapper::Initialize(HWND hWnd)
{
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

    hdc_ = GetDC(hWnd);
    int pixelFormat = ChoosePixelFormat(hdc_, &pfd);
    SetPixelFormat(hdc_, pixelFormat, &pfd);
    hglrc_ = wglCreateContext(hdc_);
    wglMakeCurrent(hdc_, hglrc_);

    if (!InitializeAPI())
    {
        return false;
    }

    wglSwapIntervalEXT(0);

    return true;
}

void OpenGLWrapper::Fill(float red, float green, float blue, float alfa)
{
    glClearColor(red, green, blue, alfa);
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLWrapper::Swap()
{
    SwapBuffers(hdc_);
}

bool OpenGLWrapper::InitializeAPI()
{
    wglSwapIntervalEXT = reinterpret_cast<PFNWGLSWAPINTERVALEXTPROC>(wglGetProcAddress("wglSwapIntervalEXT"));
    if (!wglSwapIntervalEXT)
    {
        return false;
    }

    glCreateShader = reinterpret_cast<PFNGLCREATESHADERPROC>(wglGetProcAddress("glCreateShader"));
    if (!glCreateShader)
    {
        return false;
    }

    glShaderSource = reinterpret_cast<PFNGLSHADERSOURCEPROC>(wglGetProcAddress("glShaderSource"));
    if (!glShaderSource)
    {
        return false;
    }

    glCompileShader = reinterpret_cast<PFNGLCOMPILESHADERPROC>(wglGetProcAddress("glCompileShader"));
    if (!glCompileShader)
    {
        return false;
    }

    glCreateProgram = reinterpret_cast<PFNGLCREATEPROGRAMPROC>(wglGetProcAddress("glCreateProgram"));
    if (!glCreateProgram)
    {
        return false;
    }

    glUseProgram = reinterpret_cast<PFNGLUSEPROGRAMPROC>(wglGetProcAddress("glUseProgram"));
    if (!glUseProgram)
    {
        return false;
    }

    glAttachShader = reinterpret_cast<PFNGLATTACHSHADERPROC>(wglGetProcAddress("glAttachShader"));
    if (!glAttachShader)
    {
        return false;
    }

    glBindAttribLocation = reinterpret_cast<PFNGLBINDATTRIBLOCATIONPROC>(wglGetProcAddress("glBindAttribLocation"));
    if (!glBindAttribLocation)
    {
        return false;
    }

    glLinkProgram = reinterpret_cast<PFNGLLINKPROGRAMPROC>(wglGetProcAddress("glLinkProgram"));
    if (!glLinkProgram)
    {
        return false;
    }

    glGenVertexArrays = reinterpret_cast<PFNGLGENVERTEXARRAYSPROC>(wglGetProcAddress("glGenVertexArrays"));
    if (!glGenVertexArrays)
    {
        return false;
    }

    glBindVertexArray = reinterpret_cast<PFNGLBINDVERTEXARRAYPROC>(wglGetProcAddress("glBindVertexArray"));
    if (!glBindVertexArray)
    {
        return false;
    }

    glGenBuffers = reinterpret_cast<PFNGLGENBUFFERSPROC>(wglGetProcAddress("glGenBuffers"));
    if (!glGenBuffers)
    {
        return false;
    }

    glBindBuffer = reinterpret_cast<PFNGLBINDBUFFERPROC>(wglGetProcAddress("glBindBuffer"));
    if (!glBindBuffer)
    {
        return false;
    }

    glBufferData = reinterpret_cast<PFNGLBUFFERDATAPROC>(wglGetProcAddress("glBufferData"));
    if (!glBufferData)
    {
        return false;
    }

    glEnableVertexAttribArray = reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAYPROC>(wglGetProcAddress("glEnableVertexAttribArray"));
    if (!glEnableVertexAttribArray)
    {
        return false;
    }

    glVertexAttribPointer = reinterpret_cast<PFNGLVERTEXATTRIBPOINTERPROC>(wglGetProcAddress("glVertexAttribPointer"));
    if (!glVertexAttribPointer)
    {
        return false;
    }

    glGetShaderiv = reinterpret_cast<PFNGLGETSHADERIVPROC>(wglGetProcAddress("glGetShaderiv"));
    if (!glGetShaderiv)
    {
        return false;
    }

    glGetShaderInfoLog = reinterpret_cast<PFNGLGETSHADERINFOLOGPROC>(wglGetProcAddress("glGetShaderInfoLog"));
    if (!glGetShaderInfoLog)
    {
        return false;
    }

    return true;
}

OpenGLWrapper::~OpenGLWrapper()
{
}
