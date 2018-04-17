#pragma once
class Application
{
public:
    Application(HINSTANCE hInstance, int nCmdShow);
    ~Application();

    bool Initialize();
    int Start();

private:
    OpenGLWrapper openGLWrapper_;
    Window window_;
    HINSTANCE hInstance_;
    HWND hWnd_;
    int nCmdShow_;
};
