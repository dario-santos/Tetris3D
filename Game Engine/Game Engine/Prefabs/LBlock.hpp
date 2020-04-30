#pragma once

#include <GL/glew.h>

#include "../GameEngine/Components/Transform.hpp"
#include "../GameEngine/Components/GameObject.hpp"
#include "../GameEngine/Components/Renderer.hpp"

#include "../GameEngine/Primitives/Cube.hpp"


/*
 * Class: LBlock
 * --------------------------------
 */
class LBlock
{
private:
    // This is private because we don't want SBlock objects
    LBlock();
    ~LBlock();

public:
    /*
    * Function: AddLBlock
    * --------------------------------
    *  Creates LBlock game objects
    *
    *  color: The brick color;
    *  shaderId: the Id of the shader.
    */
    static std::vector<GameObject*> AddLBlock(vec3 color, GLuint programID)
    {
        // Sets the primitive of the gameObject, a square
        IPrimitive* pDL = new Cube(color);
        IPrimitive* pD  = new Cube(color);
        IPrimitive* pDR = new Cube(color);
        IPrimitive* pUR = new Cube(color);

        // D  = [-50,50]
        // D' = [0, 200]
        // for reference, 0 is the middle line
        // 2 blocks left half, 2 right half

        Transform* tDL = new Transform(vec3(-15, 185, 1), vec3(0, 0, 0), vec3(10, 10, 10));
        Transform* tD  = new Transform(vec3(-5, 185, 1), vec3(0, 0, 0), vec3(10, 10, 10));
        Transform* tDR = new Transform(vec3(5, 185, 1), vec3(0, 0, 0), vec3(10, 10, 10));
        Transform* tUR = new Transform(vec3(5, 195, 1), vec3(0, 0, 0), vec3(10, 10, 10));

        GameObject* goDL = new GameObject(tDL, new Renderer(pDL, programID), "LBlock");
        GameObject* goD  = new GameObject(tD, new Renderer(pD, programID), "LBlock");
        GameObject* goDR = new GameObject(tDR, new Renderer(pDR, programID), "LBlock");
        GameObject* goUR = new GameObject(tUR, new Renderer(pUR, programID), "LBlock");

        std::vector<GameObject*> go = { goDL, goD, goDR, goUR };
        return go;
    }
};
