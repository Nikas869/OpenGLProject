#pragma once
#include "openglwrapper.h"

class Window
{
public:
    Window();
    ~Window();

    bool Initialize(OpenGLWrapper &glWrapper, HINSTANCE hInstance, std::wstring title);

    HWND GetHandler();
    void SetTitle(std::wstring title);

private:
    HWND hWnd_;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
