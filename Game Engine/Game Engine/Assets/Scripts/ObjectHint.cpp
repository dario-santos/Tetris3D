#include "ObjectHint.hpp"

#include "BoardObjects/BoardObject.hpp"
#include "GameManager.hpp"

ObjectHint::ObjectHint() :
  _object(nullptr)
{

}

void ObjectHint::NewBlock(const std::unique_ptr<BoardObject>& object)
{
  _object = object->Clone();
}

Position ObjectHint::PositionShadowHint(const GameBoard& board, Position pos)
{
  Position ret = pos;

  while (!_object->VerifyColision(board, pos))
  {
    ret = pos;
    pos.GoDown();
  }

  return ret;
}

void ObjectHint::Draw(GameBoard& board, std::vector<std::vector<GameObject*>>& graphicBoard, const Position& pos, std::vector<GameObject*> tetromino, float boardCenter) const
{
  _object->DrawShadow(board, graphicBoard, pos, tetromino, boardCenter, 10.0f);
}

void ObjectHint::Erase(GameBoard& board, std::vector<std::vector<GameObject*>>& graphicBoard, const Position& pos, std::vector<GameObject*> tetromino, float boardCenter) const
{
  _object->Erase(board, graphicBoard, pos, tetromino, boardCenter, 10.0f);
}
