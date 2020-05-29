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
    if (player1->score > Config::highscore)
    {
      Config::highscore = player1->score;
      Config::SaveScore("score.dat");
    }
   
    std::cout << "GameOver" << std::endl;
    std::cout << "Score: " << player1->score << std::endl;
    std::cout << "HighScore: " << Config::highscore << std::endl;
  }
  else
  {
    player1->Update();
  }
}