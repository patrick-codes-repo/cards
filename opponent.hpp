#pragma once
#include <vector>

#include "opponent_card.hpp"

using namespace std;

class Opponent {
	public:
		Opponent(SDL_Renderer* p_renderer, short p_health);
		void damaged(short damageTaken);
		void healed();
		bool makeMove();
		void renderHealth();
		void renderMana();
		void renderCards();
		void updateCards(Mouse p_mouse);
		void setMana(short &newManaAmount);
		void drawMana();
		void drawHealth();
		short getSelectedCardIndex();
		void damageCard(short &cardIndex, short p_damageTaken);
		short getCardDamage(short &cardIndex);
		void resetCardDied();
		bool getCardDied();
		int getPlayersTarget();
	private:
		SDL_Renderer* renderer;
		SDL_Texture* opponentHealthTexture; 
		SDL_Rect healthTextDest;
		SDL_Texture* manaTexture; 
		SDL_Rect manaTextDest;
		short health;
		char healthBuffer[50];
		OpponentCard deck[4] = {
			OpponentCard(renderer, 0, 1, 1, 1, 20100), 
			OpponentCard(renderer, 1, 2, 2, 2, 20200), 
			OpponentCard(renderer, 2, 3, 3, 3, 20300),
			OpponentCard(renderer, 3, 4, 4, 4, 20400)
		};
		vector<OpponentCard> cardsOnBoard;
		short chooseCard();
		short mana = 1;
		char manaBuffer[10];
		void killCard(short &cardIndex);
		void refreshCardPositions();
		bool cardDied = false;
		bool playCard();
		bool attacking = false;
};
