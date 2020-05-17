/*********************************************************************
 * \file   Script.hpp
 * \brief  Script class, a logic unit
 *
 * \author Dário Santos
 * \date   May 2020
***********************************************************************/
#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>

#include <string>

/**
 * Script.
 */
class Script
{
  public:
    /**
     * Update.
     * 
     * The Update event
     */
    virtual void Update() {};

    /**
     * OnCollision.
     * 
     * \param force The force vector
     * \param Tag the name of the gameObject that we collided with
     */
    virtual void OnCollision(glm::vec3 force, std::string tag) {};
};
