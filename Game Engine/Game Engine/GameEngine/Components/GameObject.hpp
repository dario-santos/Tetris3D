/*********************************************************************
 * \file   GameObject.hpp
 * \brief  GameObject class, in the game world every object is a game object.
 *
 * \author Dário Santos
 * \date   May 2020
***********************************************************************/
#pragma once

#include <GL/glew.h>

#include <string>
#include <list>
using namespace std;

#include "Transform.hpp"
#include "Script.hpp"
#include "Renderer.hpp"

/**
 * GameObject.
 */
class GameObject
{
  private:
    /** The transform of the game object*/
    Transform* transform;
    /** The renderer of the game object */
    Renderer* renderer;
    /** The list of scripts that this game object contains */
    list<Script*> scripts;
    /** The name of the game object */
    string tag;
    /** Informs the game engine if the game object is enabled or disabled, a disabled game object is not drawn */
    bool isEnabled  = true;
    /** Informs the game engine that this game object will be destroyed in the next frame */
    bool canDestroy = false;

  public:
    /**
     * GameObject constructor.
     * 
     * \param transform The transform of the game object
     * \param renderer The renderer of the game object
     * \param tag The tag of the game object, its name
     */
    GameObject(Transform* transform, Renderer* renderer, string tag);
    
    /**
     * ~GameObject.
     * 
     * The descructor of the GameObject class
     * 
     */
    ~GameObject();
    
    /**
     * AddScript.
     *
     * Attaches a script to this game object
     * 
     * \param script The script that will be attached
     */
    void AddScript(Script *script);

    /**
     * GetScripts.
     * 
     * \return list of scripts attached to this game object.
     */
    list<Script*> GetScripts();

    /**
     * Draw.
     * 
     * Draws this game object to the scene using the given values of view and projection
     * 
     * \param view The view matrix
     * \param projection The projection matrix
     */
    void Draw(mat4 view, mat4 projection);
    
    /**
     * IsEnabled.
     * 
     * \return true if is enabled, false otherwise
     */
    bool IsEnabled();

    /**
     * CanDestroy.
     * 
     * \return true if is to be destroyed, false otherwise.
     */
    bool CanDestroy();

    /**
     * Enable.
     * 
     * Enables this game object
     * 
     */
    void Enable();

    /**
     * Disable.
     * 
     * Disables this game object
     * 
     */
    void Disable();

    /**
     * Destroy.
     * 
     * Destroys this game object in the next fram
     * 
     */
    void Destroy();

    /**
     * GetTransform.
     * 
     * \return The transform of this game object
     */
    Transform* GetTransform();

    /**
     * Tag.
     * 
     * \return The tag of the game object
     */
    string Tag();
};
