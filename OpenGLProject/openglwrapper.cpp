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
    HGLRC hglrc = wglCreateContext(hdc_);
    wglMakeCurrent(hdc_, hglrc);

    if (!InitializeAPI())
    {
        return false;
    }

    wglSwapIntervalEXT(1);

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
    wglSwapIntervalEXT = reinterpret_cast<PFNWGLSWAPINTERVALPROC>(wglGetProcAddress("wglSwapIntervalEXT"));
    if (!wglSwapIntervalEXT)
    {
        return false;
    }

    return true;
}

OpenGLWrapper::~OpenGLWrapper()
{
}
