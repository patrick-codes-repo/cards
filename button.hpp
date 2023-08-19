#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "mouse.hpp"

class Button
{
	public:
		Button(SDL_Renderer* p_renderer, int p_sourceX, int p_sourceY, int p_destX, int p_destY);
		void update(Mouse p_mouse);
		void draw(SDL_Renderer* p_renderer);
		bool getIsSelected();

	private:
		SDL_Texture* button_texture;
		SDL_Rect source, destination;
		bool is_selected = false;
};
