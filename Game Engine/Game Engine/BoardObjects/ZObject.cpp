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

const ZObject::Shape& ZObject::GetShape() const
{
    return _shape[ _state ];
}

const std::vector< int >& ZObject::_GetMapping() const
{
    return _mappingVector;
}

void ZObject::Transformation()
{
    _state = static_cast<State>( ( _state + 1) %  State::STATES_TOTAL );
}

std::unique_ptr<BoardObject> ZObject::Clone() const
{
    return std::make_unique< ZObject >( *this );
}