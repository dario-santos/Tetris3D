#pragma once

#include <vector>
using namespace std;

#include "./Sprite.hpp"

#include "../Components/Transform.hpp"
#include "../Shader/Shader.hpp"

class Cursor
{
private:
	Shader* shader = nullptr;
	Transform* transform = nullptr;

public:
	int delta;
	Cursor(Shader* shader, Transform* transform, int delta);
	
	~Cursor();

	Shader* GetShader();

	Transform* GetTransform();
};
