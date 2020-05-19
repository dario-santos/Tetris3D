#pragma once

#include <GL/glew.h>

#include <vector>
using namespace std;

#include "GameEngine/Components/Transform.hpp"
#include "GameEngine/Components/GameObject.hpp"
#include "GameEngine/Components/Renderer.hpp"

#include "GameEngine/Primitives/Cube.hpp"

/**
 * JBlock
 */
class JBlock
{
private:
  // This is private because we don't want SBlock objects
  JBlock();
  ~JBlock();

public:
  /**
   * AddJBlock
   * 
   * \param color The J block color
   * \param programID The Id of the shader
   * \return J block game objects, 4 blocks made a tetromino.
   */
  static vector<GameObject*> AddJBlock(vec3 color, Material* material)
  {
    vector<GameObject*> gameObjects;
    // D  = [-50,50]
    // D' = [0, 200]
    // for reference, 0 is the middle line
    // 3 blocks left half, 1 right half

    Transform* t = new Transform(vec3(-15, 195, 1), vec3(0, 0, 0), vec3(10, 10, 10));
    Renderer* r = new Renderer(new Cube(color), material);
    GameObject* g = new GameObject(t, r, "JBlock");
    g->shader = new PhongShader(r, Scene::CurrentScene()->GetLigthSources());
    gameObjects.push_back(g);

    t = new Transform(vec3(-15, 185, 1), vec3(0, 0, 0), vec3(10, 10, 10));
    material = new Material(material->ambiental, material->diffuse, material->spectral, material->shininess);
    r = new Renderer(new Cube(color), material);
    g = new GameObject(t, r, "JBlock");
    g->shader = new PhongShader(r, Scene::CurrentScene()->GetLigthSources());
    gameObjects.push_back(g);

    t = new Transform(vec3(-5, 185, 1), vec3(0, 0, 0), vec3(10, 10, 10));
    material = new Material(material->ambiental, material->diffuse, material->spectral, material->shininess);
    r = new Renderer(new Cube(color), material);
    g = new GameObject(t, r, "JBlock");
    g->shader = new PhongShader(r, Scene::CurrentScene()->GetLigthSources());
    gameObjects.push_back(g);

    t = new Transform(vec3(5, 185, 1), vec3(0, 0, 0), vec3(10, 10, 10));
    material = new Material(material->ambiental, material->diffuse, material->spectral, material->shininess);
    r = new Renderer(new Cube(color), material);
    g = new GameObject(t, r, "JBlock");
    g->shader = new PhongShader(r, Scene::CurrentScene()->GetLigthSources());
    gameObjects.push_back(g);

    return gameObjects;
  }
};
