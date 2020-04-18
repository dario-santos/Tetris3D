/**
 * @file Input.hpp
 *
 * @brief Input class, manages the input system of the game engine.
 *
 * @author Dário Santos
 * Contact: dariovfsantos@gmail.com
 */
#pragma once

#include <GLFW/glfw3.h>

#include <map>
using namespace std;

/*
 * Class: GameObject
 * --------------------------------
 */
class Input
{
  private:
    // A hash map that represents if a key is being pressed or not.
    static map<int, bool> keys;
    // This is private because we don't want Ball objects
    Input();
    ~Input();

  public:
    /*
    * Function: UpdateKeyStatus
    * --------------------------------
    *  Updates the status of the givin key.
    *  
    *  key: the key glfw code ex.: KEY_GLFW_A;
    *  action: The new status of the key.
    */
    static void UpdateKeyStatus(int key, int action);

    /*
    * Function: IsPressed
    * --------------------------------
    *  Returns the status of the givin key,
    *  
    *  key: the key glfw code ex.: KEY_GLFW_A;
    * 
    *  returns: false if it's not being pressed, true otherwise.
    */
    static bool IsPressed(int key);

    /*
    * Function: KeyCallback
    * --------------------------------
    *  This function is used as the key event callbock for the glfw.
    *  
    *  window: the window that we are using;
    *  key: the pressed key;
    *  scancode: the code of the pressed key;
    *  action: The status of the pressed key.
    *  mods: modifiers, ex.: if the capslock is active, etc..
    * 
    *  returns: false if it's not being pressed, true otherwise.
    */
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
