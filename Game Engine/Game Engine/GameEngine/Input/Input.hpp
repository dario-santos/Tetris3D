 /*********************************************************************
  * \file   Input.hpp
  * \brief  Input class, manages the input system
  *
  * \author Dário Santos
  * \date   April 2020
 ***********************************************************************/
#pragma once

#include <GLFW/glfw3.h>

#include <map>
#include <vector>
using namespace std;

enum class Gamepad {
  Gamepad1 = GLFW_JOYSTICK_1,
  Gamepad2 = GLFW_JOYSTICK_2,
  Gamepad3 = GLFW_JOYSTICK_3,
  Gamepad4 = GLFW_JOYSTICK_4,
  Gamepad5 = GLFW_JOYSTICK_5,
  Gamepad6 = GLFW_JOYSTICK_6,
  Gamepad7 = GLFW_JOYSTICK_7,
  Gamepad8 = GLFW_JOYSTICK_8,
  Gamepad9 = GLFW_JOYSTICK_9,
  Gamepad10 = GLFW_JOYSTICK_10,
  Gamepad11 = GLFW_JOYSTICK_11,
  Gamepad12 = GLFW_JOYSTICK_12,
  Gamepad13 = GLFW_JOYSTICK_13,
  Gamepad14 = GLFW_JOYSTICK_14,
  Gamepad15 = GLFW_JOYSTICK_15,
  Gamepad16 = GLFW_JOYSTICK_16,
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
enum class ButtonCode {
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
  DPAD_LEFT,
};

// id | Xbox    | Playstation  
// 0 -> LAxis_X | LAxis_X
// 1 -> LAxis_Y | LAxis_Y
// 2 -> RAxis_X | RAxis_X
// 3 -> RAxis_Y | RAxis_Y
// 4 -> LT      | L2
// 5 -> RT      | R2
enum class AxesCode {
  LAxis_X = 0,
  LAxis_Y,
  RAxis_X,
  RAxis_Y,
  LT,
  RT
};

enum class KeyCode {
  RIGHT = 262,
  LEFT = 263,
  DOWN = 264,
  UP = 265
};

/**
 * Input
 */
class Input
{
  private:
    // A hash map that represents if a key is being pressed or not.
    static map<int, int> keys;
    static vector<int> gamepadsStatus;
    // This is private because we don't want Ball objects
    Input();
    ~Input();

public:
  /**
   * GetAxis
   * 
   * \param axis The axis code of the enum AxisCode
   * \param device The gamepad that will be tested
   * \return The value of the virtual axis identified by axisName. The value is in the range [-1.0, 1.0]
   */
  static float GetAxis(AxesCode axis, Gamepad device);

  /**
   * GetButton
   * 
   * \param button The button code of the enum ButtonCode
   * \param device The gamepad that will be tested
   * \return True while the virtual button identified by button is held down
   */
  static bool GetButton(ButtonCode button, Gamepad device);

  /**
   * GetButtonDown
   * 
   * \param button The button code of the enum ButtonCode
   * \param device The gamepad that will be tested
   * \return True while the virtual button identified by button is held down
   */
  static bool GetButtonDown(ButtonCode button, Gamepad device);

  /**
   * GetButtonUp
   * 
   * \param button The button code of the enum ButtonCode
   * \param device The gamepad that will be tested
   * \return True while the virtual button identified by button is held down
   */
  static bool GetButtonUp(ButtonCode button, Gamepad device);

  /**
   * GetKey
   * 
   * \param key The key code of the enum KeyCode
   * \return True while the user holds down the key identified by name
   */
  static bool GetKey(KeyCode key);

  /**
   * GetKeyDown
   * 
   * \param key The key code of the enum KeyCode
   * \return True in the frame the starts pressing down the key identified by name
   */
  static bool GetKeyDown(KeyCode key);

  /**
   * GetKeyUp
   * 
   * \param key The key code of the enum KeyCode
   * \return True during the frame the user releases the key identified by name
   */
  static bool GetKeyUp(KeyCode key);

  /**
   * KeyCallback
   * 
   * \param window The GLFW active window
   * \param key The key that evoked the event
   * \param scancode The code of the pressed key
   * \param action The status of the key
   * \param mods If there are active mods, capslock, etc.
   */
  static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

  /**
   * JoystickCallback
   * 
   * \param jid The joystick identifier
   * \param event The event that was provoked, GLFW_CONNECTED or GLFW_DISCONNECTED
   */
  static void JoystickCallback(int jid, int event);
};
