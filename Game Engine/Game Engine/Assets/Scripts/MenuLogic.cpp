#include "./MenuLogic.hpp"

#include <iostream>

MenuLogic::MenuLogic(Canvas* canvas)
{
    this->canvas = canvas;
    this->buttons = canvas->GetButtons();
    this->cursor = canvas->GetCursor();

    //oldcolor = buttons[activeIndex]->GetShader()->GetIPrimitive()->GetColor();

    //buttons[activeIndex]->GetShader()->GetIPrimitive()->UpdateColor(vec3(255, 255, 255));

    vec3 pos = buttons[activeIndex]->GetTransform()->position;
    cursor->GetTransform()->TranslateTo(vec3(pos.x - abs(cursor->delta), pos.y, pos.z));
}

bool MenuLogic::isKeyHeld = false;
bool MenuLogic::isInvokeKey = false;

void MenuLogic::Update()
{

    if (canvas == nullptr || !canvas->IsEnabled()) 
        return;

    // Movement
    if ((Input::GetKey(KeyCode::DownArrow) || Input::GetButton(ButtonCode::DPAD_DOWN)) && !MenuLogic::isKeyHeld)
    {
        MenuLogic::isKeyHeld = true;
        //buttons[activeIndex]->GetShader()->GetIPrimitive()->UpdateColor(this->oldcolor);
        activeIndex = (activeIndex + 1) % buttons.size();

        // Move cursor
        vec3 pos = buttons[activeIndex]->GetTransform()->position;
        cursor->GetTransform()->TranslateTo(vec3(pos.x - abs(cursor->delta), pos.y, pos.z));

        //oldcolor = buttons[activeIndex]->GetShader()->GetIPrimitive()->GetColor();

        //buttons[activeIndex]->GetShader()->GetIPrimitive()->UpdateColor(vec3(255,255,255));
    }
    else if ((Input::GetKey(KeyCode::UpArrow) || Input::GetButton(ButtonCode::DPAD_UP)) && !MenuLogic::isKeyHeld)
    {
        MenuLogic::isKeyHeld = true;
        //buttons[activeIndex]->GetShader()->GetIPrimitive()->UpdateColor(this->oldcolor);
        activeIndex--;

        if (activeIndex < 0)
            activeIndex = buttons.size() - 1;

        // Move cursor
        vec3 pos = buttons[activeIndex]->GetTransform()->position;
        cursor->GetTransform()->TranslateTo(vec3(pos.x - abs(cursor->delta), pos.y, pos.z));

        //oldcolor = buttons[activeIndex]->GetShader()->GetIPrimitive()->GetColor();

        //buttons[activeIndex]->GetShader()->GetIPrimitive()->UpdateColor(vec3(255, 255, 255));
    }
        
    // Action
    if ((Input::GetKey(KeyCode::M) || Input::GetButton(ButtonCode::A)) && !MenuLogic::isInvokeKey)
    {
        MenuLogic::isInvokeKey = true;

        if (buttons[activeIndex] != nullptr)
            buttons[activeIndex]->OnClick();
    }
    
    MenuLogic::isKeyHeld = !(Input::GetKeyUp(KeyCode::DownArrow) && Input::GetKeyUp(KeyCode::UpArrow)
                          && !Input::GetButton(ButtonCode::DPAD_DOWN) && !Input::GetButton(ButtonCode::DPAD_UP));
    MenuLogic::isInvokeKey = !(Input::GetKeyUp(KeyCode::M) && !Input::GetButton(ButtonCode::A));
}