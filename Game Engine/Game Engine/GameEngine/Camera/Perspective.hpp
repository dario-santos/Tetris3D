/**
 * @file Perspective.hpp
 *
 * @brief The Perspective camera
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
 * Class: Perspective
 * --------------------------------
 */
class Perspective : public ICamera
{
private:
  mat4 view;
  mat4 projection;

public:
  Perspective(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far, vec3 eye, vec3 origin, vec3 up);
  
  mat4 GetView();

  void SetView(mat4 view);

  mat4 GetProjection();

  void SetProjection(mat4 projection);

  void RotateTo(vec3 degrees);

  void TranslateTo(vec3 position);
};