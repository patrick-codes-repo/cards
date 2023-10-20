#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "mouse.hpp"
#include "globals.hpp"
#include "card_constants.hpp"

class DummyCard {
	public:
		DummyCard(short p_arrayPosition);
		/* void render(SDL_Renderer* p_renderer); */
		void update(Mouse p_mouse);
		bool getIsSelected();
		void resetCardPosition();
		void setIsVisible();
		bool getIsVisible();
		SDL_Texture* targetTexture;
		SDL_Rect targetDest;
	private:
		short ARRAY_POSITION;
		bool isSelected = false;
		bool isVisible = false;
};
