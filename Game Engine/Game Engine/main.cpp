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


const char* buttonTexture = "Assets/Sprites/na.png";
const char* logoTexture = "Assets/Sprites/logos/logo.png";

const char* marathonTexture = "Assets/Sprites/buttons/marathon.png";
const char* versusTexture = "Assets/Sprites/buttons/versus.png";
const char* optionsTexture = "Assets/Sprites/buttons/options.png";
const char* arrowTexture = "Assets/Sprites/buttons/cursor.png";
const char* themeATexture = "Assets/Sprites/buttons/themeA.png";
const char* themeBTexture = "Assets/Sprites/buttons/themeB.png";
const char* themeCTexture = "Assets/Sprites/buttons/themeC.png";
const char* backTexture = "Assets/Sprites/buttons/back.png";
const char* menuTexture = "Assets/Sprites/buttons/menu.png";
const char* plusTexture = "Assets/Sprites/buttons/plus.png";
const char* minusTexture = "Assets/Sprites/buttons/minus.png";
const char* cameraTexture = "Assets/Sprites/buttons/camera2d.png";

const char* nextTexture = "Assets/Sprites/layouts/next.png";
const char* holdTexture = "Assets/Sprites/layouts/hold.png";
const char* scoreTexture = "Assets/Sprites/layouts/score.png";
const char* levelTexture = "Assets/Sprites/layouts/level.png";

const char* darkbgTexture = "Assets/Sprites/backgrounds/dark.png";
const char* softbgTexture = "Assets/Sprites/backgrounds/soft.png";

const char* buttonA = "Assets/Sprites/gp_buttons/gp_A.png";
const char* rotateA = "Assets/Sprites/gp_buttons/clockwise.png";
const char* buttonB = "Assets/Sprites/gp_buttons/gp_B.png";
const char* rotateB = "Assets/Sprites/gp_buttons/counterclockwise.png";
const char* buttonSTART = "Assets/Sprites/gp_buttons/gp_START.png";
const char* pauseTexture = "Assets/Sprites/gp_buttons/w_pause.png";
const char* pressTexture = "Assets/Sprites/gp_buttons/w_press.png";
const char* wlevelTexture = "Assets/Sprites/gp_buttons/w_level.png";

const char* zeroTexture = "Assets/Sprites/digits/zero.png";

//  Game cameras
bool defaultcamera = true;


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

void setCamera()
{
    if (defaultcamera)
    {
        defaultcamera = false;
        cameraTexture = "Assets/Sprites/buttons/camera3d.png";
    }
        
    else
    {
        defaultcamera = true;
        cameraTexture = "Assets/Sprites/buttons/camera2d.png";
    }
        
}

void callLoadLevelSinglePlayer()
{
    scene.reset(new Scene());

    // Single Player camera 
    if (defaultcamera)
        scene->AddCamera(new Orthographic(vec3(-150, -250, -100), vec3(250, 50, 100)));
    else
        scene->AddCamera(new Perspective(45.0f, 4 / 3.0f, 0.1f, 500.0f, vec3(50, -100, 250), vec3(50, -100, 0), vec3(0, 1, 0)));
    
    Scene::LoadScene(scene);

    loadLevelSingleplayer(scene);
}

void callLoadLevelMultiPlayer()
{
    scene.reset(new Scene());
    
    //  640 x 480 | 400 x 300 | 320 x 240
    
    // Multiplayer camera
    if (defaultcamera)
        scene->AddCamera(new Orthographic(vec3(-25, -240, -100), vec3(375, 60, 100)));
    else
        scene->AddCamera(new Perspective(radians(45.0f), 4 / 3.0f, 0.1f, 700, vec3(170, -90, 400), vec3(170, -90, 0), vec3(0, 1, 0)));

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

void loadLevelMainMenu(unique_ptr<Scene>& scene)
{

    Canvas* canvas = new Canvas();

    canvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), marathonTexture),
        new Transform(vec3(0, -25, 0), vec3(0, 0, 0), vec3(120, 20, 5)),
        &callLoadLevelMarathonMenu));

    canvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), versusTexture),
        new Transform(vec3(0, -50, 0), vec3(0, 0, 0), vec3(120, 20, 5)),
        &callLoadLevelVersusMenu));

    canvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), optionsTexture),
        new Transform(vec3(0, -75, 0), vec3(0, 0, 0), vec3(120, 20, 5)),
        &callLoadLevelOptionMenu));


    canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), logoTexture),
        new Transform(vec3(0, 75, 0), vec3(0, 0, 0), vec3(360/2, 220/2, 5))));


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

    //  Plus and Minus
    canvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), plusTexture),
        new Transform(vec3(40, 0, 0), vec3(0, 0, 0), vec3(512 / 32, 512 / 32, 5)),
        &callLoadLevelSinglePlayer));
    canvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), minusTexture),
        new Transform(vec3(-40, 0, 0), vec3(0, 0, 0), vec3(512 / 32, 512 / 32, 5)),
        &callLoadLevelSinglePlayer));

    //  Digits
    canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
        new Transform(vec3(-10, 0, 0), vec3(0, 0, 0), vec3(20, 40, 5))));
    canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
        new Transform(vec3(10, 0, 0), vec3(0, 0, 0), vec3(20, 40, 5))));

    //  Level word
    canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), wlevelTexture),
        new Transform(vec3(0, -30, 0), vec3(0, 0, 0), vec3(47, 17, 5))));

    //  Press START
    canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), pressTexture),
        new Transform(vec3(-25, 80, 0), vec3(0, 0, 0), vec3(47, 13, 5))));
    canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), buttonSTART),
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

    //  Plus and Minus
    canvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), plusTexture),
        new Transform(vec3(40, 0, 0), vec3(0, 0, 0), vec3(512 / 32, 512 / 32, 5)),
        &callLoadLevelMultiPlayer));
    canvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), minusTexture),
        new Transform(vec3(-40, 0, 0), vec3(0, 0, 0), vec3(512 / 32, 512 / 32, 5)),
        &callLoadLevelMultiPlayer));

    //  Digits
    canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
        new Transform(vec3(-10, 0, 0), vec3(0, 0, 0), vec3(20, 40, 5))));
    canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
        new Transform(vec3(10, 0, 0), vec3(0, 0, 0), vec3(20, 40, 5))));

    //  Level word
    canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), wlevelTexture),
        new Transform(vec3(0, -30, 0), vec3(0, 0, 0), vec3(47, 17, 5))));

    //  Press START
    canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), pressTexture),
        new Transform(vec3(-25, 80, 0), vec3(0, 0, 0), vec3(47, 13, 5))));
    canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), buttonSTART),
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

    canvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), themeATexture),
        new Transform(vec3(0, 0, 0), vec3(0, 0, 0), vec3(120, 20, 5)),
        &setThemeA));

    canvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), themeBTexture),
        new Transform(vec3(0, -25, 0), vec3(0, 0, 0), vec3(120, 20, 5)),
        &setThemeB));

    canvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), themeCTexture),
        new Transform(vec3(0, -50, 0), vec3(0, 0, 0), vec3(120, 20, 5)),
        &setThemeC));

    canvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), cameraTexture),
        new Transform(vec3(0, -75, 0), vec3(0, 0, 0), vec3(120, 20, 5)),
        &setCamera));
    
    canvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), backTexture),
        new Transform(vec3(0, -125, 0), vec3(0, 0, 0), vec3(120, 20, 5)),
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
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
      new Transform(vec3(30, 15, -9), vec3(0, 0, 0), vec3(20/2, 40/2, 1))));
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
      new Transform(vec3(40, 15, -9), vec3(0, 0, 0), vec3(20/2, 40/2, 1))));
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
      new Transform(vec3(50, 15, -9), vec3(0, 0, 0), vec3(20/2, 40/2, 1))));
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
      new Transform(vec3(65, 15, -9), vec3(0, 0, 0), vec3(20/2, 40/2, 1))));
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
      new Transform(vec3(75, 15, -9), vec3(0, 0, 0), vec3(20/2, 40/2, 1))));
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
      new Transform(vec3(85, 15, -9), vec3(0, 0, 0), vec3(20/2, 40/2, 1))));

  //    Level digits
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
      new Transform(vec3(75, -206, -9), vec3(0, 0, 0), vec3(20 / 2, 40 / 2, 1))));
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
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
  canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), darkbgTexture),
      new Transform(vec3(44.5, -95, 0), vec3(0, 0, 0), vec3(101, 200, 1))));
  

  scene->AddCanvas(canvas);





  // Pause Menu
  const char* backTexture = "Assets/Sprites/buttons/back.png";
  const char* arrowTexture = "Assets/Sprites/buttons/cursor.png";
  const char* menuTexture = "Assets/Sprites/buttons/menu.png";
  
  Canvas* pauseCanvas = new Canvas();

  //    MENU BUTTON
  pauseCanvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), menuTexture),
    new Transform(vec3(-70, 15, 0), vec3(0, 0, 0), vec3(120/2, 20/2, 5)),
    &callLoadLevelMainMenu));

  pauseCanvas->AddCursor(new Cursor(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), arrowTexture),
    new Transform(vec3(0, 0, 0), vec3(0, 0, 0), vec3(180/20, 80/20, 5)), -40), true);

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
  //  Space between p1 and p2 boards
  const float space = 190;

  // Lights
  scene->AddLightSource(new LightSource(vec3(1.0f), vec3(0.4), vec3(1.0f), vec4(5.0f, 5.0f, 2.0f, 1.0f)));
  scene->AddLightSource(new LightSource(vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec4(-5.0f, 5.0f, 2.0f, 1.0f)));

  PhongShader::Init("Assets/Sprites/blocks/sample.png");

  //    Tabuleiro P1
  scene->AddGameObject(Brick::AddBrick(
      new Transform(vec3(45, -195, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(100.0f, 1.0f, 10.0f)), vec3(125, 200, 10), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)));
  scene->AddGameObject(Brick::AddBrick(
      new Transform(vec3(95, -95, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.0f, 200.f, 10.0f)), vec3(75, 200, 10), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)));
  scene->AddGameObject(Brick::AddBrick(
      new Transform(vec3(-5, -95, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.0f, 200.f, 10.0f)), vec3(20, 200, 10), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)));

  //    Tabuleiro P2
  scene->AddGameObject(Brick::AddBrick(
      new Transform(vec3(45 + space, -195, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(100.0f, 1.0f, 10.0f)), vec3(125, 200, 10), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)));
  scene->AddGameObject(Brick::AddBrick(
      new Transform(vec3(95 + space, -95, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.0f, 200.f, 10.0f)), vec3(75, 200, 10), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)));
  scene->AddGameObject(Brick::AddBrick(
      new Transform(vec3(-5 + space, -95, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.0f, 200.f, 10.0f)), vec3(20, 200, 10), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)));


  //    Canvas
  Canvas* p1canvas = new Canvas();
  Canvas* p2canvas = new Canvas();
  Canvas* pauseCanvas = new Canvas();



  //    PLAYER 1 LAYOUT
  //    Score digits
  p1canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
      new Transform(vec3(30, 15, -9), vec3(0, 0, 0), vec3(20 / 2, 40 / 2, 1))));
  p1canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
      new Transform(vec3(40, 15, -9), vec3(0, 0, 0), vec3(20 / 2, 40 / 2, 1))));
  p1canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
      new Transform(vec3(50, 15, -9), vec3(0, 0, 0), vec3(20 / 2, 40 / 2, 1))));
  p1canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
      new Transform(vec3(65, 15, -9), vec3(0, 0, 0), vec3(20 / 2, 40 / 2, 1))));
  p1canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
      new Transform(vec3(75, 15, -9), vec3(0, 0, 0), vec3(20 / 2, 40 / 2, 1))));
  p1canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
      new Transform(vec3(85, 15, -9), vec3(0, 0, 0), vec3(20 / 2, 40 / 2, 1))));

  //    Level digits
  p1canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
      new Transform(vec3(75, -206, -9), vec3(0, 0, 0), vec3(20 / 2, 40 / 2, 1))));
  p1canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
      new Transform(vec3(85, -206, -9), vec3(0, 0, 0), vec3(20 / 2, 40 / 2, 1))));

  //    HOLD - NEXT - SCORE - LEVEL
  p1canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), holdTexture),
      new Transform(vec3(134, -10, -9), vec3(0, 0, 0), vec3(70, 70, 1))));
  p1canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), nextTexture),
      new Transform(vec3(134, -80, -9), vec3(0, 0, 0), vec3(70, 70, 1))));
  p1canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), scoreTexture),
      new Transform(vec3(42, 15, 0), vec3(0, 0, 0), vec3(110, 20, 1))));
  p1canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), levelTexture),
      new Transform(vec3(45, -206, 0), vec3(0, 0, 0), vec3(110, 20, 1))));

  //    Background
  p1canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), darkbgTexture),
      new Transform(vec3(44.5, -95, -1.0f), vec3(0, 0, 0), vec3(101, 200, 1))));

  scene->AddCanvas(p1canvas);



  //    PLAYER 2 LAYOUT
  //    Score digits
  p2canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
      new Transform(vec3(30 + space, 15, -9), vec3(0, 0, 0), vec3(20 / 2, 40 / 2, 1))));
  p2canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
      new Transform(vec3(40 + space, 15, -9), vec3(0, 0, 0), vec3(20 / 2, 40 / 2, 1))));
  p2canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
      new Transform(vec3(50 + space, 15, -9), vec3(0, 0, 0), vec3(20 / 2, 40 / 2, 1))));
  p2canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
      new Transform(vec3(65 + space, 15, -9), vec3(0, 0, 0), vec3(20 / 2, 40 / 2, 1))));
  p2canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
      new Transform(vec3(75 + space, 15, -9), vec3(0, 0, 0), vec3(20 / 2, 40 / 2, 1))));
  p2canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
      new Transform(vec3(85 + space, 15, -9), vec3(0, 0, 0), vec3(20 / 2, 40 / 2, 1))));

  //    Level digits
  p2canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
      new Transform(vec3(75 + space, -206, -9), vec3(0, 0, 0), vec3(20 / 2, 40 / 2, 1))));
  p2canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), zeroTexture),
      new Transform(vec3(85 + space, -206, -9), vec3(0, 0, 0), vec3(20 / 2, 40 / 2, 1))));

  //    HOLD - NEXT - SCORE - LEVEL
  p2canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), holdTexture),
      new Transform(vec3(134 + space, -10, -9), vec3(0, 0, 0), vec3(70, 70, 1))));
  p2canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), nextTexture),
      new Transform(vec3(134 + space, -80, -9), vec3(0, 0, 0), vec3(70, 70, 1))));
  p2canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), scoreTexture),
      new Transform(vec3(42 + space, 15, 0), vec3(0, 0, 0), vec3(110, 20, 1))));
  p2canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), levelTexture),
      new Transform(vec3(45 + space, -206, 0), vec3(0, 0, 0), vec3(110, 20, 1))));

  //    Background
  p2canvas->AddSprite(new Sprite(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), softbgTexture),
      new Transform(vec3(44.5 + space, -95, -1.0f), vec3(0, 0, 0), vec3(101, 200, 1))));

  scene->AddCanvas(p2canvas);



  //    Pause menu
  pauseCanvas->AddButton(new Button(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), menuTexture),
      new Transform(vec3(175, 40, 0), vec3(0, 0, 0), vec3(120 / 2, 20 / 2, 5)),
      &callLoadLevelMainMenu));

  pauseCanvas->AddCursor(new Cursor(new OpaqueShader(new Renderer(new Square(vec3(255.f)), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f)), arrowTexture),
      new Transform(vec3(0, 0, 0), vec3(0, 0, 0), vec3(180 / 20, 80 / 20, 5)), -40), true);

  scene->AddCanvas(pauseCanvas);


  // Game Managers
  GameObject* go = new GameObject(
    new Transform(vec3(-200, -200, -200), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f)), nullptr, "GameManager");

  go->AddScript(new PauseMenu(pauseCanvas));
  go->AddScript(new MenuLogic(pauseCanvas));
  go->AddScript(new VersusManager(p1canvas, p2canvas));
  scene->AddGameObject(go);

}
