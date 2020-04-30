#pragma once

#include <GL/glew.h>

#include "../GameEngine/Components/Transform.hpp"
#include "../GameEngine/Components/GameObject.hpp"
#include "../GameEngine/Components/Renderer.hpp"

#include "../GameEngine/Primitives/Cube.hpp"


/*
 * Class: TBlock
 * --------------------------------
 */
class TBlock
{
private:
    // This is private because we don't want TBlock objects
    TBlock();
    ~TBlock();

public:
    /*
    * Function: AddTBlock
    * --------------------------------
    *  Creates TBlock game objects
    *
    *  color: The brick color;
    *  shaderId: the Id of the shader.
    */
    static std::vector<GameObject*> AddTBlock(vec3 color, GLuint programID)
    {
        // Sets the primitive of the gameObject, a square
        IPrimitive* pU = new Cube(color);
        IPrimitive* pDL = new Cube(color);
        IPrimitive* pD = new Cube(color);
        IPrimitive* pDR = new Cube(color);

        // D  = [-50,50]
        // D' = [0, 200]
        // for reference, 0 is the middle line
        // 3 blocks left half, 1 right half

        Transform* tU  = new Transform(vec3(-5, 195, 1), vec3(0, 0, 0), vec3(10, 10, 10));
        Transform* tDL = new Transform(vec3(-15, 185, 1), vec3(0, 0, 0), vec3(10, 10, 10));
        Transform* tD  = new Transform(vec3(-5, 185, 1), vec3(0, 0, 0), vec3(10, 10, 10));
        Transform* tDR = new Transform(vec3(5, 185, 1), vec3(0, 0, 0), vec3(10, 10, 10));

        GameObject* goU  = new GameObject(tU, new Renderer(pU, programID), "TBlock");
        GameObject* goDL = new GameObject(tDL, new Renderer(pDL, programID), "TBlock");
        GameObject* goD  = new GameObject(tD, new Renderer(pD, programID), "TBlock");
        GameObject* goDR = new GameObject(tDR, new Renderer(pDR, programID), "TBlock");

        std::vector<GameObject*> go = { goU, goDL, goD, goDR };
        return go;
    }
};
