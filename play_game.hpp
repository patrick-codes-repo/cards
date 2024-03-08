#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#include "renderer.hpp"
#include "entity.hpp"
#include "button.hpp"
#include "mouse.hpp"
#include "card_classes.cpp" 
#include "player_cards.cpp"
#include "opponent_cards.cpp"

#include "globals.hpp"

#include <iostream>

using namespace std;

int playGame();
void drawPlayerHealth(Player &player, Renderer &window);
void drawPlayerMana(Player &player, Renderer &window);
void drawOpponentHealth(Player &opponent, Renderer &window);
void drawOpponentMana(Player &opponent, Renderer &window);
void drawRoundNumber(int &roundNumber, Entity &roundNumberEntity, Renderer &window);
CombatCard* findSelectedCard(vector<PlayerCard*> playerBoard, vector<OpponentCard*> opponentBoard);
void incrementHandController(int &handController);
void decrementHandController(int &handController);
void endRound(GameState &gameState, Player &player, Player &opponent, Renderer &window, vector<PlayerCard*> playerBoard);
void endTurn(GameState &gameState);
CardBase* createNewDummy(int position, Renderer &window);
OpponentCard* createOpponentCard(int position);
void damageOpponent(PlayerCard* attacker, OpponentCard* target, Player &opponent);
void drawAfterDamage(vector<PlayerCard*> playerBoard, vector<OpponentCard*> opponentBoard, Player &player, Player &opponent, Renderer &window);
