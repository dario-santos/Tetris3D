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
  vector<Sprite*> digitSprites;

  Canvas* canvas;
  Canvas* gameoverCanvas;

  bool gameoverHappened = false;

public:
  MarathonManager(Canvas* canvas, Canvas* gameoverCanvas);
  void Update() override;
};