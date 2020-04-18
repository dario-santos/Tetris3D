#pragma once

#include <GL/glew.h>

#include "../GameEngine/Components/Transform.hpp"
#include "../GameEngine/Components/GameObject.hpp"
#include "../GameEngine/Components/Renderer.hpp"

#include "../GameEngine/Primitives/Sin.hpp"

class SinFun
{
private:
  // This is private because we don't want Ball objects
  SinFun();
  ~SinFun();

public:

  static GameObject* AddSinFun(Transform* t, GLuint shaderId)
  {
    // Sets the primitive of the gameObject, a circle
    Primitive* p = new Sin(*t, vec3(236, 240, 241));
    GameObject* go = new GameObject(t, new Renderer(p, shaderId), "SinFun");

    return go;
  }
};
