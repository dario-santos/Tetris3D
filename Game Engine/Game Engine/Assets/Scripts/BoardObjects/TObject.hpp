#pragma once
#pragma once

#include <string>

#include "Assets/Scripts/GameManager.hpp"
#include "BoardObject.hpp"

class TObject : public BoardObject
{

public:

    TObject();

    ~TObject() = default;

    TObject(const
      
      
      
    TObject& other) = default;
    TObject& operator=(const TObject& other) = default;

    virtual void Transformation(bool isClockWise) override;

    std::unique_ptr<BoardObject> Clone() const override;
    
    void Restart() override;


protected:

    const Shape& _GetShape() const override;
    const std::vector< int >& _GetMapping() const override;

private:

    enum State
    {
        STATE_UP = 0,
        STATE_RIGHT,
        STATE_DOWN,
        STATE_LEFT,
        STATES_TOTAL
    };


    static const Shape _shapeUp;
    static const Shape _shapeLeft;
    static const Shape _shapeDown;
    static const Shape _shapeRight;
    static const std::vector< BoardObject::Shape > _shape;

    static const std::vector < int > _mappingVector;

    State _state;



};