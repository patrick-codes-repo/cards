#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity
{
	public:
	//	Entity(float p_x, float p_y, char p_type, SDL_Texture* p_texture);
		Entity();
		char getType();
		SDL_Texture* getTexture();
		SDL_Rect source;
		SDL_Rect destination;
		SDL_Texture* texture;
};
