#pragma once

#include <GL/glew.h>

#include "../GameEngine/Components/Transform.hpp"
#include "../GameEngine/Components/GameObject.hpp"
#include "../GameEngine/Components/Renderer.hpp"

#include "../GameEngine/Primitives/Cube.hpp"


/*
 * Class: ZBlock
 * --------------------------------
 */
class ZBlock
{
private:
    // This is private because we don't want ZBlock objects
    ZBlock();
    ~ZBlock();

public:
    /*
    * Function: AddZBlock
    * --------------------------------
    *  Creates ZBlock game objects
    *
    *  color: The brick color;
    *  shaderId: the Id of the shader.
    */
    static std::vector<GameObject*> AddZBlock(vec3 color, GLuint programID)
    {
        // Sets the primitive of the gameObject, a square
        IPrimitive* pUL = new Cube(color);
        IPrimitive* pU  = new Cube(color);
        IPrimitive* pD  = new Cube(color);
        IPrimitive* pDR = new Cube(color);

        // D  = [-50,50]
        // D' = [0, 200]
        // for reference, 0 is the middle line
        // 3 blocks left half, 1 right half

        Transform* tUL = new Transform(vec3(-15, 195, 1), vec3(0, 0, 0), vec3(10, 10, 10));
        Transform* tU  = new Transform(vec3(-5, 195, 1), vec3(0, 0, 0), vec3(10, 10, 10));
        Transform* tD  = new Transform(vec3(-5, 185, 1), vec3(0, 0, 0), vec3(10, 10, 10));
        Transform* tDR = new Transform(vec3(5, 185, 1), vec3(0, 0, 0), vec3(10, 10, 10));

        GameObject* goUL = new GameObject(tUL, new Renderer(pUL, programID), "ZBlock");
        GameObject* goU  = new GameObject(tU, new Renderer(pU, programID), "ZBlock");
        GameObject* goD  = new GameObject(tD, new Renderer(pD, programID), "ZBlock");
        GameObject* goDR = new GameObject(tDR, new Renderer(pDR, programID), "ZBlock");

        std::vector<GameObject*> go = { goUL, goU, goD, goDR };
        return go;
    }
};
