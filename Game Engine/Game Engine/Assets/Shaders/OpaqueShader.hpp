#pragma once

#include <iostream>
using std::cerr;
using std::endl;

#include "GameEngine/Shader/Shader.hpp"

#include "GameEngine/Primitives/IPrimitive.hpp"

#include "GameEngine/Components/Renderer.hpp"

#include "GameEngine/Texture/Texture.hpp"

class OpaqueShader : public Shader
{
private:
  Renderer* renderer;
  GLuint texture;
  GLSLProgram* shader = new GLSLProgram();

public:
  OpaqueShader(Renderer* object, const char* texturePath);

  void LoadShader(mat4 model, mat4 view, mat4 projection) override;

  IPrimitive* GetIPrimitive() override;
};
