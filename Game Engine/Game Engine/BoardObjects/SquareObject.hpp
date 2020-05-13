#pragma once
#pragma once

#include <string>

#include "../Scripts\GameManager.hpp"
#include "BoardObject.hpp"

class SquareObject : public BoardObject
{

public:

    SquareObject();

    ~SquareObject() = default;

    SquareObject(const SquareObject& other) = default;
    SquareObject& operator=(const SquareObject& other) = default;

    virtual void Transformation() override;

    std::unique_ptr<BoardObject> Clone() const override;
    //void Update() override;


protected:

    const Shape& _GetShape() const override;
    const std::vector< int >& _GetMapping() const override;

private:

    static const Shape _shape;

    static const std::vector < int > _mappingVector;
};