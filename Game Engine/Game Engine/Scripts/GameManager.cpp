#include "GameManager.hpp"

#include <iostream>  
#include "../BoardObjects/ZObject.hpp"
#include "../BoardObjects/SObject.hpp"
#include "../BoardObjects/LObject.hpp"
#include "../BoardObjects/LInverseObject.hpp"
#include "../BoardObjects/TObject.hpp"
#include "../BoardObjects/SquareObject.hpp"
#include "../BoardObjects/LineObject.hpp"

const size_t BOARD_HEIGHT = 20;
const size_t BOARD_LENGTH = 10;

GameManager::GameManager(GLuint shaderId) :
    _board(BOARD_HEIGHT, std::vector<int>(BOARD_LENGTH, 0)),
    graphicBoard(BOARD_HEIGHT, vector<GameObject*>(BOARD_LENGTH, nullptr))    
{
  this->shaderId = shaderId;

    beep.reset( new AudioDevice());
    _generateNewObject = true;
}

void GameManager::ChoosePiece()
{
  switch (rand() % tetrominos::Total) // [0, 7[
  {
    case tetrominos::O:
      _currenctObject.reset(new SquareObject());
      this->piece = OBlock::AddOBlock(vec3(255, 213, 0), shaderId);
      break;
    case tetrominos::I:
      _currenctObject.reset(new LineObject());
      this->piece = IBlock::AddIBlock(vec3(0, 255, 255), shaderId);
      break;
    case tetrominos::L:
      _currenctObject.reset(new LObject());
      this->piece = LBlock::AddLBlock(vec3(3, 65, 174), shaderId);
      break;
    case tetrominos::J:
      _currenctObject.reset(new LInverseObject());
      this->piece = JBlock::AddJBlock(vec3(255, 151, 28), shaderId);
      break;
    case tetrominos::T:
      _currenctObject.reset(new TObject());
      this->piece = TBlock::AddTBlock(vec3(128, 0, 128), shaderId);
      break;
    case tetrominos::Z:
      _currenctObject.reset(new ZObject());
      this->piece = ZBlock::AddZBlock(vec3(255, 50, 19), shaderId);
      break;    
    case tetrominos::S:
      _currenctObject.reset(new SObject());      
      this->piece = SBlock::AddSBlock(vec3(114, 203, 59), shaderId);
      break;
    }

  for(GameObject *g : this->piece)
    Scene::CurrentScene()->AddGameObject(g);
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
  if (Time::GetTime() > inputDelayTime + startInputCycleTime)
  {
    startInputCycleTime = Time::GetTime();
    if (Input::GetKey(KeyCode::RightArrow) || Input::GetButton(ButtonCode::DPAD_RIGHT))
      MoveObjectRight();
    else if (Input::GetKey(KeyCode::LeftArrow) || Input::GetButton(ButtonCode::DPAD_LEFT))
      MoveObjectLeft();

    if (Input::GetKey(KeyCode::DownArrow) || Input::GetButton(ButtonCode::DPAD_DOWN))
    {
      MoveObjectDown();
      startCycleTime = Time::GetTime();
    }
  }
  
  if((Input::GetKey(KeyCode::UpArrow) || Input::GetButton(ButtonCode::RB)) && !isRotationKeyPressed)
  {
    isRotationKeyPressed = true;
    Transformation();
  }

  isRotationKeyPressed = Input::GetKey(KeyCode::UpArrow) || Input::GetButton(ButtonCode::RB);
}

void GameManager::Transformation()
{   
    std::unique_ptr< BoardObject > tmpObject = _currenctObject->Clone();
    tmpObject->Transformation();
    
    _currenctObject->Erase(_board, graphicBoard,_currentPosition, this->piece);
    if ( !tmpObject->VerifyColision( _board, _currentPosition))
        _currenctObject.reset( tmpObject.release());

    _currenctObject->Draw(_board, graphicBoard, _currentPosition, this->piece);
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

void GameManager::UpdatePosition(const Position& newPosition, const bool createNewObjectIfFailed)
{
    _currenctObject->Erase(_board, graphicBoard, _currentPosition, this->piece);

    if (_currenctObject->VerifyColision(_board, newPosition))
    {
        _currenctObject->Draw(_board, graphicBoard, _currentPosition, this->piece);

        if (createNewObjectIfFailed)
        {
            _generateNewObject = true;
            _currentPosition.Reset();
        }
    }
    else
    {
        _currenctObject->Draw(_board, graphicBoard, newPosition, this->piece);
        _currentPosition = newPosition;
    }
}

void GameManager::ClearScreen()
{
    system("cls");
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
    for(size_t j = 0; j < dstBoard[dstIndex].size() ; j++)
        dstBoard[dstIndex][j] = srcBoard[srcIndex][j];
}

void GameManager::CopyLineToOtherBoard(int dstIndex, int srcIndex, vector<vector<GameObject*>>& dstBoard, vector<vector<GameObject*>>& srcBoard)
{
  for (size_t j = 0; j < dstBoard[dstIndex].size(); j++) 
  {
    if (srcBoard[srcIndex][j] != nullptr && dstIndex != srcIndex)
    {
      vec3 translate = vec3(0, -abs(dstIndex - srcIndex), 0.0f);
      srcBoard[srcIndex][j]->GetTransform()->Translate(translate);
    }
      
    dstBoard[dstIndex][j] = srcBoard[srcIndex][j];
  }
}

void GameManager::ClearLine()
{
    std::set< int > linesToRemove;

    DetectLinesToRemove(linesToRemove);

    if (linesToRemove.empty())
        return;
    this->UpdateScore(linesToRemove.size());

    GameBoard tmp (BOARD_HEIGHT, vector<int>(BOARD_LENGTH, 0));

    vector<vector<GameObject*>> tmpGraphicBoard (BOARD_HEIGHT, vector<GameObject*>(BOARD_LENGTH, nullptr));

    for (int i : linesToRemove)
    {
      for (GameObject* g : graphicBoard[i])
        g->Destroy();
      for (int j = 0; j < graphicBoard[i].size(); j++)
        graphicBoard[i][j] = nullptr;
    }

    int j = tmpGraphicBoard.size() - 1;
    for (int i = _board.size()-1; i >= 0; --i)
    {
        if(linesToRemove.find(i) == linesToRemove.end())
        {
            CopyLineToOtherBoard(j, i, tmp, _board);
            CopyLineToOtherBoard(j, i, tmpGraphicBoard, graphicBoard);
            --j;
        }
    }

    for (int i = 0; i < _board.size(); i++)
    {
        CopyLineToOtherBoard(i, i, _board, tmp);
        CopyLineToOtherBoard(i, i, graphicBoard, tmpGraphicBoard);
    }
}

void GameManager::UpdateScore(int linesCleared)
{
  this->linesCleared += linesCleared;
  this->score += linesCleared > 1 ? ((100*linesCleared) + ((linesCleared * 100) / 2)) : 100 * linesCleared;

  this->delayTime = 1.0f - (this->linesCleared / 3) / 10.f;
}

void GameManager::GameLoop()
{
    const bool createNewObjectIfFailed = true;

    if (_generateNewObject)
    {
        ClearLine();
        ChoosePiece();
        _generateNewObject = false;
    }

     ManageInput();

    if (Time::GetTime() > delayTime + startCycleTime)
    {
      startCycleTime = Time::GetTime();
      if(!_generateNewObject)
      {
        // Cannot move the object down 
        // if this object is no longer valid
        // and a new object needs to be generated first
        MoveObjectDown();
       }
    
    }
    
    //ClearScreen();
    //DrawBoard();
}

void GameManager::Update()
{
  GameLoop();

  ClearScreen();
  cout << "Score: " << this->score << endl;
  cout << "Level: " << this->linesCleared/3 << endl;
  cout << "Cleared Lines: " << this->linesCleared<< endl;
  cout << "Delay Time: " << this->delayTime << endl;
}
