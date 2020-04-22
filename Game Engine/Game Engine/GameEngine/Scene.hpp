#pragma once

#include <list>
#include <vector>
using namespace std;

#include "./Components/GameObject.hpp"
#include "./Camera.hpp"

/*
 * Class: Scene
 * --------------------------------
 */
class Scene
{
  private:
    // The current active scene, intended to be used by scripts
    static Scene *currentScene;
    // The game objects that constitute this scene
    list<GameObject *> gameObjects;
    // Cameras in the scene
    list<Camera *> cameras;

  public:
    /*
    * Function: LoadScene
    * --------------------------------
    *  Sets the selected scene as active
    *  
    *  scene: the scene.
    */
    static void LoadScene(Scene *scene);
    
    /*
    * Function: CurrentScene
    * --------------------------------
    *  Returns the active scene
    *  
    *  returns: the active scene.
    */
    static Scene *CurrentScene();
    
    /*
    * Function: AddGameObject
    * --------------------------------
    *  Adds a game object to a scene
    *  
    *  gameObject: the game object that will be added.
    */
    void AddGameObject(GameObject *gameObject);
    
    /*
    * Function: RemoveGameObject
    * --------------------------------
    *  Removes a game object from a scene
    *  
    *  gameObject: the game object that will be removed.
    */
    void RemoveGameObject(GameObject *gameObject);

    /*
    * Function: GetGameObjects
    * --------------------------------
    *  Returns the list of game objects of a scene
    *  
    *  return: the list of game objects of the scene.
    */ 
    list<GameObject *> GetGameObjects();

    /*
    * Function: AddCamera
    * --------------------------------
    *  Adds a camera to a scene
    *
    *  camera: the camera that will be added.
    */
   void AddCamera(Camera* camera);

    /*
    * Function: RemoveGameObject
    * --------------------------------
    *  Removes a camera from a scene
    *
    *  camera: the camera that will be removed.
    */
    void RemoveCamera(Camera* camera);

    /*
    * Function: DrawScene
    * --------------------------------
    *  Draws the scene
    */
    void DrawScene();
};
