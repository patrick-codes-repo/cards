#pragma once

#include "card_classes.cpp"

class OCard1 : public OpponentCard
{
	public:
		OCard1(int arrayPosition) : OpponentCard(arrayPosition)
		{
			name = "OCard1";
			cost = 1;
			health = 2;
			damage = 2;
			description = "I am a test card";
			backgroundImagePath = "resources/card.jpg";
		}
};
