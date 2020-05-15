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

void Transform::Rotate(glm::vec3 r)
{
  //this->model = glm::translate(model, -position);

  this->model = glm::rotate(this->model, glm::radians(r.x), glm::vec3(1, 0, 0));
  this->model = glm::rotate(this->model, glm::radians(r.y), glm::vec3(0, 1, 0));
  this->model = glm::rotate(this->model, glm::radians(r.z), glm::vec3(0, 0, 1));

  //this->model = glm::translate(model, position);
}

void Transform::TranslateTo(glm::vec3 position)
{
  // Put model in the center of the world
  this->model = glm::translate(this->model, -(this->position/ this->scale));

  // Translates to the desired position
  this->model = glm::translate(this->model, position/this->scale);

  this->position.x = this->model[3].x;
  this->position.y = this->model[3].y;
  this->position.z = this->model[3].z;
}

void Transform::Scale(glm::vec3 scale)
{
  this->model = glm::scale(this->model, scale);

  this->scale.x = this->model[0].x;
  this->scale.y = this->model[1].y;
  this->scale.z = this->model[2].z;
}
