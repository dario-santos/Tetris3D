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

void Scene::AddCanvas(Canvas* canvas)
{
    this->canvas.push_back(canvas);
}

void Scene::RemoveCanvas(Canvas* canvas)
{
    this->canvas.remove(canvas);
}

list<Canvas*> Scene::GetCanvas()
{
    return this->canvas;
}


void Scene::DrawScene()
{
  for (ICamera* c : cameras)
    for (GameObject *g: this->gameObjects)
      if(g->IsEnabled())
        g->Draw(c->GetView(), c->GetProjection());
      
}

void Scene::DrawGUI()
{
    for (ICamera* cam : cameras)
    {
        for (Canvas* c : this->canvas)
        {
            if (c->IsEnabled())
            {
                for (Button* b : c->GetButtons())
                    b->GetRenderer()->Draw(b->GetTransform()->model, cam->GetView(), cam->GetProjection());
                
                //  TODO : Draw sprites
                
            }

        }
    }
}

void Scene::DestroyScene()
{
    for (ICamera* cam : cameras)
        cam->~ICamera();

    for (GameObject* go: gameObjects)
        go->~GameObject();
    
    for (Canvas* c : canvas)
        c->~Canvas();
    
    cameras.erase(cameras.begin(), cameras.end());
    gameObjects.erase(gameObjects.begin(), gameObjects.end());
    canvas.erase(canvas.begin(), canvas.end());
}
