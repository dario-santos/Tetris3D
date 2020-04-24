#include "Renderer.hpp"

Renderer::Renderer(IPrimitive *primitive, GLuint shaderId)
{
  this->primitive = primitive;
  this->shaderId = shaderId;
}

Renderer::~Renderer()
{
  this->primitive->~IPrimitive();
}

void Renderer::Draw(mat4 mvp)
{
  this->primitive->Draw(this->shaderId, mvp);
}

void Renderer::UpdateShader(GLuint shaderId)
{
  this->shaderId = shaderId;
}
