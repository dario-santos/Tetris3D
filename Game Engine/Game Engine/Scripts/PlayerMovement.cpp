#include "PlayerMovement.hpp"

PlayerMovement::PlayerMovement(Transform *transform)
{
  this->transform = transform;
}

void PlayerMovement::Update()
{
  float speed = Input::GetAxis("Horizontal", Gamepad::Gamepad1) * Time::GetDeltaTime() * horizontalSpeed;
  transform->Translate(vec3(speed, 0.0f, 0.0f));

 
  vec3 half = transform->scale * vec3(0.5f, 0.5f, 0.5f);
  // Locks the player inside the screen
  if(transform->position.x + half.x > 40)
    transform->Translate(vec3(-speed, 0.0f, 0.0f));
  else if(transform->position.x - half.x < -40.f)
    transform->Translate(vec3(-speed, 0.0f, 0.0f));
}





