#include "mouse.hpp"
#include "globals.hpp"

#include <iostream>
using namespace std;

Mouse::Mouse(SDL_Renderer* p_renderer)
{
	mouse_texture = IMG_LoadTexture(p_renderer, "resources/cursor.png");
	image_rect.w = 35;
	image_rect.h = 35;
	collisionRect.w = 1;
	collisionRect.h = 1;

	SDL_ShowCursor(SDL_DISABLE);
	SDL_WarpMouseInWindow(NULL, SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
}

void Mouse::update()
{
	SDL_GetMouseState(&image_rect.x, &image_rect.y);

	if(image_rect.x >= SCREEN_WIDTH || image_rect.y >= SCREEN_HEIGHT)
		correctMousePosition();

	collisionRect.x = image_rect.x;
	collisionRect.y = image_rect.y;
}

void Mouse::correctMousePosition()
{
	if(image_rect.x >= SCREEN_WIDTH)
		image_rect.x = SCREEN_WIDTH - 1;

	if(image_rect.y >= SCREEN_HEIGHT)
		image_rect.y = SCREEN_HEIGHT - 1;

	SDL_WarpMouseInWindow(NULL, image_rect.x, image_rect.y);
}
void Mouse::draw(SDL_Renderer* p_renderer)
{
	SDL_RenderCopy(p_renderer, mouse_texture, NULL, &image_rect);
}

int Mouse::getCollisionRectX()
{
	return collisionRect.x;
}

int Mouse::getCollisionRectY()
{
	return collisionRect.y;
}
