/**
 * @file Transform.hpp
 *
 * @brief Transform class, 
 *   Used to represent a location in the game world,
 *   the size of game object and its rotation.
 *
 * @author Dário Santos
 * Contact: dariovfsantos@gmail.com
 */
#pragma once

#include <glm/glm.hpp>
using namespace glm;

/*
 * Class: Renderer
 * --------------------------------
 */
class Transform
{   
  public:
    // Position (x, y, z), represents a position in the game world.
    vec3 position;
    // Rotation (x, y, z), in degrees, represents the rotation of a game object
    vec3 rotation;
    // Scale (x, y, z), the size of a game object.
    vec3 scale;

    /*
    * Function: Transform
    * --------------------------------
    *  Transform constructor
    *  
    *  position: The position in the game world;
    *  rotation: The rotation of the game object;
    *  scale: The size of the game object.
    */
    Transform(vec3 position, vec3 rotation, vec3 scale);
};
