#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h> 
#endif

#include <iostream>

#include "opponent.hpp"

using namespace std;

Opponent::Opponent(SDL_Renderer* p_renderer, short p_health)
	:health(p_health), renderer(p_renderer)
{	
	if(TTF_Init() < 0)
		cout << "tff_init error: " << SDL_GetError() << endl;

	SDL_Color fontColor = { 255, 255, 255 };

	TTF_Font* opponentHealthFont = TTF_OpenFont("resources/AovelSansRounded-rdDL.ttf", 100);
	sprintf(healthBuffer, "%d", health);
	SDL_Surface* opponentHealthSurface = TTF_RenderText_Blended_Wrapped(opponentHealthFont, healthBuffer, fontColor, 0);
	opponentHealthTexture = SDL_CreateTextureFromSurface(renderer, opponentHealthSurface);
	healthTextDest.x = SCREEN_WIDTH/3 - opponentHealthSurface->w/2;
	healthTextDest.y = SCREEN_HEIGHT/5 - opponentHealthSurface->h/2;
	healthTextDest.w = opponentHealthSurface->w;
	healthTextDest.h = opponentHealthSurface->h;
	SDL_RenderCopy(p_renderer, opponentHealthTexture, NULL, &healthTextDest);
	TTF_CloseFont(opponentHealthFont);
	SDL_FreeSurface(opponentHealthSurface);

	drawMana();

	TTF_Quit();
}

void Opponent::renderHealth()
{
	SDL_RenderCopy(renderer, opponentHealthTexture, NULL, &healthTextDest);
}

void Opponent::renderMana()
{
	SDL_RenderCopy(renderer, manaTexture, NULL, &manaTextDest);
}

void Opponent::damaged()
{
	//change health value
	//redraw health on screen
}

void Opponent::healed()
{
	//change health value
	//redraw health on screen
}

void Opponent::updateCards(Mouse p_mouse)
{
		for(OpponentCard& c : cardsOnBoard)
		{
			c.update(p_mouse);
		}
}

void Opponent::renderCards()
{
		for(OpponentCard& c : cardsOnBoard)
		{
			c.render(renderer);
		}
}

void Opponent::playCard()
{
	short cardToPlay = chooseCard();

	if(cardToPlay < 0)
		return;

	deck[cardToPlay].playCard(cardsOnBoard.size(), renderer);
	cardsOnBoard.push_back(deck[cardToPlay]);
}

short Opponent::chooseCard()
{ 
	for(short i = 0; i < 4; i++)
	{
		if (!deck[i].getHasBeenPlayed())
			return i;
	}

	return -1;
}

void Opponent::incrementMana()
{
	mana++;
}

void Opponent::drawMana()
{
	if(TTF_Init() < 0)
		cout << "tff_init error: " << SDL_GetError() << endl;

	SDL_Color fontColor = { 255, 255, 255 };
	TTF_Font* manaFont = TTF_OpenFont("resources/AovelSansRounded-rdDL.ttf", 100);
	sprintf(manaBuffer, "%d", mana);
	SDL_Surface* manaSurface = TTF_RenderText_Blended_Wrapped(manaFont, manaBuffer, fontColor, 0);
	manaTexture = SDL_CreateTextureFromSurface(renderer, manaSurface);
	manaTextDest.x = (2*SCREEN_WIDTH/3) - manaSurface->w/2;
	manaTextDest.y = SCREEN_HEIGHT/5 - manaSurface->h/2;
	manaTextDest.w = manaSurface->w;
	manaTextDest.h = manaSurface->h;
	SDL_RenderCopy(renderer, manaTexture, NULL, &manaTextDest);
	TTF_CloseFont(manaFont);
	SDL_FreeSurface(manaSurface);

	TTF_Quit();
}
