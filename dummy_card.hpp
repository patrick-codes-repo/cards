#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "mouse.hpp"
#include "globals.hpp"
#include "card_constants.hpp"

class DummyCard {
	public:
		DummyCard(SDL_Renderer* p_renderer, short p_arrayPosition);
		void render(SDL_Renderer* p_renderer);
		void update(Mouse p_mouse);
		bool getIsSelected();
		void resetCardPosition();
		void setIsVisible();
		bool getIsVisible();
	private:
		SDL_Texture* targetTexture;
		SDL_Rect targetDest;
		short ARRAY_POSITION;
		bool isSelected = false;
		bool isVisible = false;
};
