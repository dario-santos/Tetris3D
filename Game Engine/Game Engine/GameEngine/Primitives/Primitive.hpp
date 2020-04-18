/**
 * @file Primitive.hpp
 *
 * @brief Primitive Interface, defines the interface of the primitives

 *
 * @author Dário Santos
 * Contact: dariovfsantos@gmail.com
 */
#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
using namespace glm;

#include "../Components/Transform.hpp"

/*
 * Class: GameObject
 * --------------------------------
 */
class Primitive
{
  protected:
    // The MVP matrix of the primitive
    mat4 mvp;
    
  public:
    /*
    * Function: Draw
    * --------------------------------
    *  Draws the primitive to the screen
    *  
    *  shaderId: The shader that will be used to draw;
    *  transform: The transform that will be used to perform translations, rotations and scales.
    */
    virtual void Draw(GLuint shaderId, Transform transform) = 0;

    /*
    * Function: UpdateColor
    * --------------------------------
    *  Updates the color buffer of a primitive
    *  
    *  color: The new rgb color;
    */ 
    virtual void UpdateColor(vec3 color) = 0;
};
