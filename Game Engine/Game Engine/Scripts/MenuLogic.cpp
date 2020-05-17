#include "./MenuLogic.hpp"

// go->AddScript(new CameraMovement(mainMenu));
MenuLogic::MenuLogic(Canvas* canvas)
{
    this->canvas = canvas;
    this->buttons = canvas->GetButtons();

    oldcolor = buttons[activeIndex]->GetRenderer()->GetIPrimitive()->GetColor();

    buttons[activeIndex]->GetRenderer()->GetIPrimitive()->UpdateColor(vec3(255, 255, 255));
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
        buttons[activeIndex]->GetRenderer()->GetIPrimitive()->UpdateColor(this->oldcolor);
        activeIndex = (activeIndex + 1) % buttons.size();

        oldcolor = buttons[activeIndex]->GetRenderer()->GetIPrimitive()->GetColor();

        buttons[activeIndex]->GetRenderer()->GetIPrimitive()->UpdateColor(vec3(255,255,255));
    }
    else if ((Input::GetKey(KeyCode::UpArrow) || Input::GetButton(ButtonCode::DPAD_UP)) && !MenuLogic::isKeyHeld)
    {
        MenuLogic::isKeyHeld = true;
        buttons[activeIndex]->GetRenderer()->GetIPrimitive()->UpdateColor(this->oldcolor);
        activeIndex--;

        if (activeIndex < 0)
            activeIndex = buttons.size() - 1;

        oldcolor = buttons[activeIndex]->GetRenderer()->GetIPrimitive()->GetColor();

        buttons[activeIndex]->GetRenderer()->GetIPrimitive()->UpdateColor(vec3(255, 255, 255));
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