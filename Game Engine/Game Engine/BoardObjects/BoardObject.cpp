#include "BoardObject.hpp"

const int BLANK = 0;
const int FILL  = 1;

bool BoardObject::VerifyColision( const GameBoard& board, const Position& pos) const
{
    const Shape& shape = GetShape();
    const std::vector< int >& mappingVector = _GetMapping();

    for (size_t i = 0; i < shape.size(); ++i)
    {
        for (size_t j = 0; j < shape.size(); ++j)
        {
            if (shape[i][j] == 1)
            {
                // Check boundaries 
                if (pos._x + mappingVector[i] >= board.size())
                {
                    // Fora do tabuleiro por baixo.
                    return true;
                }

                if (pos._y + mappingVector[j] < 0 || pos._y + mappingVector[j] >= board[i].size())
                {
                    // Fora do tabuleiro à esquerda ou à direita
                    return true;
                }

                if ( pos._x + mappingVector[i] >= 0 && board[pos._x + mappingVector[i]][pos._y + mappingVector[j]] == 1)
                {
                    // Colisao com outro objecto
                    return true;
                }
            }
        }
    }

    return false;
}

void BoardObject::Draw( GameBoard& board, const Position& pos) const
{
    _Draw( board, pos, FILL);
}

void BoardObject::Erase(GameBoard& board, const Position& pos) const
{
    _Draw( board, pos, BLANK);
}

void BoardObject::_Draw(GameBoard& board, const Position& pos, const int value) const
{
    const Shape& shape = GetShape();
    const std::vector< int >& mappingVector = _GetMapping();

    for (size_t i = 0; i < shape.size(); ++i)
    {
        if (pos._x + mappingVector[i] < 0)
        {
            // Por cima do tabuleiro
            continue;
        }

        for (size_t j = 0; j < shape.size(); ++j)
        {
            if (shape[i][j] == 1)
            {
                board[pos._x + mappingVector[i]][pos._y + mappingVector[j]] = value;
            }
        }
    }
}