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

AudioDevice::~AudioDevice() 
{
  if (this->soundDevice != nullptr)
  {
    delete this->soundDevice;
    soundDevice = nullptr;
  }
}

void AudioDevice::Play2D(const char* clipPath, GLboolean loop)
{
  this->soundDevice->play2D(clipPath, loop);
}

void AudioDevice::Play3D(const char* clipPath, glm::vec3 position, GLboolean loop)
{
  this->soundDevice->play3D(clipPath, irrklang::vec3df(position.x, position.y, position.z), loop);
}

void AudioDevice::Stop()
{
  this->soundDevice->stopAllSounds();
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
