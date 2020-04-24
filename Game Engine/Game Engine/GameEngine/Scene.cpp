#include "Scene.hpp"

Scene *Scene::currentScene = nullptr;

void Scene::LoadScene(Scene *scene)
{
  Scene::currentScene = scene;
}

Scene *Scene::CurrentScene()
{
  return Scene::currentScene;
}

void Scene::AddGameObject(GameObject *gameObject)
{
  this->gameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(GameObject *gameObject)
{
  // Frees the game object memory
  gameObject->~GameObject();
  this->gameObjects.remove(gameObject);
}

list<GameObject *> Scene::GetGameObjects()
{
    return this->gameObjects;
}

void Scene::AddCamera(ICamera* camera) 
{
  this->cameras.push_back(camera);
}

void Scene::RemoveCamera(ICamera* camera)
{
  //  camera->~ICamera();
  this->cameras.remove(camera);
}

list<ICamera*> Scene::GetCameras()
{
  return this->cameras;
}

void Scene::DrawScene()
{
  for (ICamera* c : cameras)
    for (GameObject *g: this->gameObjects)
      g->Draw(c->GetView(), c->GetProjection());
}
