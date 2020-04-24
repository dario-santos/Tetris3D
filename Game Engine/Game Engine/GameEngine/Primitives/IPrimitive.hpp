/**
 * @file IPrimitive.hpp
 *
 * @brief IPrimitive Interface, defines the interface of the primitives

 *
 * @author Dário Santos
 * Contact: dariovfsantos@gmail.com
 */
#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>

/*
 * Interface: IPrimitive
 * --------------------------------
 */
class IPrimitive
{   
  public:
    /*
    * Function: Draw
    * --------------------------------
    *  Draws the primitive to the screen
    *  
    *  shaderId: The shader that will be used to draw;
    *  transform: The transform that will be used to perform translations, rotations and scales.
    */
    virtual void Draw(GLuint shaderId, glm::mat4 model, glm::mat4 projection) = 0;

    /*
    * Function: UpdateColor
    * --------------------------------
    *  Updates the color buffer of a primitive
    *  
    *  color: The new rgb color;
    */ 
    virtual void UpdateColor(glm::vec3 color) = 0;
};
