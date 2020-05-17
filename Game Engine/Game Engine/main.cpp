#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
using namespace glm;

// GameEngine
#include "./GameEngine/Components/GameObject.hpp"
#include "./GameEngine/Components/Transform.hpp"
#include "./GameEngine/Primitives/Square.hpp"
#include "./GameEngine/Primitives/Cube.hpp"

#include "./GameEngine/Camera/Orthographic.hpp"
#include "./GameEngine/Camera/Perspective.hpp"

#include "./GameEngine/Scene.hpp"
#include "./GameEngine/Window.hpp"

#include "./GameEngine/Input/Input.hpp"
#include "./GameEngine/Time/Time.hpp"
#include "./GameEngine/Config/Config.hpp"

#include "./GameEngine/Audio/AudioDevice.hpp"

// UI
#include "./GameEngine/UI/Canvas.hpp"
#include "./GameEngine/UI/Button.hpp"


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

// Scripts
#include "./Scripts/MenuLogic.hpp"

#include "shader.hpp"
#include "main.hpp"

#include <iostream>

// Shaders
GLuint transparencyShader;
GLuint opaqueShader;
GLuint phongShader;

unique_ptr<Scene> scene (new Scene());
unique_ptr<AudioDevice> theme(new AudioDevice(75));

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
  GLFWwindow *window = glfwCreateWindow((int)dimensions.x, (int)dimensions.y, "Tetris", NULL, NULL);

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
  Cube::Init();
  Config::LoadConfig("./config.cfg");

  // Loads the scene and sets it as the active one
  scene->AddCamera(new Perspective(45.0f, 4/3.0f, 0.1f, 500.0f, vec3(50, -100, 250), vec3(50, -100, 0), vec3(0, 1, 0)));
  
  loadLevelMainMenu(scene);
  Scene::LoadScene(scene);

  theme->Play2D("audio/Theme_A.mp3", GL_TRUE);

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
  glDeleteProgram(phongShader);

  // Close OpenGL window and terminate GLFW
  glfwTerminate();
  return 0;
}

void lifeCycle(unique_ptr<Scene>& scene)
{
  // Garbage Collector
  for (GameObject* g : scene->GetGameObjects())
    if (g->CanDestroy())
      scene->RemoveGameObject(g);

  // Collision
  for (GameObject* g1 : scene->GetGameObjects())
  {
    if (!g1->IsEnabled()) continue;

    for (GameObject* g2 : scene->GetGameObjects())
    {
      if (g1 == g2 || !g2->IsEnabled()) continue; // if it's the same object or if it's not enabled

      // Center of g1
      vec3 c1 = g1->GetTransform()->position;
      // Radius of g1
      vec3 r1 = g1->GetTransform()->scale * vec3(0.5f, 0.5f, 0.5f);

      // Center of g2
      vec3 c2 = g2->GetTransform()->position;

      // if the distance between the centers is smaller than the x and y radius there's a collision
      if (abs(c1.x - c2.x) < r1.x && abs(c1.y - c2.y) < r1.y && abs(c1.z - c2.z) < r1.z)
      {
        // Invokes the OnCollision method of the objects
        for (Script* s : g1->GetScripts())
          s->OnCollision(vec3(c1.x - c2.x, c1.y - c2.y, c1.y - c2.y), g2->Tag());

        for (Script* s : g2->GetScripts())
          s->OnCollision(-vec3(c1.x - c2.x, c1.y - c2.y, c1.y - c2.y), g1->Tag());
      }
    }
  }

  // Invokes the Update callback
  for (GameObject* g : scene->GetGameObjects())
    if (g->IsEnabled())
      for (Script* s : g->GetScripts())
        s->Update();

  // Invokes the Draw callback
  scene->DrawScene();

  scene->DrawGUI();
}

void callLoadLevelSinglePlayer()
{
    scene.reset(new Scene());

    // Single Player camera
    scene->AddCamera(new Perspective(45.0f, 4 / 3.0f, 0.1f, 500.0f, vec3(50, -100, 250), vec3(50, -100, 0), vec3(0, 1, 0)));
    Scene::LoadScene(scene);

    loadLevelSingleplayer(scene);
}

void callLoadLevelMultiPlayer()
{
    scene.reset(new Scene());

    // Single Player camera
    scene->AddCamera(new Perspective(45.0f, 4 / 3.0f, 0.1f, 500.0f, vec3(125, -100, 250), vec3(125, -100, 0), vec3(0, 1, 0)));
    Scene::LoadScene(scene);

    loadLevelMultiplayer(scene);
}

void callLoadLevelOptionMenu()
{
    scene.reset(new Scene());

    // Single Player camera
    scene->AddCamera(new Perspective(45.0f, 4 / 3.0f, 0.1f, 500.0f, vec3(50, -100, 250), vec3(50, -100, 0), vec3(0, 1, 0)));
    Scene::LoadScene(scene);

    loadLevelOptionMenu(scene);
}

void callLoadLevelMainMenu()
{
    scene.reset(new Scene());

    // Single Player camera
    scene->AddCamera(new Perspective(45.0f, 4 / 3.0f, 0.1f, 500.0f, vec3(50, -100, 250), vec3(50, -100, 0), vec3(0, 1, 0)));
    Scene::LoadScene(scene);
    loadLevelMainMenu(scene);

}

void setThemeA()
{
    theme->Stop();
    theme->Play2D("audio/Theme_A.mp3", GL_TRUE);
}

void setThemeB()
{
    theme->Stop();
    theme->Play2D("audio/Theme_B.mp3", GL_TRUE);
}

void setThemeC()
{
    theme->Stop();
    theme->Play2D("audio/Theme_C.mp3", GL_TRUE);
}

void loadLevelOptionMenu(unique_ptr<Scene>& scene)
{
    opaqueShader = LoadShaders("./Shaders/OpaqueShader.vert", "./Shaders/OpaqueShader.frag");

    Canvas* canvas = new Canvas();

    canvas->AddButton(new Button(new Renderer(new Square(vec3(255, 50, 0)), opaqueShader),
        new Transform(vec3(50, -50, 1), vec3(0, 0, 0), vec3(5, 5, 5)),
        &setThemeA));

    canvas->AddButton(new Button(new Renderer(new Square(vec3(0, 255, 50)), opaqueShader),
        new Transform(vec3(25, -50, 1), vec3(0, 0, 0), vec3(5, 5, 5)),
        &setThemeB));

    canvas->AddButton(new Button(new Renderer(new Square(vec3(50, 0, 255)), opaqueShader),
        new Transform(vec3(0, -50, 1), vec3(0, 0, 0), vec3(5, 5, 5)),
        &setThemeC));

    canvas->AddButton(new Button(new Renderer(new Square(vec3(50, 100, 100)), opaqueShader),
        new Transform(vec3(-100, -50, 1), vec3(0, 0, 0), vec3(5, 5, 5)),
        &callLoadLevelMainMenu));

    
    GameObject* go = new GameObject(
        new Transform(vec3(-200, -200, -200), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f)), nullptr, "Menu");
    go->AddScript(new MenuLogic(canvas));

    scene->AddGameObject(go);

    scene->AddCanvas(canvas);

}

void loadLevelMainMenu(unique_ptr<Scene>& scene)
{
    opaqueShader = LoadShaders("./Shaders/OpaqueShader.vert", "./Shaders/OpaqueShader.frag");

    Canvas* canvas = new Canvas();

    
    Button* b = new Button(new Renderer(new Square(vec3(255, 0, 0)), opaqueShader),
        new Transform(vec3(50, -50, 1), vec3(0,0,0), vec3(5, 5, 5)),
        &callLoadLevelSinglePlayer);

    Button* b2 = new Button(new Renderer(new Square(vec3(0, 255, 0)), opaqueShader),
        new Transform(vec3(25, -50, 1), vec3(0, 0, 0), vec3(5, 5, 5)),
        &callLoadLevelMultiPlayer);

    Button* b3 = new Button(new Renderer(new Square(vec3(0, 0, 255)), opaqueShader),
        new Transform(vec3(0, -50, 1), vec3(0, 0, 0), vec3(5, 5, 5)),
        &callLoadLevelOptionMenu);


    canvas->AddButton(b);
    canvas->AddButton(b2);
    canvas->AddButton(b3);

    GameObject* go = new GameObject(
        new Transform(vec3(-200, -200, -200), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f)), nullptr, "Menu");
    go->AddScript(new MenuLogic(canvas));

    scene->AddGameObject(go);

    scene->AddCanvas(canvas);

}

void loadLevelSingleplayer(unique_ptr<Scene>& scene)
{
  // Load Vertex and Fragments shaders
  transparencyShader = LoadShaders("./Shaders/TransparencyShader.vert", "./Shaders/TransparencyShader.frag");
  opaqueShader = LoadShaders("./Shaders/OpaqueShader.vert", "./Shaders/OpaqueShader.frag");
  phongShader = LoadShaders("./Shaders/PhongShader.vert", "./Shaders/PhongShader.frag");

  GameObject* go = new GameObject(
    new Transform(vec3(-200, -200, -200), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f)), nullptr, "GameManager");
  go->AddScript(new GameManager(phongShader, 0, Gamepad::Gamepad1));

  scene->AddGameObject(go);

  // Tabuleiro
  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(45, -195, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(100.0f, 1.0f, 10.0f)), vec3(125, 200, 10), phongShader));

  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(95, -95, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.0f, 200.f, 10.0f)), vec3(75, 200, 10), opaqueShader));

  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(-5, -95, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.0f, 200.f, 10.0f)), vec3(20, 200, 10), phongShader));

}

void loadLevelMultiplayer(unique_ptr<Scene>& scene)
{
  // Load Vertex and Fragments shaders
  transparencyShader = LoadShaders("./Shaders/TransparencyShader.vert", "./Shaders/TransparencyShader.frag");
  opaqueShader = LoadShaders("./Shaders/OpaqueShader.vert", "./Shaders/OpaqueShader.frag");
  phongShader = LoadShaders("./Shaders/PhongShader.vert", "./Shaders/PhongShader.frag");

  GameObject* p1 = new GameObject(
    new Transform(vec3(-200, -200, -200), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f)), nullptr, "GameManager");
  p1->AddScript(new GameManager(phongShader, 0, Gamepad::Gamepad1));

  scene->AddGameObject(p1);

  GameObject* p2 = new GameObject(
    new Transform(vec3(-200, -200, -200), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f)), nullptr, "GameManager");
  p2->AddScript(new GameManager(transparencyShader, 150, Gamepad::Gamepad2));

  scene->AddGameObject(p2);

  // Tabuleiro P1
  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(45, -195, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(100.0f, 1.0f, 10.0f)), vec3(125, 200, 10), phongShader));

  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(95, -95, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.0f, 200.f, 10.0f)), vec3(75, 200, 10), phongShader));

  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(-5, -95, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.0f, 200.f, 10.0f)), vec3(20, 200, 10), phongShader));

  // Tabuleiro P2
  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(45 + 150, -195, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(100.0f, 1.0f, 10.0f)), vec3(125, 200, 10), opaqueShader));

  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(95 + 150, -95, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.0f, 200.f, 10.0f)), vec3(75, 200, 10), opaqueShader));

  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(-5 + 150, -95, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.0f, 200.f, 10.0f)), vec3(20, 200, 10), opaqueShader));
}
