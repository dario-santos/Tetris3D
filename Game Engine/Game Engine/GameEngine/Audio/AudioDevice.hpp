/*********************************************************************
 * \file   AudioDevice.hpp
 * \brief  AudioDevice class, represents a column in the game world
 *
 * \author Dário Santos
 * \date   May 2020
***********************************************************************/
#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>

#include <irrKlang.h>
using namespace irrklang;

/**
 * AudioDevice
 */
class AudioDevice
{
private:
  ISoundEngine* soundDevice;
  bool isPlaying = false;

public:
  /**
   * AudioDevice
   * 
   * \param volume The volume of the AudioDevice, the volume ranges from 0 to 100
   */
  AudioDevice(short volume = 100);
  
  /**
   * ~AudioDevice.
   * 
   * AudioDevice desctructor
   * 
   */
  ~AudioDevice();

  /**
   * Play2D
   * 
   * \param clipPath The path of the clip that will be played
   * \param loop The loop flag
   */
  void Play2D(const char* clipPath, GLboolean loop = GL_FALSE);

  /**
   * Play3D.
   * 
   * \param clipPath The path of the clip that will be played
   * \param position The 3-Dimensional position of the clip
   * \param loop If this clip is to be looped
   */
  void Play3D(const char* clipPath, glm::vec3 position, GLboolean loop = GL_FALSE);

  /**
   * Stop.
   * 
   * Stops all sounds being playd by this device.
   * 
   */
  void Stop();

  /**
   * SetVolume
   * 
   * \param volume The volume of the AudioDevice, the volume ranges from 0 to 100
   */
  void SetVolume(short volume);

  /**
   * IsPlaying
   *
   * Readonly property
   */
  bool IsPlaying();
};
