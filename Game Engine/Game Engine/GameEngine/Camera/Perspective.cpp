#include "./Perspective.hpp"

Perspective::Perspective(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far, vec3 eye, vec3 origin, vec3 up)
{
  this->projection = perspective(fov, aspect, near, far);
  this->view = lookAt(eye, origin, up);

  this->position.x = this->view[3].x;
  this->position.y = this->view[3].y;
  this->position.z = this->view[3].z;
}

mat4 Perspective::GetView()
{
  return this->view;
}

void Perspective::SetView(mat4 view)
{
  this->view = view;
}

mat4 Perspective::GetProjection()
{
  return this->projection;
}

void Perspective::SetProjection(mat4 projection)
{
  this->projection = projection;
}

void Perspective::Rotate(vec3 degrees)
{
  this->view = rotate(this->view, radians(degrees.x), vec3(1.0f, 0.0f, 0.0f));
  this->view = rotate(this->view, radians(degrees.y), vec3(0.0f, 1.0f, 0.0f));
  this->view = rotate(this->view, radians(degrees.z), vec3(0.0f, 0.0f, 1.0f));
}

void Perspective::Translate(vec3 translation)
{
  this->view = translate(view, translation);

  this->position.x = this->view[3].x;
  this->position.y = this->view[3].y;
  this->position.z = this->view[3].z;
}
