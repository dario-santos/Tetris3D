/**
 * @file Renderer.hpp
 *
 * @brief Renderer class, defines how a game object is drawn.
 *
 * @author Dário Santos
 * Contact: dariovfsantos@gmail.com
 */
#pragma once

#include "./Transform.hpp"
#include "../Primitives/Primitive.hpp"

/*
 * Class: Renderer
 * --------------------------------
 */
class Renderer
{
  private:
    // The shader id
    GLuint shaderId;
    // The primitive of the renderer: ex.: triangle, square, circle, etc.
    Primitive *primitive;

  public:
    /*
    * Function: Renderer
    * --------------------------------
    *  Renderer constructor
    *  
    *  primitive: The renderer primitive;
    *  shaderId: The shader id.
    */
    Renderer(Primitive *primitive, GLuint shaderId);
    
    /*
    * Function: ~Renderer
    * --------------------------------
    *  Renderer Desctructor
    */
    ~Renderer();

    /*
    * Function: Draw
    * --------------------------------
    *  The function draw is called every frame and 
    *    its responsible for drawing the game object.
    * 
    *  transform: The transform that will be used in the draw,
    *   decides the position, scale and rotation of the object.
    */
    void Draw(Transform transform);

    /*
    * Function: UpdateShader
    * --------------------------------
    *  Updates the shader that is being used by this renderer.
    *  This function is used to change the shader of the renderer.
    */
    void UpdateShader(GLuint shaderId);
};
