#include "GameObject.hpp"

GameObject::GameObject(Transform *transform, Renderer *renderer, string tag)
{
  this->transform = transform;
  this->renderer = renderer;
  this->tag = tag;
}

void GameObject::AddScript(Script *script)
{
  this->scripts.push_back(script);
}

list<Script *> GameObject::GetScripts()
{
  return this->scripts;
}

void GameObject::Draw(mat4 view, mat4 projection)
{
  // If there is a renderer draw the object
  // this allows to have game objects that are not drawn.
  // An exempla is a death zone that works solely as a trigger collider.
  if(renderer != nullptr)
    this->renderer->Draw(this->transform->model, view, projection);
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
