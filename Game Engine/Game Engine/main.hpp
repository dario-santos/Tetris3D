/**
 * @file main.hpp
 *
 * @brief Header da função main
 *
 * @author Dário Santos
 * Contact: dariovfsantos@gmail.com
 */
#pragma once

/*
 * Function: loadGameObjects
 * --------------------------------
 *   Loads game objects into scene with a certain shader.
 *   
 *   scene: The scene that the objects will get loaded into;
 */
void loadLevelSingleplayer(Scene *scene);

/*
 * Function: loadGameObjects
 * --------------------------------
 *   Loads game objects into scene with a certain shader.
 *
 *   scene: The scene that the objects will get loaded into;
 */
void loadLevelMultiplayer(Scene* scene);

/*
 * Function: lifeCycle
 * --------------------------------
 *   A call represents a cycle of the game.
 *   
 *   scene: The current scene;
 */
void lifeCycle(Scene *scene);
