#include <iostream>

#include "opponent.hpp"

using namespace std;

Opponent::Opponent(short p_health)
	:health(p_health)
{	
	drawMana();
	drawHealth();

	TTF_Quit();
}

/* void Opponent::renderHealth() */
/* { */
/* 	SDL_RenderCopy(renderer, opponentHealthTexture, NULL, &healthTextDest); */
/* } */

/* void Opponent::renderMana() */
/* { */
/* 	SDL_RenderCopy(renderer, manaTexture, NULL, &manaTextDest); */
/* } */

void Opponent::damaged(short damageTaken)
{
	health -= damageTaken;
	drawHealth();
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

/* void Opponent::renderCards() */
/* { */
/* 		for(OpponentCard& c : cardsOnBoard) */
/* 		{ */
/* 			c.render(renderer); */
/* 		} */
/* } */

void Opponent::makeMove(vector<Card> &playerCards, short &playerHealth)
{
	bool cardPlayed = playCard();

	if(cardPlayed)
	{
		lastMove = playedCard;
		return;
	}

	if(cardsOnBoard.size() == 0)
	{
		lastMove = skipped;
		return;
	}

	if(attacking)
	{
		attacking = false;
		lastMove = attacked;
		return;
		/* return false; */
	}
	
	attack(playerCards, playerHealth);

	/* return true; */
	lastMove = attacked;
}

void Opponent::attack(vector<Card> &playerCards, short &playerHealth)
{
	if(!attacking)
	{
		if(playerCards.size() == 0)
			cardsOnBoard.at(0).setTarget(PLAYER_FACE);
		else
			cardsOnBoard.at(0).setTarget(playerCards.at(0).getID());
		cardsOnBoard.at(0).attack();
		attacking = true;
	}

	bool targetFound = false;
	short cardsRemainingHealth; 
	short ZERO = 0;

	for(Card &c : playerCards)
	{
		if(c.getID() == cardsOnBoard.at(0).getTarget())
		{
			c.damaged(cardsOnBoard.at(0).getDamage());
			cardsRemainingHealth = cardsOnBoard.at(0).damaged(c.getDamage());
			targetFound = true;
			break;
		}
	}

	if(!targetFound)
		playerHealth -= cardsOnBoard.at(0).getDamage();
		//needs to redraw player health
	
	if(cardsRemainingHealth <= 0)
		killCard(ZERO);
}

bool Opponent::playCard()
{
	cardToPlay = chooseCard();

	if(cardToPlay < 0)
		return false;

	/* if(cardToPlay >= 0) */
	/* { */
	deck[cardToPlay].playCard(cardsOnBoard.size());
	cardsOnBoard.push_back(deck[cardToPlay]);
	mana -= deck[cardToPlay].getCost();
	drawMana();
	/* } */

	/* return cardToPlay; */
	return true;
}

short Opponent::chooseCard()
{ 
	for(short i = 0; i < 4; i++)
	{
		if(!deck[i].getHasBeenPlayed() && mana >= deck[i].getCost())
			return i;
	}

	return -1;
}

void Opponent::setMana(short &newManaAmount)
{
	mana = newManaAmount;
}

void Opponent::drawHealth()
{
	if(TTF_Init() < 0)
		cout << "tff_init error: " << SDL_GetError() << endl;

	SDL_Color fontColor = { 255, 0, 0 };
	TTF_Font* opponentHealthFont = TTF_OpenFont("resources/AovelSansRounded-rdDL.ttf", 100);
	sprintf(healthBuffer, "%d", health);
	SDL_Surface* opponentHealthSurface = TTF_RenderText_Blended_Wrapped(opponentHealthFont, healthBuffer, fontColor, 0);
	opponentHealthTexture = SDL_CreateTextureFromSurface(renderer, opponentHealthSurface);
	healthTextDest.x = SCREEN_WIDTH/3 - opponentHealthSurface->w/2;
	healthTextDest.y = SCREEN_HEIGHT/5 - opponentHealthSurface->h/2;
	healthTextDest.w = opponentHealthSurface->w;
	healthTextDest.h = opponentHealthSurface->h;
	SDL_RenderCopy(renderer, opponentHealthTexture, NULL, &healthTextDest);
	TTF_CloseFont(opponentHealthFont);
	SDL_FreeSurface(opponentHealthSurface);

	TTF_Quit();
}

void Opponent::drawMana()
{
	if(TTF_Init() < 0)
		cout << "tff_init error: " << SDL_GetError() << endl;

	SDL_Color fontColor = { 0, 0, 255 };
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

short Opponent::getSelectedCardIndex()
{
	for(int i = 0; i < cardsOnBoard.size(); i++)
	{
		if(cardsOnBoard.at(i).getIsSelected())
			return i;
	}
	return -1;
}

int Opponent::getPlayersTarget()
{
	for(int i = 0; i < cardsOnBoard.size(); i++)
	{
		if(cardsOnBoard.at(i).getIsSelected())
			return cardsOnBoard.at(i).getID();
	}
	return OPPONENT_FACE;
}

void Opponent::damageCard(short &cardID, short p_damageTaken)
{
	/* short cardsRemainingHealth = cardsOnBoard.at(cardIndex).damaged(renderer, p_damageTaken); */	
	short cardsRemainingHealth = 1;
	short cardIndex;

	for(int i = 0; i < cardsOnBoard.size(); i++)
	{
		if(cardsOnBoard.at(i).getID() == cardID)
		{
			cardsRemainingHealth = cardsOnBoard.at(i).damaged(p_damageTaken);
			cardIndex = i;
			break;
		}
	}

	if(cardsRemainingHealth > 0)
		return;

	if(cardsRemainingHealth/4 < 0)
		damaged(cardsRemainingHealth/4 * -1);

	killCard(cardIndex);
}

void Opponent::killCard(short &cardIndex)
{
	cardsOnBoard.erase(cardsOnBoard.begin() + cardIndex);
	refreshCardPositions();
	cardDied = true;
}

bool Opponent::getCardDied()
{
	return cardDied;
}

void Opponent::resetCardDied()
{
	cardDied = false;
}

void Opponent::refreshCardPositions()
{
	for(int i = 0; i < cardsOnBoard.size(); i++)
		cardsOnBoard.at(i).changeBoardPosition(i);
}

short Opponent::getCardDamage(short &cardID)
{
	/* return cardsOnBoard.at(cardIndex).getDamage(); */
	for(int i = 0; i < cardsOnBoard.size(); i++)
	{
		if(cardsOnBoard.at(i).getID() == cardID)
		{
			return cardsOnBoard.at(i).getDamage();
		}
	}
}

opponentMove Opponent::getLastMove()
{
	return lastMove;
}

OpponentCard& Opponent::getCardToPlay()
{
	return deck[cardToPlay];
}
