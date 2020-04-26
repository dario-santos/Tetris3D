#include "CameraMovement.hpp"

CameraMovement::CameraMovement()
{
  this->cam = Scene::CurrentScene()->GetCameras().front();
}

void CameraMovement::Update()
{
  // A camera move-se em circunferência
  // A camera para 90 em 90 graus
  if(Input::GetButton(ButtonCode::RB, Gamepad::Gamepad1) && !isMoving)
  {
    isMoving = true;
    delta = abs(delta);
  }
  else if(Input::GetButton(ButtonCode::LB, Gamepad::Gamepad1) && !isMoving)
  {
    isMoving = true;
    delta = -abs(delta);
  }

  if(isMoving)
  { 
    cam->RotateTo(vec3(0.0f, delta, 0.0f));

    current += (int) delta;
    if (current >= 90 || current <= -90)
    {
      current = 0;
      isMoving = false;
    }
  }
}
