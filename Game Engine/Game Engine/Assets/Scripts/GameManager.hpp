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
#include "Assets/Prefabs/HintBlock.hpp"

#include "ObjectHint.hpp"
#include "GameBoard.hpp"
#include "Position.hpp"


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
        
        // Ordem das peças que serão dadas ao utilizador
        static vector<int> pieceList;
        // Indice da lista de peças que está
        int pieceListIndex = 0;

        // Material das peças criadas
        Material* material;
        // Centro do tabuleiro no eixo X
        float boardCenter = 0.0f;
        // Tamanho das peças
        float pieceScale = 10.0f;
        // Id deste jogador
        Gamepad gamepad;
        // Audio device
        unique_ptr<AudioDevice> beep;
        // Score of the game
        int linesCleared = 0;
        int level = 0;
        int startLevel = 0;
        int linesToNextLevel = 10;
        // Última peça gerada
        int lastPiece = -1;
        
        // Input
        int movementAmmount = 0;
        bool isHardDropKeyPressed = false;
        bool isRotationKeyPressed = false;
        bool isHoldKeyPressed = false;
        bool canHoldPiece = false;
        // Pode gerar uma nova peça
        bool _generateNewObject = true;

        // Timers - in seconds
        float inputDelayTime = 0.26f;
        float startInputCycleTime = Time::GetTime();
        float delayTime = 1;
        float startCycleTime = Time::GetTime();
        // Pieces
        vector<GameObject*> piece;
        vector<GameObject*> nextPiece;
        vector<GameObject*> holdPiece;
        vector<GameObject*> shadowPiece;
        vector<vector<GameObject*>> graphicBoard;
        
        int holdPieceType = -1;
        int currentPieceType = -1;
        int nextPieceType = -1;

        // Board
        GameBoard _board;
        unique_ptr<BoardObject> _currenctObject;
        Position _currentPosition;
        // Shadow of the piece
        ObjectHint shadowHint;
        Position _positionHint;
               
        int _currentPieceType;


        void GameOver();
        
        void DrawShadowHint();
        void EraseShadowHint();
        
        void ChooseNextPiece();

        void DrawBoard();
        void ClearScreen();
        
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
        
        void GameLoop();

    public:
        static bool isPaused;
        bool isGameOver = false;

        int score = 0;

        GameManager(Material* material, float boardCenter = 0.0f, int startLevel = 0, Gamepad gamepad = Gamepad::Gamepad1);

        void Update() override;
};
