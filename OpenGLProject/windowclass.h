#pragma once

class WindowClass
{
public:
    WindowClass(HINSTANCE hInstance, WNDPROC wndProc, std::wstring className);
    ~WindowClass();

    std::wstring getName();

    static WindowClass GetDefaultWindowClass(HINSTANCE hInstance, std::wstring className);

private:
    HINSTANCE hInstance_;
    std::wstring name_;

    void RegisterClass(WNDCLASSEX &windowClass);
};

