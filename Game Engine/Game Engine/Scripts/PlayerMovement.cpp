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
  if (Input::IsPressed(KeyCode::RIGHT) || Input::IsPressed(ButtonCode::DPAD_RIGHT, 1))
    transform->Translate(vec3(horizontalSpeed, 0.0f, 0.0f));
  else if(Input::IsPressed(KeyCode::LEFT) || Input::IsPressed(ButtonCode::DPAD_LEFT, 1))
    transform->Translate(vec3(-horizontalSpeed, 0.0f, 0.0f));

  // Locks the player inside the screen
  if(transform->position.x + half.x > 40)
    transform->Translate(vec3(-horizontalSpeed, 0.0f, 0.0f));
  else if(transform->position.x - half.x < -40.f)
    transform->Translate(vec3(horizontalSpeed, 0.0f, 0.0f));
}
