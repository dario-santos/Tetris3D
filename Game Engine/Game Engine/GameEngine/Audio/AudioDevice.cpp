#include "AudioDevice.hpp"

AudioDevice::AudioDevice(short volume)
{
  if(volume < 0)
    volume = 0;
  else if(volume > 100)
    volume = 100;

  this->soundDevice = createIrrKlangDevice();
  this->soundDevice->setSoundVolume(volume / 100.0f);
}

void AudioDevice::Play2D(const char* path, GLboolean loop)
{
  this->soundDevice->play2D(path, loop);
}

void AudioDevice::SetVolume(short volume)
{
  if (volume < 0)
    volume = 0;
  else if (volume > 100)
    volume = 100;

  this->soundDevice->setSoundVolume(volume / 100.0f);
}

bool AudioDevice::IsPlaying() 
{
  return this->isPlaying;
}
