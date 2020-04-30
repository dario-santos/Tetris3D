#pragma once

#include <GL/glew.h>

#include "../GameEngine/Components/Transform.hpp"
#include "../GameEngine/Components/GameObject.hpp"
#include "../GameEngine/Components/Renderer.hpp"

#include "../GameEngine/Primitives/Cube.hpp"


/*
 * Class: OBlock
 * --------------------------------
 */
class OBlock
{
private:
    // This is private because we don't want OBlock objects
    OBlock();
    ~OBlock();

public:
    /*
    * Function: OBlock
    * --------------------------------
    *  Creates OBlock game objects
    *
    *  color: The brick color;
    *  shaderId: the Id of the shader.
    */
    static std::vector<GameObject*> AddOBlock(vec3 color, GLuint programID)
    {
        // Sets the primitive of the gameObject, a cube
        IPrimitive* pUL = new Cube(color);
        IPrimitive* pUR = new Cube(color);
        IPrimitive* pDL = new Cube(color);
        IPrimitive* pDR = new Cube(color);

        // For reference, 0 is the middle line

        Transform* tUL = new Transform(vec3(-5, 195, 1), vec3(0,0,0), vec3(10,10,10));
        Transform* tUR = new Transform(vec3(5, 195, 1), vec3(0, 0, 0), vec3(10, 10, 10));
        Transform* tDL = new Transform(vec3(-5, 185, 1), vec3(0, 0, 0), vec3(10, 10, 10));
        Transform* tDR = new Transform(vec3(5, 185, 1), vec3(0, 0, 0), vec3(10, 10, 10));

        GameObject* goUL = new GameObject(tUL, new Renderer(pUL, programID), "OBlock");
        GameObject* goUR = new GameObject(tUR, new Renderer(pUR, programID), "OBlock");
        GameObject* goDL = new GameObject(tDL, new Renderer(pDL, programID), "OBlock");
        GameObject* goDR = new GameObject(tDR, new Renderer(pDR, programID), "OBlock");

        std::vector<GameObject*> go = { goUL, goUR, goDL, goDR };
        return go;
    }
};
