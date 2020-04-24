/**
 * @file Orthographic.hpp
 *
 * @brief The Orthographic camera
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

#include "./ICamera.hpp"

/*
 * Class: Orthographic
 * --------------------------------
 */
class Orthographic : public ICamera
{
private:
  vec3 origin;
  vec3 dimensions;
  mat4 projection;

public:
  Orthographic(vec3 origin, vec3 dimensions);
  
  Orthographic(vec2 origin, vec2 dimensions);
  
  mat4 GetView();

  mat4 GetProjection();

  vec3 GetOrigin();

  void SetOrigin(GLfloat x, GLfloat y, GLfloat z = 0.0f);

  vec3 GetDimensions();

  void SetDimensions(GLfloat x, GLfloat y, GLfloat z = 0.0f);
};