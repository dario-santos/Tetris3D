#include "BrickManager.hpp"

BrickManager::BrickManager(GameObject *brick)
{
  this->brick = brick;
}

void BrickManager::OnCollision(vec3 force, std::string tag)
{
  // If the brick as collided with a ball destroy it
  if(tag == "Ball")
    brick->Destroy();
}
