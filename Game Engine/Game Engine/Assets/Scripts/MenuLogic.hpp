#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "GameEngine/UI/Canvas.hpp"
#include "GameEngine/UI/Button.hpp"
#include "GameEngine/UI/Cursor.hpp"

#include "GameEngine/Components/Script.hpp"

#include "GameEngine/Input/Input.hpp"

#include "GameEngine/Audio/AudioDevice.hpp"
using namespace glm;

class MenuLogic : public Script
{
    private:
        unique_ptr<AudioDevice> audioDevice;

        Canvas* canvas;
        vector<Button*> buttons;

        int activeIndex = 0;
        Cursor* cursor;

        static bool isKeyHeld;
        static bool isInvokeKey;

    public:
        MenuLogic(Canvas* canvas);
        void Update() override;
};