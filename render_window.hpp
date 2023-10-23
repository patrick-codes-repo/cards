#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "entity.hpp"
#include "mouse.hpp"
#include "button.hpp"
#include "card.hpp"
#include "dummy_card.hpp"
#include "opponent_card.hpp"

class RenderWindow
{
	public:
		RenderWindow(const char* p_title);
		SDL_Texture* loadTexture(const char* filePath);
		SDL_Texture* createTextureFromSurface(SDL_Surface* surface);
		void clear();
		void render(Entity& p_entity);
		void display();
		void cleanUp();
		void renderMouse(Mouse &mouse);
		void renderButton(Button &button);
		void renderBackground(SDL_Texture* p_backgroundImage);
		void renderStat(SDL_Texture* texture, SDL_Rect &destination);
		void initializeCardTextures(Card &card);
		void drawCardDynamicStats(Card &card);
		void renderCard(Card &card);
		void initializeDummyCardTextures(DummyCard &dummyCard);
		void renderDummyCard(DummyCard &dummyCard);
		void drawOpponentCardDynamicStats(OpponentCard &card);
		void renderOpponentCard(OpponentCard &card);
	private:
		SDL_Window* window;
		SDL_Renderer* renderer;
};
