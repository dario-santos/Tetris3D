#include <GL/glew.h>

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
#include "Assets/Scripts/MarathonMenuLogic.hpp"
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
  glClearColor(229.f/255, 229.f/255, 229.f/255, 0.0f);

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
    
    //scene->AddCamera(new Perspective(45.0f, 4 / 3.0f, 0.1f, 500.0f, vec3(50, -100, 250), vec3(50, -100, 0), vec3(0, 1, 0)));
    scene->AddCamera(new Orthographic(vec3(-150, -250, -100), vec3(250, 50, 100)));
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

void callLoadLevelMainMenu()
{
    scene.reset(new Scene());

    // Single Player camera
    //scene->AddCamera(new Perspective(45.0f, 4 / 3.0f, 0.1f, 500.0f, vec3(50, -100, 250), vec3(50, -100, 0), vec3(0, 1, 0)));
    scene->AddCamera(new Orthographic(vec3(-200, -150, -100), vec3(200, 150, 100)));
    Scene::LoadScene(scene);

    loadLevelMainMenu(scene);

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

void callLoadLevelMarathonMenu()
{
    scene.reset(new Scene());

    // Single Player camera
    //scene->AddCamera(new Perspective(45.0f, 4 / 3.0f, 0.1f, 500.0f, vec3(50, -100, 250), vec3(50, -100, 0), vec3(0, 1, 0)));
    scene->AddCamera(new Orthographic(vec3(-200, -150, -100), vec3(200, 150, 100)));
    Scene::LoadScene(scene);

    loadLevelMarathonMenu(scene);
}

void callLoadLevelVersusMenu()
{
    scene.reset(new Scene());

    // Single Player camera
    //scene->AddCamera(new Perspective(45.0f, 4 / 3.0f, 0.1f, 500.0f, vec3(50, -100, 250), vec3(50, -100, 0), vec3(0, 1, 0)));
    scene->AddCamera(new Orthographic(vec3(-200, -150, -100), vec3(200, 150, 100)));
    Scene::LoadScene(scene);

    loadLevelVersusMenu(scene);
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

void loadLevelMainMenu(unique_ptr<Scene>& scene)
{
    const char* buttonTexture   = "Assets/Sprites/na.png";
    const char* logoTexture     = "Assets/Sprites/logos/logo.png";
    const char* arrowTexture    = "Assets/Sprites/buttons/cursor.png";
    const char* marathonTexture = "Assets/Sprites/buttons/marathon.png";
    const char* versusTexture   = "Assets/Sprites/buttons/versus.png";
    const char* optionsTexture  = "Assets/Sprites/buttons/options.png";


    Canvas* canvas = new Canvas();

    Button* b = new Button(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), marathonTexture),
        new Transform(vec3(0, -25, 0), vec3(0, 0, 0), vec3(120, 20, 5)),
        &callLoadLevelMarathonMenu);

    Button* b2 = new Button(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), versusTexture),
        new Transform(vec3(0, -50, 0), vec3(0, 0, 0), vec3(120, 20, 5)),
        &callLoadLevelVersusMenu);

    Button* b3 = new Button(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), optionsTexture),
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
    canvas->AddCursor(new Cursor(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), arrowTexture),
        new Transform(vec3(0, 0, 0), vec3(0, 0, 0), vec3(180/10, 80/10, 5)), -70), true);

    GameObject* go = new GameObject(
        new Transform(vec3(-200, -200, -200), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f)), nullptr, "Menu");
    go->AddScript(new MenuLogic(canvas));

    scene->AddGameObject(go);

    scene->AddCanvas(canvas);

}

void loadLevelMarathonMenu(unique_ptr<Scene>& scene)
{
    Canvas* canvas = new Canvas();

    const char* plusTexture = "Assets/Sprites/buttons/plus.png";
    const char* minusTexture = "Assets/Sprites/buttons/minus.png";
    const char* zero = "Assets/Sprites/digits/zero.png";
    const char* levelTexture = "Assets/Sprites/gp_buttons/w_level.png";
    const char* pressTexture = "Assets/Sprites/gp_buttons/w_press.png";
    const char* buttonStart= "Assets/Sprites/gp_buttons/gp_start.png";


    //  Plus and Minus
    canvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), plusTexture),
        new Transform(vec3(40, 0, 0), vec3(0, 0, 0), vec3(512 / 32, 512 / 32, 5)),
        &callLoadLevelSinglePlayer));
    canvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), minusTexture),
        new Transform(vec3(-40, 0, 0), vec3(0, 0, 0), vec3(512 / 32, 512 / 32, 5)),
        &callLoadLevelSinglePlayer));

    //  Digits
    canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zero),
        new Transform(vec3(-10, 0, 0), vec3(0, 0, 0), vec3(20, 40, 5))));
    canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zero),
        new Transform(vec3(10, 0, 0), vec3(0, 0, 0), vec3(20, 40, 5))));

    //  Level word
    canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), levelTexture),
        new Transform(vec3(0, -30, 0), vec3(0, 0, 0), vec3(47, 17, 5))));

    //  Press START
    canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), pressTexture),
        new Transform(vec3(-25, 80, 0), vec3(0, 0, 0), vec3(47, 13, 5))));
    canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), buttonStart),
        new Transform(vec3(25, 80, 0), vec3(0, 0, 0), vec3(81/2, 41/2, 5))));



    GameObject* go = new GameObject(
        new Transform(vec3(-200, -200, -200), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f)), nullptr, "Menu");
    go->AddScript(new MarathonMenuLogic(canvas));

    scene->AddGameObject(go);

    scene->AddCanvas(canvas);
}

void loadLevelVersusMenu(unique_ptr<Scene>& scene)
{
    Canvas* canvas = new Canvas();

    const char* plusTexture = "Assets/Sprites/buttons/plus.png";
    const char* minusTexture = "Assets/Sprites/buttons/minus.png";
    const char* zero = "Assets/Sprites/digits/zero.png";
    const char* levelTexture = "Assets/Sprites/gp_buttons/w_level.png";
    const char* pressTexture = "Assets/Sprites/gp_buttons/w_press.png";
    const char* buttonStart = "Assets/Sprites/gp_buttons/gp_start.png";


    //  Plus and Minus
    canvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), plusTexture),
        new Transform(vec3(40, 0, 0), vec3(0, 0, 0), vec3(512 / 32, 512 / 32, 5)),
        &callLoadLevelMultiPlayer));
    canvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), minusTexture),
        new Transform(vec3(-40, 0, 0), vec3(0, 0, 0), vec3(512 / 32, 512 / 32, 5)),
        &callLoadLevelMultiPlayer));

    //  Digits
    canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zero),
        new Transform(vec3(-10, 0, 0), vec3(0, 0, 0), vec3(20, 40, 5))));
    canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zero),
        new Transform(vec3(10, 0, 0), vec3(0, 0, 0), vec3(20, 40, 5))));

    //  Level word
    canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), levelTexture),
        new Transform(vec3(0, -30, 0), vec3(0, 0, 0), vec3(47, 17, 5))));

    //  Press START
    canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), pressTexture),
        new Transform(vec3(-25, 80, 0), vec3(0, 0, 0), vec3(47, 13, 5))));
    canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), buttonStart),
        new Transform(vec3(25, 80, 0), vec3(0, 0, 0), vec3(81 / 2, 41 / 2, 5))));



    GameObject* go = new GameObject(
        new Transform(vec3(-200, -200, -200), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f)), nullptr, "Menu");
    go->AddScript(new MarathonMenuLogic(canvas));

    scene->AddGameObject(go);

    scene->AddCanvas(canvas);
}

void loadLevelOptionMenu(unique_ptr<Scene>& scene)
{    
    Canvas* canvas = new Canvas();

    const char* buttonTexture = "Assets/Sprites/na.png";
    const char* logoTexture = "Assets/Sprites/logos/logo.png";
    const char* arrowTexture = "Assets/Sprites/buttons/cursor.png";
    const char* themeATexture = "Assets/Sprites/buttons/themeA.png";
    const char* themeBTexture = "Assets/Sprites/buttons/themeB.png";
    const char* themeCTexture= "Assets/Sprites/buttons/themeC.png";
    const char* backTexture = "Assets/Sprites/buttons/back.png";

    canvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), themeATexture),
        new Transform(vec3(0, 0, 0), vec3(0, 0, 0), vec3(120, 20, 5)),
        &setThemeA));

    canvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), themeBTexture),
        new Transform(vec3(0, -25, 0), vec3(0, 0, 0), vec3(120, 20, 5)),
        &setThemeB));

    canvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), themeCTexture),
        new Transform(vec3(0, -50, 0), vec3(0, 0, 0), vec3(120, 20, 5)),
        &setThemeC));
    
    canvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), backTexture),
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


void loadLevelSingleplayer(unique_ptr<Scene>& scene)
{
  const char* nextTexture = "Assets/Sprites/layouts/next.png";
  const char* holdTexture = "Assets/Sprites/layouts/hold.png";
  const char* scoreTexture = "Assets/Sprites/layouts/score.png";
  const char* levelTexture = "Assets/Sprites/layouts/level.png";
  const char* bgTexture = "Assets/Sprites/backgrounds/dark.png";

  const char* buttonA = "Assets/Sprites/gp_buttons/gp_A.png";
  const char* rotateA = "Assets/Sprites/gp_buttons/clockwise.png";

  const char* buttonB = "Assets/Sprites/gp_buttons/gp_B.png";
  const char* rotateB = "Assets/Sprites/gp_buttons/counterclockwise.png";

  const char* buttonSTART = "Assets/Sprites/gp_buttons/gp_START.png";
  const char* pauseTexture = "Assets/Sprites/gp_buttons/w_pause.png";

  const char* zero = "Assets/Sprites/digits/zero.png";
  
  //const char* countTexture = "Assets/Sprites/layouts/count.png";

  scene->AddLightSource(new LightSource(vec3(1.0f), vec3(0.4), vec3(1.0f), vec4(5.0f, 5.0f, 2.0f, 1.0f)));
  scene->AddLightSource(new LightSource(vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec4(-5.0f, 5.0f, 2.0f, 1.0f)));

  PhongShader::Init("Assets/Sprites/blocks/sample.png");

  // Tabuleiro
  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(45, -195, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(100.0f, 1.0f, 10.0f)), vec3(125, 200, 10), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)));

  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(95, -95, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.0f, 200.f, 10.0f)), vec3(75, 200, 10), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)));

  scene->AddGameObject(Brick::AddBrick(
    new Transform(vec3(-5, -95, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.0f, 200.f, 10.0f)), vec3(20, 200, 10), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)));

  //  Game Layout
  Canvas* canvas = new Canvas();

  //    Score digits
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zero),
      new Transform(vec3(30, 15, -9), vec3(0, 0, 0), vec3(20/2, 40/2, 1))));
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zero),
      new Transform(vec3(40, 15, -9), vec3(0, 0, 0), vec3(20/2, 40/2, 1))));
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zero),
      new Transform(vec3(50, 15, -9), vec3(0, 0, 0), vec3(20/2, 40/2, 1))));
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zero),
      new Transform(vec3(65, 15, -9), vec3(0, 0, 0), vec3(20/2, 40/2, 1))));
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zero),
      new Transform(vec3(75, 15, -9), vec3(0, 0, 0), vec3(20/2, 40/2, 1))));
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zero),
      new Transform(vec3(85, 15, -9), vec3(0, 0, 0), vec3(20/2, 40/2, 1))));

  //    Level digits
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zero),
      new Transform(vec3(75, -206, -9), vec3(0, 0, 0), vec3(20 / 2, 40 / 2, 1))));
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zero),
      new Transform(vec3(85, -206, -9), vec3(0, 0, 0), vec3(20 / 2, 40 / 2, 1))));

  //    HOLD - NEXT - SCORE - LEVEL
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), holdTexture),
      new Transform(vec3(134, -10, -9), vec3(0, 0, 0), vec3(70, 70, 1))));
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), nextTexture),
      new Transform(vec3(134, -80, -9), vec3(0, 0, 0), vec3(70, 70, 1))));
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), scoreTexture),
      new Transform(vec3(42, 15, 0), vec3(0, 0, 0), vec3(110, 20, 1))));
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), levelTexture),
      new Transform(vec3(45, -206, 0), vec3(0, 0, 0), vec3(110, 20, 1))));

  //    rotate clockwise
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), buttonA),
      new Transform(vec3(145, -155, 0), vec3(0, 0, 0), vec3(40/2, 40/2, 1))));
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), rotateA),
      new Transform(vec3(180, -155, 0), vec3(0, 0, 0), vec3(40/2, 40/2, 1))));

  //    rotate counterclockwise
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), buttonB),
      new Transform(vec3(145, -190, 0), vec3(0, 0, 0), vec3(40/2, 40/2, 1))));
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), rotateB),
      new Transform(vec3(180, -190, 0), vec3(0, 0, 0), vec3(40/2, 40/2, 1))));

  //    Pause button
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), buttonSTART),
      new Transform(vec3(-60, -170, 0), vec3(0, 0, 0), vec3(80/2, 40/2, 1))));
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), pauseTexture),
      new Transform(vec3(-60, -190, 0), vec3(0, 0, 0), vec3(41, 12, 1))));

  
  //    Background
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), bgTexture),
      new Transform(vec3(44.5, -96, 0), vec3(0, 0, 0), vec3(101, 200, 1))));
  

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
  go->AddScript(new MarathonManager(canvas));
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
