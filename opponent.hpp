#pragma once
#include <vector>

#include "opponent_card.hpp"
#include "card.hpp"

using namespace std;

class Opponent {
	public:
		Opponent(short p_health);
		void damaged(short damageTaken);
		void healed();
		void makeMove(vector<Card> &playerCards, short &playerHealth);
		/* void renderHealth(); */
		/* void renderMana(); */
		/* void renderCards(); */
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
		SDL_Texture* opponentHealthTexture; 
		SDL_Texture* manaTexture; 
		SDL_Rect healthTextDest;
		SDL_Rect manaTextDest;
		vector<OpponentCard> cardsOnBoard;
		opponentMove getLastMove();
		OpponentCard& getCardToPlay();
	private:
		/* SDL_Renderer* renderer; */
		short health;
		char healthBuffer[50];
		OpponentCard deck[4] = {
			OpponentCard(0, 1, 1, 1, 20100), 
			OpponentCard(1, 2, 2, 2, 20200), 
			OpponentCard(2, 3, 3, 3, 20300),
			OpponentCard(3, 4, 4, 4, 20400)
		};
		short chooseCard();
		short mana = 1;
		char manaBuffer[10];
		void killCard(short &cardIndex);
		void refreshCardPositions();
		bool cardDied = false;
		bool playCard();
		bool attacking = false;
		void attack(vector<Card> &playerCards, short &playerHealth);
		opponentMove lastMove;
		int cardToPlay;
};
