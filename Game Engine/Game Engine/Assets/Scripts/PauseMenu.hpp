#pragma once

#include <vector>

#include "GameEngine/UI/Canvas.hpp"

#include "GameEngine/Components/Script.hpp"

#include "GameEngine/Input/Input.hpp"

#include "GameEngine/Audio/AudioDevice.hpp"

#include "Assets/Scripts/GameManager.hpp"

class PauseMenu : public Script
{
private:
  unique_ptr<AudioDevice> audioDevice;
  Canvas* canvas;
  
  static bool isKeyPressed;

public:
  PauseMenu(Canvas* canvas);

  void Update() override;
};