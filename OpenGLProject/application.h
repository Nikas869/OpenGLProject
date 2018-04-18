#pragma once
class Application
{
public:
    Application(HINSTANCE hInstance, int nCmdShow);
    ~Application();

    bool Initialize();
    int Start();
    LRESULT CALLBACK MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
    OpenGLWrapper openGLWrapper_;
    Window window_;
    HINSTANCE hInstance_;
    HWND hWnd_;
    int nCmdShow_;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static Application * ApplicationHandle = 0;