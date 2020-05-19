#pragma once

#include <GL/glew.h>

#include <vector>
using std::vector;

#include <glm/glm.hpp>
using namespace glm;

#include <string>
using std::string;

#include "GameEngine/Shader/Material.hpp"
#include "GameEngine/Primitives/IPrimitive.hpp"

class VBOMesh : public IPrimitive
{
private:
  GLuint faces = -1;
  GLuint vaoHandle = -1;
  vec3 color = vec3(1.0f);

  void trimString(string& str);

  void storeVBO(vector<vec3>& points, vector<vec3>& normals, vector<GLuint>& elements);

  void generateAveragedNormals(vector<vec3>& points, vector<vec3>& normals, vector<GLuint>& faces);

public:

  VBOMesh(const char* fileName, vec3 color = vec3(1.f, 1.f, 1.f));

  void loadOBJ(const char* fileName);
  
  void Render() override;

  void UpdateColor(vec3 color) override;

  vec3 GetColor() override;
};
