#include "ZObject.hpp"

#include <assert.h> 

const BoardObject::Shape ZObject::_shapeHorizontal = {   { 1, 1, 0 },
                                                         { 0, 1, 1 },
                                                         { 0, 0, 0 } };

const BoardObject::Shape ZObject::_shapeVertical = {  { 0, 0, 1 },
                                                     { 0, 1, 1 },
                                                     { 0, 1, 0 } };


const std::vector< ZObject::Shape > ZObject::_shape = { _shapeHorizontal, _shapeVertical };

const std::vector < int > ZObject::_mappingVector = { -1, 0, 1 };

ZObject::ZObject() :
    _state( State::STATE_HORIZONTAL )
{

}

const ZObject::Shape& ZObject::_GetShape() const
{
    return _shape[ _state ];
}

const std::vector< int >& ZObject::_GetMapping() const
{
    return _mappingVector;
}

void ZObject::Transformation(bool isClockWise)
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

std::unique_ptr<BoardObject> ZObject::Clone() const
{
    return std::make_unique< ZObject >( *this );
}