#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 

#include "entity.hpp"

class Mouse {
	public:
		Mouse(SDL_Texture* p_mouseTexture);
		void update();
		SDL_Rect collisionRect;
		Entity entity;
	private:
		void correctMousePosition();
};
