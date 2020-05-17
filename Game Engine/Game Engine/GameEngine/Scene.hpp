#pragma once

#include <list>
#include <vector>
using namespace std;

#include "./Components/GameObject.hpp"
#include "./Camera/ICamera.hpp"
#include "./UI/Canvas.hpp"

/*
 * Class: Scene
 * --------------------------------
 */
class Scene
{
  private:
    // The current active scene, intended to be used by scripts
    static Scene* currentScene;
    // The game objects that constitute this scene
    list<GameObject*> gameObjects;
    // Cameras in the scene
    list<ICamera*> cameras;
    // Canvas in scene
    list<Canvas*> canvas;

  public:
    /*
    * Function: LoadScene
    * --------------------------------
    *  Sets the selected scene as active
    *  
    *  scene: the scene.
    */
    static void LoadScene(Scene* scene);
    
    /*
    * Function: CurrentScene
    * --------------------------------
    *  Returns the active scene
    *  
    *  returns: the active scene.
    */
    static Scene* CurrentScene();
    
    /*
    * Function: AddGameObject
    * --------------------------------
    *  Adds a game object to a scene
    *  
    *  gameObject: the game object that will be added.
    */
    void AddGameObject(GameObject* gameObject);
    
    /*
    * Function: RemoveGameObject
    * --------------------------------
    *  Removes a game object from a scene
    *  
    *  gameObject: the game object that will be removed.
    */
    void RemoveGameObject(GameObject* gameObject);

    /*
    * Function: GetGameObjects
    * --------------------------------
    *  Returns the list of game objects of a scene
    *  
    *  return: the list of game objects of the scene.
    */ 
    list<GameObject*> GetGameObjects();

    /*
    * Function: AddCamera
    * --------------------------------
    *  Adds a camera to a scene
    *
    *  camera: the camera that will be added.
    */
   void AddCamera(ICamera* camera);

    /*
    * Function: RemoveGameObject
    * --------------------------------
    *  Removes a camera from a scene
    *
    *  camera: the camera that will be removed.
    */
    void RemoveCamera(ICamera* camera);

    /*
    * Function: GetCameras
    * --------------------------------
    *  Returns the list of cameras in the scene
    *
    *  return: the list of cameras in the scene.
    */
    list<ICamera*> GetCameras();

    
    void AddCanvas(Canvas* canvas);

    
    void RemoveCanvas(Canvas* Canvas);


    list<Canvas*> GetCanvas();





    /*
    * Function: DrawScene
    * --------------------------------
    *  Draws the scene
    */
    void DrawScene();

    void DrawGUI();

    void DestroyScene();
};
