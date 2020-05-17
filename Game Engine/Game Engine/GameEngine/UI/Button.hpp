#pragma once

#include <vector>
using namespace std;

#include "./Sprite.hpp"

#include "../Components/Transform.hpp"
#include "../Components/Renderer.hpp"

class Button
{
	private:
		Renderer* renderer;
		Transform* transform;
		void (*funcEvent)(void);

	public:
		Button(Renderer* renderer, Transform* transform, void (*funcEvent)(void));

		~Button();

		void OnClick();

		Renderer* GetRenderer();

		Transform* GetTransform();
};
