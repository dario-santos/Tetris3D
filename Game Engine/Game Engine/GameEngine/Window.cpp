#include "Window.hpp"

vec2 Window::dimensions = vec2(0.0f, 0.0f);

void Window::WindowReshapeCallback(GLFWwindow* window, int width, int height)
{
  Window::dimensions = vec2(width, height);
}

vec2 Window::GetDimensions()
{
  return Window::dimensions;
}

void Window::SetDimensions(vec2 dimensions)
{
  Window::dimensions = dimensions;
}
