#include "Button.hpp"

Button::Button(Shader* shader, Transform* transform, void (*funcEvent)(void))
{
	this->shader = shader;
	this->transform = transform;
	this->funcEvent = funcEvent;
}

Button::~Button() 
{
	// Deletes renderer
	if(shader != nullptr)
	{
		delete this->shader;
		this->shader = nullptr;
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

Shader* Button::GetShader()
{
	return this->shader;
}

Transform* Button::GetTransform()
{
	return this->transform;
}
