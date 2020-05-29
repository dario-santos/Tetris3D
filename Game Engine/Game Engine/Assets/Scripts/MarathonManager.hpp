#pragma once

#include <vector>

#include "GameEngine/Components/Script.hpp"

#include "GameEngine/Audio/AudioDevice.hpp"

#include "Assets/Scripts/GameManager.hpp"

class MarathonManager : public Script
{
private:
  GameManager* player1;

public:
  MarathonManager();

  void Update() override;
};