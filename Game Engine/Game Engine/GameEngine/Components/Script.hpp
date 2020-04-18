/**
 * @file Script.hpp
 *
 * @brief Script abstract class, defines the events of the scripts

 *
 * @author Dário Santos
 * Contact: dariovfsantos@gmail.com
 */
#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
using namespace glm;

#include <string>

/*
 * Class: Script
 * --------------------------------
 */
class Script
{
  public:   
    /*
    * Function: Update
    * --------------------------------
    *  The Update event
    */
    virtual void Update() {};

    /*
    * Function: OnCollision
    * --------------------------------
    *  The OnCollision event
    * 
    *  force: The force vector;
    *  tag: the name of the gameObject that we collided with.
    */
    virtual void OnCollision(vec3 force, std::string tag) {};
};
