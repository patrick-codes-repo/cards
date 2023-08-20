#include <iostream>

#include "render_window.hpp"
#include "entity.hpp"
#include "globals.hpp"

using namespace std;

RenderWindow::RenderWindow(const char* p_title)//, int p_w, int p_h)
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

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity)
{
	if(p_entity.getType() == 'b')
	{
		SDL_RenderCopy(renderer, p_entity.getTexture(), NULL, NULL);
		return;
	}
	
	SDL_Rect source;
	source.x = p_entity.getCurrentFrame().x;
	source.y = p_entity.getCurrentFrame().y;
	source.w = p_entity.getCurrentFrame().w;
	source.h = p_entity.getCurrentFrame().h;

	SDL_Rect destination;
	destination.x = p_entity.getX() * 1;
	destination.y = p_entity.getY() * 1;
	destination.w = p_entity.getCurrentFrame().w * .25; 
	destination.h = p_entity.getCurrentFrame().h * .25;

	SDL_RenderCopy(renderer, p_entity.getTexture(), &source, &destination);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

SDL_Renderer* RenderWindow::getRenderer()
{
	return renderer;
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}
