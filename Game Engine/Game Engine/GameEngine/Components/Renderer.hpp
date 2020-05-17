/*********************************************************************
 * \file   Renderer.hpp
 * \brief  Renderer class, defines how a game object is drawn.
 *
 * \author Dário Santos
 * \date   May 2020
***********************************************************************/
#pragma once

#include <glm/glm.hpp>
using namespace glm;

#include "./Transform.hpp"

#include "../Primitives/IPrimitive.hpp"

/**
 * Renderer.
 */
class Renderer
{
  private:
    /** The shader id */
    GLuint shaderId;
    /** The primitive of the renderer: ex.: triangle, square, circle, etc. */
    IPrimitive *primitive;
    /** Does this renderer has shading? */
    bool hasShading;

  public:
    /**
     * Renderer.
     * 
     * \param primitive The renderer primitive
     * \param shaderId The shader id
     * \param hasShading If the renderer is affected by shading
     */
    Renderer(IPrimitive *primitive, GLuint shaderId, bool hasShading = true);
    
    /**
     * ~Renderer.
     * 
     * Renderer desctructir
     * 
     */
    ~Renderer();

    /**
     * Draw.
     * 
     * \param model The model matrix
     * \param view The view matrix
     * \param projection The projection matrix
     */
    void Draw(mat4 model, mat4 view, mat4 projection);

    /**
     * UpdateShader.
     * 
     * Updates the shader that is being used by this renderer.
     * 
     * \param shaderId The new shaderId
     */
    void UpdateShader(GLuint shaderId);

    /**
     * GetIPrimitive.
     * 
     * \return The primitive of this renderer
     */
    IPrimitive* GetIPrimitive();
};
