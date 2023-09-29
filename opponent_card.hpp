#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "mouse.hpp"
#include "globals.hpp"
#include "card_constants.hpp"

class OpponentCard {
	public:
		OpponentCard(SDL_Renderer* p_renderer, short p_arrayPosition, short p_health, short p_damage, short p_cost);
		void render(SDL_Renderer* p_renderer);
		short damaged(SDL_Renderer* p_renderer, short p_damageTaken);
		void update(Mouse p_mouse);
		void moveCard(Mouse p_mouse);
		int getCardY();
		void playCard(int p_numberOfCardsOnBoard, SDL_Renderer* p_renderer);
		bool getIsSelected();
		bool getHasBeenPlayed();
		short getCost();
		short getDamage();
		void changeBoardPosition(short p_position);
		void attack();
	private:
		SDL_Texture* targetTexture;
		SDL_Texture* noNumbers;
		SDL_Rect targetDest;
		SDL_Rect healthTextDest;
		SDL_Rect damageTextDest;
		short boardPosition;
		short health;
		short damage;
		short cost;
		char healthBuffer[50];
		char damageBuffer[50];
		/* void changeHealthDisplayed(SDL_Renderer* p_renderer); */
		bool isSelected = false;
		void createCardTexture(SDL_Renderer* p_renderer);
		bool hasBeenPlayed = false;
		void drawDynamicStats(SDL_Renderer* p_renderer);
};
