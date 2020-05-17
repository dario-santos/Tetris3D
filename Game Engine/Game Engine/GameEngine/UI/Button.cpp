#include "Button.hpp"

Button::Button(Renderer* renderer, Transform* transform, void (*funcEvent)(void))
{
	this->renderer = renderer;
	this->transform = transform;
	this->funcEvent = funcEvent;
}

Button::~Button() 
{
	// Deletes renderer
	if(renderer != nullptr)
	{
		delete renderer;
		renderer = nullptr;
	}
	// Deletes transform
	if(this->transform != nullptr)
	{
		delete this->transform;
		this->transform = nullptr;
	}
}

void Button::OnClick()
{
	this->funcEvent();
}

Renderer* Button::GetRenderer()
{
	return this->renderer;
}

Transform* Button::GetTransform()
{
	return this->transform;
}
