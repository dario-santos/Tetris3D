#pragma once

#include <GL/glew.h>

#include <vector>
using namespace std;

#include "../GameEngine/Components/Transform.hpp"
#include "../GameEngine/Components/GameObject.hpp"
#include "../GameEngine/Components/Renderer.hpp"

#include "../GameEngine/Primitives/Cube.hpp"

/**
 * OBlock
 */
class OBlock
{
private:
  // This is private because we don't want OBlock objects
  OBlock();
  ~OBlock();

public:
  /**
   * AddOBlock
   * 
   * \param color The O block color
   * \param programID The Id of the shader
   * \return O block game objects, 4 blocks made a tetromino.
   */
  static vector<GameObject*> AddOBlock(vec3 color, GLuint programID)
  {
    vector<GameObject*> gameObjects;
    // For reference, 0 is the middle line

    Transform* t = new Transform(vec3(-5, 195, 1), vec3(0, 0, 0), vec3(10, 10, 10));
    gameObjects.push_back(new GameObject(t, new Renderer(new Cube(color), programID), "OBlock"));

    t = new Transform(vec3(5, 195, 1), vec3(0, 0, 0), vec3(10, 10, 10));
    gameObjects.push_back(new GameObject(t, new Renderer(new Cube(color), programID), "OBlock"));

    t = new Transform(vec3(-5, 185, 1), vec3(0, 0, 0), vec3(10, 10, 10));
    gameObjects.push_back(new GameObject(t, new Renderer(new Cube(color), programID), "OBlock"));

    t = new Transform(vec3(5, 185, 1), vec3(0, 0, 0), vec3(10, 10, 10));
    gameObjects.push_back(new GameObject(t, new Renderer(new Cube(color), programID), "OBlock"));

    return gameObjects;
  }
};
