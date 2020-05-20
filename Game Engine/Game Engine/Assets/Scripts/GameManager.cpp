#include "GameManager.hpp"

#include <iostream>
#include <ctime>

#include "BoardObjects/ZObject.hpp"
#include "BoardObjects/SObject.hpp"
#include "BoardObjects/LObject.hpp"
#include "BoardObjects/LInverseObject.hpp"
#include "BoardObjects/TObject.hpp"
#include "BoardObjects/SquareObject.hpp"
#include "BoardObjects/LineObject.hpp"


const size_t BOARD_HEIGHT = 22;
const size_t BOARD_LENGTH = 10;

GameManager::GameManager(Material* material, float boardCenter, int startLevel, Gamepad gamepad) :
    _board(BOARD_HEIGHT, std::vector<int>(BOARD_LENGTH, 0)),
    graphicBoard(BOARD_HEIGHT, vector<GameObject*>(BOARD_LENGTH, nullptr))    
{
  this->startLevel = startLevel;
  this->level      = startLevel;

  if (level >= 25)
    this->linesToNextLevel = 200;
  else
    this->linesToNextLevel = min((startLevel * 10 + 10), max(100, startLevel * 10 - 50));

  // Progression
  if (level < 10)
    this->delayTime = (48 - (5 * level)) / 60.0f;
  else if (level < 12)
    this->delayTime = 5 / 60.0f;
  else if (level < 15)
    this->delayTime = 4 / 60.0f;
  else if (level < 18)
    this->delayTime = 3 / 60.0f;
  else if (level < 28)
    this->delayTime = 2 / 60.0f;
  else
    this->delayTime = 1 / 60.0f;

  this->material = material;


  this->boardCenter = boardCenter;
  this->gamepad     = gamepad;
  beep.reset(new AudioDevice(100));

  // Set random sequence
  srand((unsigned)time(0));
}

void GameManager::ChooseNextPiece()
{
  canHoldPiece = false;
  currentPieceType = nextPieceType;

  if (currentPieceType != -1)
  {
    // Passar a antiga para ativa
    piece = nextPiece;
  }


  // Nes randomizer
  int r = rand() % tetrominos::Total;
  if (lastPiece == r)
    r = rand() % tetrominos::Total;
  lastPiece = r;
  nextPieceType = r;

  switch (lastPiece) // [0, 7[
  {
  case tetrominos::O:
    _currenctObject.reset(new SquareObject());
    this->nextPiece = OBlock::AddOBlock(pieceScale, vec3(255, 213, 0), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f));
    break;
  case tetrominos::I:
    _currenctObject.reset(new LineObject());
    this->nextPiece = IBlock::AddIBlock(pieceScale, vec3(0, 255, 255), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f));
    break;
  case tetrominos::L:
    _currenctObject.reset(new LObject());
    this->nextPiece = LBlock::AddLBlock(pieceScale, vec3(3, 65, 174), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f));
    break;
  case tetrominos::J:
    _currenctObject.reset(new LInverseObject());
    this->nextPiece = JBlock::AddJBlock(pieceScale, vec3(255, 151, 28), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f));
    break;
  case tetrominos::T:
    _currenctObject.reset(new TObject());
    this->nextPiece = TBlock::AddTBlock(pieceScale, vec3(128, 0, 128), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f));
    break;
  case tetrominos::Z:
    _currenctObject.reset(new ZObject());
    this->nextPiece = ZBlock::AddZBlock(pieceScale, vec3(255, 50, 19), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f));
    break;
  case tetrominos::S:
    _currenctObject.reset(new SObject());
    this->nextPiece = SBlock::AddSBlock(pieceScale, vec3(114, 203, 59), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f));
    break;
  }

  for (GameObject* g : this->nextPiece)
    Scene::CurrentScene()->AddGameObject(g);

  _currenctObject->UpdateWorldPosition(this->nextPiece, vec3(10, 13, 1), this->boardCenter, pieceScale);

  switch (currentPieceType) // [0, 7[
  {
  case tetrominos::O:
    _currenctObject.reset(new SquareObject());
    break;
  case tetrominos::I:
    _currenctObject.reset(new LineObject());
    break;
  case tetrominos::L:
    _currenctObject.reset(new LObject());
    break;
  case tetrominos::J:
    _currenctObject.reset(new LInverseObject());
    break;
  case tetrominos::T:
    _currenctObject.reset(new TObject());
    break;
  case tetrominos::Z:
    _currenctObject.reset(new ZObject());
    break;
  case tetrominos::S:
    _currenctObject.reset(new SObject());
    break;
  }
  if (currentPieceType != -1)
  {
    _currenctObject->UpdateWorldPosition(this->piece, vec3(_currentPosition._x, _currentPosition._y, 1), this->boardCenter, pieceScale);
    canHoldPiece = true;
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
  string player = std::to_string((static_cast<int>(gamepad)));

  // Movement
  if(Time::GetTime() > inputDelayTime + startInputCycleTime)
  {
    startInputCycleTime = Time::GetTime();
    
    if(Input::GetKey("Right" + player) || Input::GetButton(ButtonCode::DPAD_RIGHT, gamepad))
    {
      MoveObjectRight();
      movementAmmount++;
    }
    else if (Input::GetKey("Left" + player) || Input::GetButton(ButtonCode::DPAD_LEFT, gamepad))
    {
      MoveObjectLeft();
      movementAmmount++;
    }
    if(Input::GetKey("Drop" + player) || Input::GetButton(ButtonCode::DPAD_DOWN, gamepad))
    {
      MoveObjectDown();
      movementAmmount++;
      startCycleTime = Time::GetTime();
    }

    if (!Input::GetKey("Right" + player) && !Input::GetButton(ButtonCode::DPAD_RIGHT, gamepad)
     && !Input::GetKey("Left" + player) && !Input::GetButton(ButtonCode::DPAD_LEFT, gamepad)
     && !Input::GetKey("Drop" + player) && !Input::GetButton(ButtonCode::DPAD_DOWN, gamepad))
      movementAmmount = 0;

    // Update DAS status
    if (movementAmmount == 0)
      inputDelayTime = 0.0f;
    else if (movementAmmount == 1)
      inputDelayTime = 0.26;
    else
      inputDelayTime = 0.1f;
  }

  // HardDrop
  if ((Input::GetKey("HardDrop" + player) || Input::GetButton(ButtonCode::DPAD_UP, gamepad)) && !isHardDropKeyPressed)
  {
    isHardDropKeyPressed = true;
    MoveObjectHardDrop();
  }

  // Rotations
  if((Input::GetKey("RotateR" + player) || Input::GetButton(ButtonCode::A, gamepad)) && !isRotationKeyPressed)
  {
    isRotationKeyPressed = true;
    Transformation(true);
  }
  else if ((Input::GetKey("RotateL" + player) || Input::GetButton(ButtonCode::B, gamepad)) && !isRotationKeyPressed)
  {
    isRotationKeyPressed = true;
    Transformation(false);
    _currenctObject->UpdateWorldPosition(this->piece, vec3(-20, -20, 1), this->boardCenter, pieceScale);

  }

  // Hold
  if((Input::GetKey("Hold" + player) || Input::GetButton(ButtonCode::RB, gamepad)) && canHoldPiece)
  {
    canHoldPiece = false;


    _currenctObject->Restart();
    _currenctObject->UpdateWorldPosition(this->piece, vec3(5, 13, 1), this->boardCenter, pieceScale);
    _currenctObject->Erase(_board, graphicBoard, _currentPosition, this->piece, this->boardCenter, pieceScale);

    _currentPosition.Reset();

    if (holdPiece.empty())
    {
      _generateNewObject = true;
      holdPiece = piece;
      holdPieceType = currentPieceType;
      currentPieceType = -1;
    }
    else
    {
      switch (holdPieceType) // [0, 7[
      {
      case tetrominos::O:
        _currenctObject.reset(new SquareObject());
        break;
      case tetrominos::I:
        _currenctObject.reset(new LineObject());
        break;
      case tetrominos::L:
        _currenctObject.reset(new LObject());
        break;
      case tetrominos::J:
        _currenctObject.reset(new LInverseObject());
        break;
      case tetrominos::T:
        _currenctObject.reset(new TObject());
        break;
      case tetrominos::Z:
        _currenctObject.reset(new ZObject());
        break;
      case tetrominos::S:
        _currenctObject.reset(new SObject());
        break;
      }
      int tmp = holdPieceType;
      holdPieceType = currentPieceType;
      currentPieceType = tmp;
      
      vector<GameObject*> tmpPiece = piece;
      piece = holdPiece;
      holdPiece = tmpPiece;
    }
    beep.get()->Play2D("Assets/Audio/SFX_PieceHold.wav");
    
    startCycleTime = startCycleTime - delayTime;
  }

  isHardDropKeyPressed = Input::GetKey("HardDrop" + player) || Input::GetButton(ButtonCode::DPAD_UP, gamepad);
  isRotationKeyPressed = Input::GetKey("RotateR" + player) || Input::GetKey("RotateL" + player) || Input::GetButton(ButtonCode::A, gamepad) || Input::GetButton(ButtonCode::B, gamepad);;
}

void GameManager::Transformation(bool isClockWise)
{   
    unique_ptr<BoardObject> tmpObject = _currenctObject->Clone();
    tmpObject->Transformation(isClockWise);
    
    _currenctObject->Erase(_board, graphicBoard,_currentPosition, this->piece, this->boardCenter, pieceScale);
    if(!tmpObject->VerifyColision(_board, _currentPosition))
    {
      beep.get()->Play2D("Assets/Audio/SFX_PieceRotate.wav");
      _currenctObject.reset(tmpObject.release());
    }

    _currenctObject->Draw(_board, graphicBoard, _currentPosition, this->piece, this->boardCenter, pieceScale);
    tmpObject.release();
}

void GameManager::MoveObjectLeft()
{
    Position newPosition = _currentPosition;
    newPosition.GoLeft();
    if(!UpdatePosition(newPosition))
      beep.get()->Play2D("Assets/Audio/SFX_PieceMove.wav");
}

void GameManager::MoveObjectRight()
{
    Position newPosition = _currentPosition;
    newPosition.GoRight();
    if(!UpdatePosition(newPosition))
      beep.get()->Play2D("Assets/Audio/SFX_PieceMove.wav");
}

void GameManager::MoveObjectDown()
{
    bool createNewObjectIfFailed = true;
    Position newPosition = _currentPosition;
    newPosition.GoDown();
    if(UpdatePosition(newPosition, createNewObjectIfFailed))
      beep.get()->Play2D("Assets/Audio/SFX_PieceFall.wav");
}

void GameManager::MoveObjectHardDrop()
{
  bool createNewObjectIfFailed = true;
  Position newPosition = _currentPosition;
  
  while(true)
  {
    newPosition = _currentPosition;
    newPosition.GoDown();
    if (UpdatePosition(newPosition, createNewObjectIfFailed))
    {
      beep.get()->Play2D("Assets/Audio/SFX_PieceHardDrop.wav");
      return;
    }
  }
}

bool GameManager::UpdatePosition(const Position& newPosition, const bool createNewObjectIfFailed)
{
    _currenctObject->Erase(_board, graphicBoard, _currentPosition, this->piece, this->boardCenter, pieceScale);

    if (_currenctObject->VerifyColision(_board, newPosition))
    {

        _currenctObject->Draw(_board, graphicBoard, _currentPosition, this->piece, this->boardCenter, pieceScale);

        if (createNewObjectIfFailed)
        {
            _generateNewObject = true;
            _currentPosition.Reset();
        }
        return true;
    }
    else
    {
        _currenctObject->Draw(_board, graphicBoard, newPosition, this->piece, this->boardCenter, pieceScale);
        _currentPosition = newPosition;
        return false;
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
  vec3 translate;

  for (size_t j = 0; j < dstBoard[dstIndex].size(); j++) 
  {
    if (srcBoard[srcIndex][j] != nullptr && dstIndex != srcIndex)
    {
      translate = vec3(0, -abs(dstIndex - srcIndex), 0.0f);
      srcBoard[srcIndex][j]->GetTransform()->Translate(translate);
    } 
    dstBoard[dstIndex][j] = srcBoard[srcIndex][j];
  }
}

void GameManager::ClearLine()
{
    set<int> linesToRemove;

    DetectLinesToRemove(linesToRemove);

    if(linesToRemove.empty())
        return;

    this->UpdateScore(linesToRemove.size());

    GameBoard tmp (BOARD_HEIGHT, vector<int>(BOARD_LENGTH, 0));

    vector<vector<GameObject*>> tmpGraphicBoard (BOARD_HEIGHT, vector<GameObject*>(BOARD_LENGTH, nullptr));

    for (int i : linesToRemove)
    {
      for (int j = 0; j < graphicBoard[i].size(); j++)
      {
        graphicBoard[i][j]->Destroy();
        graphicBoard[i][j] = nullptr;
      }
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
  this->linesToNextLevel -= linesCleared;

  if (this->linesToNextLevel <= 0)
  {
    // Maximum -> 29
    this->level = min(29, this->level + 1);
    this->linesToNextLevel += 10;
  }
  
  // Score
  switch(linesCleared)
  {
  case 1:
    this->score += 40 * (level + 1);
    beep.get()->Play2D("Assets/Audio/SFX_ClearSingle.wav");
    break;
  case 2:
    this->score += 100 * (level + 1);
    beep.get()->Play2D("Assets/Audio/SFX_ClearDouble.wav");
    break;
  case 3:
    this->score += 300 * (level + 1);
    beep.get()->Play2D("Assets/Audio/SFX_ClearTriple.wav");
    break;
  case 4:
    this->score += 1200 * (level + 1);
    beep.get()->Play2D("Assets/Audio/SFX_ClearTetris.wav");
    break;
  }

  // Progression
  if (level < 10)
    this->delayTime = (48 - (5 * level))/60.0f;
  else if (level < 12)
    this->delayTime = 5 / 60.0f;
  else if (level < 15)
    this->delayTime = 4 / 60.0f;
  else if (level < 18)
    this->delayTime = 3 / 60.0f;
  else if (level < 28)
    this->delayTime = 2 / 60.0f;
  else
    this->delayTime = 1 / 60.0f;
}

void GameManager::GameLoop()
{
    bool createNewObjectIfFailed = true;

    if (Time::GetTime() > delayTime + startCycleTime)
    {
      if (!_generateNewObject)
      {
        // Cannot move the object down 
        // if this object is no longer valid
        // and a new object needs to be generated first
        MoveObjectDown();
      }
      startCycleTime = Time::GetTime();
    }

    if(_generateNewObject)
    {
        ClearLine();
        if(nextPieceType == -1)
        {
          ChooseNextPiece();
        }
        ChooseNextPiece();
        canHoldPiece = true;
        _generateNewObject = false;
    }
     
     ManageInput();
    
    //ClearScreen();
    //DrawBoard();
}

void GameManager::ResetGame() 
{
  this->score = 0;
  this->linesCleared = 0;

  this->_generateNewObject = true;

  this->inputDelayTime = 0.28f;
  this->delayTime = 1.0f;
  this->startCycleTime = Time::GetTime();
  this->startInputCycleTime = Time::GetTime();

  for(int i = 0 ; i < piece.size() ; i++)
  {
    piece[i]->Destroy();
    piece[i] = nullptr;
  }

  for(int i = 0; i < this->graphicBoard.size(); i++)
  {
    for(int j = 0; j < this->graphicBoard[i].size(); j++)
    {
      if(this->graphicBoard[i][j] != nullptr)
      {
        this->graphicBoard[i][j]->Destroy();
        this->graphicBoard[i][j] = nullptr;
      }
    }
  }

  for (int i = 0; i < this->_board.size(); i++)
    for (int j = 0; j < this->_board[i].size(); j++)
      this->_board[i][j] = 0;

  this->_currenctObject.reset();

  this->_currentPosition.Reset();
}

void GameManager::Update()
{
  GameLoop();

  //ClearScreen();
  cout << "Score: " << this->score << endl;
  cout << "Level: " << this->level << endl;
  cout << "Lines to Next Level: " << this->linesToNextLevel << endl;
  cout << "Cleared Lines: " << this->linesCleared << endl;
  cout << "Delay Time: " << this->delayTime << endl;
}
