#include <string>

using namespace std;

string get_ability(int x)
{
	string abilities[] = 
	{
		"Reduce the cost of a card in hand by 1", //0
		"Gain 1 mana", //1
		"Spawn 1 scrub", //2
		"All damage dealt to me is dealt to the opponents face", //3
		"All damage dealt to me is dealt to my attacker", //4
		"All damage dealt to my player's face is dealt to me instead", //5
		"I take 1x damage from all sources", //6
		"I deal 1x damage to the opponent's face", //7
		"I deal 1x damage to other cards", //8
		"Spells and abilities cannot target me", //9
		"kill 1 card", //10
		"Spawn 1 knight", //11
		"1x an allied cards health and an enemy cards health", //12
		"1x an allied cards damage and an enemy cards damage", //13
		"After attacking 1x my remaining health", //14
		"After attacking 1x my damage", //15
		"After blocking 1x my remaining health", //16
		"After blocking 1x my damage", //17
		"1x a card's health and the amount of damage it takes", //18
		"Remove all effects from a card", //19
		"Win", //20
		"Spawn Scrub and Peasant", //21
		"Spawn Mordy, Brick, and Phoenix", //22
		"When I am played I attack all enemy units", //23
		"When I am played all enemy units attack me", //24
		"All damage dealt to me is dealt to your face instead", //25
		"All damage dealt to me is also dealt to your face", //26
		"All damage I deal is also dealt to my player's face", //27
		"When I am played all enemy cards strike your face", //28
		"The enemy cannot block this turn", //29
		"Earn double the income from the start of next turn", //30
		"Fully heal your player", //31
		"I kill any unit that attacks me", //32
		"Start next turn with 1 extra mana" //33
	};

	string mult_abilities[] = 
	{
		"Give 1 allied card +1 +1", //50
		"Give all allied cards +1 +1", //51
		"Give all cards +1 +1", //52
		"If I am still in your hand by turn 1 change my cost to 1", //53
		"If I am still in your hand by turn 1 give me +1 +1", //54
		"If I am still in your hand by turn 1 multiply the effects of my other abilities by 1", //55
		"I cost 1 if I am still in your hand by turn 1", //56
		"I gain +1 +1 each turn until turn 1", //57
		"After Brigadier is played I cost 1 but gain +1 +1" //58
	};

	string groups[] = 
	{
		"Reach",
		"Box",
		"Tale"
	};


	if(x < 50)
		return abilities[x];
	else if(x < 100)	
		return mult_abilities[x-50];
	else
		return groups[x-100];
}
