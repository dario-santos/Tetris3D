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

  Canvas* p1canvas;
  Canvas* p2canvas;

  vector<Sprite*> p1digitSprites;
  vector<Sprite*> p2digitSprites;

public:
  VersusManager(Canvas* p1canvas, Canvas* p2canvas);

  void Update() override;
};