#include "Canvas.hpp"


Canvas::~Canvas()
{
    for (Button* b: buttons)
        b->~Button();
    
    for (Sprite* s : sprites)
        s->~Sprite();
    
    buttons.erase(buttons.begin(), buttons.end());
    sprites.erase(sprites.begin(), sprites.end());

}

void Canvas::AddButton(Button* b)
{
	this->buttons.push_back(b);
}

vector<Button*> Canvas::GetButtons()
{
	return this->buttons;
}

void Canvas::AddSprite(Sprite* s)
{
	this->sprites.push_back(s);
}

vector<Sprite*> Canvas::GetSprites()
{
	return this->sprites;
}

void Canvas::Enable()
{
	this->isEnabled = true;
}

void Canvas::Disable()
{
	this->isEnabled = false;
}

bool Canvas::IsEnabled()
{
	return this->isEnabled;
}
