#include "Input.hpp"

map<int, int> Input::keys = {
  {GLFW_KEY_A,     GLFW_RELEASE},
  {GLFW_KEY_D,     GLFW_RELEASE},
  {GLFW_KEY_S,     GLFW_RELEASE},
  {GLFW_KEY_W,     GLFW_RELEASE},
  {GLFW_KEY_UP,    GLFW_RELEASE},
  {GLFW_KEY_RIGHT, GLFW_RELEASE},
  {GLFW_KEY_LEFT,  GLFW_RELEASE},
  {GLFW_KEY_DOWN,  GLFW_RELEASE},
  {GLFW_KEY_SPACE, GLFW_RELEASE},
};

vector<int> Input::gamepadsStatus = {GLFW_DISCONNECTED, 16};

float Input::GetAxis(AxesCode axis, Gamepad device)
{
  if (gamepadsStatus[static_cast<int>(device)] == GLFW_DISCONNECTED)
    return 0.0f;

  int count;
  const float* axes = glfwGetJoystickAxes(static_cast<int>(device), &count);

  return axes != NULL ? axes[static_cast<int>(axis)] : 0.0f;
}

bool Input::GetButton(ButtonCode button, Gamepad device)
{
  if (gamepadsStatus[static_cast<int>(device)] == GLFW_DISCONNECTED)
    return false;
  int count;
  unsigned const char* buttons = glfwGetJoystickButtons(static_cast<int>(device), &count);

  return buttons != NULL ? buttons[static_cast<int>(button)] != GLFW_RELEASE : false;
}

bool Input::GetButtonDown(ButtonCode button, Gamepad device)
{
  if (gamepadsStatus[static_cast<int>(device)] == GLFW_DISCONNECTED)
    return false;

  int count;
  unsigned const char* buttons = glfwGetJoystickButtons(static_cast<int>(device), &count);

  return buttons != NULL ? buttons[static_cast<int>(button)] == GLFW_PRESS : false;
}

bool Input::GetButtonUp(ButtonCode button, Gamepad device)
{
  if (gamepadsStatus[static_cast<int>(device)] == GLFW_DISCONNECTED)
    return false;

  int count;
  unsigned const char* buttons = glfwGetJoystickButtons(static_cast<int>(device), &count);

  return buttons != NULL ? buttons[static_cast<int>(button)] == GLFW_RELEASE : false;
}

bool Input::GetKey(KeyCode key)
{
  return Input::keys[static_cast<int>(key)] != GLFW_RELEASE;
}

bool Input::GetKeyDown(KeyCode key)
{
  return Input::keys[static_cast<int>(key)] == GLFW_PRESS;
}

bool Input::GetKeyUp(KeyCode key)
{
  return Input::keys[static_cast<int>(key)] == GLFW_RELEASE;
}

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  Input::keys[key] = action;
}

void Input::JoystickCallback(int jid, int event)
{
  gamepadsStatus[jid] = event;
}
