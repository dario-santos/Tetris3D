#pragma once

#include <vector>

#include "GameEngine/Components/Script.hpp"

#include "GameEngine/Audio/AudioDevice.hpp"

#include "Assets/Scripts/GameManager.hpp"

#include "MarathonMenuLogic.hpp"

class VersusManager : public Script
{
private:
  GameManager* player1;
  GameManager* player2;

public:
  VersusManager();

  void Update() override;
};