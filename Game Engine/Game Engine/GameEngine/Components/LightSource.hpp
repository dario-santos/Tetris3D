#pragma once

#include <glm/glm.hpp>
using glm::vec3;
using glm::vec4;

class LightSource
{
public:
  vec3 ambiental = vec3(1.0f);
  vec3 diffuse = vec3(1.0f);
  vec3 spectral = vec3(1.0f);

  vec4 position = vec4(1.0f);

  LightSource(vec3 ambiental, vec3 diffuse, vec3 spectral, vec4 position);
};
