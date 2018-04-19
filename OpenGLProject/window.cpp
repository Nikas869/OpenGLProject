#include "stdafx.h"
#include "window.h"

Window::Window()
{
}

bool Window::Initialize(OpenGLWrapper *glWrapper, HINSTANCE hInstance, WNDPROC wndProc, std::wstring title)
{
    WNDCLASSEX windowClass{};
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_OWNDC;
    windowClass.lpfnWndProc = wndProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = hInstance;
    windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hbrBackground = NULL;
    windowClass.lpszMenuName = NULL;
    windowClass.lpszClassName = title.c_str();
    windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&windowClass))
    {
        return false;
    }

    hWnd_ = CreateWindow(title.c_str(), title.c_str(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL);

    if (!hWnd_)
    {
        return false;
    }

    if (!glWrapper->Initialize(hWnd_))
    {
        return false;
    }

    ShowWindow(hWnd_, SW_SHOW);
    UpdateWindow(hWnd_);

    return true;
}

HWND Window::GetHandler()
{
    return hWnd_;
}

void Window::SetTitle(std::wstring title)
{
    SetWindowText(hWnd_, title.c_str());
}

Window::~Window()
{
    if (hWnd_)
    {
        DestroyWindow(hWnd_);
    }
}