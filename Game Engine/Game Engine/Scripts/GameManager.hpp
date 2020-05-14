#pragma once

#include <glm/glm.hpp>
#include <memory>
using namespace glm;

#include <string>
#include <list>
#include <vector>
#include <set>

#include "../GameEngine/Components/Transform.hpp"
#include "../GameEngine/Components/GameObject.hpp"
#include "../GameEngine/Components/Script.hpp"

#include "../GameEngine/Audio/AudioDevice.hpp"
#include "../GameEngine/Input/Input.hpp"

#include "../GameEngine/Scene.hpp"


#include "../Prefabs/IBlock.hpp"
#include "../Prefabs/JBlock.hpp"
#include "../Prefabs/LBlock.hpp"
#include "../Prefabs/OBlock.hpp"
#include "../Prefabs/SBlock.hpp"
#include "../Prefabs/ZBlock.hpp"
#include "../Prefabs/TBlock.hpp"


const float SPEED_X_DIRECTION = 0.3f;
const float SPEED_Y_DIRECTION = 0.6f;
const float SPEED_Z_DIRECTION = 0.0f;

typedef std::vector< std::vector< int > > GameBoard;

struct Position
{
    Position()
    {
        Reset();
    }

    Position(const int x, const int y) :
        _x(x),
        _y(y)
    {
    }

    void GoDown()
    {
        _x += 1;
    }

    void GoLeft()
    {
        _y -= 1;
    }

    void GoRight()
    {
        _y += 1;
    }

    void Reset() 
    {
        _x = 0;
        _y = 4;
    }

    int _x;
    int _y;
};

class BoardObject;

/*
 * Class: GameManager
 * --------------------------------
 *   Interface: Script
 */
class GameManager : public Script
{
    private:
        enum tetrominos{
            O = 0,
            I,
            L,
            J,
            T,
            Z,
            S,
            Total
        };

        // Transform of the gameObject
        std::unique_ptr<Transform> transform;
        // The ball gameObject
        std::unique_ptr<GameObject> gameObject;
        // Audio device
        std::unique_ptr<AudioDevice> beep;
        // Velocity of movement
        vec3 step;
        // Score of the game
        int score;
        
        GLuint shaderId;

        bool _generateNewObject;

        time_t _seconds;
        time_t _drawSeconds;

        vector<GameObject*> piece;

        vector<vector<GameObject*>> graphicBoard;
        GameBoard _board;
        std::unique_ptr< BoardObject > _currenctObject;
        Position _currentPosition;
        

        void ChoosePiece();
        void DrawBoard();
        void ManageInput();
        void Transformation();
        void MoveObjectLeft();
        void MoveObjectRight();
        void MoveObjectDown();
        void UpdatePosition(const Position& newPosition, const bool createNewObjectIfFailed = false);
        void DetectLinesToRemove(std::set< int >& linesToRemove) const;
        void CopyLineToOtherBoard(int dstIndex, int srcIndex, GameBoard& destBoard, const GameBoard& srcBoard) const;
        void CopyLineToOtherBoard(int dstIndex, int srcIndex, vector<vector<GameObject*>>& dstBoard, vector<vector<GameObject*>>& srcBoard);
        void ClearLine();
        void ClearScreen();
        void Game_loop();

    public:

        /*
        * Function: GameManager
        * --------------------------------
        *  GameManager constructor
        *
        */
        GameManager(GLuint shaderId);

        GameManager(const GameManager& other) = delete;
        GameManager& operator=(const GameManager& other) = delete;

        /*
        * Function: Update
        * --------------------------------
        *  The Update event
        */
        void Update() override; 
        
};
