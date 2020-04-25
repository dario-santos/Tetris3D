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
	/** The vertex buffer, contains the (x,y,z) points of the square */
	static std::vector<GLfloat> verticeBuffer;
	/** The id of the vertex buffer array */
	static GLuint verticeBufferId;
	/** The color buffer, contains the color of each point of the square */
	std::vector<GLfloat> verticeColor = std::vector<GLfloat>(18);
	/** The id of the color buffer array */
	GLuint verticeColorId;

public:
  /**
   * Square
   *
   * \param color The rgb color
   */
  Square(vec3 color);

  /**
   * ~Square
   *
   */
  ~Square();

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