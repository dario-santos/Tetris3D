/*********************************************************************
	 * \file   Square.hpp
	 * \brief  Square class, defines how a square is drawn,
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
 * Square
 */
class Square : public IPrimitive
{
private:
  /** The Square VAO */
  static GLuint squareVAO;
	/** The vertex buffer, contains the (x,y,z) points of the square */
	static std::vector<GLfloat> verticeBuffer;
	/** The id of the vertex buffer array */
	static GLuint verticeBufferId;
	/** The color buffer, contains the color of each point of the square */
	std::vector<GLfloat> verticeColor = std::vector<GLfloat>(18);
	/** The RGB color of the object*/
	vec3 color;

public:
  /**
   * Square
   *
   * \param color The rgb color
   */
  Square(vec3 color);

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
  void Draw(GLuint shaderId, mat4 model, mat4 view, mat4 projection);
  void DrawShading(GLuint shaderId, mat4 model, mat4 view, mat4 projection);

  /**
   * UpdateColor
   *
   * \param color The new rgb color
   */
  void UpdateColor(vec3 color);
};