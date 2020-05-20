#pragma once

#include <glm/glm.hpp>
using namespace glm;

#include <vector>
#include <set>

#include "GameEngine/Components/Transform.hpp"
#include "GameEngine/Components/GameObject.hpp"
#include "GameEngine/Components/Script.hpp"

#include "GameEngine/Audio/AudioDevice.hpp"
#include "GameEngine/Input/Input.hpp"
#include "GameEngine/Time/Time.hpp"

#include "GameEngine/Scene.hpp"

#include "GameEngine/Shader/Material.hpp"

#include "Assets/Prefabs/IBlock.hpp"
#include "Assets/Prefabs/JBlock.hpp"
#include "Assets/Prefabs/LBlock.hpp"
#include "Assets/Prefabs/OBlock.hpp"
#include "Assets/Prefabs/SBlock.hpp"
#include "Assets/Prefabs/ZBlock.hpp"
#include "Assets/Prefabs/TBlock.hpp"

//
#include "PieceHolder.hpp"
#include "ObjectHint.hpp"
#include "GameBoard.hpp"
#include "Position.hpp"
//

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
        
        static vector<int> pieceList;

        int pieceListIndex = 0;


        Material* material = nullptr;
        float boardCenter = 0.0f;
     
        // Audio device
        unique_ptr<AudioDevice> beep;
        // Score of the game
        int score = 0;
        int linesCleared = 0;

        int level = 0;
        int startLevel = 0;
        int linesToNextLevel = 10;
        Gamepad gamepad;
        int lastPiece = -1;
        
        // Movement
        int movementAmmount = 0;
        float pieceScale = 10.0f;
        bool isHardDropKeyPressed = false;
        bool isRotationKeyPressed = false;
        bool _generateNewObject = true;
        bool canHoldPiece = false;

        // In seconds
        float inputDelayTime = 0.26f;
        float startInputCycleTime = Time::GetTime();
        float delayTime = 1;
        float startCycleTime = Time::GetTime();

        vector<GameObject*> piece;
        vector<GameObject*> nextPiece;
        vector<GameObject*> holdPiece;
        vector<vector<GameObject*>> graphicBoard;
        
        int holdPieceType = -1;
        int currentPieceType = -1;
        int nextPieceType = -1;

        unique_ptr<BoardObject> _currenctObject;

        GameBoard _board;
        
        Position _currentPosition;

        //
        
        vector<GameObject*> shadowPiece;
        int _currentPieceType;
        bool _flagGameover = false;

        unique_ptr<PieceHolder> _holder;
        bool _flag_change_piece = true;
        ObjectHint shadowHint;
        Position _positionHint;

        void HoldPieces();
        void DrawShadowHint();
        void EraseShadowHint();
        void GameOver();

        //
        void ChooseNextPiece();
        void DrawBoard();
        void ManageInput();
        void HoldPiece();
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
        GameManager(Material* material, float boardCenter = 0.0f, int startLevel = 0, Gamepad gamepad = Gamepad::Gamepad1);
        /*
        * Function: Update
        * --------------------------------
        *  The Update event
        */
        void Update() override;
};
