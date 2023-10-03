#pragma once
#include <SDL2/SDL.h>

const short BACKGROUND_ORIGIN_WIDTH = 885;
const short BACKGROUND_ORIGIN_HEIGHT = 1322;
const short ADJUSTED_BACKGROUND_WIDTH = BACKGROUND_ORIGIN_WIDTH * .2;
const short ADJUSTED_BACKGROUND_HEIGHT = BACKGROUND_ORIGIN_HEIGHT * .2;

enum state {inHand, onBoard, onSide, playingAttackAnimation, readyToAttack};
enum type {unit, special, spell};
