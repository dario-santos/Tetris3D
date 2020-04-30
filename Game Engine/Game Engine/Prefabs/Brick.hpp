#pragma once

#include <GL/glew.h>

#include "../GameEngine/Components/Transform.hpp"
#include "../GameEngine/Components/GameObject.hpp"
#include "../GameEngine/Components/Renderer.hpp"

#include "../GameEngine/Primitives/Cube.hpp"


/*
 * Class: Brick
 * --------------------------------
 */
class Brick
{
  private:
    // This is private because we don't want Ball objects
    Brick();
    ~Brick();

  public:
    /*
    * Function: AddBrick
    * --------------------------------
    *  Creates Brick game objects
    *  
    *  t: The transform of the new game object;
    *  color: The brick color;
    *  shaderId: the Id of the shader.
    */
    static GameObject *AddBrick(Transform *t, vec3 color, GLuint programID)
    {
      //Sets the primitive of the gameObject, a square
      IPrimitive *p = new Cube(color);
      GameObject *go = new GameObject(t, new Renderer(p, programID), "Brick");

      return go;
    }
};
