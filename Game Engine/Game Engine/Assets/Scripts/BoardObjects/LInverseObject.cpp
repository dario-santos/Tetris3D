#include "LInverseObject.hpp"

#include <assert.h> 
#include <iostream> 


const BoardObject::Shape LInverseObject::_shapeDown = {  { 0, 0, 0 },
                                                         { 1, 1, 1 },
                                                         { 0, 0, 1 } };


const BoardObject::Shape LInverseObject::_shapeLeft = {  { 0, 1, 0 },
                                                         { 0, 1, 0 },
                                                         { 1, 1, 0 } };



const BoardObject::Shape LInverseObject::_shapeUp = {    { 1, 0, 0 },
                                                         { 1, 1, 1 },
                                                         { 0, 0, 0 } };

const BoardObject::Shape LInverseObject::_shapeRight = {  { 0, 1, 1 },
                                                          { 0, 1, 0 },
                                                          { 0, 1, 0 } };


const std::vector< LInverseObject::Shape > LInverseObject::_shape = { _shapeDown, _shapeLeft, _shapeUp, _shapeRight };

const std::vector < int > LInverseObject::_mappingVector = { -1, 0, 1 };

LInverseObject::LInverseObject() :
    _state(State::STATE_UP)
{

}

const LInverseObject::Shape& LInverseObject::_GetShape() const
{
    return _shape[_state];
}

const std::vector<int>& LInverseObject::_GetMapping() const
{
    return _mappingVector;
}

void LInverseObject::Transformation(bool isClockWise)
{
  if (isClockWise)
  {
    _state = static_cast<State>((_state + 1) % State::STATES_TOTAL);
  }
  else
  {
    int tmp = (_state - 1) % State::STATES_TOTAL;
    if (tmp == -1)
      tmp = State::STATES_TOTAL - 1;
    _state = static_cast<State>(tmp);
  }
}

std::unique_ptr<BoardObject> LInverseObject::Clone() const
{
    return std::make_unique< LInverseObject >(*this);
}