#pragma once
class Application
{
public:
    Application(HINSTANCE hInstance, int nCmdShow);
    ~Application();

    bool Initialize();
    int Start();

private:
    HINSTANCE hInstance_;
    int nCmdShow_;
};

