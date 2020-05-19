#pragma once

#include <GL/glew.h>

#include <vector>
using std::vector;

#include <glm/glm.hpp>
using namespace glm;

#include <string>
using std::string;

#include "../GameEngine/Components/Material.hpp"

class VBOMesh
{
private:
  GLuint faces;
  GLuint vaoHandle;

  void trimString(string& str);

  void storeVBO(vector<vec3>& points, vector<vec3>& normals, vector<GLuint>& elements);

  void generateAveragedNormals(vector<vec3>& points, vector<vec3>& normals, vector<GLuint>& faces);

public:
  Material* material;
  mat4 model = mat4(1.0f);

  vec3 color;

  VBOMesh(const char* fileName, Material* material, vec3 color = vec3(1.f, 1.f, 1.f));

  void render();

  void loadOBJ(const char* fileName);
};
