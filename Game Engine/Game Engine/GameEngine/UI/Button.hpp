#pragma once
#include <vector>

#include "Sprite.hpp"
#include "../Components/Transform.hpp"
#include "../Components/Renderer.hpp"

using namespace std;


class Button
{

	private:
		Renderer* render;
		Transform* t;
		void (*func)(void);

	public:
		Button(Renderer* render, Transform* t, void (*func)(void));
		void OnClick();
		Renderer* GetRenderer();
		Transform* GetTransform();
};
