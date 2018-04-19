#pragma once
class Renderer
{
public:
    Renderer(OpenGLWrapper *openGLWrapper);
    ~Renderer();

    void Render();

private:
    void InitializeBuffers();
    void RenderBuffers();

    OpenGLWrapper *openGLWrapper_;

    GLuint vertexShader_;
    GLuint fragmentShader_;
    GLuint shaderProgram_;

    unsigned int vertexArrayId_;
};
