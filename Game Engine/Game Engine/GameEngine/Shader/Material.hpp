#pragma once

#include <glm/glm.hpp>
using glm::vec3;

class Material 
{
public:
  vec3 ambiental = vec3(1.0f);
  vec3 diffuse = vec3(1.0f);;
  vec3 spectral = vec3(1.0f);;
  float shininess = 128.0f;

  Material(vec3 ambiental, vec3 diffuse, vec3 spectral, float shininess);
};
