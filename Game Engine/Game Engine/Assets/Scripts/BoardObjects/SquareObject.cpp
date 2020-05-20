#include "SquareObject.hpp"

#include <assert.h> 
#include <iostream> 


const BoardObject::Shape SquareObject::_shape = { { 0, 0, 0, 0 },
                                                  { 0, 1, 1, 0 },
                                                  { 0, 1, 1, 0 },
                                                  { 0, 0, 0, 0 } };

const std::vector < int > SquareObject::_mappingVector = { -2, -1, 0, 1, 2 };

SquareObject::SquareObject()
{

}

const SquareObject::Shape& SquareObject::_GetShape() const
{
    return _shape;
}

const std::vector<int>& SquareObject::_GetMapping() const
{
    return _mappingVector;
}

void SquareObject::Transformation(bool isClockWise)
{
    //Nothing to be done
}

std::unique_ptr<BoardObject> SquareObject::Clone() const
{
    return std::make_unique< SquareObject >(*this);
}

void SquareObject::Restart()
{
  // Nothing
}
