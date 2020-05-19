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
  vec3 position = vec3(0.0f);;
  mat4 view = mat4(1.0f);
  mat4 projection = mat4(1.0f);

public:
  Perspective(GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far, vec3 eye, vec3 origin, vec3 up);
  
  mat4 GetView();

  void SetView(mat4 view);

  mat4 GetProjection();

  void SetProjection(mat4 projection);

  void Rotate(vec3 degrees);

  void Translate(vec3 translation);
};