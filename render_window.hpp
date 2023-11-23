#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "entity.hpp"
#include "mouse.hpp"
#include "button.hpp"
#include "card.hpp"
#include "dummy_card.hpp"
#include "opponent_card.hpp"

class RenderWindow
{
	public:
		RenderWindow(const char* p_title);
		SDL_Texture* loadTexture(const char* filePath);
		SDL_Texture* createTextureFromSurface(SDL_Surface* surface);
		void clear();
		void render(Entity& p_entity);
		void display();
		void cleanUp();
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
};
