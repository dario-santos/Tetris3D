#pragma once

#include <GL/glew.h>

#include "../GameEngine/Components/Transform.hpp"
#include "../GameEngine/Components/GameObject.hpp"
#include "../GameEngine/Components/Renderer.hpp"

#include "../GameEngine/Primitives/Cube.hpp"


/*
 * Class: SBlock
 * --------------------------------
 */
class SBlock
{
private:
    // This is private because we don't want SBlock objects
    SBlock();
    ~SBlock();

public:
    /*
    * Function: AddSBlock
    * --------------------------------
    *  Creates SBlock game objects
    *
    *  color: The brick color;
    *  shaderId: the Id of the shader.
    */
    static std::vector<GameObject*> AddSBlock(vec3 color, GLuint programID)
    {
        // Sets the primitive of the gameObject, a square
        IPrimitive* pDL = new Cube(color);
        IPrimitive* pD = new Cube(color);
        IPrimitive* pU = new Cube(color);
        IPrimitive* pUR = new Cube(color);

        // D  = [-50,50]
        // D' = [0, 200]
        // for reference, 0 is the middle line
        // 3 blocks left half, 1 right half

        Transform* tDL = new Transform(vec3(-15, 185, 1), vec3(0, 0, 0), vec3(10, 10, 10));
        Transform* tD  = new Transform(vec3(-5, 185, 1), vec3(0, 0, 0), vec3(10, 10, 10));
        Transform* tU  = new Transform(vec3(-5, 195, 1), vec3(0, 0, 0), vec3(10, 10, 10));
        Transform* tUR = new Transform(vec3(5, 195, 1), vec3(0, 0, 0), vec3(10, 10, 10));

        GameObject* goDL = new GameObject(tDL, new Renderer(pDL, programID), "SBlock");
        GameObject* goD  = new GameObject(tD, new Renderer(pD, programID), "SBlock");
        GameObject* goU  = new GameObject(tU, new Renderer(pU, programID), "SBlock");
        GameObject* goUR = new GameObject(tUR, new Renderer(pUR, programID), "SBlock");

        std::vector<GameObject*> go = { goDL, goD, goU, goUR };
        return go;
    }
};
