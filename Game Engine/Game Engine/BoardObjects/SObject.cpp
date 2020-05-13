#include "SObject.hpp"

#include <assert.h> 

const BoardObject::Shape SObject::_shapeHorizontal = {   { 0, 1, 1 },
                                                         { 1, 1, 0 },
                                                         { 0, 0, 0 } };

const BoardObject::Shape SObject::_shapeVertical = {  { 1, 0, 0 },
                                                     { 1, 1, 0 },
                                                     { 0, 1, 0 } };


const std::vector< SObject::Shape > SObject::_shape = { _shapeHorizontal, _shapeVertical };

const std::vector < int > SObject::_mappingVector = { -1, 0, 1 };

SObject::SObject() :
    _state(State::STATE_HORIZONTAL)
{

}

const SObject::Shape& SObject::GetShape() const
{
    return _shape[_state];
}

const std::vector< int >& SObject::_GetMapping() const
{
    return _mappingVector;
}

void SObject::Transformation()
{
    _state = static_cast<State>((_state + 1) % State::STATES_TOTAL);
}

std::unique_ptr<BoardObject> SObject::Clone() const
{
    return std::make_unique< SObject >(*this);
}