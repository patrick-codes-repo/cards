#include <iostream>

#include "renderer.hpp"
#include "entity.hpp"
#include "globals.hpp"

using namespace std;

Renderer::Renderer(const char* p_title)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN); // && SDL_WINDOW_BORDERLESS

	if (window == NULL)
		cout << "Window failed to init: " << SDL_GetError() << endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(renderer, 1920, 1080);
}

SDL_Texture* Renderer::loadTexture(const char* filePath)
{
	SDL_Texture * texture = IMG_LoadTexture(renderer, filePath);

	if (texture == NULL)
		cout << "Failed to load texture: " << SDL_GetError() << endl;

	return texture;
}

SDL_Texture* Renderer::createTextureFromSurface(SDL_Surface* surface)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == NULL)
		cout << "Failed to create texture from surface: " << SDL_GetError() << endl;

	return texture;
}

void Renderer::clear()
{
	SDL_RenderClear(renderer);
}

void Renderer::render(Entity& p_entity)
{
	SDL_RenderCopy(renderer, p_entity.texture, &p_entity.source, &p_entity.destination);
}

void Renderer::renderFullSource(Entity& p_entity)
{
	SDL_RenderCopy(renderer, p_entity.texture, NULL, &p_entity.destination);
}

void Renderer::renderBackground(SDL_Texture* p_backgroundImage)
{
	SDL_RenderCopy(renderer, p_backgroundImage, NULL, NULL);
}
void Renderer::display()
{
	SDL_RenderPresent(renderer);
}

void Renderer::cleanUp()
{
	SDL_DestroyWindow(window);
}
