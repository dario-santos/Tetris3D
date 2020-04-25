/**
 * @file PlayerMovement.hpp
 *
 * @brief The manager of the Player object, its
 *   responsible for limiting the paddle to the screen
 *   and its movement.
 *
 * @author Dário Santos
 * Contact: dariovfsantos@gmail.com
 */
#pragma once

#include <glm/glm.hpp>
using namespace glm;

#include "../GameEngine/Components/Transform.hpp"
#include "../GameEngine/Components/Script.hpp"

#include "../GameEngine/Scene.hpp"
/*
 * Class: BrickManager
 * --------------------------------
 *   Interface: Script
 */
class PlayerMovement : public Script
{
  private:
    // Transform of the gameObject
    Transform *transform;
    // The horizontal movement speed
    float horizontalSpeed = 0.2f;
  
  public:
    /*
    * Function: PlayerMovement
    * --------------------------------
    *  PlayerMovement constructor
    *  
    *  transform: The transform of the gambeObject.
    */
    PlayerMovement(Transform *transform);

    /*
    * Function: Update
    * --------------------------------
    *  The Update event
    */
  void Update() override;
};
