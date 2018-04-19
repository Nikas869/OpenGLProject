#include "stdafx.h"
#include "renderer.h"

const char* vertexShaderSource = "#version 330 core\n \
layout (location = 0) in vec3 inputPosition;\
layout (location = 1) in vec3 inputColor; \
out vec3 myColor; \
void main() \
{ \
gl_Position = vec4(inputPosition, 1.0f); \
myColor = inputColor; \
}";
const char* fragmentShaderSource = "#version 400 core\n \
in vec3 myColor; \
out vec4 color; \
void main() \
{ \
color = vec4(myColor, 1.0f); \
}";

Renderer::Renderer(OpenGLWrapper *openGLWrapper) : openGLWrapper_(openGLWrapper)
{
    vertexShader_ = openGLWrapper_->glCreateShader(GL_VERTEX_SHADER);
    fragmentShader_ = openGLWrapper_->glCreateShader(GL_FRAGMENT_SHADER);

    openGLWrapper_->glShaderSource(vertexShader_, 1, &vertexShaderSource, NULL);
    openGLWrapper_->glShaderSource(fragmentShader_, 1, &fragmentShaderSource, NULL);

    openGLWrapper_->glCompileShader(vertexShader_);
    openGLWrapper_->glCompileShader(fragmentShader_);

    //GLint success;
    //GLchar infoLog[512];
    //openGLWrapper_->glGetShaderiv(vertexShader_, GL_COMPILE_STATUS, &success);
    //if (!success)
    //{
    //    openGLWrapper_->glGetShaderInfoLog(vertexShader_, 512, NULL, infoLog);
    //    MessageBoxA(0, infoLog, "ERROR::SHADER::VERTEX::COMPILATION_FAILED", MB_OK);
    //}

    shaderProgram_ = openGLWrapper_->glCreateProgram();
    openGLWrapper_->glAttachShader(shaderProgram_, vertexShader_);
    openGLWrapper_->glAttachShader(shaderProgram_, fragmentShader_);

    openGLWrapper_->glBindAttribLocation(shaderProgram_, 0, "inputPosition");
    openGLWrapper_->glBindAttribLocation(shaderProgram_, 1, "inputColor");

    openGLWrapper_->glLinkProgram(shaderProgram_);

    InitializeBuffers();
}

void Renderer::Render()
{
    openGLWrapper_->Fill(0.2f, 0.4f, 0.1f, 1.0f);

    RenderBuffers();

    openGLWrapper_->Swap();
}

void Renderer::InitializeBuffers()
{
    unsigned int m_vertexBufferId, m_indexBufferId;

    // Set the number of vertices in the vertex array.
    int m_vertexCount = 18;

    // Set the number of indices in the index array.
    int m_indexCount = 3;

    GLfloat vertices[] = {
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };

    // Create the index array.
    GLuint indices[] = {
        0,
        1,
        2
    };

    openGLWrapper_->glGenVertexArrays(1, &vertexArrayId_);
    openGLWrapper_->glBindVertexArray(vertexArrayId_);

    openGLWrapper_->glGenBuffers(1, &m_vertexBufferId);
    openGLWrapper_->glGenBuffers(1, &m_indexBufferId);

    openGLWrapper_->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
    openGLWrapper_->glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    openGLWrapper_->glEnableVertexAttribArray(0);  // Vertex position.
    openGLWrapper_->glEnableVertexAttribArray(1);  // Vertex color.

    openGLWrapper_->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
    openGLWrapper_->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);

    openGLWrapper_->glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
    openGLWrapper_->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) + (3 * sizeof(GLfloat)));

    openGLWrapper_->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
    openGLWrapper_->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

void Renderer::RenderBuffers()
{
    openGLWrapper_->glUseProgram(shaderProgram_);
    openGLWrapper_->glBindVertexArray(vertexArrayId_);

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}

Renderer::~Renderer()
{
}
