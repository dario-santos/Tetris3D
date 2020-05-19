#include "CubeTetrisManager.hpp"

CubeTetrisManager::CubeTetrisManager(vector<GameManager*> tetris)
{
  this->cam = Scene::CurrentScene()->GetCameras().front();
  this->tetris = tetris;
}

void CubeTetrisManager::MoveCamera()
{
  cam->Rotate(vec3(0.0f, delta, 0.0f));

  current += (int)delta;
  if (current >= 90 || current <= -90)
  {
    current = 0;
    canMoveCamera = false;
  }
}

void CubeTetrisManager::Update()
{
  // A camera move-se em circunferência
  // A camera para 90 em 90 graus
  if(Input::GetButton(ButtonCode::RB, Gamepad::Gamepad1) && !canMoveCamera)
  {
    canMoveCamera = true;
    delta = abs(delta);
    activeBoard = (activeBoard + 1) % tetris.size();
  }
  else if(Input::GetButton(ButtonCode::LB, Gamepad::Gamepad1) && !canMoveCamera)
  {
    canMoveCamera = true;
    delta = -abs(delta);
  }

  if(canMoveCamera)
    MoveCamera();
}
