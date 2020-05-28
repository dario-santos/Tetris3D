#pragma once

#include <GL/glew.h>

#include <vector>
using namespace std;

#include "GameEngine/Components/Transform.hpp"
#include "GameEngine/Components/GameObject.hpp"
#include "GameEngine/Components/Renderer.hpp"

#include "GameEngine/Primitives/Cube.hpp"

#include "Assets/Shaders/PhongShader.hpp"

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
  static vector<GameObject*> AddIBlock(float scale, vec3 color, Material* material)
  {

      const char* texture = "Assets/Sprites/na.png";


    vector<GameObject*> gameObjects;
    // D  = [-50,50]
    // D' = [0, 200]
    // for reference, 0 is the middle line
    // 2 blocks left half, 2 right half

    Transform* t = new Transform(vec3(-15, 195, 1), vec3(0), vec3(scale));
    Renderer* r = new Renderer(new Cube(color), material);
    GameObject* g = new GameObject(t, r, "IBlock");
    g->shader = new PhongShader(r, Scene::CurrentScene()->GetLigthSources(), texture);
    gameObjects.push_back(g);

    t = new Transform(vec3(-5, 195, 1), vec3(0), vec3(scale));
    material = new Material(material->ambiental, material->diffuse, material->spectral, material->shininess);
    r = new Renderer(new Cube(color), material);
    g = new GameObject(t, r, "IBlock");
    g->shader = new PhongShader(r, Scene::CurrentScene()->GetLigthSources(), texture);
    gameObjects.push_back(g);

    t = new Transform(vec3(5, 195, 1), vec3(0), vec3(scale));
    material = new Material(material->ambiental, material->diffuse, material->spectral, material->shininess);
    r = new Renderer(new Cube(color), material);
    g = new GameObject(t, r, "IBlock");
    g->shader = new PhongShader(r, Scene::CurrentScene()->GetLigthSources(), texture);
    gameObjects.push_back(g);

    t = new Transform(vec3(15, 195, 1), vec3(0), vec3(scale));
    material = new Material(material->ambiental, material->diffuse, material->spectral, material->shininess);
    r = new Renderer(new Cube(color), material);
    g = new GameObject(t, r, "IBlock");
    g->shader = new PhongShader(r, Scene::CurrentScene()->GetLigthSources(), texture);
    gameObjects.push_back(g);

    return gameObjects;
  }
};
