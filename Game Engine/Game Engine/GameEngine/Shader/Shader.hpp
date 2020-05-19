#pragma once

#include <glm/glm.hpp>
using glm::mat4;

#include "./GLSLProgram.hpp"
#include "../Primitives/IPrimitive.hpp"

class Shader 
{
public:
  ~Shader()
  {
    if (shader != nullptr)
    {
      delete shader;
      shader = nullptr;
    }
  }

  virtual void LoadShader(mat4 model, mat4 view, mat4 projection) = 0;
  virtual IPrimitive* GetIPrimitive() = 0;

protected:
  GLSLProgram* shader = new GLSLProgram();
};
