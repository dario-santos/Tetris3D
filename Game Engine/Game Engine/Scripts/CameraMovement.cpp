#include "CameraMovement.hpp"

CameraMovement::CameraMovement()
{
  this->cam = Scene::CurrentScene()->GetCameras().front();
}

void CameraMovement::Update()
{
  // A camera move-se em circunferência
  // A camera para 90 em 90 graus

  if(Input::IsPressed(KeyCode::RIGHT) && !isMoving)
  {
    isMoving = true;
    delta = abs(delta);
  }
  else if(Input::IsPressed(KeyCode::LEFT) && !isMoving)
  {
    isMoving = true;
    delta = -abs(delta);
  }

  if(isMoving)
  {
    mat4 view = rotate(cam->GetView(), radians((float)delta), vec3(0.0f, 1.0f, 0.0f));
    cam->SetView(view);

    current += delta;
    if (current >= 90 || current <= -90)
    {
      current = 0;
      isMoving = false;
    }
  }
}
