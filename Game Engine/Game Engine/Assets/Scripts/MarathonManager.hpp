#pragma once

#include <vector>

#include "GameEngine/Components/Script.hpp"

#include "GameEngine/Audio/AudioDevice.hpp"

#include "Assets/Scripts/GameManager.hpp"

#include "GameEngine/UI/Canvas.hpp"
#include "GameEngine/UI/Sprite.hpp"

#include "MarathonMenuLogic.hpp"

class MarathonManager : public Script
{
private:
  GameManager* player1;
  Canvas* canvas;
  vector<Sprite*> digitSprites;

public:
  MarathonManager(Canvas* canvas);
  void Update() override;
};