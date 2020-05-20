#pragma once
#include <limits>

struct Position
{
  Position()
  {
    SetNull();
  }

  Position(const int x, const int y) :
    _x(x),
    _y(y)
  {
  }

  void SetNull()
  {
    _x = INT_MAX;
    _y = INT_MAX;
  }

  bool IsNull()
  {
    return _x == INT_MAX && _y == INT_MAX;
  }

  void Reset()
  {
    _x = 2;
    _y = 5;
  }

  void GoDown()
  {
    _x += 1;
  }

  void GoLeft()
  {
    _y -= 1;
  }

  void GoRight()
  {
    _y += 1;
  }

  int _x;
  int _y;
};
