#include "Transform.hpp"
  
Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
  this->position = position;
  this->rotation = rotation;
  this->scale = scale;

  // Rotation
  this->model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
  this->model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
  this->model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));

  //Translate
  this->model = glm::translate(model, position);
  // Scale
  this->model = glm::scale(model, scale);
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
  // Put model in the center of the world
  this->model = glm::translate(model, -this->position);
  // Translates to the desired position
  this->model = glm::translate(model, position);
  this->position = position;
}

void Transform::Scale(glm::vec3 scale)
{
  this->model = glm::scale(this->model, scale);

  this->scale.x = this->model[0].x;
  this->scale.y = this->model[1].y;
  this->scale.z = this->model[2].z;
}
