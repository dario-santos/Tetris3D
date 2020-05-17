#include "Sprite.hpp"
/*

Sprite::Sprite(texture2d texture, Transform* t)
{
	this->texture = texture;
	this->t = t;
}

void Sprite::UpdateTexture(texture2d texture)
{
	this->texture = texture;
}
*/

Sprite::~Sprite() 
{
	if(transform != nullptr)
	{
		delete transform;
		transform = nullptr;
	}
}