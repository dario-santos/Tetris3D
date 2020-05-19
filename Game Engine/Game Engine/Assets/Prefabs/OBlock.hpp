#pragma once

#include <GL/glew.h>

#include <vector>
using namespace std;

#include "GameEngine/Components/Transform.hpp"
#include "GameEngine/Components/GameObject.hpp"
#include "GameEngine/Components/Renderer.hpp"

#include "GameEngine/Primitives/Cube.hpp"

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
  static vector<GameObject*> AddOBlock(vec3 color, Material* material)
  {
    vector<GameObject*> gameObjects;
    // For reference, 0 is the middle line

    Transform* t = new Transform(vec3(-5, 195, 1), vec3(0, 0, 0), vec3(10, 10, 10));
    Renderer* r = new Renderer(new Cube(color), material);
    GameObject* g = new GameObject(t, r, "OBlock");
    g->shader = new PhongShader(r, Scene::CurrentScene()->GetLigthSources());
    gameObjects.push_back(g);

    t = new Transform(vec3(5, 195, 1), vec3(0, 0, 0), vec3(10, 10, 10));
    material = new Material(material->ambiental, material->diffuse, material->spectral, material->shininess);
    r = new Renderer(new Cube(color), material);
    g = new GameObject(t, r, "OBlock");
    g->shader = new PhongShader(r, Scene::CurrentScene()->GetLigthSources());
    gameObjects.push_back(g);

    t = new Transform(vec3(-5, 185, 1), vec3(0, 0, 0), vec3(10, 10, 10));
    material = new Material(material->ambiental, material->diffuse, material->spectral, material->shininess);
    r = new Renderer(new Cube(color), material);
    g = new GameObject(t, r, "OBlock");
    g->shader = new PhongShader(r, Scene::CurrentScene()->GetLigthSources());
    gameObjects.push_back(g);

    t = new Transform(vec3(5, 185, 1), vec3(0, 0, 0), vec3(10, 10, 10));
    material = new Material(material->ambiental, material->diffuse, material->spectral, material->shininess);
    r = new Renderer(new Cube(color), material);
    g = new GameObject(t, r, "OBlock");
    g->shader = new PhongShader(r, Scene::CurrentScene()->GetLigthSources());
    gameObjects.push_back(g);

    return gameObjects;
  }
};
