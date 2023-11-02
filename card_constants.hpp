#pragma once
#include <SDL2/SDL.h>

const short BACKGROUND_ORIGIN_WIDTH = 885;
const short BACKGROUND_ORIGIN_HEIGHT = 1322;
const short ADJUSTED_BACKGROUND_WIDTH = BACKGROUND_ORIGIN_WIDTH * .2;
const short ADJUSTED_BACKGROUND_HEIGHT = BACKGROUND_ORIGIN_HEIGHT * .2;

const int PLAYER_FACE = 100;
const int OPPONENT_FACE = 200;
const int NO_TARGET = 0;

enum state {inHand, onBoard, onSide, inAttackingGroup, playingAttackAnimation, readyToDealDamage, attackedThisTurn};
/* //can reuse existing enum and only use the needed values */
/* enum opponentCardStates {onBoard, inAttackingGroup, attackedThisTurn}; */
enum opponentMove {skipped, attacked, playedCard};
enum type {unit, special, spell};
