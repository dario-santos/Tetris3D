#include "./Perspective.hpp"

Perspective::Perspective(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far, vec3 eye, vec3 origin, vec3 up)
{
  this->projection = perspective(fov, aspect, near, far);
  this->view = lookAt(eye, origin, up);
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

