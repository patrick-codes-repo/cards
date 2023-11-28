#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "mouse.hpp"
#include "card_constants.hpp"
#include "globals.hpp"

class CardBase
{
	public:
		bool getIsSelected()
		{
			return isSelected;
		}

		virtual void update(Mouse &mouse) = 0;
		virtual void resetCardPosition() = 0;
		virtual void moveCard(Mouse &mouse) = 0;
		virtual void drawDynamicStats() = 0;
		Entity entity;
	protected:
		bool isSelected = false;
};

class DummyCard : public CardBase
{
	public:
		DummyCard(int arrayPosition, SDL_Texture* cardTexture)
		{
			entity.texture = cardTexture;
			entity.destination.x = (SCREEN_WIDTH/4) + ((SCREEN_WIDTH/8) * arrayPosition);
			entity.destination.y = SCREEN_HEIGHT - ADJUSTED_BACKGROUND_HEIGHT/2;
			entity.destination.w = ADJUSTED_BACKGROUND_WIDTH;
			entity.destination.h = ADJUSTED_BACKGROUND_HEIGHT;
		}

		void update(Mouse &mouse)
		{
			if(SDL_HasIntersection(&entity.destination, &mouse.collisionRect))
			{
				isSelected = true;
				entity.destination.y = SCREEN_HEIGHT - ADJUSTED_BACKGROUND_HEIGHT; 
				return;
			}	
			isSelected = false;
			resetCardPosition();	
		}	

		void moveCard(Mouse &mouse)
		{
			return;
		}

		void drawDynamicStats()
		{
			return;
		}
	private:	
		void resetCardPosition()
		{
			entity.destination.y = SCREEN_HEIGHT - ADJUSTED_BACKGROUND_HEIGHT/2;
		}
};

class CombatCard : public CardBase
{
	public:
		void playCard();
		SDL_Texture* noStats;
		const char* backgroundImagePath;
		const char* description;
		int health;
		int damage;
		int cost;
	protected:		
		std::string name;
		int ID;
		State state = inHand;
		int position;
};

class PlayerCard : public CombatCard
{
	public:
		PlayerCard(int arrayPosition)
		{
			entity.destination.x = (SCREEN_WIDTH/4) + ((SCREEN_WIDTH/8) * arrayPosition);
			entity.destination.y = SCREEN_HEIGHT - ADJUSTED_BACKGROUND_HEIGHT/2;
			entity.destination.w = ADJUSTED_BACKGROUND_WIDTH;
			entity.destination.h = ADJUSTED_BACKGROUND_HEIGHT;

			position = arrayPosition;
		}

		void update(Mouse &mouse)
		{
			if(SDL_HasIntersection(&entity.destination, &mouse.collisionRect))
			{
				isSelected = true;
				entity.destination.y = SCREEN_HEIGHT - ADJUSTED_BACKGROUND_HEIGHT; 
				return;
			}	
			isSelected = false;
			resetCardPosition();	
		}	

		void moveCard(Mouse &mouse)
		{
			entity.destination.x = mouse.collisionRect.x - entity.destination.w/2;
			entity.destination.y = mouse.collisionRect.y - entity.destination.h/2;
		}

		void drawDynamicStats()
		{
			return;
		}
	protected:
		void resetCardPosition()
		{
			if(state == inHand)
			{
				entity.destination.x = (SCREEN_WIDTH/4) + ((SCREEN_WIDTH/8) * position);
				entity.destination.y = SCREEN_HEIGHT - ADJUSTED_BACKGROUND_HEIGHT/2;
				return;
			}

			entity.destination.y = SCREEN_HEIGHT/2;
			entity.destination.x = SCREEN_WIDTH/8 + position * SCREEN_WIDTH/8;
		}

};

class OpponentCard
{

};
