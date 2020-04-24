/**
 * @file Square.hpp
 *
 * @brief Square class, defines how a circle is drawn,
 *   contains the vertex and color buffers.
 *
 * @author Dário Santos
 * Contact: dariovfsantos@gmail.com
 */
#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include <vector>

#include "Primitive.hpp"
#include "../Components/Transform.hpp"


/*
 * Class: Square
 * --------------------------------
 *  Interface: Primitive
 */

class Square : public Primitive
{

private:
	// The vertex buffer, contains the (x,y,z) points of the circle
	static std::vector<GLfloat> verticeBuffer;
	// The id of the vertex buffer array
	static GLuint verticeBufferId;
	// The color buffer, contains the color of each point of the circle
	std::vector<GLfloat> verticeColor = std::vector<GLfloat>(18);
	// The id of the color buffer array
	GLuint verticeColorId;

public:
	/*
	* Function: Square
	* --------------------------------
	*  Square constructor
	*
	*  transform: The transform that will be used to calculate the vertex buffer;
	*  color: The rgb color of the primitive.
	*/
	Square(Transform t, vec3 color);
	/*
	* Function: ~Square
	* --------------------------------
	*  Square destructor, frees the vertex and color buffer.
	*/
	~Square();

	static void Init();

	/*
	* Function: Draw
	* --------------------------------
	*  Draws the primitive to the screen
	*
	*  shaderId: The shader that will be used to draw;
	*  transform: The transform that will be used to perform translations, rotations and scales.
	*/
	void Draw(GLuint shaderId, Transform transform);
	/*
	 * Function: UpdateColor
	 * --------------------------------
	 *  Updates the color buffer of a primitive
	 *
	 *  color: The new rgb color;
	 */
	void UpdateColor(vec3 color);
};