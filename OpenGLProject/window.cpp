#include "stdafx.h"
#include "window.h"

Window::Window(HINSTANCE hInstance, WindowClass &windowClass, std::wstring title, std::int32_t weight, std::int32_t height)
{
    hWnd_ = CreateWindow(
        windowClass.GetName().c_str(),
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

HWND Window::GetHandler()
{
    return hWnd_;
}

void Window::Show(int cmdShow)
{
    ShowWindow(hWnd_, cmdShow);
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
