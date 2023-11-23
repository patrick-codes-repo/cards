#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity
{
	public:
		Entity();
		SDL_Texture* getTexture();
		SDL_Rect source;
		SDL_Rect destination;
		SDL_Texture* texture;
};
