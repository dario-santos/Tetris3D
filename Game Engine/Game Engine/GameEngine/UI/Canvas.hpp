#pragma once
#include <vector>
using namespace std;

#include "Sprite.hpp"
#include "Button.hpp"
#include "../Components/Transform.hpp"

class Canvas
{
	private:

		vector<Sprite*> sprites = vector<Sprite*>();
		vector<Button*> buttons = vector<Button*>();
		bool isEnabled = true;

	public:

		~Canvas();

		void AddButton(Button* b);
		vector<Button*> GetButtons();

		void AddSprite(Sprite* s);
		vector<Sprite*> GetSprites();

		void Enable();
		void Disable();

		bool IsEnabled();
};
