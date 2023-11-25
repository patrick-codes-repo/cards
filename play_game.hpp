#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "renderer.hpp"
#include "entity.hpp"
#include "button.hpp"
#include "mouse.hpp"
#include "card_classes.cpp" 

#include "globals.hpp"

#include <iostream>

using namespace std;

int playGame();
void drawPlayerHealth(Player &player, Renderer &window);
void drawPlayerMana(Player &player, Renderer &window);
void drawOpponentHealth(Player &opponent, Renderer &window);
void drawOpponentMana(Player &opponent, Renderer &window);
void drawRoundNumber(int &roundNumber, Entity &roundNumberEntity, Renderer &window);
