#pragma once

#include <vector>

#include "../Scripts/GameManager.hpp"

class BoardObject
{

public:
	bool VerifyColision( const GameBoard& board, const Position& pos) const;
	
	void Draw(GameBoard& board, vector<vector<GameObject*>>& graphicBoard, const Position& pos, vector<GameObject*> tetromino, float boardCenter) const;
	
	void Erase(GameBoard& board, vector<vector<GameObject*>>& graphicBoard, const Position& pos, vector<GameObject*> tetromino, float boardCenter) const;

	virtual void Transformation() = 0;

	virtual std::unique_ptr<BoardObject> Clone() const = 0;
	
protected:
	
	typedef std::vector<std::vector<int>> Shape;

	BoardObject() = default;

	virtual const Shape& _GetShape() const = 0;
	
	virtual const std::vector<int>& _GetMapping() const = 0;

private:
	void _Draw(GameBoard& board, vector<vector<GameObject*>>& graphicBoard, const Position& pos, const int value, vector<GameObject*> tetromino, float boardCenter) const;
};