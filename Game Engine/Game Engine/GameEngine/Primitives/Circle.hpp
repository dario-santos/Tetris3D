/*********************************************************************
  * \file   Circle.hpp
  * \brief  Circle class, defines how a circle is drawn,
  *   contains the vertex and color geometry
  *
  * \author Dário Santos
  * \date   April 2020
 ***********************************************************************/
#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
using namespace glm;

#include <vector>

#include "IPrimitive.hpp"

/**
 * Circle
 */
class Circle : public IPrimitive
{
private:
  /** The vertex buffer, contains the (x,y,z) points of the circle */
  static std::vector<GLfloat> verticeBuffer;
  /** The id of the vertex buffer array */
  static GLuint verticeBufferId;
  /** The color buffer, contains the color of each point of the circle */
  std::vector<GLfloat> verticeColor = std::vector<GLfloat>(180);
  /** The id of the color buffer array */
  GLuint verticeColorId;

public:
  /**
   * Circle
   *
   * \param color The rgb color
   */
  Circle(vec3 color);

  /**
   * ~Circle
   *
   */
  ~Circle();

  /**
   * Init
   *
   */
  static void Init();

  /**
   * Draw
   *
   * \param shaderId The shader id that will be used
   * \param mvp The Model-View-Projection matrix
   */
  void Draw(GLuint shaderId, mat4 mvp);

  /**
   * UpdateColor
   *
   * \param color The new rgb color
   */
  void UpdateColor(vec3 color);
};
