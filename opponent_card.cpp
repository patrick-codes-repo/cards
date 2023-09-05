#include "opponent_card.hpp"

#include <iostream>

using namespace std;

OpponentCard::OpponentCard(SDL_Renderer* p_renderer, short p_arrayPosition, short p_health, short p_attack, short p_cost)
	:ARRAY_POSITION(p_arrayPosition), health(p_health), attack(p_attack), cost(p_cost)
{
}

void OpponentCard::createCardTexture(SDL_Renderer* p_renderer)
{
	targetTexture = SDL_CreateTexture(p_renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, BACKGROUND_ORIGIN_WIDTH, BACKGROUND_ORIGIN_HEIGHT);
	noNumbers = SDL_CreateTexture(p_renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, BACKGROUND_ORIGIN_WIDTH, BACKGROUND_ORIGIN_HEIGHT);

	targetDest.x = (SCREEN_WIDTH/4) + ((SCREEN_WIDTH/8) * ARRAY_POSITION);
	targetDest.y = (SCREEN_HEIGHT/3) - ADJUSTED_BACKGROUND_HEIGHT/2;
	targetDest.w = ADJUSTED_BACKGROUND_WIDTH;
	targetDest.h = ADJUSTED_BACKGROUND_HEIGHT;

	if(targetTexture == NULL)
		cout << "render target not created: " << SDL_GetError() << endl;

	if(SDL_SetRenderTarget(p_renderer, noNumbers) < 0)
		cout << "Changing render target to noNumbers failed: " << SDL_GetError() << endl;

	SDL_Texture* cardBackground = IMG_LoadTexture(p_renderer, "resources/card.jpg");
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
	SDL_Surface* cardDescriptionSurface = TTF_RenderText_Blended_Wrapped(cardDescriptionFont, "Welcome to\nGigi Labs", fontColor, 0);
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


	if(SDL_SetRenderTarget(p_renderer, targetTexture) < 0)
		cout << "Changing render target to targetTexture failed: " << SDL_GetError() << endl;

	SDL_RenderCopy(p_renderer, noNumbers, NULL, NULL);

	TTF_Font* cardStatsFont = TTF_OpenFont("resources/AovelSansRounded-rdDL.ttf", 200);
	sprintf(healthBuffer, "%d", health);
	SDL_Surface* healthSurface = TTF_RenderText_Blended_Wrapped(cardStatsFont, healthBuffer, fontColor, 0);
	SDL_Texture* healthTexture = SDL_CreateTextureFromSurface(p_renderer, healthSurface);
	healthTextDest.x = BACKGROUND_ORIGIN_WIDTH - 200;
	healthTextDest.y = BACKGROUND_ORIGIN_HEIGHT - 300;
	healthTextDest.w = healthSurface->w;
	healthTextDest.h = healthSurface->h;
	SDL_RenderCopy(p_renderer, healthTexture, NULL, &healthTextDest);
	/* TTF_CloseFont(cardStatsFont); */
	SDL_FreeSurface(healthSurface);
	SDL_DestroyTexture(healthTexture);
	
	sprintf(attackBuffer, "%d", attack);
	SDL_Surface* attackSurface = TTF_RenderText_Blended_Wrapped(cardStatsFont, attackBuffer, fontColor, 0);
	SDL_Texture* attackTexture = SDL_CreateTextureFromSurface(p_renderer, attackSurface);
	attackTextDest.x = 100;
	attackTextDest.y = BACKGROUND_ORIGIN_HEIGHT - 300;
	attackTextDest.w = attackSurface->w;
	attackTextDest.h = attackSurface->h;
	SDL_RenderCopy(p_renderer, attackTexture, NULL, &attackTextDest);
	TTF_CloseFont(cardStatsFont);
	SDL_FreeSurface(attackSurface);
	SDL_DestroyTexture(attackTexture);

	TTF_Quit();

	if(SDL_SetRenderTarget(p_renderer, NULL) < 0)
		cout << "Changing render target to default failed: " << SDL_GetError() << endl;
}

void OpponentCard::update(Mouse p_mouse)
{
	/* return; */
	if(SDL_HasIntersection(&targetDest, &p_mouse.collisionRect))
	{
		//display card information
		isSelected = true;
		return;
	}

	isSelected = false;
}

void OpponentCard::render(SDL_Renderer* p_renderer)
{
	SDL_RenderCopy(p_renderer, targetTexture, NULL, &targetDest);
}

void OpponentCard::playCard(int p_numberOfCardsOnBoard, SDL_Renderer* p_renderer)
{
	createCardTexture(p_renderer);
	hasBeenPlayed = true;
}

bool OpponentCard::getHasBeenPlayed()
{
	return hasBeenPlayed;
}

/* void Card::changeHealthDisplayed(SDL_Renderer* p_renderer) */
/* { */
/* 	SDL_DestroyTexture(targetTexture); */
/* 	targetTexture = SDL_CreateTexture(p_renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, BACKGROUND_ORIGIN_WIDTH, BACKGROUND_ORIGIN_HEIGHT); */

/* 	if(SDL_SetRenderTarget(p_renderer, targetTexture) < 0) */
/* 		cout << "Changing render target to targetTexture failed: " << SDL_GetError() << endl; */

/* 	SDL_RenderCopy(p_renderer, noNumbers, NULL, NULL); */

/* 	SDL_Color fontColor = { 255, 255, 255 }; */
/* 	TTF_Init(); */
/* 	TTF_Font* cardStatsFont = TTF_OpenFont("resources/AovelSansRounded-rdDL.ttf", 200); */
/* 	SDL_Surface* healthSurface = TTF_RenderText_Blended_Wrapped(cardStatsFont, healthBuffer, fontColor, 0); */
/* 	SDL_Texture* healthTexture = SDL_CreateTextureFromSurface(p_renderer, healthSurface); */
/* 	SDL_RenderCopy(p_renderer, healthTexture, NULL, &healthTextDest); */
/* 	TTF_CloseFont(cardStatsFont); */
/* 	SDL_FreeSurface(healthSurface); */
/* 	SDL_DestroyTexture(healthTexture); */
/* 	TTF_Quit(); */

/* 	if(SDL_SetRenderTarget(p_renderer, NULL) < 0) */
/* 		cout << "Changing render target to default failed: " << SDL_GetError() << endl; */
/* } */

/* void Card::damaged(SDL_Renderer* p_renderer, short p_damageTaken) */
/* { */
/* 	memset(healthBuffer, 0, sizeof healthBuffer); */
/* 	sprintf(healthBuffer, "%d", int(health - p_damageTaken)); */
/* 	health -= p_damageTaken; */
/* 	changeHealthDisplayed(p_renderer); */
/* } */

bool OpponentCard::getIsSelected()
{
	return isSelected;
}

short OpponentCard::getCost()
{
	return cost;
}
