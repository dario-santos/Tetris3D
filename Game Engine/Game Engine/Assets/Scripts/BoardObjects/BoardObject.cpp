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

void BoardObject::Draw(GameBoard& board, vector<vector<GameObject*>>& graphicBoard, const Position& pos, vector<GameObject*> tetromino, float boardCenter) const
{
    _Draw(board, graphicBoard, pos, FILL, tetromino, boardCenter);
}

void BoardObject::Erase(GameBoard& board, vector<vector<GameObject*>>& graphicBoard, const Position& pos, vector<GameObject*> tetromino, float boardCenter) const
{
    _Draw(board, graphicBoard, pos, BLANK, tetromino, boardCenter);
}

void BoardObject::_Draw(GameBoard& board, vector<vector<GameObject*>>& graphicBoard, const Position& center, const int value, vector<GameObject*> tetromino, float boardCenter) const
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
              tetromino[cnt]->GetTransform()->TranslateTo(vec3(world_x * 10 + boardCenter, world_y * -10, 1.0f));
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
