#include "mouse.hpp"
#include "globals.hpp"

#include <iostream>
using namespace std;

Mouse::Mouse(SDL_Texture* p_mouseTexture)
	:mouseTexture(p_mouseTexture)
{
	imageRect.w = 35;
	imageRect.h = 35;
	collisionRect.w = 1;
	collisionRect.h = 1;

	SDL_ShowCursor(SDL_DISABLE);
	SDL_WarpMouseInWindow(NULL, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
}

void Mouse::update()
{
	SDL_GetMouseState(&imageRect.x, &imageRect.y);

	if(imageRect.x >= SCREEN_WIDTH || imageRect.y >= SCREEN_HEIGHT)
		correctMousePosition();

	collisionRect.x = imageRect.x;
	collisionRect.y = imageRect.y;
}

void Mouse::correctMousePosition()
{
	if(imageRect.x >= SCREEN_WIDTH)
		imageRect.x = SCREEN_WIDTH - 1;

	if(imageRect.y >= SCREEN_HEIGHT)
		imageRect.y = SCREEN_HEIGHT - 1;

	SDL_WarpMouseInWindow(NULL, imageRect.x, imageRect.y);
}

SDL_Texture* Mouse::getTexture()
{
	return mouseTexture;
}

int Mouse::getCollisionRectX()
{
	return collisionRect.x;
}

int Mouse::getCollisionRectY()
{
	return collisionRect.y;
}
