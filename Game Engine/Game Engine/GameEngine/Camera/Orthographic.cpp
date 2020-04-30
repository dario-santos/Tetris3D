#include "./Orthographic.hpp"

Orthographic::Orthographic(vec3 origin, vec3 dimensions)
{
  this->origin = origin;

  this->dimensions = dimensions;
 
  this->projection = ortho(origin[0], dimensions[0], origin[1], dimensions[1], origin[2], dimensions[2]);
}

Orthographic::Orthographic(vec2 origin, vec2 dimensions)
{
  this->origin = vec3(origin, 0.0f);

  this->dimensions = vec3(dimensions, 0.0f);

  this->projection = ortho(origin[0], dimensions[0], origin[1], dimensions[1]);
}

mat4 Orthographic::GetView()
{
  return this->view;
}

void Orthographic::SetView(mat4 view)
{
  this->view = view;
}

mat4 Orthographic::GetProjection()
{
  return projection;
}

void Orthographic::SetProjection(mat4 projection)
{
  this->projection = projection;
}

void Orthographic::Rotate(vec3 degrees)
{
  this->view = rotate(this->view, radians(degrees.x), vec3(1.0f, 0.0f, 0.0f));
  this->view = rotate(this->view, radians(degrees.y), vec3(0.0f, 1.0f, 0.0f));
  this->view = rotate(this->view, radians(degrees.z), vec3(0.0f, 0.0f, 1.0f));
}

void Orthographic::Translate(vec3 translation)
{
  this->view = translate(view, translation);
}

vec3 Orthographic::GetOrigin()
{
  return this->origin;
}

void Orthographic::SetOrigin(GLfloat x, GLfloat y, GLfloat z)
{
  this->origin = vec3(x, y, z);
}

vec3 Orthographic::GetDimensions()
{
  return this->dimensions;
}

void Orthographic::SetDimensions(GLfloat x, GLfloat y, GLfloat z)
{
  this->dimensions = vec3(x, y, z);
}
