#include "LightSource.hpp"

LightSource::LightSource(vec3 ambiental, vec3 diffuse, vec3 spectral, vec4 position)
{
  this->ambiental = ambiental;
  this->diffuse = diffuse;
  this->spectral = spectral;
  this->position = position;
}
