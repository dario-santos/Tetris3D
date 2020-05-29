#pragma once

#include <vector>
using namespace std;

#include "../Components/Transform.hpp"
#include "../Shader/Shader.hpp"

class Button
{
	private:
		Shader* shader = nullptr;
		Transform* transform = nullptr;
		void (*funcEvent)(void) = nullptr;

	public:
		Button(Shader* shader, Transform* transform, void (*funcEvent)(void));

		~Button();

		void OnClick();

		Shader* GetShader();

		Transform* GetTransform();
};
