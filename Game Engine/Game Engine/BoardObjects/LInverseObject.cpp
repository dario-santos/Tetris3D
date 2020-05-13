#include "LInverseObject.hpp"

#include <assert.h> 
#include <iostream> 

const BoardObject::Shape LInverseObject::_shapeUp = {    { 1, 0, 0 },
                                                         { 1, 1, 1 },
                                                         { 0, 0, 0 } };

const BoardObject::Shape LInverseObject::_shapeRight = {  { 0, 1, 1 },
                                                          { 0, 1, 0 },
                                                          { 0, 1, 0 } };

const BoardObject::Shape LInverseObject::_shapeDown = {  { 0, 0, 0 },
                                                         { 1, 1, 1 },
                                                         { 0, 0, 1 } };

const BoardObject::Shape LInverseObject::_shapeLeft = {  { 0, 1, 0 },
                                                         { 0, 1, 0 },
                                                         { 1, 1, 0 } };

const std::vector< LInverseObject::Shape > LInverseObject::_shape = { _shapeUp, _shapeRight, _shapeDown, _shapeLeft };

const std::vector < int > LInverseObject::_mappingVector = { -1, 0, 1 };

LInverseObject::LInverseObject() :
    _state(State::STATE_UP)
{

}

const LInverseObject::Shape& LInverseObject::GetShape() const
{
    return _shape[_state];
}

const std::vector< int >& LInverseObject::_GetMapping() const
{
    return _mappingVector;
}

void LInverseObject::Transformation()
{
    _state = static_cast<State>((_state + 1) % State::STATES_TOTAL);
}

std::unique_ptr<BoardObject> LInverseObject::Clone() const
{
    return std::make_unique< LInverseObject >(*this);
}