﻿#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
using namespace glm;

// GameEngine
#include "GameEngine/Components/GameObject.hpp"
#include "GameEngine/Components/Transform.hpp"
#include "GameEngine/Primitives/Square.hpp"
#include "GameEngine/Primitives/Cube.hpp"

#include "GameEngine/Camera/Orthographic.hpp"
#include "GameEngine/Camera/Perspective.hpp"

#include "GameEngine/Scene.hpp"
#include "GameEngine/Window.hpp"

#include "GameEngine/Input/Input.hpp"
#include "GameEngine/Time/Time.hpp"
#include "GameEngine/Config/Config.hpp"

#include "GameEngine/Audio/AudioDevice.hpp"

// UI
#include "GameEngine/UI/Canvas.hpp"
#include "GameEngine/UI/Button.hpp"


// Prefabs
#include "Assets/Prefabs/Player.hpp"
#include "Assets/Prefabs/Brick.hpp"
#include "Assets/Prefabs/IBlock.hpp"

// Scripts
#include "Assets/Scripts/MarathonManager.hpp"
#include "Assets/Scripts/VersusManager.hpp"
#include "Assets/Scripts/MenuLogic.hpp"
#include "Assets/Scripts/PauseMenu.hpp"

#include "Assets/Shaders/OpaqueShader.hpp"
#include "Assets/Shaders/PhongShader.hpp"

#include "main.hpp"

#include <iostream>

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
  GLFWwindow *window = glfwCreateWindow((int)dimensions.x, (int)dimensions.y, "Tetris 3D", NULL, NULL);

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
  //glClearColor(45.f/255, 52.f/255, 54.f/255, 0.0f);
  glClearColor(236.f/255, 240.f/255, 241.f/255, 0.0f);

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
  Config::LoadConfig("config.cfg");
  Config::LoadScore("score.dat");

  // Loads the scene and sets it as the active one
  //scene->AddCamera(new Perspective(45.0f, 4/3.0f, 0.1f, 500.0f, vec3(50, -100, 250), vec3(50, -100, 0), vec3(0, 1, 0)));
  scene->AddCamera(new Orthographic(vec3(-200, -150, -100), vec3(200, 150, 100)));
  
  loadLevelMainMenu(scene);
  Scene::LoadScene(scene);

  theme->Play2D("Assets/Audio/Theme_A.mp3", GL_TRUE);
  glfwSwapInterval(1);
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
    //scene->AddCamera(new Orthographic(vec3(-100, -200, -100), vec3(300 - 100, 225 - 200, 100)));
    Scene::LoadScene(scene);

    loadLevelSingleplayer(scene);
}

void callLoadLevelMultiPlayer()
{
    scene.reset(new Scene());
    
    // Single Player camera
    //scene->AddCamera(new Perspective(glm::radians(45.0f), 4 / 3.0f, 0.1f, 900, vec3(140, -90, 400), vec3(140, -90, 0), vec3(0, 1, 0)));
    scene->AddCamera(new Orthographic(vec3(-50, -220, 0), vec3(400 - 50, 300 - 220, 5)));
    Scene::LoadScene(scene);

    loadLevelMultiplayer(scene);
}

void callLoadLevelOptionMenu()
{
    scene.reset(new Scene());

    // Single Player camera
    //scene->AddCamera(new Perspective(45.0f, 4 / 3.0f, 0.1f, 500.0f, vec3(50, -100, 250), vec3(50, -100, 0), vec3(0, 1, 0)));
    scene->AddCamera(new Orthographic(vec3(-200, -150, -100), vec3(200, 150, 100)));
    Scene::LoadScene(scene);

    loadLevelOptionMenu(scene);
}

void callLoadLevelMainMenu()
{
    scene.reset(new Scene());

    // Single Player camera
    //scene->AddCamera(new Perspective(45.0f, 4 / 3.0f, 0.1f, 500.0f, vec3(50, -100, 250), vec3(50, -100, 0), vec3(0, 1, 0)));
    scene->AddCamera(new Orthographic(vec3(-200, -150, -100), vec3(200, 150, 100)));
    Scene::LoadScene(scene);

    loadLevelMainMenu(scene);

}

void setThemeA()
{
    theme->Stop();
    theme->Play2D("Assets/Audio/Theme_A.mp3", GL_TRUE);
}

void setThemeB()
{
    theme->Stop();
    theme->Play2D("Assets/Audio/Theme_B.mp3", GL_TRUE);
}

void setThemeC()
{
    theme->Stop();
    theme->Play2D("Assets/Audio/Theme_C.mp3", GL_TRUE);
}

void loadLevelOptionMenu(unique_ptr<Scene>& scene)
{    
    Canvas* canvas = new Canvas();

    const char* buttonTexture = "Assets/Sprites/na.png";
    const char* logoTexture = "Assets/Sprites/logo_2.png";
    const char* arrowTexture = "Assets/Sprites/arrow_2.png";
    const char* themeATexture = "Assets/Sprites/menu_words/themeA.png";
    const char* themeBTexture = "Assets/Sprites/menu_words/themeB.png";
    const char* themeCTexture= "Assets/Sprites/menu_words/themeC.png";
    const char* backTexture = "Assets/Sprites/menu_words/back.png";

    canvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(255, 50, 0)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), themeATexture),
        new Transform(vec3(0, 0, 0), vec3(0, 0, 0), vec3(120, 20, 5)),
        &setThemeA));

    canvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(0, 255, 50)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), themeBTexture),
        new Transform(vec3(0, -25, 0), vec3(0, 0, 0), vec3(120, 20, 5)),
        &setThemeB));

    canvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(50, 0, 255)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), themeCTexture),
        new Transform(vec3(0, -50, 0), vec3(0, 0, 0), vec3(120, 20, 5)),
        &setThemeC));
    
    canvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(50, 100, 100)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), backTexture),
        new Transform(vec3(0, -100, 0), vec3(0, 0, 0), vec3(120, 20, 5)),
        &callLoadLevelMainMenu));

    Sprite* logo = new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), logoTexture),
        new Transform(vec3(0, 75, 0), vec3(0, 0, 0), vec3(360 / 2, 220 / 2, 5)));
    canvas->AddSprite(logo);

    // Nav cursor
    // Delta é a width do botao
    canvas->AddCursor(new Cursor(new OpaqueShader(new Renderer(new Square(vec3(255, 255, 255)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), arrowTexture),
        new Transform(vec3(0, 0, 0), vec3(0, 0, 0), vec3(180 / 10, 80 / 10, 5)), -70), true);

    
    
    GameObject* go = new GameObject(
        new Transform(vec3(-200, -200, -200), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f)), nullptr, "Menu");
    go->AddScript(new MenuLogic(canvas));

    scene->AddGameObject(go);

    scene->AddCanvas(canvas);
}

void loadLevelMainMenu(unique_ptr<Scene>& scene)
{
    const char* buttonTexture = "Assets/Sprites/na.png";
    const char* logoTexture = "Assets/Sprites/logo_2.png";
    const char* arrowTexture = "Assets/Sprites/arrow_2.png";
    const char* marathonTexture = "Assets/Sprites/menu_words/marathon.png";
    const char* versusTexture = "Assets/Sprites/menu_words/versus.png";
    const char* optionsTexture = "Assets/Sprites/menu_words/options.png";


    Canvas* canvas = new Canvas();

    Button* b = new Button(new OpaqueShader(new Renderer(new Square(vec3(255, 0, 0)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), marathonTexture),
        new Transform(vec3(0, -25, 0), vec3(0, 0, 0), vec3(120, 20, 5)),
        &callLoadLevelSinglePlayer);

    Button* b2 = new Button(new OpaqueShader(new Renderer(new Square(vec3(0, 255, 0)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), versusTexture),
        new Transform(vec3(0, -50, 0), vec3(0, 0, 0), vec3(120, 20, 5)),
        &callLoadLevelMultiPlayer);

    Button* b3 = new Button(new OpaqueShader(new Renderer(new Square(vec3(0, 0, 255)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), optionsTexture),
        new Transform(vec3(0, -75, 0), vec3(0, 0, 0), vec3(120, 20, 5)),
        &callLoadLevelOptionMenu);


    Sprite* logo = new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), logoTexture),
        new Transform(vec3(0, 75, 0), vec3(0, 0, 0), vec3(360/2, 220/2, 5)));


    canvas->AddButton(b);
    canvas->AddButton(b2);
    canvas->AddButton(b3);

    canvas->AddSprite(logo);

    // Nav cursor
    // Delta é a width do botao
    canvas->AddCursor(new Cursor(new OpaqueShader(new Renderer(new Square(vec3(255, 255, 255)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), arrowTexture),
        new Transform(vec3(0, 0, 0), vec3(0, 0, 0), vec3(180/10, 80/10, 5)), -70), true);

    GameObject* go = new GameObject(
        new Transform(vec3(-200, -200, -200), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f)), nullptr, "Menu");
    go->AddScript(new MenuLogic(canvas));

    scene->AddGameObject(go);

    scene->AddCanvas(canvas);

}

void loadLevelSingleplayer(unique_ptr<Scene>& scene)
{
  const char* nextTexture = "Assets/Sprites/layout/l_next.png";
  const char* holdTexture = "Assets/Sprites/layout/l_hold.png";

  scene->AddLightSource(new LightSource(vec3(1.0f), vec3(0.4), vec3(1.0f), vec4(5.0f, 5.0f, 2.0f, 1.0f)));
  scene->AddLightSource(new LightSource(vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec4(-5.0f, 5.0f, 2.0f, 1.0f)));

  PhongShader::Init("Assets/Sprites/na.png");

  // Tabuleiro
  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(45, -195, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(100.0f, 1.0f, 10.0f)), vec3(125, 200, 10), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)));

  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(95, -95, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.0f, 200.f, 10.0f)), vec3(75, 200, 10), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)));

  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(-5, -95, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.0f, 200.f, 10.0f)), vec3(20, 200, 10), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)));

  //  Game Layout
  Canvas* canvas = new Canvas();

  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), holdTexture),
      new Transform(vec3(130, -10, -9), vec3(0, 0, 0), vec3(70, 70, 1))));
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), nextTexture),
      new Transform(vec3(130, -80, -9), vec3(0, 0, 0), vec3(70, 70, 1))));

  scene->AddCanvas(canvas);

  // Pause Menu
  const char* buttonTexture = "Assets/Sprites/na.png";
  
  Canvas* pauseCanvas = new Canvas();
  
  pauseCanvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(255, 0, 0)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), buttonTexture),
    new Transform(vec3(0, -50, 0), vec3(0, 0, 0), vec3(100, 10, 5)),
    &callLoadLevelMainMenu));

  pauseCanvas->AddCursor(new Cursor(new OpaqueShader(new Renderer(new Square(vec3(255, 255, 255)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), buttonTexture),
    new Transform(vec3(0, 0, 0), vec3(0, 0, 0), vec3(5, 5, 5)), -65), true);

  scene->AddCanvas(pauseCanvas);


  // GameManager
  GameObject* go = new GameObject(
    new Transform(vec3(-200, -200, -200), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f)), nullptr, "GameManager");
  go->AddScript(new MarathonManager());
  go->AddScript(new PauseMenu(pauseCanvas));
  go->AddScript(new MenuLogic(pauseCanvas));
  scene->AddGameObject(go);
}

void loadLevelMultiplayer(unique_ptr<Scene>& scene)
{
  // Lights
  scene->AddLightSource(new LightSource(vec3(1.0f), vec3(0.4), vec3(1.0f), vec4(5.0f, 5.0f, 2.0f, 1.0f)));
  scene->AddLightSource(new LightSource(vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec4(-5.0f, 5.0f, 2.0f, 1.0f)));

  PhongShader::Init("Assets/Sprites/na.png");


  // Pause Menu
  const char* buttonTexture = "Assets/Sprites/na.png";

  Canvas* canvas = new Canvas();

  canvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(255, 0, 0)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), buttonTexture),
    new Transform(vec3(0, -50, 0), vec3(0, 0, 0), vec3(100, 10, 5)),
    &callLoadLevelMainMenu));

  canvas->AddCursor(new Cursor(new OpaqueShader(new Renderer(new Square(vec3(255, 255, 255)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), buttonTexture),
    new Transform(vec3(0, 0, 0), vec3(0, 0, 0), vec3(5, 5, 5)), -65), true);

  scene->AddCanvas(canvas);

  // Game Managers
  GameObject* go = new GameObject(
    new Transform(vec3(-200, -200, -200), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f)), nullptr, "GameManager");

  go->AddScript(new PauseMenu(canvas));
  go->AddScript(new MenuLogic(canvas));
  go->AddScript(new VersusManager());
  scene->AddGameObject(go);


  // Tabuleiro P1
  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(45, -195, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(100.0f, 1.0f, 10.0f)), vec3(125, 200, 10), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)));

  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(95, -95, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.0f, 200.f, 10.0f)), vec3(75, 200, 10), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)));

  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(-5, -95, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.0f, 200.f, 10.0f)), vec3(20, 200, 10), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)));

  // Tabuleiro P2
  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(45 + 190, -195, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(100.0f, 1.0f, 10.0f)), vec3(125, 200, 10), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)));

  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(95 + 190, -95, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.0f, 200.f, 10.0f)), vec3(75, 200, 10), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)));

  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(-5 + 190, -95, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.0f, 200.f, 10.0f)), vec3(20, 200, 10), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)));
}
