/**
 * @file Renderer.hpp
 *
 * @brief Renderer class, defines how a game object is drawn.
 *
 * @author Dário Santos
 * Contact: dariovfsantos@gmail.com
 */
#pragma once

#include <glm/glm.hpp>
using namespace glm;

#include "./Transform.hpp"
#include "../Primitives/IPrimitive.hpp"

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
    IPrimitive *primitive;
    // Does this objet has shading?
    bool hasShading;

  public:
    /*
    * Function: Renderer
    * --------------------------------
    *  Renderer constructor
    *  
    *  primitive: The renderer primitive;
    *  shaderId: The shader id.
    */
    Renderer(IPrimitive *primitive, GLuint shaderId, bool hasShading = true);
    
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
    void Draw(mat4 model, mat4 view, mat4 projection);

    /*
    * Function: UpdateShader
    * --------------------------------
    *  Updates the shader that is being used by this renderer.
    *  This function is used to change the shader of the renderer.
    */
    void UpdateShader(GLuint shaderId);

    IPrimitive* GetIPrimitive();
};
