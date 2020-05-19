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

#include "GameEngine/Components/Transform.hpp"

#include "GameEngine/Primitives/IPrimitive.hpp"

#include "GameEngine/Shader/Material.hpp"

/**
 * Renderer.
 */
class Renderer
{
  private:
    /** The mesh of the object: ex.: triangle, square, circle, etc. */
    IPrimitive* mesh = nullptr;
    /** The shader id */
    Material* material = nullptr;
    
  public:
    /**
     * Renderer.
     * 
     * \param primitive The renderer primitive
     * \param shaderId The shader id
     * \param hasShading If the renderer is affected by shading
     */
    Renderer(IPrimitive *primitive, Material* material);
    
    /**
     * ~Renderer.
     * 
     * Renderer desctructir
     * 
     */
    ~Renderer();
    
    void Render();

    /**
     * GetIPrimitive.
     * 
     * \return The primitive of this renderer
     */
    IPrimitive* GetIPrimitive();

    /**
     * SetMaterial.
     * 
     * Updates the shader that is being used by this renderer.
     * 
     * \param shaderId The new shaderId
     */
    void SetMaterial(Material* material);

    /**
     * GetMaterial.
     *
     * \return The material of this renderer
     */
    Material* GetMaterial();
};
