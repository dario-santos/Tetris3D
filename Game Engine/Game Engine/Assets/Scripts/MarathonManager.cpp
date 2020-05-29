#include "./MarathonManager.hpp"
#include <iostream>

MarathonManager::MarathonManager()
{
  this->player1 = new GameManager(new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f), 0);
}

void MarathonManager::Update()
{
  if (player1->isGameOver)
  {
    std::cout << "GameOver" << std::endl;
  }
  else
  {
    player1->Update();
  }
}