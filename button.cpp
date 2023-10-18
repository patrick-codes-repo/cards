#include "button.hpp"

Button::Button(SDL_Texture* p_buttonTexture, int p_sourceX, int p_sourceY, int p_destX, int p_destY)
	:buttonTexture(p_buttonTexture)
{
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
		isSelected = true;
		source.y = 190;
		return;
	}
	
	isSelected = false;
	source.y = 115;
}

bool Button::getIsSelected()
{
	return isSelected;
}

SDL_Texture* Button::getTexture()
{
	return buttonTexture;
}
