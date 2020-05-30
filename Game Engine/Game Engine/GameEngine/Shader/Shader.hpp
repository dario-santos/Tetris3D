#pragma once

#include <glm/glm.hpp>
using glm::mat4;

#include "./GLSLProgram.hpp"
#include "../Primitives/IPrimitive.hpp"

class Shader 
{
public:
  virtual void LoadShader(mat4 model, mat4 view, mat4 projection) = 0;
  virtual IPrimitive* GetIPrimitive() = 0;
  virtual void UpdateShader(const char* texturePath) = 0;
};
