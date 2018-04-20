#pragma once
class OpenGLWrapper
{
public:
    OpenGLWrapper();
    ~OpenGLWrapper();

    bool Initialize(HWND hWnd);

    void Fill(float red, float green, float blue, float alfa);
    void Swap();

    PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;
    PFNGLCREATESHADERPROC glCreateShader;
    PFNGLSHADERSOURCEPROC glShaderSource;
    PFNGLCOMPILESHADERPROC glCompileShader;
    PFNGLCREATEPROGRAMPROC glCreateProgram;
    PFNGLUSEPROGRAMPROC glUseProgram;
    PFNGLATTACHSHADERPROC glAttachShader;
    PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
    PFNGLLINKPROGRAMPROC glLinkProgram;
    PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
    PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
    PFNGLGENBUFFERSPROC glGenBuffers;
    PFNGLBINDBUFFERPROC glBindBuffer;
    PFNGLBUFFERDATAPROC glBufferData;
    PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
    PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
    PFNGLGETSHADERIVPROC glGetShaderiv;
    PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
    PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
    PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;

    HDC hdc_;
    HGLRC hglrc_;
private:
    bool InitializeAPI();
};

