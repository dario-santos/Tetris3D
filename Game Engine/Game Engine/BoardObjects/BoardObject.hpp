#pragma once

#include <vector>
#include "../Scripts/GameManager.hpp"

class BoardObject
{

public:
	
	~BoardObject() = default;

	typedef std::vector< std::vector < int > > Shape;

	bool VerifyColision( const GameBoard& board, const Position& pos) const;
	void Draw( GameBoard& board, const Position& pos) const;
	void Erase( GameBoard& board, const Position& pos) const;

	virtual void Transformation() = 0;

	virtual const Shape& GetShape() const = 0;

	virtual std::unique_ptr<BoardObject> Clone() const = 0;
	
protected:

	BoardObject() = default;

	virtual const std::vector< int >& _GetMapping() const = 0;

private:
	void _Draw( GameBoard& board, const Position& pos, const int value) const;
};