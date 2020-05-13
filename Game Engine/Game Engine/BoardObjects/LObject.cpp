#include "LObject.hpp"

#include <assert.h> 
#include <iostream> 

const BoardObject::Shape LObject::_shapeUp = {    { 0, 0, 1 },
                                                  { 1, 1, 1 },
                                                  { 0, 0, 0 } };

const BoardObject::Shape LObject::_shapeRight = {  { 0, 1, 0 },
                                                   { 0, 1, 0 },
                                                   { 0, 1, 1 } };

const BoardObject::Shape LObject::_shapeDown = {  { 0, 0, 0 },
                                                  { 1, 1, 1 },
                                                  { 1, 0, 0 } };

const BoardObject::Shape LObject::_shapeLeft = {  { 1, 1, 0 },
                                                  { 0, 1, 0 },
                                                  { 0, 1, 0 } };




const std::vector< LObject::Shape > LObject::_shape = { _shapeUp, _shapeRight, _shapeDown, _shapeLeft };

const std::vector < int > LObject::_mappingVector = { -1, 0, 1 };

LObject::LObject() :
    _state(State::STATE_UP)
{

}

const LObject::Shape& LObject::GetShape() const
{
    return _shape[_state];
}

const std::vector< int >& LObject::_GetMapping() const
{
    return _mappingVector;
}

void LObject::Transformation()
{
    _state = static_cast<State>((_state + 1) % State::STATES_TOTAL);
}

std::unique_ptr<BoardObject> LObject::Clone() const
{
    return std::make_unique< LObject >(*this);
}