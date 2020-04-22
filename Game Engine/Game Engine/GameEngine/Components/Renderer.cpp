#include "Renderer.hpp"

Renderer::Renderer(Primitive *primitive, GLuint shaderId)
{
  this->primitive = primitive;
  this->shaderId = shaderId;
}

Renderer::~Renderer()
{
  this->primitive->~Primitive();
}

void Renderer::Draw(Transform transform)
{
  this->primitive->Draw(this->shaderId, transform);
}

void Renderer::UpdateShader(GLuint shaderId)
{
  this->shaderId = shaderId;
}
