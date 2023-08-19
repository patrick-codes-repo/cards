#include <iostream>
#include "card_types.h"

using namespace std;

int main()
{
	cout << string(20, '#') << "  0  COST  " << string(20, '#') << endl;
	scrub.show_stats();
	cout << endl;
	bump.show_stats();
	peasant.show_stats();
	cout << endl;


	cout << string(20, '#') << "  1  COST  " << string(20, '#') << endl;
	squirt.show_stats();
	bonerfart.show_stats();
	cout << endl;
	brave.show_stats();


	cout << string(20, '#') << "  2  COST  " << string(20, '#') << endl;
	mutt.show_stats();
	cout << endl;
	common.show_stats();
	cout << endl;
	noble.show_stats();
	doubleTrouble.show_stats();


	cout << string(20, '#') << "  3  COST  " << string(20, '#') << endl;
	turtle.show_stats();
	hound.show_stats();
	lieutenant.show_stats();
	cout << endl;


	cout << string(20, '#') << "  4  COST  " << string(20, '#') << endl;
	mordy.show_stats();
	
	
	cout << string(20, '#') << "  5  COST  " << string(20, '#') << endl;
	number.show_stats();
	bank.show_stats();
	
	cout << string(20, '#') << "  6  COST  " << string(20, '#') << endl;
	brigadier.show_stats();
	cout << endl;
	brick.show_stats();
	craze.show_stats();
	bigPlay.show_stats();
	
	cout << string(20, '#') << "  7  COST  " << string(20, '#') << endl;
	martyr.show_stats();

	cout << string(20, '#') << "  8  COST  " << string(20, '#') << endl;
	inhibitor.show_stats();
	savior.show_stats();

	cout << string(20, '#') << "  9  COST  " << string(20, '#') << endl;
	cout << string(20, '#') << "  10 COST  " << string(20, '#') << endl;
	lance.show_stats();
	
	cout << string(20, '#') << "  UNIQUES  " << string(20, '#') << endl;
}
