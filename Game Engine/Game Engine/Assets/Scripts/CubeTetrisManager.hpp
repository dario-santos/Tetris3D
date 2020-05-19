#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include <string>

#include "GameManager.hpp"

#include "GameEngine/Scene.hpp"

#include "GameEngine/Camera/ICamera.hpp"

#include "GameEngine/Components/Script.hpp"

#include "GameEngine/Input/Input.hpp"

class CubeTetrisManager : public Script
{
private:
  ICamera* cam;
  vec3 position;
  int step = 90;
  int current = 0;
  float delta = 1;
  bool canMoveCamera = false;

  vector<GameManager *> tetris;
  int activeBoard = 0;

public:
  /*
  * Function: CubeTetrisManager
  * --------------------------------
  *  CubeTetrisManager const
  * 
  * 
  * 
  * 
  * 
  * ructor
  */
  CubeTetrisManager(vector<GameManager*> tetris);

  /*
  * Function: Update
  * --------------------------------
  *  The Update event
  */
  void Update() override;

  void MoveCamera();
};
