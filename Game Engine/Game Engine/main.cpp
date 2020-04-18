#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
using namespace glm;

// GameEngine
#include "./GameEngine/Components/GameObject.hpp"
#include "./GameEngine/Components/Transform.hpp"
#include "./GameEngine/Scene.hpp"
#include "./GameEngine/Window.hpp"

#include "./GameEngine/Input/Input.hpp"

#include "./GameEngine/Model/ModelLoader.hpp"

#include "./GameEngine/Audio/AudioDevice.hpp"

// Prefabs
#include "./Prefabs/Brick.hpp"
#include "./Prefabs/Player.hpp"
#include "./Prefabs/Deathzone.hpp"
#include "./Prefabs/Ball.hpp"

#include "shader.hpp"
#include "main.hpp"

#include <iostream>

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
  int width = 800;
  int height = 600;
  Window::SetDimensions(vec2(width, height));
  GLFWwindow *window = glfwCreateWindow(width, height, "Breakout With Sound", NULL, NULL);

  // Create window context
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  glewExperimental = true; // Needed for core profile
  // Initialization of GLEW
  glewInit();

  AudioDevice *theme = new AudioDevice(10);
  theme->Play2D("audio/tetris.mp3", GL_TRUE);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // Callbacks
  glfwSetKeyCallback(window, Input::KeyCallback);
  glfwSetWindowSizeCallback(window, Window::WindowReshapeCallback);

  // Background Color
  glClearColor(45.f/255, 52.f/255, 54.f/255, 0.0f);

  // Transfer VAO
  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  // Load Vertex and Fragment shader
  GLuint programID = LoadShaders("./VertexShader.vs", "./FragmentShader.fs");

  // Loads the scene and sets it as the active one
  Scene * scene = new Scene();
  
  scene->AddCamera(new Camera(vec2(-40.0f, 40.0f), vec2(-30.0f, 30.0f)));
  Scene::LoadScene(scene);
  loadGameObjects(scene, programID);

  // render scene for each frame
  do
  {
    // Iterate Objects
    glClear(GL_COLOR_BUFFER_BIT);

    lifeCycle(scene);

    // Swap buffers
    glfwSwapBuffers(window);

    // looking for events
    glfwPollEvents();

   // Check if the ESC key was pressed or the window was closed
  }while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

  // Cleanup VAO, VBOs, and shaders from GPU
  for(GameObject *g: scene->GetGameObjects())
    g->~GameObject();
  scene->GetGameObjects().clear();

  /// Frees the vertex array
  glDeleteVertexArrays(1, &VertexArrayID);
  // Frees the shader
  glDeleteProgram(programID);

  // Close OpenGL window and terminate GLFW
  glfwTerminate();
  return 0;
}

void loadGameObjects(Scene* scene, GLuint programID)
{
  // Bricks
  for (int i = 25; i >= 10; i -= 3)
    for (int j = -35; j <= 35; j += 5)
      scene->AddGameObject(Brick::AddBrick(
        new Transform(vec3(j, i, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(5.0f, 2.0f, 0.0f)), vec3(abs(j) * i * 0.5f, abs(j) * i + 200, 0), programID));

  // Ball
  scene->AddGameObject(Ball::AddBall(
    new Transform(vec3(0.0f, -15.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.0f, 2.0f, 0.0f)), programID));

  // Player
  scene->AddGameObject(Player::AddPlayer(
    new Transform(vec3(0.0f, -25.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(10.0f, 2.0f, 0.0f)), programID));

  // DeathZone
  scene->AddGameObject(DeathZone::AddDeathZone(
    new Transform(vec3(0.0f, -30.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(80.0f, 2.0f, 0.0f))));
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
      vec3 c1 = g1->GetTransform().position;
      // Radius of g1
      vec3 r1 = g1->GetTransform().scale * vec3(0.5f, 0.5f, 0.5f);

      // Center of g2
      vec3 c2 = g2->GetTransform().position;

      // if the distance between the centers is smaller than the x and y radius there's a collision
      if(abs(c1.x - c2.x) < r1.x && abs(c1.y - c2.y) < r1.y)
      {
        // Invokes the OnCollision method of the objects
        for(Script *s : g1->GetScripts())
          s->OnCollision(vec3(c1.x - c2.x, c1.y - c2.y, 0.0f), g2->Tag());

        for(Script *s : g2->GetScripts())
          s->OnCollision(-vec3(c1.x - c2.x, c1.y - c2.y, 0.0f), g1->Tag());
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
