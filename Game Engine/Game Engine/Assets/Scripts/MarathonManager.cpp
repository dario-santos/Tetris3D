#include "./MarathonManager.hpp"
#include <iostream>

MarathonManager::MarathonManager(Canvas* canvas, Canvas* gameoverCanvas)
{
  this->player1 = new GameManager(new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f), 0, MarathonMenuLogic::levelCont);
  this->canvas = canvas;
  this->digitSprites = canvas->GetSprites();
  this->gameoverCanvas = gameoverCanvas;

  this->gameoverCanvas->Disable();
}

void MarathonManager::Update()
{
  if (GameManager::isPaused || gameoverHappened)
      return;

  if (player1->isGameOver)
  {
    gameoverHappened = true;

    if (player1->score > Config::highscore)
    {
      Config::highscore = player1->score;
      Config::SaveScore("score.dat");
    }
    this->gameoverCanvas->Enable();
  }
  else
  {
    player1->Update();
  }

  char scoreDigits[7];
  snprintf(scoreDigits, 7, "%06d", player1->score);

  const char* zero = "Assets/Sprites/digits/zero.png";
  const char* one = "Assets/Sprites/digits/one.png";
  const char* two = "Assets/Sprites/digits/two.png";
  const char* three = "Assets/Sprites/digits/three.png";
  const char* four = "Assets/Sprites/digits/four.png";
  const char* five = "Assets/Sprites/digits/five.png";
  const char* six = "Assets/Sprites/digits/six.png";
  const char* seven = "Assets/Sprites/digits/seven.png";
  const char* eight = "Assets/Sprites/digits/eight.png";
  const char* nine = "Assets/Sprites/digits/nine.png";

  //    Logic for showing score digits
  for (int i = 0; i < 7; i++)
  {
          
      switch (scoreDigits[i])
      {

          case '0':
              digitSprites[i]->GetShader()->UpdateShader(zero);
              break;
          case '1':
              digitSprites[i]->GetShader()->UpdateShader(one);
              break;
          case '2':
              digitSprites[i]->GetShader()->UpdateShader(two);
              break;
          case '3':
              digitSprites[i]->GetShader()->UpdateShader(three);
              break;
          case '4':
              digitSprites[i]->GetShader()->UpdateShader(four);
              break;
          case '5':
              digitSprites[i]->GetShader()->UpdateShader(five);
              break;
          case '6':
              digitSprites[i]->GetShader()->UpdateShader(six);
              break;
          case '7':
              digitSprites[i]->GetShader()->UpdateShader(seven);
              break;
          case '8':
              digitSprites[i]->GetShader()->UpdateShader(eight);
              break;
          case '9':
              digitSprites[i]->GetShader()->UpdateShader(nine);
              break;
      }
      

  }

  char levelDigits[3];
  snprintf(levelDigits, 3, "%02d", player1->level);

  for (int i = 0; i < 2; i++)
  {
      
      switch (levelDigits[i])
      {
      
          case '0':
              digitSprites[6+i]->GetShader()->UpdateShader(zero);
              break;
          case '1':
              digitSprites[6+i]->GetShader()->UpdateShader(one);
              break;
          case '2':
              digitSprites[6+i]->GetShader()->UpdateShader(two);
              break;
          case '3':
              digitSprites[6+i]->GetShader()->UpdateShader(three);
              break;
          case '4':
              digitSprites[6+i]->GetShader()->UpdateShader(four);
              break;
          case '5':
              digitSprites[6+i]->GetShader()->UpdateShader(five);
              break;
          case '6':
              digitSprites[6+i]->GetShader()->UpdateShader(six);
              break;
          case '7':
              digitSprites[6+i]->GetShader()->UpdateShader(seven);
              break;
          case '8':
              digitSprites[6+i]->GetShader()->UpdateShader(eight);
              break;
          case '9':
              digitSprites[6+i]->GetShader()->UpdateShader(nine);
              break;    
      }
  }
}