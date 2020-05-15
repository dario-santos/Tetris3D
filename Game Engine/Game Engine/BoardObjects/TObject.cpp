#include "TObject.hpp"

#include <assert.h> 
#include <iostream> 

const BoardObject::Shape TObject::_shapeUp = {    { 0, 1, 0 },
                                                  { 1, 1, 1 },
                                                  { 0, 0, 0 } };

const BoardObject::Shape TObject::_shapeRight = {  { 0, 1, 0 },
                                                   { 0, 1, 1 },
                                                   { 0, 1, 0 } };

const BoardObject::Shape TObject::_shapeDown = {  { 0, 0, 0 },
                                                  { 1, 1, 1 },
                                                  { 0, 1, 0 } };

const BoardObject::Shape TObject::_shapeLeft = {  { 0, 1, 0 },
                                                  { 1, 1, 0 },
                                                  { 0, 1, 0 } };




const std::vector< TObject::Shape > TObject::_shape = { _shapeUp, _shapeRight, _shapeDown, _shapeLeft };

const std::vector < int > TObject::_mappingVector = { -1, 0, 1 };

TObject::TObject() :
    _state(State::STATE_UP)
{

}

const TObject::Shape& TObject::_GetShape() const
{
    return _shape[_state];
}

const std::vector<int>& TObject::_GetMapping() const
{
    return _mappingVector;
}

void TObject::Transformation(bool isClockWise)
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


std::unique_ptr<BoardObject> TObject::Clone() const
{
    return std::make_unique< TObject >(*this);
}