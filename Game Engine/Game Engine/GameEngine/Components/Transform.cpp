#include "Transform.hpp"
  
Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
  this->position = position;
  this->rotation = rotation;
  this->scale = scale;

  this->model = glm::translate(model, position);
  this->model = glm::scale(model, scale * glm::vec3(0.5f, 0.5f, 0.5f));
}

void Transform::Translate(glm::vec3 translation)
{
  this->model = glm::translate(model, translation);
  
  this->position.x = this->model[3].x;
  this->position.y = this->model[3].y;
  this->position.z = this->model[3].z;
}

void Transform::TranslateTo(glm::vec3 position)
{
  this->model = glm::translate(model, -this->position);

  this->position = position;
}
