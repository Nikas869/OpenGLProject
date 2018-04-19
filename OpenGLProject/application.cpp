#include "stdafx.h"
#include "application.h"

Application::Application(HINSTANCE hInstance, int nCmdShow) : hInstance_(hInstance), nCmdShow_(nCmdShow)
{
    window_ = 0;
    openGLWrapper_ = 0;
    renderer_ = 0;
}

bool Application::Initialize()
{
    std::wstring szWindowClass = (L"OpenGLApp");

    openGLWrapper_ = new OpenGLWrapper;
    window_ = new Window;

    if (!window_->Initialize(openGLWrapper_, hInstance_, WndProc, szWindowClass))
    {
        return false;
    }
    hWnd_ = window_->GetHandler();

    renderer_ = new Renderer(openGLWrapper_);

    return true;
}

int Application::Start()
{
    MSG msg{};
    int nbFrames = 0;
    auto lastTime = std::chrono::time_point_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now());
    while (msg.message != WM_QUIT)
    {
        // fps counter
        auto currentTime = std::chrono::time_point_cast<std::chrono::duration<float>>(std::chrono::high_resolution_clock::now());
        nbFrames++;
        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastTime).count() >= 1) {
            SetWindowText(hWnd_, (std::to_wstring(1000.0 / double(nbFrames)) + L" ms/frame, " + std::to_wstring(nbFrames) + L" fps").c_str());
            nbFrames = 0;
            lastTime += (std::chrono::seconds)1;
        }
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        renderer_->Render();
    }

    return 0;
}

LRESULT CALLBACK Application::MessageHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    default:
    {
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    }
}

Application::~Application()
{
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        break;
    }
    default:
    {
        return ApplicationHandle->MessageHandler(hWnd, message, wParam, lParam);
    }
    }

    return 0;
}