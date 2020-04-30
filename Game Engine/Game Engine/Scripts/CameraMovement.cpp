#include "CameraMovement.hpp"

#include <iostream>

CameraMovement::CameraMovement()
{
  this->cam = Scene::CurrentScene()->GetCameras().front();
}

void CameraMovement::Update()
{
  // A camera move-se em circunferência
  // A camera para 90 em 90 graus
  /*
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
    cam->Rotate(vec3(0.0f, delta, 0.0f));

    current += (int) delta;
    if (current >= 90 || current <= -90)
    {
      current = 0;
      isMoving = false;
    }
  }
  */


  float rotationY = Input::GetAxis(AxesCode::RAxis_X) * -delta;

  vec3 position;
  position.x = cam->GetView()[2].x;
  position.y = cam->GetView()[2].y;
  position.z = cam->GetView()[2].z;

  if (position.x > 0.2f && sign(rotationY) == 1)
  {
    rotationY = 0.0f;
  }

  else if (position.x < -0.2f && sign(rotationY) == -1)
  {
    rotationY = 0.0f;
  }


  cam->Rotate(vec3(0.0f, rotationY, 0.0f));

  
  std::cout << position.x << " " << position.y << " " << position.z << std::endl;
}
