#pragma once

#include <iostream>
using std::cerr;
using std::endl;

#include "../../GameEngine/Shader/Shader.hpp"

#include "../../GameEngine/Primitives/IPrimitive.hpp"

#include "../../GameEngine/Components/Renderer.hpp"

class TransparencyShader : public Shader
{
private:
  Renderer* renderer;
  GLSLProgram* shader = new GLSLProgram();

public:
  TransparencyShader(Renderer* object);

  void LoadShader(mat4 model, mat4 view, mat4 projection) override;

  IPrimitive* GetIPrimitive() override;
};
