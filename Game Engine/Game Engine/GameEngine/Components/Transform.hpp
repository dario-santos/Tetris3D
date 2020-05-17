/*********************************************************************
 * \file   Transform.hpp
 * \brief  Transform class, represents: a point,  a rotation and a scale
 *
 * \author Dário Santos
 * \date   May 2020
***********************************************************************/
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
 * Transform.
 */
class Transform
{   
  public:
    /** Position (x, y, z), represents a position in the game world */
    glm::vec3 position;
    /** Rotation (x, y, z), in degrees, represents the rotation of a game object */
    glm::vec3 rotation;
    /** Scale (x, y, z), the size of a game object */
    glm::vec3 scale;
    /** The object model */
    glm::mat4 model = glm::mat4(1.0f);

    /**
     * Transform.
     * 
     * \param position The position in the game world
     * \param rotation The rotation of the game object
     * \param scale The size of the game object
     */
    Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    
    /**
     * Translate.
     *
     * Translates the model by a vector
     *  
     * \param translation The translation vector
     */
    void Translate(glm::vec3 translation);

    /**
     * TranslateTo.
     * 
     * Translates the model by to a certain position
     * 
     * \param position The new position of the model
     */
    void TranslateTo(glm::vec3 position);

    /**
     * Rotate.
     * 
     * Rotates the model
     * 
     * \param rotation The rotation vector
     */
    void Rotate(glm::vec3 rotation);

    /**
     * Scale.
     * 
     * \param scale The ammount of scale that will be done
     */
    void Scale(glm::vec3 scale);
};
