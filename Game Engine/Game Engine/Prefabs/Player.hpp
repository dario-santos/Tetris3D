/**
 * @file Player.hpp
 *
 * @brief Creates Player game objects
 *
 * @author Dário Santos
 * Contact: dariovfsantos@gmail.com
 */
#pragma once

#include <GL/glew.h>

#include "../GameEngine/Components/Transform.hpp"
#include "../GameEngine/Components/GameObject.hpp"
#include "../GameEngine/Components/Renderer.hpp"

#include "../GameEngine/Primitives/Square.hpp"

#include "../Scripts/PlayerMovement.hpp"

/*
 * Class: DeathZone
 * --------------------------------
 */
class Player
{
  private:
    // This is private because we don't want Ball objects
    Player();
    ~Player();

  public:
    /*
    * Function: AddPlayer
    * --------------------------------
    *  Creates Player game objects
    *  
    *  t: The transform of the new game object;
    *  shaderId: the Id of the shader.
    */
    static GameObject *AddPlayer(Transform *t, GLuint shaderId)
    {
      // Sets the primitive of the gameObject, a circle
      Primitive *p = new Square(*t, vec3(245, 0, 80));
      GameObject *go = new GameObject(t, new Renderer(p, shaderId), "Player");
      
      // Adds the PlayerMovement script
      go->AddScript(new PlayerMovement(t));
      return go;
    }
};
