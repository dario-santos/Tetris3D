#include "PlayerMovement.hpp"

#include <GLFW/glfw3.h>

#include "../GameEngine/Input/Input.hpp"

PlayerMovement::PlayerMovement(Transform *transform)
{
  this->transform = transform;
}

void PlayerMovement::Update()
{
  vec3 half = transform->scale * vec3(0.5f, 0.5f, 0.5f);
  
  // Sees if the right or left keys are being pressed
  if(Input::IsPressed(GLFW_KEY_RIGHT))
    transform->position.x += horizontalSpeed;
  else if(Input::IsPressed(GLFW_KEY_LEFT))
    transform->position.x -= horizontalSpeed;

  // Looks the player inside the screen
  if(transform->position.x + half.x > 40.f)
    transform->position.x -= horizontalSpeed;
  else if(transform->position.x - half.x < -40.f)
    transform->position.x += horizontalSpeed;
}
