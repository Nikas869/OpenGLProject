#include "stdafx.h"
#include "renderer.h"

const char* vertexShaderSource = "#version 330 core\n \
layout (location = 0) in vec3 inputPosition;\
layout (location = 1) in vec3 inputColor; \
out vec3 myColor; \
uniform mat4 model; \
uniform mat4 view; \
uniform mat4 projection; \
void main() \
{ \
gl_Position = projection * view * model * vec4(inputPosition, 1.0f); \
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

    GLint success;
    GLchar infoLog[512];
    openGLWrapper_->glGetShaderiv(vertexShader_, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        openGLWrapper_->glGetShaderInfoLog(vertexShader_, 512, NULL, infoLog);
        MessageBoxA(0, infoLog, "ERROR::SHADER::VERTEX::COMPILATION_FAILED", MB_OK);
    }

    openGLWrapper_->glGetShaderiv(fragmentShader_, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        openGLWrapper_->glGetShaderInfoLog(fragmentShader_, 512, NULL, infoLog);
        MessageBoxA(0, infoLog, "ERROR::SHADER::VERTEX::COMPILATION_FAILED", MB_OK);
    }

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

    // Set the number of indices in the index array.
    int m_indexCount = 36;

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f
    };

    // Create the index array.
    GLuint indices[] = {
        0,
        1,
        2,
        3,
        4,
        5,
        6,
        7,
        8,
        9,
        10,
        11,
        12,
        13,
        14,
        15,
        16,
        17,
        18,
        19,
        20,
        21,
        22,
        23,
        24,
        25,
        26,
        27,
        28,
        29,
        30,
        31,
        32,
        33,
        34,
        35
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
    openGLWrapper_->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

    openGLWrapper_->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
    openGLWrapper_->glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount * sizeof(GLuint), indices, GL_STATIC_DRAW);
}

void Renderer::RenderBuffers()
{
    openGLWrapper_->glUseProgram(shaderProgram_);

    glm::vec3 cubes[] = {
        glm::vec3(0.0f,   0.0f,  0.0f),
        glm::vec3(2.0f,   0.0f, -2.5f),
        glm::vec3(-2.0f,  0.2f, -2.5f)
    };

    glm::mat4 view;
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

    glm::mat4 model;
    model = glm::rotate(model, (GLfloat)std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count() * 50.0f, glm::vec3(0.5f, 1.0f, 0.0f));
    glm::mat4 projection = glm::perspective(45.0f, (float)640 / (float)480, 0.1f, 100.0f);

    GLuint modelLocation = openGLWrapper_->glGetUniformLocation(shaderProgram_, "model");
    openGLWrapper_->glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
    GLuint viewLocation = openGLWrapper_->glGetUniformLocation(shaderProgram_, "view");
    openGLWrapper_->glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
    GLuint projectionLocation = openGLWrapper_->glGetUniformLocation(shaderProgram_, "projection");
    openGLWrapper_->glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

    openGLWrapper_->glBindVertexArray(vertexArrayId_);

    for (GLuint i = 0; i < 3; i++)
    {
        glm::mat4 model;
        model = glm::translate(model, cubes[i]);
        model = glm::rotate(model, (GLfloat)std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count() * 50.0f, glm::vec3(0.5f, 1.0f, 0.0f));
        GLfloat angle = 20.0f * i;
        model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
        openGLWrapper_->glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
}

Renderer::~Renderer()
{
}
