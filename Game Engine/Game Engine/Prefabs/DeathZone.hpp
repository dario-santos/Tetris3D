/**
 * @file DeathZone.hpp
 *
 * @brief Creates DeathZone game objects
 *
 * @author Dário Santos
 * Contact: dariovfsantos@gmail.com
 */
#pragma once

#include "../GameEngine/Components/Transform.hpp"
#include "../GameEngine/Components/GameObject.hpp"

/*
 * Class: DeathZone
 * --------------------------------
 */
class DeathZone
{
  private:
    // This is private because we don't want Ball objects
    DeathZone();
    ~DeathZone();

  public:
    /*
    * Function: AddDeathZone
    * --------------------------------
    *  Creates DeathZone game objects
    *  
    *  t: The transform of the new game object.
    */
    static GameObject *AddDeathZone(Transform *t)
    {
      // The DeathZone as no renderer because it's only used as a collider
      return new GameObject(t, nullptr, "DeathZone");
    }
};
