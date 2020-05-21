#pragma once
#include <vector>
using namespace std;

#include "Sprite.hpp"
#include "Button.hpp"
#include "Cursor.hpp"
#include "../Components/Transform.hpp"

class Canvas
{
	private:

		vector<Sprite*> sprites = vector<Sprite*>();
		vector<Button*> buttons = vector<Button*>();
		Cursor* cursor;
		bool isEnabled = true;
		bool isCursorEnabled = false;

	public:

		~Canvas();

		void AddCursor(Cursor* cursor, bool enable);
		Cursor* GetCursor();

		void AddButton(Button* b);
		vector<Button*> GetButtons();

		void AddSprite(Sprite* s);
		vector<Sprite*> GetSprites();

		void Enable();
		void Disable();

		void EnableCursor();
		void DisableCursor();

		bool IsEnabled();
		bool IsCursorEnabled();
};
