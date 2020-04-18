#pragma once

#include <glm/glm.hpp>
using namespace glm;

#include <string>

#include "../GameEngine/Components/GameObject.hpp"
#include "../GameEngine/Components/Script.hpp"

/*
 * Class: BrickManager
 * --------------------------------
 *   Interface: Script
 */
class BrickManager : public Script
{
  private:
    // The brick gameObject
    GameObject *brick;

  public:
    /*
    * Function: BrickManager
    * --------------------------------
    *  BrickManager constructor
    *  
    *  gameObject: The brick gameObject.
    */
    BrickManager(GameObject *brick);

    /*
    * Function: OnCollision
    * --------------------------------
    *  The OnCollision event
    * 
    *  force: The force vector;
    *  tag: the name of the gameObject that we collided with.
    */
    void OnCollision(vec3 force, std::string tag) override;
};
