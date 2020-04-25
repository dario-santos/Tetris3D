/*********************************************************************
 * \file   AudioDevice.hpp
 * \brief  AudioDevice class, represents a column in the game world
 *
 * \author Dário Santos
 * \date   April 2020
***********************************************************************/
#pragma once

#include <GL/glew.h>

#include <irrKlang.h>
using namespace irrklang;

/**
 * AudioDevice
 */
class AudioDevice
{
private:
  ISoundEngine* soundEngine;

public:
  /**
   * AudioDevice
   * 
   * \param volume The volume of the AudioDevice, the volume ranges from 0 to 100
   */
  AudioDevice(short volume = 100);
  
  /**
   * Play2D
   * 
   * \param path The music file path
   * \param loop The loop flag
   */
  void Play2D(const char* path, GLboolean loop = GL_FALSE);

  /**
   * SetVolume
   * 
   * \param volume The volume of the AudioDevice, the volume ranges from 0 to 100
   */
  void SetVolume(short volume);
};
