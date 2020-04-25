#include "PlayerMovement.hpp"

#include "../GameEngine/Input/Input.hpp"
#include <iostream>

PlayerMovement::PlayerMovement(Transform *transform)
{
  this->transform = transform;
}

void PlayerMovement::Update()
{
  vec3 half = transform->scale * vec3(0.5f, 0.5f, 0.5f);
  
  // Sees if the right or left keys are being pressed
  if (Input::GetKey(KeyCode::RIGHT) || Input::GetAxis(AxesCode::LAxis_X, Gamepad::Gamepad1) > 0.3f)
    transform->Translate(vec3(horizontalSpeed, 0.0f, 0.0f));
  else if(Input::GetKey(KeyCode::LEFT) || Input::GetAxis(AxesCode::LAxis_X, Gamepad::Gamepad1) < -0.3f)
    transform->Translate(vec3(-horizontalSpeed, 0.0f, 0.0f));

  // Locks the player inside the screen
  if(transform->position.x + half.x > 40)
    transform->Translate(vec3(-horizontalSpeed, 0.0f, 0.0f));
  else if(transform->position.x - half.x < -40.f)
    transform->Translate(vec3(horizontalSpeed, 0.0f, 0.0f));
}
