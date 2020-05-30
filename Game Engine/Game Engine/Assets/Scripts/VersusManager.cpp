#include "./VersusManager.hpp"
#include <iostream>

VersusManager::VersusManager()
{  
  this->player1 = new GameManager(new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f), 0, MarathonMenuLogic::levelCont);
  this->player2 = new GameManager(new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f), 190, MarathonMenuLogic::levelCont, Gamepad::Gamepad2);
}

void VersusManager::Update()
{
  if(player1->isGameOver)
  {
    std::cout << "Player 2 wins"<< std::endl;
  }
  else if(player2->isGameOver)
  {
    std::cout << "Player 1 wins" << std::endl;
  }
  else
  {
    player1->Update();
    player2->Update();
  }
}