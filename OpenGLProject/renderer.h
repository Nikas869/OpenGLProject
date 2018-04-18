#pragma once
class Renderer
{
public:
    Renderer(OpenGLWrapper *openGLWrapper);
    ~Renderer();

    void Render();

private:
    OpenGLWrapper *openGLWrapper_;
};

