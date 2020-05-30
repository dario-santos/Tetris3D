#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "GameEngine/UI/Canvas.hpp"
#include "GameEngine/UI/Button.hpp"
#include "GameEngine/UI/Sprite.hpp"
#include "GameEngine/UI/Cursor.hpp"

#include "GameEngine/Audio/AudioDevice.hpp"

#include "GameEngine/Components/Script.hpp"

#include "GameEngine/Input/Input.hpp"

class MarathonMenuLogic : public Script
{
private:

    unique_ptr<AudioDevice> audioDevice;

    Canvas* canvas;
    vector<Button*> buttons;
    vector<Sprite*> sprites;

    int activeIndex = 0;
    Cursor* cursor;

    static bool isKeyHeld;
    static bool isInvokeKey;

public:
    static int levelCont;
    MarathonMenuLogic(Canvas* canvas);
    void Update() override;
};