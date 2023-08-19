#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "mouse.hpp"
#include "globals.hpp"
#include "card_constants.hpp"

class Card {
	public:
		Card(SDL_Renderer* p_renderer, short p_arrayPosition, short p_health, short p_attack);
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
	private:
		SDL_Texture* targetTexture;
		SDL_Texture* noNumbers;
		SDL_Rect targetDest;
		SDL_Rect healthTextDest;
		SDL_Rect attackTextDest;
		short ARRAY_POSITION;
		short health;
		short attack;
		char healthBuffer[50];
		char attackBuffer[50];
		state cardState = inHand;
		bool isSelected = false;
		void changeHealthDisplayed(SDL_Renderer* p_renderer);
		void moveCardToSide();
};