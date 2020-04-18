#include "Camera.hpp"  
#include <iostream>

Camera::Camera(vec2 origin, vec2 dimensions)
{
  this->dimensions.push_back(origin[0]);
  this->dimensions.push_back(origin[1]);

  this->dimensions.push_back(dimensions[0]);
  this->dimensions.push_back(dimensions[1]);
}

Camera::Camera(vec2 x, vec2 y, vec3 z)
{}

std::vector<float> Camera::GetViewPort()
{
  return dimensions;
}

void Camera::SetViewPort(vec2 origin, vec2 dimensions)
{
  this->dimensions[0] = origin[0];
  this->dimensions[1] = origin[1];

  this->dimensions[2] = dimensions[0];
  this->dimensions[3] = dimensions[1];
 }
