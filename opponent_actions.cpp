#include "opponent_actions.hpp"

Action makeMove(vector<OpponentCard*> opponentBoard)
{
    Action action;

    chooseAction(action, opponentBoard);
    
    if(action == playCard)
    {
        //play a card
        //or shold playCard be returned then card is actually played in main
    }

    return action;
}

void chooseAction(Action &action, vector<OpponentCard*> opponentBoard)
{
    if(opponentBoard.size() >= 4)
    {
        action = skipTurn;
        return;
    }

    action = playCard;
}
