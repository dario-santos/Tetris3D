#pragma once

#include <GL/glew.h>

#include <vector>
using namespace std;

#include "GameEngine/Components/Transform.hpp"
#include "GameEngine/Components/GameObject.hpp"
#include "GameEngine/Components/Renderer.hpp"

#include "GameEngine/Primitives/Cube.hpp"


#include "Assets/Shaders/TransparencyShader.hpp"


/**
 * HintBlock
 */
class HintBlock
{
private:
  // This is private because we don't want OBlock objects
  HintBlock() = default;
  ~HintBlock() = default;

public:
  /**
   * HintBlock
   * 
   * \param color The hint block color
   * \param programID The Id of the shader
   * \return hint block game objects, 4 blocks made a tetromino.
   */
  static vector<GameObject*> AddHintBlock(float scale, vec3 color, Material* material)
  {
      const char* buttonTexture = "Assets/Sprites/na.png";


    vector<GameObject*> gameObjects;
    // For reference, 0 is the middle line

    Transform* t = new Transform(vec3(-5, 195, 1), vec3(0), vec3(scale));
    Renderer* r = new Renderer(new Cube(color), material);
    GameObject* g = new GameObject(t, r, "OBlock");
    g->shader = new TransparencyShader(r);
    gameObjects.push_back(g);

    t = new Transform(vec3(5, 195, 1), vec3(0), vec3(scale));
    material = new Material(material->ambiental, material->diffuse, material->spectral, material->shininess);
    r = new Renderer(new Cube(color), material);
    g = new GameObject(t, r, "OBlock");
    g->shader = new TransparencyShader(r);
    gameObjects.push_back(g);

    t = new Transform(vec3(-5, 185, 1), vec3(0), vec3(scale));
    material = new Material(material->ambiental, material->diffuse, material->spectral, material->shininess);
    r = new Renderer(new Cube(color), material);
    g = new GameObject(t, r, "OBlock");
    g->shader = new TransparencyShader(r);
    gameObjects.push_back(g);

    t = new Transform(vec3(5, 185, 1), vec3(0), vec3(scale));
    material = new Material(material->ambiental, material->diffuse, material->spectral, material->shininess);
    r = new Renderer(new Cube(color), material);
    g = new GameObject(t, r, "OBlock");
    g->shader = new TransparencyShader(r);
    gameObjects.push_back(g);

    return gameObjects;
  }
};
