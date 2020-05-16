#pragma once

#include <glm/glm.hpp>
using namespace glm;

#include <vector>
#include <set>

#include "../GameEngine/Components/Transform.hpp"
#include "../GameEngine/Components/GameObject.hpp"
#include "../GameEngine/Components/Script.hpp"

#include "../GameEngine/Audio/AudioDevice.hpp"
#include "../GameEngine/Input/Input.hpp"
#include "../GameEngine/Time/Time.hpp"

#include "../GameEngine/Scene.hpp"

#include "../Prefabs/IBlock.hpp"
#include "../Prefabs/JBlock.hpp"
#include "../Prefabs/LBlock.hpp"
#include "../Prefabs/OBlock.hpp"
#include "../Prefabs/SBlock.hpp"
#include "../Prefabs/ZBlock.hpp"
#include "../Prefabs/TBlock.hpp"

typedef vector<vector<int>>GameBoard;

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

        float boardCenter;
        GLuint shaderId;

        // Audio device
        unique_ptr<AudioDevice> beep;
        // Score of the game
        int score = 0;
        int linesCleared = 0;
        Gamepad gamepad;
        int lastPiece = -1;
        int movementAmmount = 0;
        bool isHardDropKeyPressed = false;
        bool isRotationKeyPressed = false;
        bool _generateNewObject = true;

        // In seconds
        float inputDelayTime = 0.28f;
        float startInputCycleTime = Time::GetTime();
        float delayTime = 1;
        float startCycleTime = Time::GetTime();

        vector<GameObject*> piece;
        vector<vector<GameObject*>> graphicBoard;
        
        unique_ptr<BoardObject> _currenctObject;
        GameBoard _board;
        
        Position _currentPosition;

        void ChoosePiece();
        void DrawBoard();
        void ManageInput();
        void Transformation(bool isClockWise);
        void MoveObjectLeft();
        void MoveObjectRight();
        void MoveObjectDown();
        void MoveObjectHardDrop();
        bool UpdatePosition(const Position& newPosition, const bool createNewObjectIfFailed = false);
        void DetectLinesToRemove(std::set< int >& linesToRemove) const;
        void CopyLineToOtherBoard(int dstIndex, int srcIndex, GameBoard& destBoard, const GameBoard& srcBoard) const;
        void CopyLineToOtherBoard(int dstIndex, int srcIndex, vector<vector<GameObject*>>& dstBoard, vector<vector<GameObject*>>& srcBoard);
        void ClearLine();
        void UpdateScore(int linesCleared);
        void ClearScreen();
        void ResetGame();
        void GameLoop();

    public:
        /*
        * Function: GameManager
        * --------------------------------
        *  GameManager constructor
        *
        */
        GameManager(GLuint shaderId, float boardCenter, Gamepad gamepad);

        GameManager(const GameManager& other) = delete;
        GameManager& operator=(const GameManager& other) = delete;

        /*
        * Function: Update
        * --------------------------------
        *  The Update event
        */
        void Update() override;
};
