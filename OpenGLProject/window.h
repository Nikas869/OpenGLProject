#pragma once
#include "openglwrapper.h"

class Window
{
public:
    Window();
    ~Window();

    bool Initialize(OpenGLWrapper *glWrapper, HINSTANCE hInstance, WNDPROC wndProc, std::wstring title);

    HWND GetHandler();
    void SetTitle(std::wstring title);

private:
    HWND hWnd_;
};
