#include "Input.hpp"

// GLFW_PRESSED = true 
// GLFW_REPEAT  = true
// GLFW_RELEASE = false
map<int, bool> Input::keys = {
  {GLFW_KEY_A,     false},
  {GLFW_KEY_D,     false},
  {GLFW_KEY_S,     false},
  {GLFW_KEY_W,     false},
  {GLFW_KEY_UP,    false},
  {GLFW_KEY_RIGHT, false},
  {GLFW_KEY_LEFT,  false},
  {GLFW_KEY_DOWN,  false},
  {GLFW_KEY_SPACE, false},
};

void Input::UpdateKeyStatus(int key, int action)
{
  Input::keys[key] = !(action == GLFW_RELEASE);
}

bool Input::IsPressed(int key)
{
  return Input::keys[key];
}

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if(action == GLFW_PRESS || action == GLFW_REPEAT)
    Input::UpdateKeyStatus(key, action);

  if(action == GLFW_RELEASE)
    Input::UpdateKeyStatus(key, action);
}

#include <iostream>

void Input::JoystickCallback(int jid, int event)
{
  if (event == GLFW_CONNECTED)
  {
    cout << "JOYSTICK " << jid << " CONNECTED" << endl;
  }
  else if (event == GLFW_DISCONNECTED)
  {
    cout << "JOYSTICK " << jid << "  DISCONNECTED" << endl;
  }
}
