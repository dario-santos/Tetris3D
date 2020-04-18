#include "Transform.hpp"
  
Transform::Transform(vec3 position, vec3 rotation, vec3 scale)
{
  this->position = position;
  this->rotation = rotation;
  this->scale = scale;
}
