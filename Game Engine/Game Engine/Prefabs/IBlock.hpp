#pragma once

#include <GL/glew.h>

#include "../GameEngine/Components/Transform.hpp"
#include "../GameEngine/Components/GameObject.hpp"
#include "../GameEngine/Components/Renderer.hpp"

#include "../GameEngine/Primitives/Cube.hpp"


/*
 * Class: IBlock
 * --------------------------------
 */
class IBlock
{
private:
    // This is private because we don't want SBlock objects
    IBlock();
    ~IBlock();

public:
    /*
    * Function: AddIBlock
    * --------------------------------
    *  Creates IBlock game objects
    *
    *  color: The brick color;
    *  shaderId: the Id of the shader.
    */
    static std::vector<GameObject*> AddIBlock(vec3 color, GLuint programID)
    {
        // Sets the primitive of the gameObject, a square
        IPrimitive* pULL = new Cube(color);
        IPrimitive* pUL  = new Cube(color);
        IPrimitive* pUR  = new Cube(color);
        IPrimitive* pURR = new Cube(color);

        // D  = [-50,50]
        // D' = [0, 200]
        // for reference, 0 is the middle line
        // 2 blocks left half, 2 right half

        Transform* tULL = new Transform(vec3(-15, 195, 1), vec3(0, 0, 0), vec3(10, 10, 10));
        Transform* tUL  = new Transform(vec3(-5, 195, 1), vec3(0, 0, 0), vec3(10, 10, 10));
        Transform* tUR  = new Transform(vec3(5, 195, 1), vec3(0, 0, 0), vec3(10, 10, 10));
        Transform* tURR = new Transform(vec3(15, 195, 1), vec3(0, 0, 0), vec3(10, 10, 10));

        GameObject* goULL = new GameObject(tULL, new Renderer(pULL, programID), "IBlock");
        GameObject* goUL  = new GameObject(tUL, new Renderer(pUL, programID), "IBlock");
        GameObject* goUR  = new GameObject(tUR, new Renderer(pUR, programID), "IBlock");
        GameObject* goURR = new GameObject(tURR, new Renderer(pURR, programID), "IBlock");

        std::vector<GameObject*> go = { goULL, goUL, goUR, goURR };
        return go;
    }
};
