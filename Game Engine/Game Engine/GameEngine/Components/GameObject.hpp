/**
 * @file GameObject.hpp
 *
 * @brief GameObject class, used by all prefabs,
 *   all objects are game objects.
 *
 * @author Dário Santos
 * Contact: dariovfsantos@gmail.com
 */
#pragma once

#include <GL/glew.h>

#include <string>
#include <list>
using namespace std;

#include "Transform.hpp"
#include "Script.hpp"
#include "Renderer.hpp"

/*
 * Class: GameObject
 * --------------------------------
 */
class GameObject
{
  private:
    // The transform of the game object
    Transform *transform;
    // The renderer of the game object
    Renderer *renderer;
    // The tag of the game object, its name
    string tag;
    // if is active
    bool isEnabled  = true;
    // if it can be destroyed by the garbage collector
    bool canDestroy = false;
    // The list of scripts
    list<Script *> scripts;

  public:
    /*
    * Function: GameObject
    * --------------------------------
    *  GameObject constructor
    *  
    *  transform: The transform of the game object;
    *  renderer: The renderer of the game object.
    *  tag :The tag of the game object, its name
    */
    GameObject(Transform *transform, Renderer *renderer, string tag);
    
    /*
    * Function: AddScript
    * --------------------------------
    *  Adds a script to the script list.
    *  
    *  script: The script that will be added.
    */
    void AddScript(Script *script);

    /*
    * Function: GetScripts
    * --------------------------------
    *  Returns the script list
    *  
    *  return: The script list.
    */
    list<Script *> GetScripts();

    /*
    * Function: Draw
    * --------------------------------
    *  The function draw is called every frame and 
    *    its responsible for drawing the game object.
    */
    void Draw(mat4 Projection);
    
    /*
    * Function: IsEnabled
    * --------------------------------
    *  Returns the status of the game object.
    * 
    *  return: true if is enabled, false otherwise.
    */
    bool IsEnabled();

    /*
    * Function: CanDestroy
    * --------------------------------
    *  Returns if the game object can be destroyed, 
    *   is used by the garbage collector.
    * 
    *  return: true if is to be destroyed, false otherwise.
    */
    bool CanDestroy();

    /*
    * Function: Enable
    * --------------------------------
    *  Enables the game object
    */
    void Enable();

    /*
    * Function: Disable
    * --------------------------------
    *  Disables the game object
    */
    void Disable();

    /*
    * Function: Destroy
    * --------------------------------
    * Destroys the game object in the next frame.
    */
    void Destroy();

    /*
    * Function: GetTransform
    * --------------------------------
    * Returns the transform of the game object.
    * 
    * return: the transform of the game object.
    */
    Transform GetTransform();

    /*
    * Function: Tag
    * --------------------------------
    * Returns tag of the game object.
    * 
    * return: the tag of the game object.
    */
    string Tag();
};
