#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 

#include "render_window.hpp"

class Mouse {
	public:
		Mouse(SDL_Renderer* p_renderer);
		void update();
		void draw(SDL_Renderer* p_renderer);
		SDL_Rect collision_rect;

	private:
		SDL_Texture* mouse_texture;
		SDL_Rect image_rect;
		void correctMousePosition();
};
