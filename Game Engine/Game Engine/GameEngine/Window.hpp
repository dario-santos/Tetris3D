/*********************************************************************
 * \file   Window.hpp
 * \brief  Window class, represents the game window
 *
 * \author Dário Santos
 * \date   May 2020
***********************************************************************/
#pragma once

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

class Window
{
private:
  /** The dimensions of the window */
  static glm::vec2 dimensions;
  Window()  = default;
  ~Window() = default;

public:
  /**
   * GetDimensions.
   * 
   * \return The dimensions of the window
   */
  static glm::vec2 GetDimensions();

  /**
   * SetDimensions.
   * 
   * \param dimensions Changes the dimensions of the window
   */
  static void SetDimensions(glm::vec2 dimensions);
  
  /**
   * WindowReshapeCallback.
   * 
   * \param window The glfw representation of the active window
   * \param width The width of the window
   * \param height The height of the window
   */
  static void WindowReshapeCallback(GLFWwindow* window, int width, int height);
};