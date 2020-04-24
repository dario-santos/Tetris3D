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
  return mat4(1.0f);
}

mat4 Orthographic::GetProjection()
{
  return this->projection;
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
