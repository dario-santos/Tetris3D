#include "Window.hpp"

glm::vec2 Window::dimensions = glm::vec2(0.0f, 0.0f);

glm::vec2 Window::GetDimensions()
{
  return Window::dimensions;
}

void Window::SetDimensions(glm::vec2 dimensions)
{
  Window::dimensions = dimensions;
}

void Window::WindowReshapeCallback(GLFWwindow* window, int width, int height)
{
  Window::dimensions = glm::vec2(width, height);
  
  glViewport(0, 0, width, height);
}
