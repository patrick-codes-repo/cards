#include "entity.hpp"

Entity::Entity(float p_x, float p_y, char p_type,  SDL_Texture* p_texture)
:x(p_x), y(p_y), type(p_type), texture(p_texture)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	
	if(type == 'b')
	{
		currentFrame.w = 1920;
		currentFrame.h = 1080;
		return;
	}

	currentFrame.w = 885;
	currentFrame.h = 1322;
}

float Entity::getX()
{
	return x;
}


float Entity::getY()
{
	return y;
}

SDL_Texture* Entity::getTexture()
{
	return texture;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}

char Entity::getType()
{
	return type;
}
