#include "stdafx.h"
#include "window.h"

Window::Window(HINSTANCE hInstance, WindowClass &windowClass, std::wstring title, std::int32_t weight, std::int32_t height)
{
    hWnd_ = CreateWindow(
        windowClass.getName().c_str(),
        title.c_str(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        weight, height,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd_)
    {
        MessageBox(
            NULL,
            (L"Call to CreateWindow failed!"),
            (L"Error!"),
            NULL);

        hWnd_ = nullptr;
    }
}

HWND Window::getHandler()
{
    return hWnd_;
}

void Window::show(int cmdShow)
{
    ShowWindow(hWnd_, cmdShow);
}

void Window::setTitle(std::wstring title)
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
