#include "LineObject.hpp"

#include <assert.h> 
#include <iostream> 

const BoardObject::Shape LineObject::_shapeHorizontal = {    { 0, 0, 0, 0, 0 },
                                                             { 0, 0, 0, 0, 0 },
                                                             { 0, 1, 1, 1, 1 },
                                                             { 0, 0, 0, 0, 0 },
                                                             { 0, 0, 0, 0, 0 } };

const BoardObject::Shape LineObject::_shapeVertical = {      { 0, 0, 0, 0, 0 },
                                                             { 0, 0, 1, 0, 0 },
                                                             { 0, 0, 1, 0, 0 },
                                                             { 0, 0, 1, 0, 0 },
                                                             { 0, 0, 1, 0, 0 } };





const std::vector< LineObject::Shape > LineObject::_shape = { _shapeHorizontal, _shapeVertical };

const std::vector < int > LineObject::_mappingVector = { -2, -1, 0, 1, 2 };

LineObject::LineObject() :
    _state(State::STATE_HORIZONTAL)
{

}

const LineObject::Shape& LineObject::GetShape() const
{
    return _shape[_state];
}

const std::vector< int >& LineObject::_GetMapping() const
{
    return _mappingVector;
}

void LineObject::Transformation()
{
    _state = static_cast<State>((_state + 1) % State::STATES_TOTAL);
}

std::unique_ptr<BoardObject> LineObject::Clone() const
{
    return std::make_unique< LineObject >(*this);
}