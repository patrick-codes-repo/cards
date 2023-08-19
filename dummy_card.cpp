#include "dummy_card.hpp"

#include <iostream>

using namespace std;

DummyCard::DummyCard(SDL_Renderer* p_renderer, short p_arrayPosition)
	:ARRAY_POSITION(p_arrayPosition)
{
	targetTexture = SDL_CreateTexture(p_renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, BACKGROUND_ORIGIN_WIDTH, BACKGROUND_ORIGIN_HEIGHT);

	if(targetTexture == NULL)
		cout << "render target not created: " << SDL_GetError() << endl;

	targetDest.x = (SCREEN_WIDTH/4) + ((SCREEN_WIDTH/8) * ARRAY_POSITION);
	targetDest.y = SCREEN_HEIGHT - ADJUSTED_BACKGROUND_HEIGHT/2;
	targetDest.w = ADJUSTED_BACKGROUND_WIDTH;
	targetDest.h = ADJUSTED_BACKGROUND_HEIGHT;

	if(SDL_SetRenderTarget(p_renderer, targetTexture) < 0)
		cout << "Changing render target to targetTexture failed: " << SDL_GetError() << endl;

	SDL_Texture* cardBackground = IMG_LoadTexture(p_renderer, "resources/dummy_card.jpg");
	SDL_Rect backgroundSource;
	backgroundSource.x = 0;
	backgroundSource.y = 0;
	backgroundSource.w = BACKGROUND_ORIGIN_WIDTH;
	backgroundSource.h = BACKGROUND_ORIGIN_HEIGHT;
	SDL_RenderCopy(p_renderer, cardBackground, &backgroundSource, NULL);
	SDL_DestroyTexture(cardBackground);

	if(TTF_Init() < 0)
		cout << "tff_init error: " << SDL_GetError() << endl;

	SDL_Color fontColor = { 255, 255, 255 };

	TTF_Font* cardDescriptionFont = TTF_OpenFont("resources/AovelSansRounded-rdDL.ttf", 100);
	SDL_Surface* cardDescriptionSurface = TTF_RenderText_Blended_Wrapped(cardDescriptionFont, "This is a\ndummy card", fontColor, 0);
	SDL_Texture* cardDescriptionTexture = SDL_CreateTextureFromSurface(p_renderer, cardDescriptionSurface);
	SDL_Rect descriptionTextDest;
	descriptionTextDest.x = BACKGROUND_ORIGIN_WIDTH/2 - cardDescriptionSurface->w/2;
	descriptionTextDest.y = BACKGROUND_ORIGIN_HEIGHT/2;
	descriptionTextDest.w = cardDescriptionSurface->w;
	descriptionTextDest.h = cardDescriptionSurface->h;
	SDL_RenderCopy(p_renderer, cardDescriptionTexture, NULL, &descriptionTextDest);
	TTF_CloseFont(cardDescriptionFont);
	SDL_FreeSurface(cardDescriptionSurface);
	SDL_DestroyTexture(cardDescriptionTexture);


	TTF_Font* cardStatsFont = TTF_OpenFont("resources/AovelSansRounded-rdDL.ttf", 200);
	char healthBuffer[16];
	short health = 5;
	sprintf(healthBuffer, "%d", health);
	SDL_Surface* healthSurface = TTF_RenderText_Blended_Wrapped(cardStatsFont, healthBuffer, fontColor, 0);
	SDL_Texture* healthTexture = SDL_CreateTextureFromSurface(p_renderer, healthSurface);
	SDL_Rect healthTextDest;
	healthTextDest.x = BACKGROUND_ORIGIN_WIDTH - 200;
	healthTextDest.y = BACKGROUND_ORIGIN_HEIGHT - 300;
	healthTextDest.w = healthSurface->w;
	healthTextDest.h = healthSurface->h;
	SDL_RenderCopy(p_renderer, healthTexture, NULL, &healthTextDest);
	TTF_CloseFont(cardStatsFont);
	SDL_FreeSurface(healthSurface);
	SDL_DestroyTexture(healthTexture);

	TTF_Quit();

	if(SDL_SetRenderTarget(p_renderer, NULL) < 0)
		cout << "Changing render target to default failed: " << SDL_GetError() << endl;
}

void DummyCard::update(Mouse p_mouse)
{
	if(SDL_HasIntersection(&targetDest, &p_mouse.collision_rect))
	{
		isSelected = true;
		targetDest.y = SCREEN_HEIGHT - ADJUSTED_BACKGROUND_HEIGHT; 
		return;
	}	
	isSelected = false;
	resetCardPosition();
}

void DummyCard::render(SDL_Renderer* p_renderer)
{
	SDL_RenderCopy(p_renderer, targetTexture, NULL, &targetDest);
}

bool DummyCard::getIsSelected()
{
	return isSelected;
}

void DummyCard::resetCardPosition()
{
	targetDest.y = SCREEN_HEIGHT - ADJUSTED_BACKGROUND_HEIGHT/2;
}

void DummyCard::setIsVisible()
{
	isVisible = true;
}

bool DummyCard::getIsVisible()
{
	return isVisible;
}
