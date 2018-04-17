#pragma once
class OpenGLWrapper
{
public:
    OpenGLWrapper();
    ~OpenGLWrapper();

    bool Initialize(HWND hWnd);

    HDC hdc_;
};

