#include "Renderer.hpp"

Renderer::Renderer(IPrimitive *primitive, GLuint shaderId , bool hasShading)
{
  this->primitive = primitive;
  this->shaderId = shaderId;
  this->hasShading = hasShading;
}

Renderer::~Renderer()
{
  this->primitive->~IPrimitive();
}

void Renderer::Draw(mat4 model, mat4 view, mat4 projection)
{
  if(hasShading)
    this->primitive->DrawShading(this->shaderId, model, view, projection);
  else
    this->primitive->Draw(this->shaderId, model, view, projection);
}

void Renderer::UpdateShader(GLuint shaderId)
{
  this->shaderId = shaderId;
}
