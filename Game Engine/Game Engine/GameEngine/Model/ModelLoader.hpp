#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <vector>
#include <string>

using namespace std;
using namespace glm;

class ModelLoader 
{
public:
  static bool LoadObject(const char* filename, vector<glm::vec4>& vertices, vector<glm::vec3>& normals, vector<GLushort>& elements);
};