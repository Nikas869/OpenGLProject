#pragma once
typedef void (APIENTRY * PFNWGLSWAPINTERVALPROC)(int);

class OpenGLWrapper
{
public:
    OpenGLWrapper();
    ~OpenGLWrapper();

    bool Initialize(HWND hWnd);

    void Fill(float red, float green, float blue, float alfa);
    void Swap();

    PFNWGLSWAPINTERVALPROC wglSwapIntervalEXT;

    HDC hdc_;
private:
    bool InitializeAPI();
};

