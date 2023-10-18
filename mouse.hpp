#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> 

class Mouse {
	public:
		Mouse(SDL_Texture* p_mouseTexture);
		void update();
		int getCollisionRectX();
		int getCollisionRectY();
		SDL_Texture* getTexture();
		SDL_Rect collisionRect;
		SDL_Rect imageRect;
	private:
		SDL_Texture* mouseTexture;
		void correctMousePosition();
};
