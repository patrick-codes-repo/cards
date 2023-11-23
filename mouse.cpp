#include "mouse.hpp"
#include "globals.hpp"

#include <iostream>
using namespace std;

Mouse::Mouse(SDL_Texture* p_mouseTexture)
{
	collisionRect.w = 1;
	collisionRect.h = 1;

	SDL_ShowCursor(SDL_DISABLE);
	SDL_WarpMouseInWindow(NULL, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);

	entity.destination.w = 35;
	entity.destination.h = 35;

	entity.texture = p_mouseTexture;
}

void Mouse::update()
{
	SDL_GetMouseState(&entity.destination.x, &entity.destination.y);

	if(entity.destination.x >= SCREEN_WIDTH || entity.destination.y >= SCREEN_HEIGHT)
		correctMousePosition();

	collisionRect.x = entity.destination.x;
	collisionRect.y = entity.destination.y;
}

void Mouse::correctMousePosition()
{
	if(entity.destination.x >= SCREEN_WIDTH)
		entity.destination.x = SCREEN_WIDTH - 1;

	if(entity.destination.y >= SCREEN_HEIGHT)
		entity.destination.y = SCREEN_HEIGHT - 1;

	SDL_WarpMouseInWindow(NULL, entity.destination.x, entity.destination.y);
}
