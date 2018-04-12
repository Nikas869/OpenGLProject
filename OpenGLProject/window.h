#pragma once
#include "windowclass.h"

class Window
{
public:
    Window(HINSTANCE hInstance, WindowClass &windowClass, std::wstring title, std::int32_t weight, std::int32_t height);
    ~Window();

    HWND getHandler();
    void show(int cmdShow);
    void setTitle(std::wstring title);

private:
    HWND hWnd_;
};

