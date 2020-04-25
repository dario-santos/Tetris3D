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
 * Interface: ICamera
 * --------------------------------
 */
class ICamera
{
public:
  virtual mat4 GetView() = 0;
  
  virtual void SetView(mat4 view) = 0;
  
  virtual mat4 GetProjection() = 0;

  virtual void SetProjection(mat4 projection) = 0;

  virtual void RotateTo(vec3 degrees) = 0;

  virtual void TranslateTo(vec3 position) = 0;
};
