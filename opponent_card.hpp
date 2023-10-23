#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "mouse.hpp"
#include "globals.hpp"
#include "card_constants.hpp"

class OpponentCard {
	public:
		OpponentCard(short p_arrayPosition, short p_health, short p_damage, short p_cost, int p_id);
		/* void render(SDL_Renderer* p_renderer); */
		short damaged(short p_damageTaken);
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
		int getID();
		void setTarget(int targetID);
		int getTarget();
		SDL_Texture* targetTexture;
		SDL_Rect targetDest;
		SDL_Texture* noNumbers;
		short getHealth();
	private:
		SDL_Rect healthTextDest;
		SDL_Rect damageTextDest;
		short boardPosition;
		short health;
		short damage;
		short cost;
		char healthBuffer[50];
		char damageBuffer[50];
		bool isSelected = false;
		void createCardTexture(SDL_Renderer* p_renderer);
		bool hasBeenPlayed = false;
		/* void drawDynamicStats(SDL_Renderer* p_renderer); */
		int ID;
		int attackTarget;
};
