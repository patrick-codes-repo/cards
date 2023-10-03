#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "mouse.hpp"
#include "globals.hpp"
#include "card_constants.hpp"

class Card {
	public:
		Card(SDL_Renderer* p_renderer, short cost,  short p_arrayPosition, short p_health, short p_damage);
		void render(SDL_Renderer* p_renderer);
		void damaged(SDL_Renderer* p_renderer, short p_damageTaken);
		void update(Mouse p_mouse);
		void moveCard(Mouse p_mouse);
		bool getIsSelected();
		int getCardY();
		void resetCardPosition();
		bool playCard(int p_numberOfCardsOnBoard);
		state getCardState();
		void setStateInHand();
		void attack();
		short getCost();
		type getCardType();
		short getDamage();
		/* void resetAttacked(); */
		/* bool getAttacked(); */
		void setAttacking();
		bool getAttacking();
		void setTarget(short &targetIndex);
		short getTarget();
		short getHealth();
		int getCardPosition();
		void changeBoardPosition(int p_position);
		void playAttackAnimation();
		void setStateOnBoard();
	private:
		SDL_Texture* targetTexture;
		SDL_Texture* noNumbers;
		SDL_Rect targetDest;
		SDL_Rect healthTextDest;
		SDL_Rect damageTextDest;
		SDL_Rect costTextDest;
		short health;
		short damage;
		short cost;
		char healthBuffer[50];
		char damageBuffer[50];
		char costBuffer[50];
		short ARRAY_POSITION;
		state cardState = inHand;
		bool isSelected = false;
		void drawDynamicStats(SDL_Renderer* p_renderer);
		void moveCardToSide();
		int cardPosition;
		type cardType;
		/* bool attacked = false; */
		bool attacking = false;
		short attackTarget;
		Uint32 animationEnd;
};
