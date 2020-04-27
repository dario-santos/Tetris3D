#include "GameManager.hpp"

#include <iostream>
#include <ctime>   
#include <set>   
#include <fstream>   
#include "../BoardObjects/ZObject.hpp"
#include "../BoardObjects/SObject.hpp"
#include "../BoardObjects/LObject.hpp"
#include "../BoardObjects/LInverseObject.hpp"
#include "../BoardObjects/TObject.hpp"
#include "../BoardObjects/SquareObject.hpp"
#include "../BoardObjects/LineObject.hpp"

const size_t BOARD_HEIGHT = 20;
const size_t BOARD_LENGTH = 10;


GameManager::GameManager(/*Transform* transform, GameObject* gameObject*/) :
    _board(BOARD_HEIGHT, std::vector<int>(BOARD_LENGTH, 0)),
    _seconds( time(NULL) ),
    _drawSeconds(time(NULL))
    
{
    //this->transform.reset( transform );
    //this->gameObject.reset( gameObject );

    beep.reset( new AudioDevice() );
    
    
    score = 0;
   // myfile.open("TetrisLog.log");
    _generateNewObject = true;
    step = vec3(SPEED_X_DIRECTION, SPEED_Y_DIRECTION, SPEED_Z_DIRECTION);
}

void GameManager::ChoosePiece()
{
    switch (rand() % BOARD_OBJECT_TYPE_TOTAL_OBJECTS) // [0, 7[
    {
        case BOARD_OBJECT_TYPE_SQUARE: // Square
            _currenctObject.reset(new SquareObject());
            break;
        case BOARD_OBJECT_TYPE_LINE: // Line
            _currenctObject.reset(new LineObject());
            break;
        case BOARD_OBJECT_TYPE_L: // L
            _currenctObject.reset(new LObject());
            break;
        case BOARD_OBJECT_TYPE_LINVERSE: // Inverse L
            _currenctObject.reset(new LInverseObject());
            break;
        case BOARD_OBJECT_TYPE_T: // T 
            _currenctObject.reset(new TObject());
            break;
        case BOARD_OBJECT_TYPE_Z: // z
            _currenctObject.reset ( new ZObject()) ;
            break;
        case BOARD_OBJECT_TYPE_S: // s
           _currenctObject.reset(new SObject());
            break;
    }
}

void GameManager::DrawBoard()
{
    for (size_t i = 0; i < _board.size(); i++)
    {
        cout << endl;
        for (size_t j = 0; j < _board[i].size(); j++)
        {
            if (_board[i][j] == 0)
                cout << ". ";
            else
                cout << "# ";
        }
    }
}

void GameManager::ManageInput()
{
    if ( Input::GetKey(KeyCode::LeftArrow) )
    {
        MoveObjectLeft();
    }
    else if ( Input::GetKey(KeyCode::RightArrow) )
    {
        MoveObjectRight();
    }
    else if (Input::GetKey(KeyCode::DownArrow))
    {
        MoveObjectDown();
    }
    else  if (Input::GetKey(KeyCode::UpArrow))
    {
        Transformation();
    }
}

void GameManager::Transformation()
{   
    std::unique_ptr< BoardObject > tmpObject = _currenctObject->Clone();
    tmpObject->Transformation();
    
    _currenctObject->Erase(_board, _currentPosition);
    if ( !tmpObject->VerifyColision( _board, _currentPosition))
        _currenctObject.reset( tmpObject.release() );

    _currenctObject->Draw(_board, _currentPosition);
}

void GameManager::MoveObjectLeft()
{
    Position newPosition = _currentPosition;
    newPosition.GoLeft();
    UpdatePosition(newPosition);
}

void GameManager::MoveObjectRight()
{
    Position newPosition = _currentPosition;
    newPosition.GoRight();
    UpdatePosition(newPosition);
}

void GameManager::MoveObjectDown()
{
    const bool createNewObjectIfFailed = true;
    Position newPosition = _currentPosition;
    newPosition.GoDown();
    UpdatePosition( newPosition, createNewObjectIfFailed);
}

void GameManager::UpdatePosition(const Position& newPosition, const bool createNewObjectIfFailed /*= false*/)
{
    _currenctObject->Erase(_board, _currentPosition);

    if (_currenctObject->VerifyColision(_board, newPosition))
    {
        _currenctObject->Draw(_board, _currentPosition);

        if (createNewObjectIfFailed)
        {
            _generateNewObject = true;
            _currentPosition.Reset();
        }
    }
    else
    {
        _currenctObject->Draw(_board, newPosition);
        _currentPosition = newPosition;
    }
}

void GameManager::ClearScreen()
{ 
   // cout << string(100, '\n'); 
    system("cls");// remover caso não seja no Windows
}

void GameManager::DetectLinesToRemove(std::set< int >& linesToRemove) const
{
    bool flagLineFilled;    

    for (size_t i = 0; i < _board.size(); i++)
    {
        flagLineFilled = true;
        for (size_t j = 0; j < _board[i].size(); j++)
        {
            if (_board[i][j] == 0)
            {
                flagLineFilled = false;
                break;
            }               
        }

        if (flagLineFilled)
            linesToRemove.insert(i);
    }
}

void GameManager::CopyLineToOtherBoard(int dstIndex, int srcIndex, GameBoard& dstBoard, const GameBoard& srcBoard) const
{
    for (size_t j = 0; j < dstBoard[dstIndex].size() ; j++)
    {
        dstBoard[dstIndex][j] = srcBoard[srcIndex][j];
    }
}

void GameManager::ClearLine()
{
    std::set< int > linesToRemove;

    DetectLinesToRemove(linesToRemove);

    if (linesToRemove.empty())
        return;

    GameBoard tmp (BOARD_HEIGHT, std::vector<int>(BOARD_LENGTH, 0));
   
    int j = tmp.size() - 1;
    for (int i = _board.size()-1; i >= 0; --i)
    {
        if ( linesToRemove.find( i ) == linesToRemove.end() )
        {
            CopyLineToOtherBoard(j, i, tmp, _board);
            --j;
        }
    }

    for (int i = 0; i < _board.size(); i++)
    {
        CopyLineToOtherBoard(i, i, _board, tmp);
    }

}

void GameManager::Game_loop()
{
    const bool createNewObjectIfFailed = true;

    if (_generateNewObject)
    {
        ClearLine();
        ChoosePiece();
        _generateNewObject = false;
    }

    ManageInput();

    if (_seconds < time(NULL))
    {
        _seconds = time(NULL) + 2;
        MoveObjectDown();
    }
    
    //if (_drawSeconds < time(NULL) )
    //{
        ClearScreen();
        DrawBoard();
    //    _drawSeconds = time(NULL) + 1;
    //}
}

void GameManager::Update()
{
    
    Game_loop();
}

