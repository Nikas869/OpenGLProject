#pragma once
class Application
{
public:
    Application(HINSTANCE hInstance, int nCmdShow);
    ~Application();

    int start();

private:
    HINSTANCE hInstance_;
    int nCmdShow_;
};

