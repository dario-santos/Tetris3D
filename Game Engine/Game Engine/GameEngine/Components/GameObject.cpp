#include "GameObject.hpp"

GameObject::GameObject(Transform* transform, Renderer* renderer, string tag)
{
  this->transform = transform;
  this->renderer = renderer;
  this->tag = tag;
}

GameObject::~GameObject() 
{
  // Deletes Renderer
  if(renderer != nullptr)
  {
    delete this->renderer;
    this->renderer = nullptr;
  }
  // Delete Transform
  if(transform != nullptr)
  {
    delete this->transform;
    this->transform = nullptr;
  }
  // Delete Shader
  if (shader != nullptr)
  {
    delete this->shader;
    this->shader = nullptr;
  }

  // Delete scripts
  if(scripts.size() > 0)
  {
    for (Script* s : this->scripts)
    {
      if (s != nullptr)
      {
        delete s;
        s = nullptr;
      }
    }
    scripts.clear();
  }
}

void GameObject::AddScript(Script* script)
{
  this->scripts.push_back(script);
}

list<Script*> GameObject::GetScripts()
{
  return this->scripts;
}

void GameObject::Draw(mat4 view, mat4 projection)
{
  // If there is a renderer then draw the object
  // this allows to have game objects that are not drawn.
  // An exemple is a death zone that works solely as a trigger collider.
  if (shader != nullptr)
  {
    this->shader->LoadShader(this->transform->model, view, projection);
    return;
  }
}

bool GameObject::IsEnabled()
{
  return this->isEnabled;
}

bool GameObject::CanDestroy()
{
  return this->canDestroy;
}

void GameObject::Enable()
{
  this->isEnabled = true;
}

void GameObject::Disable()
{
  this->isEnabled = false;
}

void GameObject::Destroy()
{
  this->Disable();
  this->canDestroy = true;
}

Transform* GameObject::GetTransform()
{
  return this->transform;
}

std::string GameObject::Tag()
{
  return this->tag;
}
