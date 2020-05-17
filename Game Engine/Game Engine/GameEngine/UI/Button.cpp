#include "Button.hpp"

Button::Button(Renderer* render, Transform* t, void (*func)(void))
{
	this->render = render;
	this->t = t;
	this->func = func;
}

void Button::OnClick()
{
	func();
}

Renderer* Button::GetRenderer()
{
	return this->render;
}

Transform* Button::GetTransform()
{
	return this->t;
}