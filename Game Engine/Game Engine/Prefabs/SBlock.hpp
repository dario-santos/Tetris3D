#pragma once

#include <GL/glew.h>

#include <vector>
using namespace std;

#include "../GameEngine/Components/Transform.hpp"
#include "../GameEngine/Components/GameObject.hpp"
#include "../GameEngine/Components/Renderer.hpp"

#include "../GameEngine/Primitives/Cube.hpp"

/**
 * SBlock
 */
class SBlock
{
private:
  // This is private because we don't want SBlock objects
  SBlock();
  ~SBlock();

public:
  /**
   * AddSBlock
   * 
   * \param color The S block color
   * \param programID The Id of the shader
   * \return S block game objects, 4 blocks made a tetromino.
   */
  static vector<GameObject*> AddSBlock(vec3 color, GLuint programID)
  {
    vector<GameObject*> gameObjects;
    // D  = [-50,50]
    // D' = [0, 200]
    // for reference, 0 is the middle line
    // 3 blocks left half, 1 right half

    Transform* t = new Transform(vec3(-15, 185, 1), vec3(0, 0, 0), vec3(10, 10, 10));
    gameObjects.push_back(new GameObject(t, new Renderer(new Cube(color), programID), "SBlock"));

    t = new Transform(vec3(-5, 185, 1), vec3(0, 0, 0), vec3(10, 10, 10));
    gameObjects.push_back(new GameObject(t, new Renderer(new Cube(color), programID), "SBlock"));

    t = new Transform(vec3(-5, 195, 1), vec3(0, 0, 0), vec3(10, 10, 10));
    gameObjects.push_back(new GameObject(t, new Renderer(new Cube(color), programID), "SBlock"));

    t = new Transform(vec3(5, 195, 1), vec3(0, 0, 0), vec3(10, 10, 10));
    gameObjects.push_back(new GameObject(t, new Renderer(new Cube(color), programID), "SBlock"));

    return gameObjects;
  }
};
