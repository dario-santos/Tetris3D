#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
using namespace glm;

// GameEngine
#include "./GameEngine/Components/GameObject.hpp"
#include "./GameEngine/Components/Transform.hpp"
#include "./GameEngine/Primitives/Square.hpp"
#include "./GameEngine/Primitives/Circle.hpp"
#include "./GameEngine/Primitives/Cube.hpp"

#include "./GameEngine/Camera/Orthographic.hpp"
#include "./GameEngine/Camera/Perspective.hpp"

#include "./GameEngine/Scene.hpp"
#include "./GameEngine/Window.hpp"

#include "./GameEngine/Input/Input.hpp"
#include "./GameEngine/Time/Time.hpp"
#include "./GameEngine/Config/Config.hpp"

#include "./GameEngine/Audio/AudioDevice.hpp"

// Prefabs
#include "./Prefabs/Player.hpp"
#include "./Prefabs/Brick.hpp"
#include "./Prefabs/OBlock.hpp"
#include "./Prefabs/ZBlock.hpp"
#include "./Prefabs/TBlock.hpp"
#include "./Prefabs/SBlock.hpp"
#include "./Prefabs/LBlock.hpp"
#include "./Prefabs/JBlock.hpp"
#include "./Prefabs/IBlock.hpp"

#include "shader.hpp"
#include "main.hpp"

#include <iostream>

// Shaders
GLuint transparencyShader;
GLuint opaqueShader;

int main(void)
{
  // Initialization of the GLFW
  glfwInit();

  glfwWindowHint(GLFW_SAMPLES, 4); //4xMSAA
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Opengl 3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Opengl 3.3
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           // Removes functionality deprecated opengl functions
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // sets the Opengl profile as core, added in 3.2

  // Creates the window
  vec2 dimensions = vec2(800, 600);
  Window::SetDimensions(dimensions);
  GLFWwindow *window = glfwCreateWindow((int)dimensions.x, (int)dimensions.y, "Breakout With Sound", NULL, NULL);

  // Create window context
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  glewExperimental = true; // Needed for core profile
  // Initialization of GLEW
  glewInit();

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // Callbacks
  glfwSetKeyCallback(window, Input::KeyCallback);
  glfwSetWindowSizeCallback(window, Window::WindowReshapeCallback);

  // Background Color
  glClearColor(45.f/255, 52.f/255, 54.f/255, 0.0f);

  // Enable depth test and blend
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Accept fragment if it closer to the camera than the former one
  glDepthFunc(GL_LESS);

  // Transfer VAO
  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);
  
  // Initializations and configurations
  Square::Init();
  Circle::Init();
  Cube::Init();
  Config::LoadConfig("./config.cfg");

  AudioDevice *theme = new AudioDevice(30);
  theme->Play2D("audio/Theme_A.mp3", GL_TRUE);

  // Loads the scene and sets it as the active one
  Scene* scene = new Scene();
  // Single Player camera
  //scene->AddCamera(new Perspective(45.0f, 4/3.0f, 0.1f, 500.0f, vec3(50, -100, 250), vec3(50, -100, 0), vec3(0, 1, 0)));
  // Multiplayer camera
  scene->AddCamera(new Perspective(45.0f, 4 / 3.0f, 0.1f, 500.0f, vec3(125, -100, 250), vec3(125, -100, 0), vec3(0, 1, 0)));

  Scene::LoadScene(scene);
  loadLevelMultiplayer(scene);

  // render scene for each frame
  do
  {
    Time::UpdateValues();
    
    // Iterate Objects
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    lifeCycle(scene);

    // Swap buffers
    glfwSwapBuffers(window);

    // looking for events
    glfwPollEvents();
  }while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

  // Cleanup VAO, VBOs, and shaders from GPU
  for(GameObject *g: scene->GetGameObjects())
    g->~GameObject();
  scene->GetGameObjects().clear();

  /// Frees the vertex array
  glDeleteVertexArrays(1, &VertexArrayID);

  // Frees the shaders
  glDeleteProgram(transparencyShader);
  glDeleteProgram(opaqueShader);

  // Close OpenGL window and terminate GLFW
  glfwTerminate();
  return 0;
}

void loadLevelSingleplayer(Scene* scene)
{
  // Load Vertex and Fragments shaders
  transparencyShader = LoadShaders("./Shaders/TransparencyShader.vert", "./Shaders/TransparencyShader.frag");
  opaqueShader = LoadShaders("./Shaders/OpaqueShader.vert", "./Shaders/OpaqueShader.frag");

  GameObject* go = new GameObject(
    new Transform(vec3(-200, -200, -200), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f)), nullptr, "GameManager");
  go->AddScript(new GameManager(opaqueShader, 0));

  scene->AddGameObject(go);

  // Tabuleiro
  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(45, -195, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(100.0f, 1.0f, 10.0f)), vec3(125, 200, 10), opaqueShader));

  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(95, -95, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.0f, 200.f, 10.0f)), vec3(75, 200, 10), opaqueShader));

  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(-5, -95, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.0f, 200.f, 10.0f)), vec3(20, 200, 10), opaqueShader));
}

void loadLevelMultiplayer(Scene* scene)
{
  // Load Vertex and Fragments shaders
  transparencyShader = LoadShaders("./Shaders/TransparencyShader.vert", "./Shaders/TransparencyShader.frag");
  opaqueShader = LoadShaders("./Shaders/OpaqueShader.vert", "./Shaders/OpaqueShader.frag");

  GameObject* p1 = new GameObject(
    new Transform(vec3(-200, -200, -200), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f)), nullptr, "GameManager");
  p1->AddScript(new GameManager(opaqueShader, 0, Gamepad::Gamepad1));

  scene->AddGameObject(p1);

  GameObject* p2 = new GameObject(
    new Transform(vec3(-200, -200, -200), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f)), nullptr, "GameManager");
  p2->AddScript(new GameManager(opaqueShader, 150, Gamepad::Gamepad2));

  scene->AddGameObject(p2);

  // Tabuleiro P1
  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(45, -195, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(100.0f, 1.0f, 10.0f)), vec3(125, 200, 10), opaqueShader));

  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(95, -95, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.0f, 200.f, 10.0f)), vec3(75, 200, 10), opaqueShader));

  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(-5, -95, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.0f, 200.f, 10.0f)), vec3(20, 200, 10), opaqueShader));

  // Tabuleiro P2
  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(45 + 150, -195, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(100.0f, 1.0f, 10.0f)), vec3(125, 200, 10), opaqueShader));

  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(95 + 150, -95, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.0f, 200.f, 10.0f)), vec3(75, 200, 10), opaqueShader));

  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(-5 + 150, -95, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.0f, 200.f, 10.0f)), vec3(20, 200, 10), opaqueShader));
}

void lifeCycle(Scene *scene)
{
  // Garbage Collector
  for(GameObject *g : scene->GetGameObjects())
    if(g->CanDestroy())
      scene->RemoveGameObject(g);

  // Collision
  for(GameObject *g1: scene->GetGameObjects())
  {
    if(!g1->IsEnabled()) continue;

    for(GameObject *g2: scene->GetGameObjects())
    {
      if(g1 == g2 || !g2->IsEnabled()) continue; // if it's the same object or if it's not enabled

      // Center of g1
      vec3 c1 = g1->GetTransform()->position;
      // Radius of g1
      vec3 r1 = g1->GetTransform()->scale * vec3(0.5f, 0.5f, 0.5f);

      // Center of g2
      vec3 c2 = g2->GetTransform()->position;

      // if the distance between the centers is smaller than the x and y radius there's a collision
      if(abs(c1.x - c2.x) < r1.x && abs(c1.y - c2.y) < r1.y && abs(c1.z - c2.z) < r1.z)
      {
        // Invokes the OnCollision method of the objects
        for(Script *s : g1->GetScripts())
          s->OnCollision(vec3(c1.x - c2.x, c1.y - c2.y, c1.y - c2.y), g2->Tag());

        for(Script *s : g2->GetScripts())
          s->OnCollision(-vec3(c1.x - c2.x, c1.y - c2.y, c1.y - c2.y), g1->Tag());
      }
    }
  }

  // Invokes the Update callback
  for(GameObject *g : scene->GetGameObjects())
    if(g->IsEnabled())
      for(Script *s : g->GetScripts())
        s->Update();

  // Invokes the Draw callback
  scene->DrawScene();
}
