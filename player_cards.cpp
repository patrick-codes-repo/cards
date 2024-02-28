#pragma once

#include <cstring>

#include "card_classes.cpp"
#include "card_constants.hpp"

class Squirt : public PlayerCard
{
	public:
		Squirt(int arrayPosition) : PlayerCard(arrayPosition)
		{
			name = "Squirt";
			cost = 1;
			health = 2;
			damage = 2;
            type = special;
			description = "If I am still in your\nhand by turn 4\ngive me +2 +2";
			backgroundImagePath = "resources/card.jpg";
		}
};

class Bonerfart : public PlayerCard
{
	public:
		Bonerfart(int arrayPosition) : PlayerCard(arrayPosition)
		{
			name = "Bonerfart";
			cost = 1;
			health = 1;
			damage = 2;
            type = unit; 
			description = "F";
			backgroundImagePath = "resources/card.jpg";
		}
};

class Brave : public PlayerCard
{
	public:
		Brave(int arrayPosition) : PlayerCard(arrayPosition)
		{
			name = "Brave";
			cost = 1;
			health = 1;
			damage = 1;
            type = special; 
			description = "Give 2 allied cards\n+1 +1";
			backgroundImagePath = "resources/card.jpg";
		}
};

class TestSpell : public PlayerCard
{
    public:
        TestSpell(int arrayPosition) : PlayerCard(arrayPosition)
        {
            name = "Test Spell";
            cost = 1;
            damage = 0;
            health = 0;
            type = spell;
            description = "I am a test spell";
            backgroundImagePath = "resources/card.jpg";
    }
};


class Mutt : public PlayerCard
{
	public:
		Mutt(int arrayPosition) : PlayerCard(arrayPosition)
		{
			name = "Mutt";
			cost = 2;
			health = 2;
			damage = 3;
            type = unit;
			description = "F";
			backgroundImagePath = "resources/card.jpg";
		}
};

class Common : public PlayerCard
{
	public:
		Common(int arrayPosition) : PlayerCard(arrayPosition)
		{
			name = "Common";
			cost = 2;
			health = 2;
			damage = 2;
            type = unit;
			description = "F";
			backgroundImagePath = "resources/card.jpg";
		}
};

class DoubleTrouble : public PlayerCard
{
	public:
		DoubleTrouble(int arrayPosition) : PlayerCard(arrayPosition)
		{
			name = "Double Trouble";
			cost = 2;
			health = 0;
			damage = 0;
            type = special;
			description = "Spawn Scrub and Peasant. Give all cards +1 +1";
			backgroundImagePath = "resources/card.jpg";
		}
};

