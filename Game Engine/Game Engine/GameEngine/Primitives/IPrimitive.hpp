 /*********************************************************************
  * \file   IPrimitive.hpp
  * \brief  IPrimitive Interface, defines the interface of the primitives
  *
  * \author Dário Santos
  * \date   April 2020
 ***********************************************************************/
#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>

/**
 * IPrimitive
 */
class IPrimitive
{
public:
  /**
    * Draw
    *
    * \param shaderId The shader id that will be used
    * \param mvp The Model-View-Projection matrix
    */
  virtual void Draw(GLuint shaderId, glm::mat4 mvp) = 0;

  /**
   * UpdateColor
   *
   * \param color The new rgb color
   */
  virtual void UpdateColor(glm::vec3 color) = 0;
};
