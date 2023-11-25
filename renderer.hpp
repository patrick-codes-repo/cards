#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "entity.hpp"
#include "mouse.hpp"
#include "button.hpp"

class Renderer
{
	public:
		Renderer(const char* p_title);
		SDL_Texture* loadTexture(const char* filePath);
		SDL_Texture* createTextureFromSurface(SDL_Surface* surface);
		void clear();
		void render(Entity& p_entity);
		void renderFullSource(Entity& p_entity);
		void renderBackground(SDL_Texture* p_backgroundImage);
		void display();
		void cleanUp();
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
};
