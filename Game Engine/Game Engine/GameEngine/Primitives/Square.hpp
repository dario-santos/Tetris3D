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

#include "GameEngine/Primitives/IPrimitive.hpp"

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
	/** The RGB color of the object*/
	vec3 color = vec3(1.0f);

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

  void Render() override;

  /**
   * UpdateColor
   *
   * \param color The new rgb color
   */
  void UpdateColor(vec3 color);

  vec3 GetColor();
};