#include "card_outlines.h"

using namespace std;

//###########################  0 COSTS, NEED 1 MORE  ########################
unit scrub(0, "Scrub", 1, 0);

float bump_mults[] = {1};
int bump_abils[] = {1};
spell bump(0, "Bump", 1, 1, bump_mults, bump_abils);

float peasant_mults[] = {.5};
int peasant_abils[] = {14, 27};
special peasant(0, "Peasant", 2, 2, 1, 2, peasant_mults, peasant_abils); //make a special with a negative affect

//###########################  1  COSTS, NEED 1 MORE  ######################## 
float squirt_mults[] = {1,4,2,2};
int squirt_abils[] = {0,54};
special squirt(1, "Squirt", 2, 2, 4, 2, squirt_mults, squirt_abils);

float brave_mults[] = {2, 1, 1};
int brave_abils[] = {50};
special brave(1, "Brave", 1, 1, 3, 1, brave_mults, brave_abils);

unit bonerfart(1, "Bonerfart", 1, 2);

//###########################  2  COSTS, NEED 0 MORE  ######################## 
unit mutt(2, "Mutt", 2, 3);
unit common(2, "Common", 2, 2);

float noble_mults[] = {1, 1, 5, 7, 4, 4};
int noble_abils[] = {57, 58};
special noble(2, "Noble", 2, 2, 6, 2, noble_mults, noble_abils);

float doubleTrouble_mults[] = {1, 1};
int doubleTrouble_abils[] = {21, 52};
spell doubleTrouble(2, "Double Trouble", 2, 2, doubleTrouble_mults, doubleTrouble_abils);

//###########################  3  COSTS, NEED 1 MORE  ######################## 
float turtle_mults[] = {.5};
int turtle_abils[] = {6, 24};
special turtle(3, "Turtle", 3, 3, 1, 2, turtle_mults, turtle_abils);

float hound_mults[] = {2.5};
int hound_abils[] = {8};
special hound(3, "Hound", 3, 2, 1, 1, hound_mults, hound_abils);

unit lieutenant(3, "Lieutenant", 3, 3);

//###########################  4  COSTS, NEED ? MORE  ######################## 
float mordy_mults[] = {2};
int mordy_abils[] = {7};
special mordy(4, "Mordy", 3, 5, 1, 1, mordy_mults, mordy_abils);

float test_mults[] = {2};
int test_abils[] = {13};
spell Test(4, "Test", 1, 1, test_mults, test_abils);

//###########################  5  COSTS, NEED ? MORE  ######################## 
float number_mults[] = {1.5, .5};
int number_abils[] = {7, 8, 9};
special number(5, "Number", 4, 7, 2, 3, number_mults, number_abils);

float bank_mults[] = {3};
int bank_abils[] = {33};
spell bank(6, "Bank", 1, 1, bank_mults, bank_abils);
//###########################  6  COSTS, NEED 0 MORE  ######################## 
unit brigadier(6, "Brigadier", 7, 9);

float brick_mults[] = {1, 2, 2};
int brick_abils[] = {10, 14, 15};
special brick(6, "Brick", 5, 5, 3, 3, brick_mults, brick_abils);

float craze_mults[] = {.5};
int craze_abils[] = {6, 23};
special craze(6, "Craze", 7, 4, 1, 2, craze_mults, craze_abils);

float bigPlay_mults[] = {};
int bigPlay_abils[] = {30};
spell bigPlay(6, "Big Play", 0, 1, bigPlay_mults, bigPlay_abils);

//###########################  7  COSTS, NEED ? MORE  ######################## 
float martyr_mults[] = {};
int martyr_abils[] = {32};
special martyr(7, "Martyr", 12, 3, 0, 1, martyr_mults, martyr_abils);

//###########################  8  COSTS, NEED ? MORE  ######################## 
float inhibitor_mults[] = {};
int inhibitor_abils[] = {28, 29};
special inhibitor(8, "Inhibitor", 3, 14, 0, 2, inhibitor_mults, inhibitor_abils);

float savior_mults[] = {.75, 2, 1.5};
int savior_abils[] = {6, 12, 16, 31};
special savior(8, "Savior", 10, 8, 3, 4, savior_mults, savior_abils);

//###########################  9  COSTS, NEED ? MORE  ######################## 

//###########################  10 COSTS, NEED ? MORE  ######################## 
float lance_mults[] = {};
int lance_abils[] = {22};
special lance(10, "Lance", 4, 4, 0, 1, lance_mults, lance_abils);
//###########################  UNIQUES  ######################## 



