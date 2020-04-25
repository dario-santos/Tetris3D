#include "Time.hpp"

float Time::deltaTime = 0.0f;
float Time::lastTime = 0.0f;
float Time::time = 0.0f;

void Time::UpdateValues()
{
  Time::lastTime = Time::time;
  Time::time = glfwGetTime();
  Time::deltaTime = Time::time - Time::lastTime;
}

float Time::GetDeltaTime()
{
  return Time::deltaTime;
}

float Time::GetTime()
{
  return Time::time;
}
