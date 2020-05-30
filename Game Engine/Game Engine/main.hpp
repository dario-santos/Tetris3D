/**
 * @file main.hpp
 *
 * @brief Header da função main
 *
 * @author Dário Santos
 * Contact: dariovfsantos@gmail.com
 */
#pragma once

#include <memory>
using namespace std;


void loadLevelMainMenu(unique_ptr<Scene>& scene);

void loadLevelOptionMenu(unique_ptr<Scene>& scene);

void loadLevelMarathonMenu(unique_ptr<Scene>& scene);

void loadLevelVersusMenu(unique_ptr<Scene>& scene);

/*
 * Function: loadGameObjects
 * --------------------------------
 *   Loads game objects into scene with a certain shader.
 *   
 *   scene: The scene that the objects will get loaded into;
 */
void loadLevelSingleplayer(unique_ptr<Scene>& scene);

/*
 * Function: loadGameObjects
 * --------------------------------
 *   Loads game objects into scene with a certain shader.
 *
 *   scene: The scene that the objects will get loaded into;
 */
void loadLevelMultiplayer(unique_ptr<Scene>& scene);

/*
 * Function: lifeCycle
 * --------------------------------
 *   A call represents a cycle of the game.
 *   
 *   scene: The current scene;
 */
void lifeCycle(unique_ptr<Scene>& scene);
