#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "mouse.hpp"

class Button
{
	public:
		Button(SDL_Texture* p_buttonTexture, int p_sourceX, int p_sourceY, int p_destX, int p_destY);
		void update(Mouse p_mouse);
		bool getIsSelected();
		SDL_Rect source;
		SDL_Rect destination;
		SDL_Texture* getTexture();
	private:
		bool isSelected = false;
		SDL_Texture* buttonTexture;
};
