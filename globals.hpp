#pragma once
#include <SDL2/SDL.h>

#include "entity.hpp"

const short SCREEN_WIDTH = 1920;
const short SCREEN_HEIGHT = 1080;

struct Player
{
	int health;
	int mana;
	Entity healthEntity;
	Entity manaEntity;
};

struct GameState
{
	int roundNumber;
	Entity roundNumberEntity;
	bool playersTurn;
};
