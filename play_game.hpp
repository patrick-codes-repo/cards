#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "render_window.hpp"
#include "entity.hpp"
#include "button.hpp"
#include "mouse.hpp"
#include "card.hpp"
#include "dummy_card.hpp"
#include "globals.hpp"
#include "opponent.hpp"

using namespace std;

extern SDL_Renderer* renderer; 
extern short handDisplayController;
extern bool playersTurn;
extern short playerHealth;
extern char playerHealthBuffer[50];
extern short roundNumber;
extern char roundNumberBuffer[50];
extern short playerMana;
extern char playerManaBuffer[10];
extern SDL_Texture* roundNumberTexture; 
extern SDL_Texture* playerHealthTexture; 
extern SDL_Texture* playerManaTexture; 
extern SDL_Rect roundNumberDest;
extern SDL_Rect healthTextDest;
extern SDL_Rect manaTextDest;
	
int playGame();
void checkIfCardPlayed(Card p_displayedCards[], vector<Card> &p_cardsOnBoard, DummyCard p_dummyCard[]);
void playCard(Card &p_currentCard, vector<Card> &p_cardsOnBoard, DummyCard &p_dummyCard);
void incrementHandDisplayController();
void decrementHandDisplayController();
bool checkIfCardOnSide(Card p_displayedCards[], short &p_onsideCardIndex);
void replaceCard(Card &p_currentCard, vector<Card> &p_cardsOnBoard, DummyCard &p_dummyCard, int p_positionToReplace);
void updatePlayerHand(DummyCard p_currentHandFillers[], Card p_currentHandCards[], Mouse p_mouse);
void renderPlayerHand(Card p_currentHandCards[], DummyCard p_currentHandFillers[], int &p_selectedIndex);
void endRound();
void drawRoundNumber();
void drawPlayerMana();
void drawPlayerHealth();