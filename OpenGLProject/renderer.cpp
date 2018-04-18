#include "stdafx.h"
#include "renderer.h"


Renderer::Renderer(OpenGLWrapper *openGLWrapper) : openGLWrapper_(openGLWrapper)
{
}

void Renderer::Render()
{
    openGLWrapper_->Fill(0.2f, 0.4f, 0.1f, 1.0f);

    openGLWrapper_->Swap();
}

Renderer::~Renderer()
{
}
