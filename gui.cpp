#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "render_window.hpp"
#include "entity.hpp"
#include "button.hpp"
#include "mouse.hpp"
#include "card.hpp"
#include "dummy_card.hpp"
#include "globals.hpp"
#include "opponent.hpp"

using namespace std;

int mainMenu();
int playGame();
void checkIfCardPlayed(Card p_displayedCards[], vector<Card> &p_cardsOnBoard, DummyCard p_dummyCard[]);
void playCard(Card &p_currentCard, vector<Card> &p_cardsOnBoard, DummyCard &p_dummyCard);
void incrementHandDisplayController(short &handDisplayController);
void decrementHandDisplayController(short &handDisplayController);
bool checkIfCardOnSide(Card p_displayedCards[], short &p_onsideCardIndex);
void replaceCard(Card &p_currentCard, vector<Card> &p_cardsOnBoard, DummyCard &p_dummyCard, int p_positionToReplace);

int main()
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		cout << "Video Init error: " << SDL_GetError() << endl;
	}

	if(!(IMG_Init(IMG_INIT_PNG || IMG_INIT_JPG)))
	{
		cout << "IMG Init error: " << SDL_GetError() << endl;
	}

	short gameLoopValue = 1;

	while(gameLoopValue)
	{
		switch (gameLoopValue)
		{
			case 1:
				gameLoopValue = mainMenu();
				break;
			case 2:
				gameLoopValue = playGame();
				break;
			default:
				return 0;
		}
	}
}

int mainMenu()
{
	RenderWindow window("Main Menu", SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_Renderer* renderer = window.getRenderer();

	Mouse mouse(renderer);
	
	Button play_button(renderer, 50, 115, SCREEN_WIDTH/2 - 100, 500);
	Button exit_button(renderer, 50, 115, SCREEN_WIDTH/2 - 100, 600);

	SDL_Texture* background_image = window.loadTexture("resources/background.png");

	vector<Entity> entity_array = {Entity(1616, 1215, 'b', background_image)};
	SDL_Event event;

	while(true)
	{
		mouse.update();
		play_button.update(mouse);
		exit_button.update(mouse);

		while(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					window.cleanUp();
					return 0;
				case SDL_MOUSEBUTTONUP:
					if(event.button.button == SDL_BUTTON_LEFT)
					{
						if (play_button.getIsSelected())
						{
							cout << "play clicked" << endl;
							window.cleanUp();
							return 2;
						}
						
						else if (exit_button.getIsSelected())
						{
							cout << "exit clicked" << endl;
							window.cleanUp();
							return 0;
						}
					}
					break;
			}
		}
		
		window.clear();
		
		for(Entity& e : entity_array)
		{
			window.render(e);
		}

		play_button.draw(renderer);
		exit_button.draw(renderer);
		mouse.draw(renderer);

		window.display();
	}
}

int playGame()
{
	RenderWindow window ("Playing Game", SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_Renderer* renderer = window.getRenderer();

	Mouse mouse (renderer);
	
	Button mainMenuButton(renderer, 50, 115, 960 - 100, 50);
	Button testFunctionButton(renderer, 50, 115, 960 - 100, 150);
	Button scrollDeckup(renderer, 50, 115, 1500, 850);
	Button scrollDeckDown(renderer, 50, 115, 1500, 950);

	SDL_Texture* background_image = window.loadTexture("resources/game_background.png");
	SDL_Texture* card_image = window.loadTexture("resources/card.png");

	Card deck[][4] = {
		{Card(renderer, 0, 1, 0), Card(renderer, 1, 0, 0), Card(renderer, 2, 2, 2), Card(renderer, 3, 0, 0)},
		{Card(renderer, 0, 2, 2), Card(renderer, 1, 1, 2), Card(renderer, 2, 1, 1), Card(renderer, 3, 0, 0)},
		{Card(renderer, 0, 2, 3), Card(renderer, 1, 2, 2), Card(renderer, 2, 3, 2), Card(renderer, 3, 0, 0)} 
	};

	DummyCard handFillers[][4] = {
		{DummyCard(renderer, 0), DummyCard(renderer, 1), DummyCard(renderer, 2), DummyCard(renderer, 3)},
		{DummyCard(renderer, 0), DummyCard(renderer, 1), DummyCard(renderer, 2), DummyCard(renderer, 3)},
		{DummyCard(renderer, 0), DummyCard(renderer, 1), DummyCard(renderer, 2), DummyCard(renderer, 3)}
	};

	short handDisplayController = 0;

	vector<Card> cardsOnBoard;

	bool playersTurn = true;
	short playerHealth = 30;
	char playerHealthBuffer[50];
	short roundNumber = 1;
	short playerMana = 1;
	char playerManaBuffer[10];
	
	if(TTF_Init() < 0)
		cout << "tff_init error: " << SDL_GetError() << endl;

	SDL_Color fontColor = { 255, 255, 255 };

	TTF_Font* playerHealthFont = TTF_OpenFont("resources/AovelSansRounded-rdDL.ttf", 100);
	sprintf(playerHealthBuffer, "%d", playerHealth);
	SDL_Surface* playerHealthSurface = TTF_RenderText_Blended_Wrapped(playerHealthFont, playerHealthBuffer, fontColor, 0);
	SDL_Texture* playerHealthTexture = SDL_CreateTextureFromSurface(renderer, playerHealthSurface);
	SDL_Rect healthTextDest;
	healthTextDest.x = (2*SCREEN_WIDTH)/3 - playerHealthSurface->w/2;
	healthTextDest.y = (4*SCREEN_HEIGHT)/5 - playerHealthSurface->h/2;
	healthTextDest.w = playerHealthSurface->w;
	healthTextDest.h = playerHealthSurface->h;
	SDL_RenderCopy(renderer, playerHealthTexture, NULL, &healthTextDest);
	TTF_CloseFont(playerHealthFont);
	SDL_FreeSurface(playerHealthSurface);

	TTF_Font* playerManaFont = TTF_OpenFont("resources/AovelSansRounded-rdDL.ttf", 100);
	sprintf(playerManaBuffer, "%d", playerMana);
	SDL_Surface* playerManaSurface = TTF_RenderText_Blended_Wrapped(playerManaFont, playerManaBuffer, fontColor, 0);
	SDL_Texture* playerManaTexture = SDL_CreateTextureFromSurface(renderer, playerManaSurface);
	SDL_Rect manaTextDest;
	manaTextDest.x = (2*SCREEN_WIDTH)/5 - playerManaSurface->w/2;
	manaTextDest.y = (4*SCREEN_HEIGHT)/5 - playerManaSurface->h/2;
	manaTextDest.w = playerManaSurface->w;
	manaTextDest.h = playerManaSurface->h;
	SDL_RenderCopy(renderer, playerManaTexture, NULL, &manaTextDest);
	TTF_CloseFont(playerManaFont);
	SDL_FreeSurface(playerManaSurface);

	TTF_Quit();

	vector<Entity> entity_array = {Entity(6200, 4500, 'b', background_image)};

	bool cardOnside = false;
	short cardOnSideIndex;
	int selectedIndex;

	Opponent opponent(renderer, 50);

	SDL_Event event;

	while(true)
	{
		mouse.update();
		mainMenuButton.update(mouse);
		testFunctionButton.update(mouse);
		scrollDeckup.update(mouse);
		scrollDeckDown.update(mouse);

		(!handFillers[handDisplayController][0].getIsVisible()) ? deck[handDisplayController][0].update(mouse) : handFillers[handDisplayController][0].update(mouse);
		(!handFillers[handDisplayController][1].getIsVisible()) ? deck[handDisplayController][1].update(mouse) : handFillers[handDisplayController][1].update(mouse);
		(!handFillers[handDisplayController][2].getIsVisible()) ? deck[handDisplayController][2].update(mouse) : handFillers[handDisplayController][2].update(mouse);
		(!handFillers[handDisplayController][3].getIsVisible()) ? deck[handDisplayController][3].update(mouse) : handFillers[handDisplayController][3].update(mouse);

		if (!(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON_LMASK))
			selectedIndex = -1;
		else
		{
			deck[handDisplayController][selectedIndex].moveCard(mouse);
		}


		for(Card& c : cardsOnBoard)
		{
			c.update(mouse);
		}

		opponent.updateCards(mouse);

		cardOnside = checkIfCardOnSide(deck[handDisplayController], cardOnSideIndex);
		
		while(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					window.cleanUp();
					return 0;
				case SDL_MOUSEBUTTONDOWN:
					for(int i = 0; i < 4; i++)
					{
						if(deck[handDisplayController][i].getIsSelected() && (deck[handDisplayController][i].getCardState() == inHand))
							selectedIndex = i;
					}
					break;
				case SDL_MOUSEBUTTONUP:
					if(event.button.button == SDL_BUTTON_LEFT)
					{
						if (mainMenuButton.getIsSelected())
						{
							cout << "main menu clicked" << endl;
							window.cleanUp();
							return 1;
						}

						if (testFunctionButton.getIsSelected())
						{
							cout << "test button clicked" << endl;
							/* test.damaged(renderer, 2); */
							opponent.playCard();
						}

						if (scrollDeckup.getIsSelected() && !cardOnside)
						{
							incrementHandDisplayController(handDisplayController);
						}

						if (scrollDeckDown.getIsSelected() && !cardOnside)
						{
							decrementHandDisplayController(handDisplayController);
						}

						if(cardOnside)
						{
							for (int i = 0; i < cardsOnBoard.size(); i++)
							{
								if(cardsOnBoard.at(i).getIsSelected())
								{
									cout << "card " << i << " clicked" << endl;
									replaceCard(deck[handDisplayController][cardOnSideIndex], cardsOnBoard, handFillers[handDisplayController][cardOnSideIndex], i);
								}
							}
							for(int i = 3; i >=0; i--)
							{
								if(deck[handDisplayController][i].getCardState() == onSide)
								{
									deck[handDisplayController][i].setStateInHand();
									deck[handDisplayController][i].resetCardPosition();
									break;
								}
							}

						}

						checkIfCardPlayed(deck[handDisplayController], cardsOnBoard, handFillers[handDisplayController]);
					}
					break;
				case SDL_MOUSEWHEEL:
					if(mouse.collision_rect.y < 700 || mouse.collision_rect.x > 1400 || mouse.collision_rect.x < 520)
						break;
					if(event.wheel.y > 0)
					{
						incrementHandDisplayController(handDisplayController);
					}
					else if(event.wheel.y < 0)
					{
						decrementHandDisplayController(handDisplayController);
					}
					break;
			}
		}
		
		window.clear();
		
		for(Entity& e : entity_array)
		{
			window.render(e);
		}

		SDL_RenderCopy(renderer, playerHealthTexture, NULL, &healthTextDest);
		SDL_RenderCopy(renderer, playerManaTexture, NULL, &manaTextDest);

		opponent.renderHealth();
		opponent.renderCards();
		opponent.renderMana();

		mainMenuButton.draw(renderer);
		testFunctionButton.draw(renderer);
		scrollDeckup.draw(renderer);
		scrollDeckDown.draw(renderer);
		

		for(Card& c : cardsOnBoard)
		{
			c.render(renderer);
		}

		for(int i = 0; i < 4; i++)
		{
			if(i != selectedIndex)
				(deck[handDisplayController][i].getCardState() != onBoard) ? deck[handDisplayController][i].render(renderer) : handFillers[handDisplayController][i].render(renderer);
		}
		if(selectedIndex > -1)
			(deck[handDisplayController][selectedIndex].getCardState() != onBoard) ? deck[handDisplayController][selectedIndex].render(renderer) : handFillers[handDisplayController][selectedIndex].render(renderer);


		mouse.draw(renderer);

		window.display();
	}
}

void checkIfCardPlayed(Card p_displayedCards[], vector<Card> &p_cardsOnBoard, DummyCard p_dummyCard[])
{
	(p_displayedCards[0].getCardY() < 700 && (p_displayedCards[0].getCardState() != onBoard)) ? playCard(p_displayedCards[0], p_cardsOnBoard, p_dummyCard[0]) : p_displayedCards[0].resetCardPosition();
	(p_displayedCards[1].getCardY() < 700 && (p_displayedCards[1].getCardState() != onBoard)) ? playCard(p_displayedCards[1], p_cardsOnBoard, p_dummyCard[1]) : p_displayedCards[1].resetCardPosition();
	(p_displayedCards[2].getCardY() < 700 && (p_displayedCards[2].getCardState() != onBoard)) ? playCard(p_displayedCards[2], p_cardsOnBoard, p_dummyCard[2]) : p_displayedCards[2].resetCardPosition();
	(p_displayedCards[3].getCardY() < 700 && (p_displayedCards[3].getCardState() != onBoard)) ? playCard(p_displayedCards[3], p_cardsOnBoard, p_dummyCard[3]) : p_displayedCards[3].resetCardPosition();
}

void playCard(Card &p_currentCard, vector<Card> &p_cardsOnBoard, DummyCard &p_dummyCard)
{
	if(p_currentCard.getCardState() == inHand)
	{
		if(p_currentCard.playCard(p_cardsOnBoard.size()))
		{
			p_cardsOnBoard.push_back(p_currentCard);
			p_dummyCard.setIsVisible();
			return;
		}
	}
}

void replaceCard(Card &p_currentCard, vector<Card> &p_cardsOnBoard, DummyCard &p_dummyCard, int p_positionToReplace)
{
	p_currentCard.playCard(p_positionToReplace);
	p_cardsOnBoard[p_positionToReplace] = p_currentCard;
	p_dummyCard.setIsVisible();
}	

void incrementHandDisplayController(short &handDisplayController)
{
	handDisplayController++;

	if(handDisplayController >= 3)
		handDisplayController = 0;
}

void decrementHandDisplayController(short &handDisplayController)
{
	handDisplayController--;

	if(handDisplayController < 0)
		handDisplayController = 2;
}

bool checkIfCardOnSide(Card p_displayedCards[], short &p_onsideCardIndex)
{
	for(int i = 0; i < 4; i++)
	{
		if(p_displayedCards[i].getCardState() == onSide)
		{
			p_onsideCardIndex = i;
			return true;
		}
	}
	return false;
}
