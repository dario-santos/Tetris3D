#pragma once
#pragma once

#include <string>

#include "Assets/Scripts/GameManager.hpp"
#include "BoardObject.hpp"

class SquareObject : public BoardObject
{

public:

    SquareObject();

    ~SquareObject() = default;

    SquareObject(const
      
      
      SquareObject& other) = default;
    SquareObject& operator=(const SquareObject& other) = default;

    virtual void Transformation(bool isClockWise) override;

    std::unique_ptr<BoardObject> Clone() const override;
    
    void Restart() override;


protected:

    const Shape& _GetShape() const override;
    const std::vector< int >& _GetMapping() const override;

private:

    static const Shape _shape;

    static const std::vector < int > _mappingVector;
};