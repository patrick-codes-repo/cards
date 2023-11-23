#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "mouse.hpp"
#include "entity.hpp"

class Button
{
	public:
		Button(SDL_Texture* p_buttonTexture, int p_sourceX, int p_sourceY, int p_destX, int p_destY);
		void update(Mouse p_mouse);
		bool getIsSelected();
		Entity entity;
	private:
		bool isSelected = false;
};
