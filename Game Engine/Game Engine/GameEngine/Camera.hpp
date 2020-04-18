/**
 * @file Camera.hpp
 *
 * @brief The camera, contains the view port.
 *
 * @author Dário Santos
 * Contact: dariovfsantos@gmail.com
 */
#pragma once

#include <vector>

#include <glm/glm.hpp>
using namespace glm;

/*
 * Class: Camera
 * --------------------------------
 */
class Camera
{
  private:
    std::vector<float> dimensions;
  public:
    Camera(vec2 x, vec2 y);
    Camera(vec2 x, vec2 y, vec3 z);
    std::vector<float> GetViewPort();
    void SetViewPort(vec2 x, vec2 y);

};