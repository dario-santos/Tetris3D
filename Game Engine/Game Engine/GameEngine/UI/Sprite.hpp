#pragma once

#include <vector>
using namespace std;

//#include <gli/gli.hpp>
//using namespace gli;

#include "../Components/Transform.hpp"

class Sprite
{
	private:
		//texture2d texture;
		Transform* transform;
	
	public:
		//Sprite(texture2d texture, Transform* t);
		
		~Sprite();
		
		//void UpdateTexture(texture2d texture);
};
