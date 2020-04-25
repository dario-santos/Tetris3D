#pragma once

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
using namespace glm;

#include <vector>

class Window
{
private:
  static vec2 dimensions;
  Window();
  ~Window();

public:
  static void WindowReshapeCallback(GLFWwindow* window, int width, int height);

  static vec2 GetDimensions();

  static void SetDimensions(vec2 dimensions);
};