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

  static GLuint verticeBufferId;
  // Cube VAO
  static GLuint cubeVAO;
  // The vertex buffer, contains the (x,y,z) points of the circle
  static std::vector<GLfloat> verticeBuffer;
  // The id of the vertex buffer array
  // The rgb color of the cube
  vec3 color = vec3(1.0f);

  static GLuint textureVBO;

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

    void Render() override;

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
