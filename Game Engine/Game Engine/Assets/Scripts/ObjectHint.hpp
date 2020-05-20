#pragma once

#include <memory>
#include "GameBoard.hpp"
#include "Position.hpp"

// Forward Declaration
class BoardObject;
class GameObject;


class ObjectHint
{

public:

  ObjectHint();
  ~ObjectHint() = default;

  void NewBlock(const std::unique_ptr<BoardObject>& object);

  Position PositionShadowHint(const GameBoard& board, Position pos);

  void Draw(GameBoard& board, std::vector<std::vector<GameObject*>>& graphicBoard, const Position& pos, std::vector<GameObject*> tetromino, float boardCenter) const;
  void Erase(GameBoard& board, std::vector<std::vector<GameObject*>>& graphicBoard, const Position& pos, std::vector<GameObject*> tetromino, float boardCenter) const;

private:

  std::unique_ptr<BoardObject> _object;

};
