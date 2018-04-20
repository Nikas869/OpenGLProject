#pragma once
class Renderer
{
public:
    Renderer(OpenGLWrapper *openGLWrapper);
    ~Renderer();

    void Render();

    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    GLfloat cameraSpeed = 0.1f;

private:
    void InitializeBuffers();
    void RenderBuffers();

    OpenGLWrapper *openGLWrapper_;

    GLuint vertexShader_;
    GLuint fragmentShader_;
    GLuint shaderProgram_;

    unsigned int vertexArrayId_;
};
