#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include <string>

#include "../GameEngine/Scene.hpp"

#include "../GameEngine/Camera/ICamera.hpp"

#include "../GameEngine/Components/Script.hpp"

#include "../GameEngine/Input/Input.hpp"

/*
 * Class: CameraMovement
 * --------------------------------
 *   Interface: Script
 */
class CameraMovement : public Script
{
  private:
    ICamera *cam;
    vec3 position;
    int step = 90;
    int current = 0;
    int delta = 2;
    bool isPressed = false;
    bool isMoving = false;

  public:
    /*
    * Function: CameraMovement
    * --------------------------------
    *  CameraMovement constructor
    */
    CameraMovement();
    
    /*
    * Function: Update
    * --------------------------------
    *  The Update event
    */
    void Update() override;
};
