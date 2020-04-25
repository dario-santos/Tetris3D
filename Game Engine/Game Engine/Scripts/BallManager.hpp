#pragma once

#include <glm/glm.hpp>
using namespace glm;

#include <string>

#include "../GameEngine/Components/Transform.hpp"
#include "../GameEngine/Components/GameObject.hpp"
#include "../GameEngine/Components/Script.hpp"

#include "../GameEngine/Audio/AudioDevice.hpp"

#include "../GameEngine/Time/Time.hpp"

/*
 * Class: BallManager
 * --------------------------------
 *   Interface: Script
 */
class BallManager : public Script
{
  private:
    // Transform of the gameObject
    Transform *transform;
    // The ball gameObject
    GameObject *gameObject;
    // Audio device
    AudioDevice *beep = new AudioDevice();
    // Velocity of movement
    vec3 step = vec3(10.0f, 6.0f, 0.0f);
    // Number of lives
    int numberOfLives = 2;
    // Score of the game
    int score = 0;

  public:
    /*
    * Function: BallManager
    * --------------------------------
    *  BallManager constructor
    *  
    *  transform: The transform of the gameObject;
    *  gameObject: The ball gameObject.
    */
    BallManager(Transform *transform, GameObject *gameObject);
    
    /*
    * Function: Update
    * --------------------------------
    *  The Update event
    */
    void Update() override;    
    
    /*
    * Function: OnCollision
    * --------------------------------
    *  The OnCollision event
    * 
    *  force: The force vector;
    *  tag: the name of the gameObject that we collided with.
    */
    void OnCollision(vec3 force, std::string tag) override;
};
