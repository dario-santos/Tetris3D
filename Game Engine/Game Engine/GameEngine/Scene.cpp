#include "Scene.hpp"

Scene::~Scene() 
{
  for (ICamera* cam : cameras)
  {
    delete cam;
    cam = nullptr;
  }

  for (GameObject* go : gameObjects)
  {
    delete go;
    go = nullptr;
  }

  for (Canvas* c : canvas)
  {
    delete c;
    c = nullptr;
  }

  cameras.clear();
  gameObjects.clear();
  canvas.clear();
}

Scene* Scene::currentScene = nullptr;

void Scene::LoadScene(unique_ptr<Scene>& scene)
{
  Scene::currentScene = scene.get();
}

Scene* Scene::CurrentScene()
{
  return Scene::currentScene;
}

void Scene::AddGameObject(GameObject *gameObject)
{
  this->gameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(GameObject *gameObject)
{
  this->gameObjects.remove(gameObject);
  delete gameObject;
  gameObject = nullptr;
}

list<GameObject*> Scene::GetGameObjects()
{
  return this->gameObjects;
}

void Scene::AddCamera(ICamera* camera) 
{
  this->cameras.push_back(camera);
}

void Scene::RemoveCamera(ICamera* camera)
{
  this->cameras.remove(camera);
  delete camera;
  camera = nullptr;
}

list<ICamera*> Scene::GetCameras()
{
  return this->cameras;
}

void Scene::AddCanvas(Canvas* canvas)
{
    this->canvas.push_back(canvas);
}

void Scene::RemoveCanvas(Canvas* canvas)
{
    this->canvas.remove(canvas);
    delete canvas;
    canvas = nullptr;
}

list<Canvas*> Scene::GetCanvas()
{
    return this->canvas;
}

void Scene::DrawScene()
{
  for(ICamera* c: cameras)
    for(GameObject *g: this->gameObjects)
      if(g->IsEnabled())
        g->Draw(c->GetView(), c->GetProjection());
}

void Scene::DrawGUI()
{
  for(ICamera* cam: cameras)
  {
    for(Canvas* c: this->canvas)
    {
      if(c->IsEnabled())
        {
          for (Button* b : c->GetButtons())
            b->GetRenderer()->Draw(b->GetTransform()->model, cam->GetView(), cam->GetProjection());
                
          //  TODO : Draw sprites
        }
    }
  }
}
