/**
 * @file BallManager.hpp
 *
 * @brief Creates Ball game objects
 *
 * @author Dário Santos
 * Contact: dariovfsantos@gmail.com
 */
#pragma once

#include <GL/glew.h>

#include "../GameEngine/Components/Transform.hpp"
#include "../GameEngine/Components/GameObject.hpp"
#include "../GameEngine/Components/Renderer.hpp"

#include "../GameEngine/Primitives/Circle.hpp"

#include "../Scripts/BallManager.hpp"

/*
 * Class: Ball
 * --------------------------------
 */
class Ball
{
  private:
    // This is private because we don't want Ball objects
    Ball();
    ~Ball();

  public:
    /*
    * Function: AddBall
    * --------------------------------
    *  Creates Ball game objects
    *  
    *  t: The transform of the new game object;
    *  shaderId: the Id of the shader.
    */
    static GameObject *AddBall(Transform *t, GLuint shaderId)
    {
      // Sets the primitive of the gameObject, a circle
      Primitive *p = new Circle(*t, vec3(236, 240, 241));
      GameObject *go = new GameObject(t, new Renderer(p, shaderId), "Ball");

      // Adds the BallManager script
      go->AddScript(new BallManager(t, go));
      return go;
    }
};
