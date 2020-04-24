/**
 * @file ICamera.hpp
 *
 * @brief The interface of the cameras
 *
 * @author Dário Santos
 * Contact: dariovfsantos@gmail.com
 */
#pragma once

#include<GL/glew.h>

#include <glm/glm.hpp>
using namespace glm;

/*
 * Interface: Camera
 * --------------------------------
 */
class ICamera
{
public:
  virtual mat4 GetProjection() = 0;

  virtual vec3 GetOrigin() = 0;
  
  virtual void SetOrigin(GLfloat x, GLfloat y, GLfloat z) = 0;

  virtual vec3 GetDimensions() = 0;

  virtual void SetDimensions(GLfloat x, GLfloat y, GLfloat z) = 0;
};
