#include <iostream>

#include "render_window.hpp"
#include "entity.hpp"
#include "globals.hpp"

using namespace std;

RenderWindow::RenderWindow(const char* p_title)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN); // && SDL_WINDOW_BORDERLESS

	if (window == NULL)
		cout << "Window failed to init: " << SDL_GetError() << endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(renderer, 1920, 1080);
}

SDL_Texture* RenderWindow::loadTexture(const char* filePath)
{
	SDL_Texture * texture = IMG_LoadTexture(renderer, filePath);

	if (texture == NULL)
		cout << "Failed to load texture: " << SDL_GetError() << endl;

	return texture;
}

SDL_Texture* RenderWindow::createTextureFromSurface(SDL_Surface* surface)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == NULL)
		cout << "Failed to create texture from surface: " << SDL_GetError() << endl;

	return texture;
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity)
{
	SDL_RenderCopy(renderer, p_entity.texture, &p_entity.source, &p_entity.destination);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}
