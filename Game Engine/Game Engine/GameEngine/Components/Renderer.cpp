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

void Renderer::Draw(mat4 model, mat4 view, mat4 projection)
{
  this->primitive->Draw(this->shaderId, model, view, projection);
}

void Renderer::UpdateShader(GLuint shaderId)
{
  this->shaderId = shaderId;
}
