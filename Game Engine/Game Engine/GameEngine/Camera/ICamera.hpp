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
  
  virtual mat4 GetProjection() = 0;
};
