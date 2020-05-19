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
using glm::vec3;
using glm::mat4;

/**
 * Transform.
 */
class Transform
{   
  public:
    /** Position (x, y, z), represents a position in the game world */
    vec3 position = vec3(0.0f);
    /** Rotation (x, y, z), in degrees, represents the rotation of a game object */
    vec3 rotation = vec3(0.0f);
    /** Scale (x, y, z), the size of a game object */
    vec3 scale = vec3(1.0f);
    /** The object model */
    mat4 model = mat4(1.0f);

    /**
     * Transform.
     * 
     * \param position The position in the game world
     * \param rotation The rotation of the game object
     * \param scale The size of the game object
     */
    Transform(vec3 position, vec3 rotation, vec3 scale);
    
    /**
     * Translate.
     *
     * Translates the model by a vector
     *  
     * \param translation The translation vector
     */
    void Translate(vec3 translation);

    /**
     * TranslateTo.
     * 
     * Translates the model by to a certain position
     * 
     * \param position The new position of the model
     */
    void TranslateTo(vec3 position);

    /**
     * Rotate.
     * 
     * Rotates the model
     * 
     * \param rotation The rotation vector
     */
    void Rotate(vec3 rotation);

    /**
     * Scale.
     * 
     * \param scale The ammount of scale that will be done
     */
    void Scale(vec3 scale);
};
