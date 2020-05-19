#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "GameEngine/UI/Canvas.hpp"
#include "GameEngine/UI/Button.hpp"
#include "GameEngine/Components/Script.hpp"
#include "GameEngine/Input/Input.hpp"

using namespace glm;

class MenuLogic : public Script
{
    private:
        Canvas* canvas;
        vector<Button*> buttons;
        int activeIndex = 0;

        static bool isKeyHeld;
        static bool isInvokeKey;

        vec3 oldcolor;

    public:
        MenuLogic(Canvas* canvas);
        void Update() override;
};