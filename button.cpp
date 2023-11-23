#include "button.hpp"

Button::Button(SDL_Texture* p_buttonTexture, int p_sourceX, int p_sourceY, int p_destX, int p_destY)
{
	entity.source.w = 155;
	entity.source.h = 55;
	entity.source.x = p_sourceX;
	entity.source.y = p_sourceY;

	entity.destination.w = 200;
	entity.destination.h = 75;
	entity.destination.x = p_destX;
	entity.destination.y = p_destY;

	entity.texture = p_buttonTexture;
}

void Button::update(Mouse p_mouse)
{
	if(SDL_HasIntersection(&entity.destination, &p_mouse.collisionRect))
	{
		isSelected = true;
		entity.source.y = 190;
		return;
	}
	
	isSelected = false;
	entity.source.y = 115;
}

bool Button::getIsSelected()
{
	return isSelected;
}
