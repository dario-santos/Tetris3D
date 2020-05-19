#pragma once

#include <iostream>
using std::cerr;
using std::endl;

#include <vector>
using std::vector;

#include "../../GameEngine/Shader/Shader.hpp"

#include "../../GameEngine/Primitives/IPrimitive.hpp"

#include "../../GameEngine/Components/LightSource.hpp"
#include "../../GameEngine/Components/Renderer.hpp"

#include "../../GameEngine/Primitives/Cube.hpp"

class PhongShader : public Shader
{
private:
  Renderer* renderer = nullptr;
  vector<LightSource*> lights;

public:
  PhongShader(Renderer* renderer, vector<LightSource*> lights);

  void LoadShader(mat4 model, mat4 view, mat4 projection) override;

  IPrimitive* GetIPrimitive() override;
};
