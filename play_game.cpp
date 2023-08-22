#include "play_game.hpp"

SDL_Renderer* renderer; 

short handDisplayController = 0;
bool playersTurn = true;
short playerHealth = 30;
char playerHealthBuffer[50];
short roundNumber = 1;
char roundNumberBuffer[50];
short playerMana = 1;
char playerManaBuffer[10];

SDL_Texture* roundNumberTexture; 
SDL_Texture* playerHealthTexture; 
SDL_Texture* playerManaTexture; 
SDL_Rect roundNumberDest;
SDL_Rect healthTextDest;
SDL_Rect manaTextDest;

int playGame()
{
	RenderWindow window ("Playing Game");
	renderer = window.getRenderer();

	Mouse mouse (renderer);
	
	Button mainMenuButton(renderer, 50, 115, 960 - 100, 50);
	Button testFunctionButton(renderer, 50, 115, 960 - 100, 150);
	Button scrollDeckup(renderer, 50, 115, 1500, 850);
	Button scrollDeckDown(renderer, 50, 115, 1500, 950);
	Button skip(renderer, 50, 115, 1800, SCREEN_HEIGHT/2);

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

	vector<Card> cardsOnBoard;

	drawPlayerMana();
	drawPlayerHealth();
	drawRoundNumber();

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
		skip.update(mouse);

		updatePlayerHand(handFillers[handDisplayController], deck[handDisplayController], mouse);

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
							incrementHandDisplayController();
						}

						if (scrollDeckDown.getIsSelected() && !cardOnside)
						{
							decrementHandDisplayController();
						}

						if (skip.getIsSelected() && !cardOnside)
						{
							endRound();
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
					if(event.wheel.y > 0 && !cardOnside)
					{
						incrementHandDisplayController();
					}
					else if(event.wheel.y < 0 && !cardOnside)
					{
						decrementHandDisplayController();
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
		SDL_RenderCopy(renderer, roundNumberTexture, NULL, &roundNumberDest);

		opponent.renderHealth();
		opponent.renderCards();
		opponent.renderMana();

		mainMenuButton.draw(renderer);
		testFunctionButton.draw(renderer);
		scrollDeckup.draw(renderer);
		scrollDeckDown.draw(renderer);
		skip.draw(renderer);
		
		for(Card& c : cardsOnBoard)
		{
			c.render(renderer);
		}

		renderPlayerHand(deck[handDisplayController], handFillers[handDisplayController], selectedIndex);

		mouse.draw(renderer);

		window.display();

		for( int j = 0; j<3; j++)
		{
		for (int i = 0; i < 4; i++)
		{
			cout << "handFillers at " << j << ", " << i << " visible " << handFillers[j][i].getIsVisible() << endl;
			if (handFillers[j][i].getIsVisible() >1)
			exit(1);
		}
		}
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

void incrementHandDisplayController()
{
	handDisplayController++;

	if(handDisplayController >= 3)
		handDisplayController = 0;
}

void decrementHandDisplayController()
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

void updatePlayerHand(DummyCard p_currentHandFillers[], Card p_currentHandCards[], Mouse p_mouse)
{
	
	(!p_currentHandFillers[0].getIsVisible()) ? p_currentHandCards[0].update(p_mouse) : p_currentHandFillers[0].update(p_mouse);
	(!p_currentHandFillers[1].getIsVisible()) ? p_currentHandCards[1].update(p_mouse) : p_currentHandFillers[1].update(p_mouse);
	(!p_currentHandFillers[2].getIsVisible()) ? p_currentHandCards[2].update(p_mouse) : p_currentHandFillers[2].update(p_mouse);
	(!p_currentHandFillers[3].getIsVisible()) ? p_currentHandCards[3].update(p_mouse) : p_currentHandFillers[3].update(p_mouse);
}

void renderPlayerHand(Card p_currentHandCards[], DummyCard p_currentHandFillers[], int &p_selectedIndex)
{
	for(int i = 0; i < 4; i++)
	{
		if(i != p_selectedIndex)
			(p_currentHandCards[i].getCardState() != onBoard) ? p_currentHandCards[i].render(renderer) : p_currentHandFillers[i].render(renderer);
	}
	if(p_selectedIndex > -1)
		(p_currentHandCards[p_selectedIndex].getCardState() != onBoard) ? p_currentHandCards[p_selectedIndex].render(renderer) : p_currentHandFillers[p_selectedIndex].render(renderer);
}

void endRound()
{
	roundNumber++;
	playersTurn = (roundNumber % 2 != 0);
	drawRoundNumber();
}

void drawRoundNumber()
{
	if(TTF_Init() < 0)
		cout << "tff_init error: " << SDL_GetError() << endl;

	SDL_Color fontColor = {255, 255, 255};

	TTF_Font* roundNumberFont = TTF_OpenFont("resources/AovelSansRounded-rdDL.ttf", 100);
	sprintf(roundNumberBuffer, "%d", roundNumber);
	SDL_Surface* roundNumberSurface = TTF_RenderText_Blended_Wrapped(roundNumberFont, roundNumberBuffer, fontColor, 0);
	roundNumberTexture = SDL_CreateTextureFromSurface(renderer, roundNumberSurface);
	roundNumberDest.x = SCREEN_WIDTH - 50 - roundNumberSurface->w/2;
	roundNumberDest.y = (1*SCREEN_HEIGHT)/5 - roundNumberSurface->h/2;
	roundNumberDest.w = roundNumberSurface->w;
	roundNumberDest.h = roundNumberSurface->h;
	SDL_RenderCopy(renderer, roundNumberTexture, NULL, &roundNumberDest);
	TTF_CloseFont(roundNumberFont);
	SDL_FreeSurface(roundNumberSurface);

	TTF_Quit();
}

void drawPlayerHealth()
{
	if(TTF_Init() < 0)
		cout << "tff_init error: " << SDL_GetError() << endl;

	SDL_Color fontColor = {255, 255, 255};

	TTF_Font* playerHealthFont = TTF_OpenFont("resources/AovelSansRounded-rdDL.ttf", 100);
	sprintf(playerHealthBuffer, "%d", playerHealth);
	SDL_Surface* playerHealthSurface = TTF_RenderText_Blended_Wrapped(playerHealthFont, playerHealthBuffer, fontColor, 0);
	playerHealthTexture = SDL_CreateTextureFromSurface(renderer, playerHealthSurface);
	healthTextDest.x = (2*SCREEN_WIDTH)/3 - playerHealthSurface->w/2;
	healthTextDest.y = (4*SCREEN_HEIGHT)/5 - playerHealthSurface->h/2;
	healthTextDest.w = playerHealthSurface->w;
	healthTextDest.h = playerHealthSurface->h;
	SDL_RenderCopy(renderer, playerHealthTexture, NULL, &healthTextDest);
	TTF_CloseFont(playerHealthFont);
	SDL_FreeSurface(playerHealthSurface);

	TTF_Quit();
}

void drawPlayerMana()
{
	if(TTF_Init() < 0)
		cout << "tff_init error: " << SDL_GetError() << endl;

	SDL_Color fontColor = {255, 255, 255};


	TTF_Font* playerManaFont = TTF_OpenFont("resources/AovelSansRounded-rdDL.ttf", 100);
	sprintf(playerManaBuffer, "%d", playerMana);
	SDL_Surface* playerManaSurface = TTF_RenderText_Blended_Wrapped(playerManaFont, playerManaBuffer, fontColor, 0);
	playerManaTexture = SDL_CreateTextureFromSurface(renderer, playerManaSurface);
	manaTextDest.x = (2*SCREEN_WIDTH)/5 - playerManaSurface->w/2;
	manaTextDest.y = (4*SCREEN_HEIGHT)/5 - playerManaSurface->h/2;
	manaTextDest.w = playerManaSurface->w;
	manaTextDest.h = playerManaSurface->h;
	SDL_RenderCopy(renderer, playerManaTexture, NULL, &manaTextDest);
	TTF_CloseFont(playerManaFont);
	SDL_FreeSurface(playerManaSurface);

	TTF_Quit();
}