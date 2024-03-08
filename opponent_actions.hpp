#pragma once

#include <vector>

#include "card_classes.cpp"
#include "globals.hpp"

Action makeMove(vector<OpponentCard*> opponentBoard);
void chooseAction(Action &action, vector<OpponentCard*> opponentBoard);
