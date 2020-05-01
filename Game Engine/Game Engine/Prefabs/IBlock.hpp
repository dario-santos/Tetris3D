#pragma once

#include <GL/glew.h>

#include <vector>
using namespace std;

#include "../GameEngine/Components/Transform.hpp"
#include "../GameEngine/Components/GameObject.hpp"
#include "../GameEngine/Components/Renderer.hpp"

#include "../GameEngine/Primitives/Cube.hpp"

/**
 * IBlock
 */
class IBlock
{
private:
  // This is private because we don't want SBlock objects
  IBlock();
  ~IBlock();

public:
  /**
   * AddIBlock
   * 
   * \param color The I block color
   * \param programID the Id of the shader.
   * \return I block game objects, 4 blocks made a tetromino.
   */
  static vector<GameObject*> AddIBlock(vec3 color, GLuint programID)
  {
    vector<GameObject*> gameObjects;
    // D  = [-50,50]
    // D' = [0, 200]
    // for reference, 0 is the middle line
    // 2 blocks left half, 2 right half

    Transform* t = new Transform(vec3(-15, 195, 1), vec3(0, 0, 0), vec3(10, 10, 10));
    gameObjects.push_back(new GameObject(t, new Renderer(new Cube(color), programID), "IBlock"));

    t = new Transform(vec3(-5, 195, 1), vec3(0, 0, 0), vec3(10, 10, 10));
    gameObjects.push_back(new GameObject(t, new Renderer(new Cube(color), programID), "IBlock"));

    t = new Transform(vec3(5, 195, 1), vec3(0, 0, 0), vec3(10, 10, 10));
    gameObjects.push_back(new GameObject(t, new Renderer(new Cube(color), programID), "IBlock"));

    t = new Transform(vec3(15, 195, 1), vec3(0, 0, 0), vec3(10, 10, 10));
    gameObjects.push_back(new GameObject(t, new Renderer(new Cube(color), programID), "IBlock"));

    return gameObjects;
  }
};
