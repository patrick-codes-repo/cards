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
bool playerSkipped = false;
bool opponentSkipped = false;

SDL_Texture* roundNumberTexture; 
SDL_Texture* playerHealthTexture; 
SDL_Texture* playerManaTexture; 
SDL_Rect roundNumberDest;
SDL_Rect healthTextDest;
SDL_Rect manaTextDest;
Opponent* opponent;

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
		{Card(renderer, 0, 0, 1, 0), Card(renderer, 0, 1, 0, 0), Card(renderer, 0, 2, 2, 2), Card(renderer, 0, 3, 0, 0)},
		{Card(renderer, 1, 0, 2, 2), Card(renderer, 1, 1, 1, 2), Card(renderer, 1, 2, 1, 1), Card(renderer, 1, 3, 0, 0)},
		{Card(renderer, 2, 0, 2, 3), Card(renderer, 2, 1, 2, 2), Card(renderer, 2, 2, 3, 2), Card(renderer, 2, 3, 0, 0)} 
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

	/* Opponent* opponent;//;(renderer, 50); */
	opponent = new Opponent(renderer, 50);

	SDL_Event event;

	while(true)
	{
		mouse.update();
		mainMenuButton.update(mouse);
		testFunctionButton.update(mouse);
		scrollDeckup.update(mouse);
		scrollDeckDown.update(mouse);
		skip.update(mouse);

		if(playerSkipped && opponentSkipped)
			endRound();

		updatePlayerHand(handFillers[handDisplayController], deck[handDisplayController], mouse);

		for(Card& c : cardsOnBoard)
		{
			c.update(mouse);
		}

		if (!(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON_LMASK))
			selectedIndex = -1;

		if(selectedIndex > -1 && selectedIndex < 10)
			deck[handDisplayController][selectedIndex].moveCard(mouse);

		if(selectedIndex >= 10)
			cardsOnBoard[selectedIndex - 10].moveCard(mouse);

		opponent->updateCards(mouse);

		cardOnside = checkIfCardOnSide(deck[handDisplayController], cardOnSideIndex);

		if(!playersTurn)
		{
			if(opponent->playCard())
			{
				playerSkipped = false;
				opponentSkipped = false;
			}
			else
				opponentSkipped = true;
			/* endRound(); */
			endTurn();
		}	

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
						{
							selectedIndex = i;
							break;
						}
					}
					for(int i = 0; i < cardsOnBoard.size(); i++)
					{
						if(cardsOnBoard[i].getIsSelected()) 
							selectedIndex = i + 10; 
					}
					if(cardOnside)
						cardOnSideHandler(cardOnSideIndex, cardsOnBoard, deck[handDisplayController], handFillers[handDisplayController]);
					break;
				case SDL_MOUSEBUTTONUP:
					if(event.button.button == SDL_BUTTON_LEFT)
					{
						if (mainMenuButton.getIsSelected() && selectedIndex < 0)
						{
							cout << "main menu clicked" << endl;
							window.cleanUp();
							return 1;
						}

						if (testFunctionButton.getIsSelected() && selectedIndex < 0)
						{
							cout << "test button clicked" << endl;
							/* test.damaged(renderer, 2); */
							opponent->playCard();
						}

						if (scrollDeckup.getIsSelected() && !cardOnside && selectedIndex < 0)
						{
							decrementHandDisplayController();
						}

						if (scrollDeckDown.getIsSelected() && !cardOnside && selectedIndex < 0)
						{
							incrementHandDisplayController();
						}

						if (skip.getIsSelected() && !cardOnside && selectedIndex < 0)
						{
							/* endRound(); */
							playerSkipped = true;
							endTurn();
						}

						if(selectedIndex > -1 && selectedIndex < 10)
							checkIfCardPlayed(deck[handDisplayController][selectedIndex], cardsOnBoard, handFillers[handDisplayController][selectedIndex]);
						if(selectedIndex >= 10)
							checkIfCardAttacked(cardsOnBoard[selectedIndex - 10]);
					}
					break;
				case SDL_MOUSEWHEEL:
					if(mouse.getCollisionRectY() < 700 || mouse.getCollisionRectX() > 1400 || mouse.getCollisionRectX() < 520)
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

		opponent->renderHealth();
		opponent->renderCards();
		opponent->renderMana();

		mainMenuButton.draw(renderer);
		testFunctionButton.draw(renderer);
		scrollDeckup.draw(renderer);
		scrollDeckDown.draw(renderer);
		skip.draw(renderer);
		
		renderCardsOnBoard(cardsOnBoard, selectedIndex);
		renderPlayerHand(deck[handDisplayController], handFillers[handDisplayController], selectedIndex);
		renderSelectedCard(selectedIndex, cardsOnBoard, deck[handDisplayController]);

		mouse.draw(renderer);

		window.display();
	}
}

void checkIfCardPlayed(Card &selectedCard, vector<Card> &p_cardsOnBoard, DummyCard &p_dummyCard)
{
	if(selectedCard.getCost() > playerMana)
	{
		selectedCard.resetCardPosition();
		return;
	}

	(selectedCard.getCardY() < 700 && (selectedCard.getCardState() != onBoard)) ? playCard(selectedCard, p_cardsOnBoard, p_dummyCard) : selectedCard.resetCardPosition();
}

void playCard(Card &selectedCard, vector<Card> &p_cardsOnBoard, DummyCard &p_dummyCard)
{
	if(selectedCard.getCardState() == inHand)
	{
		if(selectedCard.playCard(p_cardsOnBoard.size()))
		{
			playerMana -= selectedCard.getCost();
			drawPlayerMana();
			p_cardsOnBoard.push_back(selectedCard);
			p_dummyCard.setIsVisible();
			playerSkipped = false;
			opponentSkipped = false;
			endTurn();
			return;
		}
	}
}

void checkIfCardAttacked(Card &selectedCard)
{
	(selectedCard.getCardY() < 400 && (selectedCard.getCardState() == onBoard)) ? attack(selectedCard) : selectedCard.resetCardPosition();
}

void attack(Card &selectedCard)
{
	if(opponent->getSelectedCardIndex() > -1)
	{
		cout << "attacking opponent card " << opponent->getSelectedCardIndex() << endl;
		return;
	}
	selectedCard.attack();
}

void replaceCard(Card &p_currentCard, vector<Card> &p_cardsOnBoard, DummyCard &p_dummyCard, int p_positionToReplace)
{
	p_currentCard.playCard(p_positionToReplace);
	playerMana -= p_currentCard.getCost();
	drawPlayerMana();
	p_cardsOnBoard[p_positionToReplace] = p_currentCard;
	p_dummyCard.setIsVisible();
}	

void playSpell(Card &p_currentCard, vector<Card> &p_cardsOnBoard, DummyCard &p_dummyCard)
{
	/* p_currentCard.playCard(p_positionToReplace); */
	playerMana -= p_currentCard.getCost();
	drawPlayerMana();
	/* p_cardsOnBoard[p_positionToReplace] = p_currentCard; */
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
			(!p_currentHandFillers[i].getIsVisible()) ? p_currentHandCards[i].render(renderer) : p_currentHandFillers[i].render(renderer);
			/* (p_currentHandCards[i].getCardState() != onBoard) ? p_currentHandCards[i].render(renderer) : p_currentHandFillers[i].render(renderer); */
	}
}

void renderCardsOnBoard(vector<Card> p_cardsOnBoard, int &p_selectedIndex)
{
	for(int i = 0; i < p_cardsOnBoard.size(); i++)
	{
		if(i != p_selectedIndex - 10)
			p_cardsOnBoard[i].render(renderer); 
	}
}

void renderSelectedCard(int &p_selectedIndex, vector<Card> p_cardsOnBoard, Card p_currentHandCards[])
{
	if (p_selectedIndex < 0)
		return;

	(p_selectedIndex < 10) ? p_currentHandCards[p_selectedIndex].render(renderer) : p_cardsOnBoard[p_selectedIndex - 10].render(renderer);
}

void endTurn()
{
	playersTurn = !playersTurn;
}

void endRound()
{
	playerSkipped = false;
	opponentSkipped = false;

	roundNumber++;
	playersTurn = (roundNumber % 2 != 0);
	drawRoundNumber();
	
	playerMana = roundNumber;
	drawPlayerMana();

	opponent->setMana(roundNumber);
	opponent->drawMana();
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

void cardOnSideHandler(short &cardOnSideIndex, vector<Card> &cardsOnBoard, Card currentHand[], DummyCard p_currentHandFillers[])
{
	bool cardOnBoardReplaced = false;

	if(currentHand[cardOnSideIndex].getCardType() == spell)
	{
		for (int i = 0; i < cardsOnBoard.size(); i++)
		{
			if(cardsOnBoard.at(i).getIsSelected())
			{
				cout << "spell casted at player card " << i << endl;
				playSpell(currentHand[cardOnSideIndex], cardsOnBoard, p_currentHandFillers[cardOnSideIndex]);
				return;
			}
		}
		if(opponent->getSelectedCardIndex() > -1)
		{
			cout << "spell casted at opponent card " << opponent->getSelectedCardIndex() << endl;
			playSpell(currentHand[cardOnSideIndex], cardsOnBoard, p_currentHandFillers[cardOnSideIndex]);
		}
	}

	for (int i = 0; i < cardsOnBoard.size(); i++)
	{
		if(cardsOnBoard.at(i).getIsSelected())
		{
			cout << "card " << i << " replaced" << endl;
			replaceCard(currentHand[cardOnSideIndex], cardsOnBoard, p_currentHandFillers[cardOnSideIndex], i);
			cardOnBoardReplaced = true;
			break;
		}
	}
	if(!cardOnBoardReplaced)
	{
		currentHand[cardOnSideIndex].setStateInHand();
		currentHand[cardOnSideIndex].resetCardPosition();
	}
}
