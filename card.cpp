#include "card.hpp"

#include <iostream>

using namespace std;

Card::Card(SDL_Renderer* p_renderer, short p_cost, short p_arrayPosition, short p_health, short p_damage)
	:ARRAY_POSITION(p_arrayPosition), health(p_health), damage(p_damage), cost(p_cost)
{
	if(health < 1)
		cardType = spell;

	targetTexture = SDL_CreateTexture(p_renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, BACKGROUND_ORIGIN_WIDTH, BACKGROUND_ORIGIN_HEIGHT);
	noNumbers = SDL_CreateTexture(p_renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, BACKGROUND_ORIGIN_WIDTH, BACKGROUND_ORIGIN_HEIGHT);

	targetDest.x = (SCREEN_WIDTH/4) + ((SCREEN_WIDTH/8) * ARRAY_POSITION);
	targetDest.y = SCREEN_HEIGHT - ADJUSTED_BACKGROUND_HEIGHT/2;
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

	TTF_Quit();

	drawDynamicStats(p_renderer);
}

void Card::update(Mouse p_mouse)
{
	isSelected = SDL_HasIntersection(&targetDest, &p_mouse.collisionRect);

	if(cardState == playingAttackAnimation)
	{
		if(SDL_GetTicks() < animationEnd)
		{
			targetDest.y = SCREEN_HEIGHT/2 - 50;
			return;
		}
		cardState = readyToDealDamage;
	}

	if(cardState == onSide)
	{
		/* targetDest.y = SCREEN_HEIGHT/2 - ADJUSTED_BACKGROUND_HEIGHT/2; */
		/* targetDest.x = 20; */
		return;
	}

	/* if(cardState == onBoard) */
	/* { */
	/* 	//display card info */
	/* } */

	if(isSelected && (cardState == inHand))
	{
		targetDest.y = SCREEN_HEIGHT - ADJUSTED_BACKGROUND_HEIGHT; 
		return;
	}	
		
	resetCardPosition();
}

void Card::moveCard(Mouse p_mouse)
{
	targetDest.x = p_mouse.getCollisionRectX() - targetDest.w/2;
	targetDest.y = p_mouse.getCollisionRectY() - targetDest.h/2;
}

void Card::render(SDL_Renderer* p_renderer)
{
	SDL_RenderCopy(p_renderer, targetTexture, NULL, &targetDest);
}

void Card::drawDynamicStats(SDL_Renderer* p_renderer)
{
	if(SDL_SetRenderTarget(p_renderer, targetTexture) < 0)
		cout << "Changing render target to targetTexture failed: " << SDL_GetError() << endl;

	SDL_RenderCopy(p_renderer, noNumbers, NULL, NULL);

	if(TTF_Init() < 0)
		cout << "tff_init error: " << SDL_GetError() << endl;

	SDL_Color fontColor = { 255, 0, 0 };

	TTF_Font* cardStatsFont = TTF_OpenFont("resources/AovelSansRounded-rdDL.ttf", 200);

	sprintf(healthBuffer, "%d", health);
	SDL_Surface* healthSurface = TTF_RenderText_Blended_Wrapped(cardStatsFont, healthBuffer, fontColor, 0);
	SDL_Texture* healthTexture = SDL_CreateTextureFromSurface(p_renderer, healthSurface);
	healthTextDest.x = BACKGROUND_ORIGIN_WIDTH - 200;
	healthTextDest.y = BACKGROUND_ORIGIN_HEIGHT - 300;
	healthTextDest.w = healthSurface->w;
	healthTextDest.h = healthSurface->h;
	SDL_RenderCopy(p_renderer, healthTexture, NULL, &healthTextDest);
	SDL_FreeSurface(healthSurface);
	/* SDL_DestroyTexture(healthTexture); */
	
	fontColor = { 255, 255, 255 };
	
	sprintf(damageBuffer, "%d", damage);
	SDL_Surface* damageSurface = TTF_RenderText_Blended_Wrapped(cardStatsFont, damageBuffer, fontColor, 0);
	SDL_Texture* damageTexture = SDL_CreateTextureFromSurface(p_renderer, damageSurface);
	damageTextDest.x = 100;
	damageTextDest.y = BACKGROUND_ORIGIN_HEIGHT - 300;
	damageTextDest.w = damageSurface->w;
	damageTextDest.h = damageSurface->h;
	SDL_RenderCopy(p_renderer, damageTexture, NULL, &damageTextDest);
	SDL_FreeSurface(damageSurface);
	/* SDL_DestroyTexture(damageTexture); */
	
	sprintf(costBuffer, "%d", cost);
	SDL_Surface* costSurface = TTF_RenderText_Blended_Wrapped(cardStatsFont, costBuffer, fontColor, 0);
	SDL_Texture* costTexture = SDL_CreateTextureFromSurface(p_renderer, costSurface);
	costTextDest.x = BACKGROUND_ORIGIN_WIDTH/2 - costSurface->w/2;
	costTextDest.y = 0;
	costTextDest.w = costSurface->w;
	costTextDest.h = costSurface->h;
	SDL_RenderCopy(p_renderer, costTexture, NULL, &costTextDest);
	SDL_FreeSurface(costSurface);
	/* SDL_DestroyTexture(costTexture); */

	TTF_CloseFont(cardStatsFont);
	TTF_Quit();

	if(SDL_SetRenderTarget(p_renderer, NULL) < 0)
		cout << "Changing render target to default failed: " << SDL_GetError() << endl;
}

void Card::damaged(SDL_Renderer* p_renderer, short p_damageTaken)
{
	health -= p_damageTaken;
	drawDynamicStats(p_renderer);
}

bool Card::getIsSelected()
{
	return isSelected;
}

int Card::getCardY()
{
	return targetDest.y;
}

void Card::resetCardPosition()
{
	if(cardState == inHand)
	{
		targetDest.x = (SCREEN_WIDTH/4) + ((SCREEN_WIDTH/8) * ARRAY_POSITION);
		targetDest.y = SCREEN_HEIGHT - ADJUSTED_BACKGROUND_HEIGHT/2;
		return;
	}

	targetDest.y = SCREEN_HEIGHT/2;
	targetDest.x = SCREEN_WIDTH/8 + cardPosition * SCREEN_WIDTH/8;
}

bool Card::playCard(int p_numberOfCardsOnBoard)
{
	if(p_numberOfCardsOnBoard >= 6 || cardType == spell)
	{
		moveCardToSide();
		return false;
	}

	cardState = onBoard;
	targetDest.y = SCREEN_HEIGHT/2;
	targetDest.x = SCREEN_WIDTH/8 + p_numberOfCardsOnBoard * SCREEN_WIDTH/8;
	cardPosition = p_numberOfCardsOnBoard;

	return true;
}

void Card::moveCardToSide()
{
	targetDest.y = SCREEN_HEIGHT/2 - ADJUSTED_BACKGROUND_HEIGHT/2;
	targetDest.x = 20;
	cardState = onSide;
}

state Card::getCardState()
{
	return cardState;
}

void Card::setStateInHand()
{
	cardState = inHand;
}

void Card::dealDamage()
{
	cardState = attackedThisTurn;
	attackTarget = -1;
}

short Card::getCost()
{
	return cost;
}

type Card::getCardType()
{
	return cardType;
}

short Card::getDamage()
{
	return damage;
}

void Card::setStateInAttackingGroup()
{
	cardState = inAttackingGroup;
}

void Card::setTarget(short &targetIndex)
{
	attackTarget = targetIndex;
}

short Card::getTarget()
{
	return attackTarget;
}

short Card::getHealth()
{
	return health;
}

int Card::getCardPosition()
{
	return cardPosition;
}

void Card::changeBoardPosition(int p_position)
{
	cardPosition = p_position;
	/* targetDest.x = SCREEN_WIDTH/8 + cardPosition * SCREEN_WIDTH/8; */
}

void Card::playAttackAnimation()
{
	cardState = playingAttackAnimation;
	animationEnd = SDL_GetTicks() + 750;
}

void Card::setStateOnBoard()
{
	cardState = onBoard;
}
