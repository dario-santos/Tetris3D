#pragma once

#include <string>

using namespace std;

#include "./GameObject.hpp"
#include "./Transform.hpp"

class Component 
{
public:
  /** The game object this component is attached to. A component is always attached to a game object. */
  GameObject gameObject;
  /** The tag of this game object. */
  string tag;
  /** The Transform attached to this GameObject. */
  Transform transform;

  template<typename T>
  void GetComponent(T *out);
};