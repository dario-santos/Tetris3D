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
  this->shadowPiece = HintBlock::AddHintBlock(10, vec3(255, 255, 255), material);
  
  for (GameObject* g : this->shadowPiece)
    Scene::CurrentScene()->AddGameObject(g);

  this->_currentPosition.Reset();


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

vector<int> GameManager::pieceList = vector<int>();
bool GameManager::isPaused = false;

void GameManager::ChooseNextPiece()
{
  switch (lastPiece) // [0, 7[
  {
  case tetrominos::O:
    _currenctObject.reset(new SquareObject());
    this->nextPiece = IBlock::AddIBlock(pieceScale, vec3(255, 213, 0), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f));
    break;
  case tetrominos::I:
    _currenctObject.reset(new LineObject());
    this->nextPiece = IBlock::AddIBlock(pieceScale, vec3(0, 255, 255), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f));
    break;
  case tetrominos::L:
    _currenctObject.reset(new LObject());
    this->nextPiece = IBlock::AddIBlock(pieceScale, vec3(3, 65, 174), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f));
    break;
  case tetrominos::J:
    _currenctObject.reset(new LInverseObject());
    this->nextPiece = IBlock::AddIBlock(pieceScale, vec3(255, 151, 28), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f));
    break;
  case tetrominos::T:
    _currenctObject.reset(new TObject());
    this->nextPiece = IBlock::AddIBlock(pieceScale, vec3(128, 0, 128), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f));
    break;
  case tetrominos::Z:
    _currenctObject.reset(new ZObject());
    this->nextPiece = IBlock::AddIBlock(pieceScale, vec3(255, 50, 19), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f));
    break;
  case tetrominos::S:
    _currenctObject.reset(new SObject());
    this->nextPiece = IBlock::AddIBlock(pieceScale, vec3(114, 203, 59), new Material(vec3(1.0f), vec3(1.0f), vec3(1.0f), 128.0f));
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
    // Update Shadow Color
    vec3 color = piece[0]->shader->GetIPrimitive()->GetColor();
    for (GameObject* g : this->shadowPiece)
      g->shader->GetIPrimitive()->UpdateColor(color);

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
      else if (_board[i][j] == 1)
        cout << "# ";
      else
        cout << "o ";
    }
  }
}

void GameManager::ManageInput()
{
  string player = std::to_string((static_cast<int>(gamepad)));

  // Reset DAS
  if (!Input::GetKey("Right" + player) && !Input::GetButton(ButtonCode::DPAD_RIGHT, gamepad)
    && !Input::GetKey("Left" + player) && !Input::GetButton(ButtonCode::DPAD_LEFT, gamepad)
    && !Input::GetKey("Drop" + player) && !Input::GetButton(ButtonCode::DPAD_DOWN, gamepad))
    movementAmmount = 0;

  // Update DAS
  if(movementAmmount == 0)
    inputDelayTime = 0.0f;
  else if(movementAmmount == 1)
    inputDelayTime = 0.26;
  else
    inputDelayTime = 0.1f;

  // Movement
  if(Time::GetTime() > inputDelayTime + startInputCycleTime)
  {
    startInputCycleTime = Time::GetTime();
    
    if(Input::GetKey("Right" + player) || Input::GetButton("Right", gamepad))
    {
      MoveObjectRight();
      movementAmmount++;
    }
    else if (Input::GetKey("Left" + player) || Input::GetButton("Left", gamepad))
    {
      MoveObjectLeft();
      movementAmmount++;
    }
    if(Input::GetKey("Drop" + player) || Input::GetButton("Drop", gamepad))
    {
      MoveObjectDown();
      movementAmmount++;
      startCycleTime = Time::GetTime();
    }
  }

  // HardDrop
  if ((Input::GetKey("HardDrop" + player) || Input::GetButton("HardDrop", gamepad)) && !isHardDropKeyPressed)
  {
    isHardDropKeyPressed = true;
    MoveObjectHardDrop();
  }

  // Rotations
  if((Input::GetKey("RotateR" + player) || Input::GetButton("RotateR", gamepad)) && !isRotationKeyPressed)
  {
    isRotationKeyPressed = true;
    Transformation(true);
  }
  else if ((Input::GetKey("RotateL" + player) || Input::GetButton("RotateL", gamepad)) && !isRotationKeyPressed)
  {
    isRotationKeyPressed = true;
    Transformation(false);
  }

  // Hold
  if((Input::GetKey("Hold" + player) || Input::GetButton("Hold", gamepad) || Input::GetButton("HoldAlt", gamepad)) && canHoldPiece && !isHoldKeyPressed)
  {
    canHoldPiece = false;
    
    HoldPiece();

    beep.get()->Play2D("Assets/Audio/SFX_PieceHold.wav");
    
    // Ends cycle loop
    startCycleTime -= delayTime;
  }

  isHardDropKeyPressed = Input::GetKey("HardDrop" + player) || Input::GetButton("HardDrop", gamepad);
  isRotationKeyPressed = Input::GetKey("RotateR" + player) || Input::GetKey("RotateL" + player) || Input::GetButton("RotateR", gamepad) || Input::GetButton("RotateL", gamepad);
  isHoldKeyPressed = Input::GetKey("Hold" + player) || Input::GetButton("Hold", gamepad) || Input::GetButton("HoldAlt", gamepad);
}

void GameManager::HoldPiece() 
{
  _currenctObject->Erase(_board, graphicBoard, _currentPosition, this->piece, this->boardCenter, pieceScale);

  _currenctObject->Restart();
  _currenctObject->UpdateWorldPosition(this->piece, vec3(4, 13, 1), this->boardCenter, pieceScale);

  for (GameObject* g : piece)
    g->Enable();

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


  // Update Shadow Color
  vec3 color = piece[0]->shader->GetIPrimitive()->GetColor();
  for (GameObject* g : this->shadowPiece)
    g->shader->GetIPrimitive()->UpdateColor(color);
}

void GameManager::Transformation(bool isClockWise)
{   
  if (_generateNewObject)
    return;

    unique_ptr<BoardObject> tmpObject = _currenctObject->Clone();
    tmpObject->Transformation(isClockWise);
    
    _currenctObject->Erase(_board, graphicBoard, _currentPosition, this->piece, this->boardCenter, pieceScale);
    EraseShadowHint();

    if(!tmpObject->VerifyColision(_board, _currentPosition))
    {
      beep.get()->Play2D("Assets/Audio/SFX_PieceRotate.wav");
      _currenctObject.reset(tmpObject.get());
    }
    
    DrawShadowHint();
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
  if (_generateNewObject)
    return false;

    _currenctObject->Erase(_board, graphicBoard, _currentPosition, this->piece, this->boardCenter, pieceScale);

    if (_currenctObject->VerifyColision(_board, newPosition))
    {

        _currenctObject->Draw(_board, graphicBoard, _currentPosition, this->piece, this->boardCenter, pieceScale);

        if (createNewObjectIfFailed)
        {
          _currentPosition.Reset();
          _generateNewObject = true;
        }
        return true;
    }
    else
    {
      EraseShadowHint();
      _currenctObject->Draw(_board, graphicBoard, newPosition, this->piece, this->boardCenter, pieceScale);
      _currentPosition = newPosition;
      DrawShadowHint();

      return false;
    }
}

void GameManager::ClearScreen()
{
    system("cls");
}

void GameManager::DetectLinesToRemove(std::set<int>& linesToRemove) const
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

    beep.get()->Play2D("Assets/Audio/SFX_LevelUp.wav");

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
  if (level < 9)
    this->delayTime = (48 - (5 * level))/60.0f;
  else if (level == 9)
    this->delayTime = 6 / 60.0f;
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

void GameManager::GameOver()
{
  if(_currenctObject->VerifyColision(_board, _currentPosition))
  {
    isGameOver = true;
  }
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

     ManageInput();
    
     if(_generateNewObject)
      {
        // Delete hold piece
        canHoldPiece = false;
        ClearLine();

        if (nextPieceType == -1)
        {
          // Add new int to vector
          if (GameManager::pieceList.empty() || this->pieceListIndex >= GameManager::pieceList.size())
          {
            // Nes randomizer
            int r = rand() % tetrominos::Total;
            pieceList.push_back(r);
          }

          lastPiece = pieceList[pieceListIndex];
          nextPieceType = pieceList[pieceListIndex];
          pieceListIndex++;

          ChooseNextPiece();
        }
         
        // Add new int to vector
        if (this->pieceListIndex >= GameManager::pieceList.size())
        {
          // Nes randomizer
          int r = rand() % tetrominos::Total;
          if (pieceList[pieceList.size() - 1] == r)
            r = rand() % tetrominos::Total;

          pieceList.push_back(r);
        }
        
        currentPieceType = lastPiece;

        lastPiece = pieceList[pieceListIndex];
        nextPieceType = pieceList[pieceListIndex];
        pieceListIndex++;
        

        // Passar a antiga para ativa
        if (currentPieceType != -1)
            piece = nextPiece;
        
        ChooseNextPiece();

        GameOver();

        if(isGameOver)
          return;
        
        canHoldPiece = true;
        _generateNewObject = false;

        EraseShadowHint();
        DrawShadowHint();
    }
    
    // ClearScreen();
    // DrawBoard();
}

void GameManager::Update()
{
  if(GameManager::isPaused)
    return;

  GameLoop();

  //ClearScreen();
  cout << "Score: " << this->score << endl;
  cout << "Level: " << this->level << endl;
  cout << "Lines to Next Level: " << this->linesToNextLevel << endl;
  cout << "Cleared Lines: " << this->linesCleared << endl;
  cout << "Delay Time: " << this->delayTime << endl;
}

void GameManager::DrawShadowHint()
{
  shadowHint.NewBlock(_currenctObject);

  //_currenctObject->Erase(_board, graphicBoard, _currentPosition, shadowPiece, boardCenter, pieceScale);
  
  shadowHint.Erase(_board, graphicBoard, _currentPosition, shadowPiece, boardCenter);
  
  _positionHint = shadowHint.PositionShadowHint(_board, _currentPosition);

  //_currenctObject->Draw(_board, graphicBoard, _currentPosition, shadowPiece, boardCenter, pieceScale);
  shadowHint.Draw(_board, graphicBoard, _currentPosition, shadowPiece, boardCenter);

  if (_positionHint._x != _currentPosition._x)
    shadowHint.Draw(_board, graphicBoard, _positionHint, shadowPiece, boardCenter);

}

void GameManager::EraseShadowHint()
{
  shadowHint.NewBlock(_currenctObject);

  shadowHint.Erase(_board, graphicBoard, _currentPosition, shadowPiece, boardCenter);

  //_currenctObject->Erase(_board, graphicBoard, _currentPosition, shadowPiece, boardCenter, pieceScale);
  _positionHint = shadowHint.PositionShadowHint(_board, _currentPosition);

  if (_positionHint._x != _currentPosition._x)
  {
    shadowHint.Erase(_board, graphicBoard, _currentPosition, shadowPiece, boardCenter);
  }
}
