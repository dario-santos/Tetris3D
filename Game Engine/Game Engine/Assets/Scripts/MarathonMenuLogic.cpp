#include "./MarathonMenuLogic.hpp"

MarathonMenuLogic::MarathonMenuLogic(Canvas* canvas)
{
    this->canvas = canvas;
    this->buttons = canvas->GetButtons();
    this->sprites = canvas->GetSprites();
    this->cursor = canvas->GetCursor();

    levelCont = 0;

    audioDevice.reset(new AudioDevice(75));
    
    MarathonMenuLogic::isKeyHeld = true;
    MarathonMenuLogic::isInvokeKey = true;
    MarathonMenuLogic::levelCont = 0;

}

bool MarathonMenuLogic::isKeyHeld = true;
bool MarathonMenuLogic::isInvokeKey = true;
int MarathonMenuLogic::levelCont = 0;


const char* zero = "Assets/Sprites/digits/zero.png";
const char* one = "Assets/Sprites/digits/one.png";
const char* two = "Assets/Sprites/digits/two.png";
const char* three = "Assets/Sprites/digits/three.png";
const char* four = "Assets/Sprites/digits/four.png";
const char* five = "Assets/Sprites/digits/five.png";
const char* six = "Assets/Sprites/digits/six.png";
const char* seven = "Assets/Sprites/digits/seven.png";
const char* eight = "Assets/Sprites/digits/eight.png";
const char* nine = "Assets/Sprites/digits/nine.png";


void MarathonMenuLogic::Update()
{

    if (canvas == nullptr || !canvas->IsEnabled())
        return;

    // Movement
    if ((Input::GetKey(KeyCode::RightArrow) || Input::GetButton(ButtonCode::DPAD_RIGHT)) && !MarathonMenuLogic::isKeyHeld)
    {

        MarathonMenuLogic::isKeyHeld = true;

        audioDevice->Play2D("Assets/Audio/SFX_MenuMove.wav");

        //  Mover o controlo para o MAIS
        if (activeIndex != 1)
            activeIndex = (activeIndex + 1) % buttons.size();
        
        if (levelCont < 29)
        {
            levelCont++;
            char digitSprites[3];
            snprintf(digitSprites, 3, "%02d", levelCont);
            
            for (int i = 0; i < 2; i++)
            {

                switch (digitSprites[i])
                {

                case '0':
                    sprites[i]->GetShader()->UpdateShader(zero);
                    break;
                case '1':
                    sprites[i]->GetShader()->UpdateShader(one);
                    break;
                case '2':
                    sprites[i]->GetShader()->UpdateShader(two);
                    break;
                case '3':
                    sprites[i]->GetShader()->UpdateShader(three);
                    break;
                case '4':
                    sprites[i]->GetShader()->UpdateShader(four);
                    break;
                case '5':
                    sprites[i]->GetShader()->UpdateShader(five);
                    break;
                case '6':
                    sprites[i]->GetShader()->UpdateShader(six);
                    break;
                case '7':
                    sprites[i]->GetShader()->UpdateShader(seven);
                    break;
                case '8':
                    sprites[i]->GetShader()->UpdateShader(eight);
                    break;
                case '9':
                    sprites[i]->GetShader()->UpdateShader(nine);
                    break;
                }
            }
        }
    }

    else if ((Input::GetKey(KeyCode::LeftArrow) || Input::GetButton(ButtonCode::DPAD_LEFT)) && !MarathonMenuLogic::isKeyHeld)
    {
        MarathonMenuLogic::isKeyHeld = true;

        audioDevice->Play2D("Assets/Audio/SFX_MenuMove.wav");

        //  Mover o controlo para o MENOS
        if (activeIndex != 0)
            activeIndex--;
            
        if (levelCont > 0)  
        {
            levelCont--;
            char digitSprites[3];
            snprintf(digitSprites, 3, "%02d", levelCont);

            for (int i = 0; i < 2; i++)
            {

                switch (digitSprites[i])
                {

                case '0':
                    sprites[i]->GetShader()->UpdateShader(zero);
                    break;
                case '1':
                    sprites[i]->GetShader()->UpdateShader(one);
                    break;
                case '2':
                    sprites[i]->GetShader()->UpdateShader(two);
                    break;
                case '3':
                    sprites[i]->GetShader()->UpdateShader(three);
                    break;
                case '4':
                    sprites[i]->GetShader()->UpdateShader(four);
                    break;
                case '5':
                    sprites[i]->GetShader()->UpdateShader(five);
                    break;
                case '6':
                    sprites[i]->GetShader()->UpdateShader(six);
                    break;
                case '7':
                    sprites[i]->GetShader()->UpdateShader(seven);
                    break;
                case '8':
                    sprites[i]->GetShader()->UpdateShader(eight);
                    break;
                case '9':
                    sprites[i]->GetShader()->UpdateShader(nine);
                    break;
                }
            }
        }
    }


    // Action
    if ((Input::GetKey(KeyCode::M) || Input::GetButton(ButtonCode::Start)) && !MarathonMenuLogic::isInvokeKey)
    {
        MarathonMenuLogic::isInvokeKey = true;

        audioDevice->Play2D("Assets/Audio/SFX_MenuSelection.wav");

        if (buttons[activeIndex] != nullptr)
            buttons[activeIndex]->OnClick();

    }

    MarathonMenuLogic::isKeyHeld = !(Input::GetKeyUp(KeyCode::LeftArrow) && Input::GetKeyUp(KeyCode::RightArrow)
        && !Input::GetButton(ButtonCode::DPAD_LEFT) && !Input::GetButton(ButtonCode::DPAD_RIGHT));
    MarathonMenuLogic::isInvokeKey = !(Input::GetKeyUp(KeyCode::M) && !Input::GetButton(ButtonCode::Start));
}
