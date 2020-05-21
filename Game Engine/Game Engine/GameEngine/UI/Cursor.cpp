#include "Cursor.hpp"

Cursor::Cursor(Shader* shader, Transform* transform, int delta)
{
	this->shader = shader;
	this->transform = transform;
	this->delta = delta;
}

Cursor::~Cursor()
{
	// Deletes renderer
	if (shader != nullptr)
	{
		delete this->shader;
		this->shader = nullptr;
	}
	// Deletes transform
	if (this->transform != nullptr)
	{
		delete this->transform;
		this->transform = nullptr;
	}
}

Shader* Cursor::GetShader()
{
	return this->shader;
}

Transform* Cursor::GetTransform()
{
	return this->transform;
}
