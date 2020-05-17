/**
 * @file Cube.hpp
 *
 * @brief Cube class, defines how a cube is drawn,
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

#include "IPrimitive.hpp"
#include "../Components/Transform.hpp"

/*
 * Class: Square
 * --------------------------------
 *  Interface: Primitive
 */
class Cube : public IPrimitive
{
private:
  // Cube VAO
  static GLuint cubeVAO;
  // The vertex buffer, contains the (x,y,z) points of the circle
  static std::vector<GLfloat> verticeBuffer;
  // The id of the vertex buffer array
  static GLuint verticeBufferId;
  // The rgb color of the cube
  vec3 color;

public:
   /*
    * Function: Square
    * --------------------------------
    *  Square constructor
    *
    *  transform: The transform that will be used to calculate the vertex buffer;
    *  color: The rgb color of the primitive.
    */
    Cube(vec3 color);

    static void Init();

    /*
    * Function: Draw
    * --------------------------------
    *  Draws the primitive to the screen
    *
    *  shaderId: The shader that will be used to draw;
    *  transform: The transform that will be used to perform translations, rotations and scales.
    */
    void Draw(GLuint shaderId, mat4 model, mat4 view, mat4 projection);
    void DrawShading(GLuint shaderId, mat4 model, mat4 view, mat4 projection);

    /*
     * Function: UpdateColor
     * --------------------------------
     *  Updates the color buffer of a primitive
     *
     *  color: The new rgb color;
     */
    void UpdateColor(vec3 color);
    vec3 GetColor();
    
};
