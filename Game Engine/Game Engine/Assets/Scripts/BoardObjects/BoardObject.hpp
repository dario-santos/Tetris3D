#pragma once

#include <vector>

#include "Assets/Scripts/GameManager.hpp"

class BoardObject
{
public:
	bool VerifyColision(const GameBoard& board, const Position& pos) const;
	
	void Draw(GameBoard& board, vector<vector<GameObject*>>& graphicBoard, const Position& pos, vector<GameObject*> tetromino, float boardCenter, float pieceScale) const;
	
	void DrawShadow(GameBoard& board, vector<vector<GameObject*>>& graphicBoard, const Position& pos, vector<GameObject*> tetromino, float boardCenter, float pieceScale) const;

	void Erase(GameBoard& board, vector<vector<GameObject*>>& graphicBoard, const Position& pos, vector<GameObject*> tetromino, float boardCenter, float pieceScale) const;

	void UpdateWorldPosition(vector<GameObject*> tetromino, vec3 newPosition, float boardCenter, float pieceScale);
	
	virtual void Transformation(bool isClockWise) = 0;

	virtual std::unique_ptr<BoardObject> Clone() const = 0;

	virtual void Restart() = 0;

	~BoardObject() = default;

protected:
	typedef std::vector<std::vector<int>> Shape;

	BoardObject() = default;

	virtual const Shape& _GetShape() const = 0;
	
	virtual const std::vector<int>& _GetMapping() const = 0;

private:
	void _Draw(GameBoard& board, vector<vector<GameObject*>>& graphicBoard, const Position& pos, const int value, vector<GameObject*> tetromino, float boardCenter, float pieceScale) const;
};