#pragma once

#include <iostream>
using std::cerr;
using std::endl;

#include <vector>
using std::vector;

#include "GameEngine/Shader/Shader.hpp"

#include "GameEngine/Primitives/IPrimitive.hpp"

#include "GameEngine/Components/LightSource.hpp"
#include "GameEngine/Components/Renderer.hpp"

#include "GameEngine/Texture/Texture.hpp"

#include "GameEngine/Scene.hpp"


class PhongShader : public Shader
{
private:
  Renderer* renderer = nullptr;
  static vector<LightSource*> lights;
  static GLuint texture;
  static GLSLProgram* shader;

public:
  PhongShader(Renderer* renderer);
  
  static void Init(const char* texturePath);

  void LoadShader(mat4 model, mat4 view, mat4 projection) override;

  IPrimitive* GetIPrimitive() override;

  void UpdateShader(const char* texturePath) override;
};
