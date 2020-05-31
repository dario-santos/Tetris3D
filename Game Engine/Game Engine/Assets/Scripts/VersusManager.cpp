#include "./VersusManager.hpp"
#include <iostream>

VersusManager::VersusManager(Canvas* p1canvas, Canvas* p2canvas, Canvas* gameoverCanvas)
{  
  this->player1 = new GameManager(new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f), 0, MarathonMenuLogic::levelCont);
  this->player2 = new GameManager(new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f), 190, MarathonMenuLogic::levelCont, Gamepad::Gamepad2);

  this->p1canvas = p1canvas;
  this->p2canvas = p2canvas;
  this->gameoverCanvas = gameoverCanvas;

  this->p1digitSprites = p1canvas->GetSprites();
  this->p2digitSprites = p2canvas->GetSprites();
  this->gameoverSprites = gameoverCanvas->GetSprites();

  this->gameoverCanvas->Disable();
}

void VersusManager::Update()
{
  if (GameManager::isPaused || gameoverHappened)
    return;

  if(player1->isGameOver)
  {
    gameoverHappened = true;
    std::cout << "Player 2 wins"<< std::endl;
    gameoverCanvas->Enable();
    gameoverSprites[0]->GetShader()->UpdateShader("Assets/Sprites/gameover/p2.png");
    return;
  }
  else if(player2->isGameOver)
  {
    gameoverHappened = true;
    std::cout << "Player 1 wins" << std::endl;
    gameoverCanvas->Enable();
    gameoverSprites[0]->GetShader()->UpdateShader("Assets/Sprites/gameover/p1.png");
    return;
  }
  else
  {
    player1->Update();
    player2->Update();
  }


  char p1scoreDigits[7];
  char p2scoreDigits[7];
  snprintf(p1scoreDigits, 7, "%06d", player1->score);
  snprintf(p2scoreDigits, 7, "%06d", player2->score);

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

      switch (p1scoreDigits[i])
      {

      case '0':
          p1digitSprites[i]->GetShader()->UpdateShader(zero);
          break;
      case '1':
          p1digitSprites[i]->GetShader()->UpdateShader(one);
          break;
      case '2':
          p1digitSprites[i]->GetShader()->UpdateShader(two);
          break;
      case '3':
          p1digitSprites[i]->GetShader()->UpdateShader(three);
          break;
      case '4':
          p1digitSprites[i]->GetShader()->UpdateShader(four);
          break;
      case '5':
          p1digitSprites[i]->GetShader()->UpdateShader(five);
          break;
      case '6':
          p1digitSprites[i]->GetShader()->UpdateShader(six);
          break;
      case '7':
          p1digitSprites[i]->GetShader()->UpdateShader(seven);
          break;
      case '8':
          p1digitSprites[i]->GetShader()->UpdateShader(eight);
          break;
      case '9':
          p1digitSprites[i]->GetShader()->UpdateShader(nine);
          break;
      }

      switch (p2scoreDigits[i])
      {

      case '0':
          p2digitSprites[i]->GetShader()->UpdateShader(zero);
          break;
      case '1':
          p2digitSprites[i]->GetShader()->UpdateShader(one);
          break;
      case '2':
          p2digitSprites[i]->GetShader()->UpdateShader(two);
          break;
      case '3':
          p2digitSprites[i]->GetShader()->UpdateShader(three);
          break;
      case '4':
          p2digitSprites[i]->GetShader()->UpdateShader(four);
          break;
      case '5':
          p2digitSprites[i]->GetShader()->UpdateShader(five);
          break;
      case '6':
          p2digitSprites[i]->GetShader()->UpdateShader(six);
          break;
      case '7':
          p2digitSprites[i]->GetShader()->UpdateShader(seven);
          break;
      case '8':
          p2digitSprites[i]->GetShader()->UpdateShader(eight);
          break;
      case '9':
          p2digitSprites[i]->GetShader()->UpdateShader(nine);
          break;
      }


  }

  char p1levelDigits[3];
  char p2levelDigits[3];
  snprintf(p1levelDigits, 3, "%02d", player1->level);
  snprintf(p2levelDigits, 3, "%02d", player2->level);

  for (int i = 0; i < 2; i++)
  {

      switch (p1levelDigits[i])
      {

      case '0':
          p1digitSprites[6 + i]->GetShader()->UpdateShader(zero);
          break;
      case '1':
          p1digitSprites[6 + i]->GetShader()->UpdateShader(one);
          break;
      case '2':
          p1digitSprites[6 + i]->GetShader()->UpdateShader(two);
          break;
      case '3':
          p1digitSprites[6 + i]->GetShader()->UpdateShader(three);
          break;
      case '4':
          p1digitSprites[6 + i]->GetShader()->UpdateShader(four);
          break;
      case '5':
          p1digitSprites[6 + i]->GetShader()->UpdateShader(five);
          break;
      case '6':
          p1digitSprites[6 + i]->GetShader()->UpdateShader(six);
          break;
      case '7':
          p1digitSprites[6 + i]->GetShader()->UpdateShader(seven);
          break;
      case '8':
          p1digitSprites[6 + i]->GetShader()->UpdateShader(eight);
          break;
      case '9':
          p1digitSprites[6 + i]->GetShader()->UpdateShader(nine);
          break;
      }

      switch (p2levelDigits[i])
      {

      case '0':
          p2digitSprites[6 + i]->GetShader()->UpdateShader(zero);
          break;
      case '1':
          p2digitSprites[6 + i]->GetShader()->UpdateShader(one);
          break;
      case '2':
          p2digitSprites[6 + i]->GetShader()->UpdateShader(two);
          break;
      case '3':
          p2digitSprites[6 + i]->GetShader()->UpdateShader(three);
          break;
      case '4':
          p2digitSprites[6 + i]->GetShader()->UpdateShader(four);
          break;
      case '5':
          p2digitSprites[6 + i]->GetShader()->UpdateShader(five);
          break;
      case '6':
          p2digitSprites[6 + i]->GetShader()->UpdateShader(six);
          break;
      case '7':
          p2digitSprites[6 + i]->GetShader()->UpdateShader(seven);
          break;
      case '8':
          p2digitSprites[6 + i]->GetShader()->UpdateShader(eight);
          break;
      case '9':
          p2digitSprites[6 + i]->GetShader()->UpdateShader(nine);
          break;
      }
  }
}
