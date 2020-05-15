#pragma once
#pragma once

#include <string>

#include "../Scripts\GameManager.hpp"
#include "BoardObject.hpp"

class LineObject : public BoardObject
{

public:

    LineObject();

    ~LineObject() = default;

    LineObject(const LineObject& other) = default;
    LineObject& operator=(const LineObject& other) = default;

    virtual void Transformation(bool isClockWise) override;

    std::unique_ptr<BoardObject> Clone() const override;
    //void Update() override;


protected:

    const Shape& _GetShape() const override;
    const std::vector< int >& _GetMapping() const override;

private:

    enum State
    {
        STATE_HORIZONTAL = 0,
        STATE_VERTICAL,
        STATES_TOTAL
    };


    static const Shape _shapeHorizontal;
    static const Shape _shapeVertical;
    static const std::vector< BoardObject::Shape > _shape;

    static const std::vector < int > _mappingVector;

    State _state;



};