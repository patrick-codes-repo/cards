#pragma once
#include <vector>

#include "opponent_card.hpp"

using namespace std;

class Opponent {
	public:
		Opponent(SDL_Renderer* p_renderer, short p_health);
		void damaged();
		void healed();
		void playCard();
		void renderHealth();
		void renderMana();
		void renderCards();
		void updateCards(Mouse p_mouse);
		short getMana();
		void incrementMana();
		void drawMana();
	private:
		SDL_Renderer* renderer;
		SDL_Texture* opponentHealthTexture; 
		SDL_Rect healthTextDest;
		SDL_Texture* manaTexture; 
		SDL_Rect manaTextDest;
		short health;
		char healthBuffer[50];
		OpponentCard deck[4] = {
			OpponentCard(renderer, 0, 1, 0), 
			OpponentCard(renderer, 1, 0, 0), 
			OpponentCard(renderer, 2, 2, 2), 
			OpponentCard(renderer, 3, 0, 0)
		};
		vector<OpponentCard> cardsOnBoard;
		short chooseCard();
		short mana = 1;
		char manaBuffer[10];
};
