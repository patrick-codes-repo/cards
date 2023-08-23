#include "button.hpp"

Button::Button(SDL_Renderer* p_renderer, int p_sourceX, int p_sourceY, int p_destX, int p_destY)
{
	button_texture = IMG_LoadTexture(p_renderer, "resources/buttons.png");

	source.w = 155;
	source.h = 55;
	source.x = p_sourceX;
	source.y = p_sourceY;

	destination.w = 200;
	destination.h = 75;
	destination.x = p_destX;
	destination.y = p_destY;
}

void Button::update(Mouse p_mouse)
{
	if(SDL_HasIntersection(&destination, &p_mouse.collisionRect))
	{
		is_selected = true;
		source.y = 190;
		return;
	}
	
	is_selected = false;
	source.y = 115;
}

void Button::draw(SDL_Renderer* p_renderer)
{
	SDL_RenderCopy(p_renderer, button_texture, &source, &destination);
}

bool Button::getIsSelected()
{
	return is_selected;
}
