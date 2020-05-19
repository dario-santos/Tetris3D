#include "Material.hpp"

Material::Material(vec3 ambiental, vec3 diffuse, vec3 spectral, float shininess)
{
  this->ambiental = ambiental;
  this->diffuse   = diffuse;
  this->spectral  = spectral;
  this->shininess = shininess;
}
