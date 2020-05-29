#pragma once

#include <vector>
using namespace std;

#include "../Components/Transform.hpp"
#include "../Shader/Shader.hpp"

class Sprite
{
	private:
		Shader* shader = nullptr;
		Transform* transform = nullptr;
	
	public:
		Sprite(Shader* shader, Transform* transform);
		~Sprite();
		Shader* GetShader();
		Transform* GetTransform();
};
