#pragma once

class WindowClass
{
public:
    WindowClass(HINSTANCE hInstance, WNDPROC wndProc, std::wstring className);
    ~WindowClass();

    std::wstring GetName();

private:
    HINSTANCE hInstance_;
    std::wstring name_;

    void RegisterClass(WNDCLASSEX &windowClass);
};

