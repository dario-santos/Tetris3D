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
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/*
 * Class: Transform
 * --------------------------------
 */
class Transform
{   
  public:
    // Position (x, y, z), represents a position in the game world.
    glm::vec3 position;
    // Rotation (x, y, z), in degrees, represents the rotation of a game object
    glm::vec3 rotation;
    // Scale (x, y, z), the size of a game object.
    glm::vec3 scale;
    // The object model
    glm::mat4 model = glm::mat4(1.0f);


    /*
    * Function: Transform
    * --------------------------------
    *  Transform constructor
    *  
    *  position: The position in the game world;
    *  rotation: The rotation of the game object;
    *  scale: The size of the game object.
    */
    Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    
    void Translate(glm::vec3 translation);

    void TranslateTo(glm::vec3 position);

    void Rotate(glm::vec3 rotation);

    void Scale(glm::vec3 scale);
};
