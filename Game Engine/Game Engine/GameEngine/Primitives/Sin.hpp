/**
 * @file Sin.hpp
 *
 * @brief Draws the sin function.
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
 * Class: Sin
 * --------------------------------
 *  Interface: Primitive
 */
class Sin : public Primitive
{
private:
  // The vertex buffer, contains the (x,y,z) points of the function
  std::vector<GLfloat> verticeBuffer = std::vector<GLfloat>(80, 0.0f);
  // The id of the vertex buffer array
  GLuint verticeBufferId;

public:
  /*
  * Function: Sin
  * --------------------------------
  *  Sin constructor
  *
  *  transform: The transform that will be used to calculate the vertex buffer;
  *  color: The rgb color of the primitive.
  */
  Sin(Transform t, vec3 color);

  /*
  * Function: ~Sin
  * --------------------------------
  *  Sin destructor, frees the vertex and color buffer.
  */
  ~Sin();

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

