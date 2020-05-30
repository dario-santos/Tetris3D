#include "Sprite.hpp"

Sprite::Sprite(Shader* shader, Transform* transform)
{
	this->shader = shader;
	this->transform = transform;
}

Sprite::~Sprite() 
{
	if(transform != nullptr)
	{
		delete transform;
		transform = nullptr;
	}

	if (shader != nullptr)
	{
		delete shader;
		shader = nullptr;
	}
}

Shader* Sprite::GetShader()
{
	return this->shader;
}

Transform* Sprite::GetTransform()
{
	return this->transform;
}