#pragma once
typedef void (APIENTRY * PFNWGLSWAPINTERVALPROC)(int);

class OpenGLWrapper
{
public:
    OpenGLWrapper();
    ~OpenGLWrapper();

    bool Initialize(HWND hWnd);

    PFNWGLSWAPINTERVALPROC wglSwapIntervalEXT;

    HDC hdc_;
private:
    bool InitializeAPI();
};

