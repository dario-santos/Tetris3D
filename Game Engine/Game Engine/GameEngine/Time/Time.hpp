/*********************************************************************
 * \file   Time.hpp
 * \brief  Time class, calculates deltaTime, currentTime.
 *
 * \author Dário Santos
 * \date   April 2020
***********************************************************************/
#pragma once

#include <GLFW/glfw3.h>

/**
 * Time
 */
class Time
{
private:
  /** The completion time in seconds since the last frame */
  static float deltaTime;
  /** The time in seconds of the last frame */
  static float lastTime;
  /** The time at the beginning of this frame . This is the time in seconds since the start of the game. */
  static float time;

public:
  /**
   * UpdateValues
   * 
   */
  static void UpdateValues();
  
  /**
   * GetDeltaTime
   * 
   * \return The completion time in seconds since the last frame
   */
  static float GetDeltaTime();

  /**
   * GetTime
   * 
   * \return The time at the beginning of this frame . This is the time in seconds since the start of the game
   */
  static float GetTime();
};
