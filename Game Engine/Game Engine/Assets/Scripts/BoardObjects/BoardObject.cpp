#include "BoardObject.hpp"

const int BLANK = 0;
const int FILL  = 1;

bool BoardObject::VerifyColision(const GameBoard& board, const Position& pos) const
{
    const Shape& shape = _GetShape();
    const std::vector<int>& mappingVector = _GetMapping();

    for(size_t i = 0 ; i < shape.size() ; ++i)
    {
        for(size_t j = 0 ; j < shape.size() ; ++j)
        {
            if(shape[i][j] == 1)
            {
                if(pos._x + mappingVector[i] >= board.size())
                {
                    // Fora do tabuleiro por baixo.
                    return true;
                }

                if(pos._y + mappingVector[j] < 0 || pos._y + mappingVector[j] >= board[i].size())
                {
                    // Fora do tabuleiro à esquerda ou à direita
                    return true;
                }

                if(pos._x + mappingVector[i] >= 0 && board[pos._x + mappingVector[i]][pos._y + mappingVector[j]] == 1)
                {
                    // Colisao com outro objecto
                    return true;
                }
            }
        }
    }

    return false;
}

void BoardObject::Draw(GameBoard& board, vector<vector<GameObject*>>& graphicBoard, const Position& pos, vector<GameObject*> tetromino, float boardCenter, float pieceScale) const
{
    _Draw(board, graphicBoard, pos, FILL, tetromino, boardCenter, pieceScale);
}

void BoardObject::Erase(GameBoard& board, vector<vector<GameObject*>>& graphicBoard, const Position& pos, vector<GameObject*> tetromino, float boardCenter, float pieceScale) const
{
    _Draw(board, graphicBoard, pos, BLANK, tetromino, boardCenter, pieceScale);
}

void BoardObject::_Draw(GameBoard& board, vector<vector<GameObject*>>& graphicBoard, const Position& center, const int value, vector<GameObject*> tetromino, float boardCenter, float pieceScale) const
{
    int cnt = 0;
    const Shape& shape = _GetShape();
    const std::vector<int>& mappingVector = _GetMapping();
    for (size_t i = 0; i < shape.size(); ++i)
    {
        // Por cima do tabuleiro
        if (center._x + mappingVector[i] < 0)
            continue;

        for (size_t j = 0 ; j < shape.size() ; ++j)
          if (shape[i][j] == 1)
          {
            int world_y = center._x + mappingVector[i] - 2; // BoardSize is 22, 22 - 20 = 2
            int world_x = center._y + mappingVector[j];

            if(value == 1)
            {

              if (world_y < 0)
              {
                tetromino[cnt]->Disable();
              }
              else
              {
                tetromino[cnt]->Enable();

              }
              tetromino[cnt]->GetTransform()->TranslateTo(vec3(world_x * pieceScale + boardCenter, world_y * -pieceScale, 1.0f));
              graphicBoard[center._x + mappingVector[i]][center._y + mappingVector[j]] = tetromino[cnt];
              cnt++;
            }
            else
            {
              graphicBoard[center._x + mappingVector[i]][center._y + mappingVector[j]] = nullptr;
            }

            board[center._x + mappingVector[i]][center._y + mappingVector[j]] = value;
          }
    }
}

void BoardObject::UpdateWorldPosition(vector<GameObject*> tetromino, vec3 newPosition, float boardCenter, float pieceScale)
{
  int cnt = 0;

  const Shape& shape = _GetShape();
  const std::vector<int>& mappingVector = _GetMapping();

  for(size_t i = 0; i < shape.size(); ++i)
  {
    for (size_t j = 0; j < shape.size(); ++j)
    {
      if (shape[i][j] == 1)
      {
        int world_y = newPosition.x + mappingVector[i] - 2; // BoardSize is 22, 22 - 20 = 2
        int world_x = newPosition.y + mappingVector[j];

        tetromino[cnt]->GetTransform()->TranslateTo(vec3(world_x * pieceScale + boardCenter, world_y * -pieceScale, 1.0f));
        cnt++;
      }
    }
  }
}