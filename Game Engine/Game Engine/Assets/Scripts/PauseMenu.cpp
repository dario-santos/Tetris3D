#include "./PauseMenu.hpp"

PauseMenu::PauseMenu(Canvas* canvas)
{
  this->canvas = canvas;

  GameManager::isPaused = false;
  canvas->Disable();

  audioDevice.reset(new AudioDevice(75));

  isKeyPressed = true;
}

bool PauseMenu::isKeyPressed = true;

void PauseMenu::Update() 
{
  if((Input::GetButton("Pause") || Input::GetButton("Pause", Gamepad::Gamepad2)) && !PauseMenu::isKeyPressed)
  {
    PauseMenu::isKeyPressed = true;

    GameManager::isPaused = !GameManager::isPaused;
    
    if(GameManager::isPaused)
      canvas->Enable();
    else
      canvas->Disable();
  }

  PauseMenu::isKeyPressed = Input::GetButton("Pause") || Input::GetButton("Pause", Gamepad::Gamepad2);
}
