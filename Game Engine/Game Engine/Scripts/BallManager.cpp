#include "BallManager.hpp"

#include <iostream>

BallManager::BallManager(Transform *transform, GameObject *gameObject)
{
  this->transform = transform;
  this->gameObject = gameObject;
}

void BallManager::Update()
{
  vec3 r = transform->scale * vec3(0.5f, 0.5f, 0.0f);

  // If the ball is not inside of the screen then change its direction
  if(transform->position.x + r.x > 40 || transform->position.x - r.x < -40)
    step.x = -step.x;
  if(transform->position.y + r.y > 30)
    step.y = -step.y;

  // Updates the position of the transform
  transform->Translate(step);
}

void BallManager::OnCollision(vec3 force, std::string tag)
{
  if(tag == "Player")
  {
    step = vec3(force.x, force.y, 0.0f) / 5.0f;
    beep->Play2D("audio/beep.mp3");
  }
  else if(tag == "Brick")
  {
    step = vec3(force.x, force.y, 0.0f) / 5.0f;
    score += 10;

    beep->Play2D("audio/beep.mp3");  
  }
  else if(tag == "DeathZone")
  {
    if(numberOfLives == 0)
    {
      std::cout << "Score: " << score << std::endl;
      numberOfLives = -1; // End of the game
    }
    else if(numberOfLives > 0)
    {
      step = vec3(0.3f, 0.6, 0.0f);
      transform->TranslateTo(vec3(0.0f, -15, 1.0f));
      --numberOfLives;
    }
  }
}
