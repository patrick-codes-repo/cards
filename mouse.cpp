#include "mouse.hpp"

Mouse::Mouse(SDL_Renderer* p_renderer)
{
	mouse_texture = IMG_LoadTexture(p_renderer, "resources/cursor.png");
	image_rect.w = 35;
	image_rect.h = 35;
	collision_rect.w = 1;
	collision_rect.h = 1;

	SDL_ShowCursor(false);
}

void Mouse::update()
{
	SDL_GetMouseState(&image_rect.x, &image_rect.y);
	collision_rect.x = image_rect.x;
	collision_rect.y = image_rect.y;
}

void Mouse::draw(SDL_Renderer* p_renderer)
{
	SDL_RenderCopy(p_renderer, mouse_texture, NULL, &image_rect);
}
