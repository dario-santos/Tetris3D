#pragma once

#include <GL/glew.h>

#include "../GameEngine/Components/Transform.hpp"
#include "../GameEngine/Components/GameObject.hpp"
#include "../GameEngine/Components/Renderer.hpp"

#include "../GameEngine/Primitives/Cos.hpp"

class CosFun
{
  private:
    // This is private because we don't want Ball objects
    CosFun();
    ~CosFun();

  public:

    static GameObject *AddCosFun(Transform *t, GLuint shaderId)
    {
      // Sets the primitive of the gameObject, a circle
      Primitive *p = new Cos(*t, vec3(236, 240, 241));
      GameObject *go = new GameObject(t, new Renderer(p, shaderId), "CosFun");

      return go;
    }
};
