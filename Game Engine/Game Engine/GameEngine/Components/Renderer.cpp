#include "Renderer.hpp"

Renderer::Renderer(IPrimitive* mesh, Material* material)
{
  this->mesh = mesh;
  this->material = material;
}

Renderer::~Renderer()
{
  if(mesh != nullptr)
  {
    delete mesh;
    mesh = nullptr;
  }
  if (material != nullptr)
  {
    delete material;
    material = nullptr;
  }
}

void Renderer::Render()
{
  mesh->Render();
}

IPrimitive* Renderer::GetIPrimitive()
{
    return this->mesh;
}

Material* Renderer::GetMaterial()
{
  return this->material;
}

void Renderer::SetMaterial(Material* material)
{
  delete this->material;

  this->material = material;
}