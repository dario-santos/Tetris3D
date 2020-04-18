#pragma once

#include <GL/glew.h>

#include <irrKlang.h>
using namespace irrklang;

class AudioDevice
{
private:
  ISoundEngine* soundEngine;

public:
  AudioDevice(short volume = 100);
  
  void Play2D(const char* path, GLboolean loop = GL_FALSE);

  void SetVolume(short volume);
};
