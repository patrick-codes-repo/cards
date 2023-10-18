#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "entity.hpp"
#include "mouse.hpp"
#include "button.hpp"

class RenderWindow
{
	public:
		RenderWindow(const char* p_title);
		SDL_Texture* loadTexture(const char* filePath);
		void clear();
		void render(Entity& p_entity);
		void display();
		void cleanUp();
		void renderMouse(Mouse &mouse);
		void renderButton(Button &button);
		void renderBackground(SDL_Texture* p_backgroundImage);
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
};
