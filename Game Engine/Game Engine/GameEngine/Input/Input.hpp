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
#include <vector>
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
    static vector<bool> gamepadsStatus;
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
    *  device: The gamepad/keyboard that will be tested, keyboard = 0, gamepad#N = N
    * 
    *  returns: false if it's not being pressed, true otherwise.
    */
    static bool IsPressed(int key, int device=0);

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
    */
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    /*
    * Function: JoystickCallback
    * --------------------------------
    *  This function is used as the joystick event callbock for the glfw.
    *
    *  window: the window that we are using;
    *  key: the pressed key;
    *  scancode: the code of the pressed key;
    *  action: The status of the pressed key.
    *  mods: modifiers, ex.: if the capslock is active, etc..
    */
    static void JoystickCallback(int jid, int event);
};

// id | Xbox    | Playstation  
// 0 -> A       | X
// 1 -> B       | O
// 2 -> X       | Square
// 3 -> Y       | Triangle
// 4 -> LB      | L1
// 5 -> RB      | R1
// 6 -> select  | select
// 7 -> start   | start
// 8 -> L3      | L3
// 9 -> R3      | R3
// 10 -> D-UP   | D-UP
// 11 -> D-RIGHT| D-RIGHT
// 12 -> D-DOWN | D-DOWN
// 13 -> D-LEFT | D-LEFT 
static enum ButtonCode {
  A = 0,
  B,
  X,
  Y,
  LB,
  RB,
  Select,
  Start,
  L3,
  R3,
  DPAD_UP,
  DPAD_RIGHT,
  DPAD_DOWN,
  DPAD_LEFT
};

static enum KeyCode {
  RIGHT = 262,
  LEFT = 263,
  DOWN = 264,
  UP = 265
};
