#include "stdafx.h"
#include "windowclass.h"

WindowClass::WindowClass(HINSTANCE hInstance, WNDPROC wndProc, std::wstring className) : hInstance_(hInstance), name_(className)
{
    WNDCLASSEX windowClass{};
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_OWNDC;
    windowClass.lpfnWndProc = wndProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = hInstance_;
    windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hbrBackground = NULL;
    windowClass.lpszMenuName = NULL;
    windowClass.lpszClassName = name_.c_str();
    windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClass(windowClass);
}

std::wstring WindowClass::GetName()
{
    return name_;
}

void WindowClass::RegisterClass(WNDCLASSEX &windowClass)
{
    if (!RegisterClassEx(&windowClass))
    {
        MessageBox(
            NULL,
            (L"Call to RegisterClassEx failed!"),
            (L"Error!"),
            NULL
        );

        hInstance_ = nullptr;
        name_.clear();
    }
}

WindowClass::~WindowClass()
{
    if (hInstance_)
    {
        UnregisterClass(name_.c_str(), hInstance_);
    }

    hInstance_ = nullptr;
    name_.clear();
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}

WindowClass WindowClass::GetDefaultWindowClass(HINSTANCE hInstance, std::wstring className)
{
    return WindowClass(hInstance, WndProc, className);
}