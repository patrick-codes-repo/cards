#include "play_game.hpp"
#include "card_constants.hpp"

int playGame()
{
	Renderer window("Playing Game");

	SDL_Texture* backgroundImage = window.loadTexture("resources/game_background.png");

	Button mainMenuButton(window.loadTexture("resources/buttons.png"), 50, 115, 960 - 100, 50);
	Button testFunctionButton(window.loadTexture("resources/buttons.png"), 50, 115, 960 - 100, 150);
	Button scrollDeckup(window.loadTexture("resources/buttons.png"), 50, 115, 1500, 850);
	Button scrollDeckDown(window.loadTexture("resources/buttons.png"), 50, 115, 1500, 950);
	Button skip(window.loadTexture("resources/buttons.png"), 50, 115, 1800, SCREEN_HEIGHT/2);	

	Mouse mouse(window.loadTexture("resources/cursor.png"));

	GameState gameState;
	gameState.playersTurn = true;
	gameState.roundNumber = 1;
	gameState.status = playersTurn;
	drawRoundNumber(gameState.roundNumber, gameState.roundNumberEntity, window);

	Player player;
	player.health = 30;
	player.mana = 1;
	drawPlayerHealth(player, window);
	drawPlayerMana(player, window);

	Squirt squirt(0);
	Bonerfart bonerfart(1);
	Brave brave(2);
    TestSpell testSpell(3);
	
	Mutt mutt(0);
	Common common(1);
	DoubleTrouble doubleTrouble(2);

	PlayerCard* allPlayerCards[][4] = {
		{&squirt, &bonerfart, &brave, &testSpell},
		{&mutt, &common, &doubleTrouble, NULL}
	};

	CardBase* playerDeck[2][4];

	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			if(allPlayerCards[i][j] == NULL)
			{
				playerDeck[i][j] = createNewDummy(j, window);
				continue;
			}

			playerDeck[i][j] = allPlayerCards[i][j];
			window.drawCombatCard(*allPlayerCards[i][j]);
		}
	}

	vector<PlayerCard*> playerBoard;
	vector<PlayerCard*> playersAttackingCards;

	vector<OpponentCard*> opponentBoard;

	CardBase* movingCard = NULL;

    int cardOnSideIndex = -1;

	int handController = 0;

	Player opponent;
	opponent.health = 50;
	opponent.mana = 1;
	drawOpponentHealth(opponent, window);
	drawOpponentMana(opponent, window);

	SDL_Event event;

	while(true)
	{
		mouse.update();
		mainMenuButton.update(mouse);
		testFunctionButton.update(mouse);
		scrollDeckup.update(mouse);
		scrollDeckDown.update(mouse);
		skip.update(mouse);

		for (int i = 0; i < 4; i++)
		{
			playerDeck[handController][i]->update(mouse);
		}
		
		for(PlayerCard* c : playerBoard)
		{
			c->update(mouse);
		}

		if (!(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON_LMASK))
		{
			if (movingCard != NULL)
				movingCard->resetCardPosition();
			movingCard = NULL;
		}

		if(movingCard != NULL)
			movingCard->moveCard(mouse);

		if(!gameState.playersTurn)
		{
			opponentBoard.push_back(createOpponentCard(opponentBoard.size()));
			endTurn(gameState);
			window.drawCombatCard(*opponentBoard.back());
		}
		
		for(OpponentCard* c : opponentBoard)
		{
			c->update(mouse);
		}

		if(gameState.status == playerAttacking)
		{
			if(playersAttackingCards.at(0)->state == attackedThisTurn)
			{
				damageOpponent(playersAttackingCards.at(0), playersAttackingCards.at(0)->target, opponent);
				drawAfterDamage(playerBoard, opponentBoard, player, opponent, window);
				cout << playersAttackingCards.at(0)->position << " has attacked" << endl;

				playersAttackingCards.erase(playersAttackingCards.begin());

				if(playersAttackingCards.size() > 0)
          playersAttackingCards.at(0)->playAttackAnimation();
				else
					endTurn(gameState);
			}
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
						if(playerDeck[handController][i]->getIsSelected()) 
						{
							movingCard = playerDeck[handController][i];
							break;
						}
					}
					for(PlayerCard* c : playerBoard)
					{
						if(c->getIsSelected())
						{
							movingCard = c;
							break;
						}
					}
					break;
				case SDL_MOUSEBUTTONUP:
					if(event.button.button == SDL_BUTTON_LEFT)
					{
						if(testFunctionButton.getIsSelected())
						{
							endRound(gameState, player, opponent, window, playerBoard);
						}
						
						if(skip.getIsSelected())
						{
							if(gameState.status == playerStartedAttack)
							{
                                playersAttackingCards.at(0)->playAttackAnimation();
								gameState.status = playerAttacking;
							}
							else
								endTurn(gameState);
						}

						if(mainMenuButton.getIsSelected())
						{
							cout << "main menu clicked" << endl;
							window.cleanUp();
							return 1;
						}

                        if(cardOnSideIndex != -1)
                        {
                            for(PlayerCard* c : playerBoard)
					        {
						        if(c->getIsSelected())
						        {
                                    cout << "Spell targeting card at position " << c->position << endl;
                                    playerDeck[handController][cardOnSideIndex]->state = dead;
								    playerDeck[handController][cardOnSideIndex] = createNewDummy(cardOnSideIndex, window);
							        break;
						        }
					        }
                            
                            if(playerDeck[handController][cardOnSideIndex]->state != dead)
                            {
                                playerDeck[handController][cardOnSideIndex]->state = inHand;
                            }
                            
                            cardOnSideIndex = -1;
                        }

						if(scrollDeckup.getIsSelected())
						{
							decrementHandController(handController);
						}

						if(scrollDeckDown.getIsSelected())
						{
							incrementHandController(handController);
						}

						if(movingCard != NULL)
						{
							if(movingCard->entity.destination.y < 400 && movingCard->state == onBoard)
							{
								playerBoard[movingCard->position]->target = NULL;

								for(OpponentCard* c : opponentBoard)
								{
									if(c->getIsSelected())
									{
										playerBoard[movingCard->position]->target = c;
										break;
									}
								}

								if(playerBoard[movingCard->position]->target == NULL)
								{
									cout << movingCard->position << " is attacking player face" << endl;	
								} else
									cout << movingCard->position << " is attacking " << playerBoard[movingCard->position]->target << endl;	

								playersAttackingCards.push_back(playerBoard[movingCard->position]);
								playersAttackingCards.back()->state = inAttackingGroup;

								gameState.status = playerStartedAttack;
							}

							if(movingCard->entity.destination.y < 700 && movingCard->state == inHand)
							{
                                if(movingCard->type == spell)
                                {
                                    cardOnSideIndex = movingCard->position;
                                    movingCard->state = onSide;
                                } else {
								    playerBoard.push_back(allPlayerCards[handController][movingCard->position]);
								    playerDeck[handController][movingCard->position] = createNewDummy(movingCard->position, window);
								    playerBoard.back()->state = onBoard;
								    playerBoard.back()->position = playerBoard.size() - 1;
                                }
							}
						}
					}
					break;
				case SDL_MOUSEWHEEL:
					if(mouse.collisionRect.y < 700 || mouse.collisionRect.x > 1400 || mouse.collisionRect.x < 520)
						break;

					if(event.wheel.y > 0)
					{
						incrementHandController(handController);
						break;
					}

					if(event.wheel.y < 0)
					{
						decrementHandController(handController);
					}
					break;
			}
		}
	
		window.clear();

		window.renderBackground(backgroundImage);

		window.render(mainMenuButton.entity);
		window.render(testFunctionButton.entity);
		window.render(scrollDeckup.entity);
		window.render(scrollDeckDown.entity);
		window.render(skip.entity);

		window.renderFullSource(player.healthEntity);
		window.renderFullSource(opponent.healthEntity);
		window.renderFullSource(opponent.manaEntity);
		window.renderFullSource(player.manaEntity);
		window.renderFullSource(gameState.roundNumberEntity);

		for (int i = 0; i < 4; i++)
		{
			window.renderFullSource(playerDeck[handController][i]->entity);
		}

		for(PlayerCard* c : playerBoard)
		{
			window.renderFullSource(c->entity);
		}

		for(OpponentCard* c : opponentBoard)
		{
			window.renderFullSource(c->entity);
		}

		if(movingCard != NULL)
		{
			window.renderFullSource(movingCard->entity);
		}

		window.renderFullSource(mouse.entity);

		window.display();
	}
}

void drawRoundNumber(int &roundNumber, Entity &roundNumberEntity, Renderer &window)
{
	if(TTF_Init() < 0)
		cout << "tff_init error: " << SDL_GetError() << endl;

	SDL_Color fontColor = {255, 255, 255};

	TTF_Font* roundNumberFont = TTF_OpenFont("resources/AovelSansRounded-rdDL.ttf", 100);
	char roundNumberBuffer[10];
	sprintf(roundNumberBuffer, "%d", roundNumber);
	SDL_Surface* roundNumberSurface = TTF_RenderText_Blended_Wrapped(roundNumberFont, roundNumberBuffer, fontColor, 0);
	roundNumberEntity.texture = window.createTextureFromSurface(roundNumberSurface);
	roundNumberEntity.destination.x = SCREEN_WIDTH - 50 - roundNumberSurface->w/2;
	roundNumberEntity.destination.y = (1*SCREEN_HEIGHT)/5 - roundNumberSurface->h/2;
	roundNumberEntity.destination.w = roundNumberSurface->w;
	roundNumberEntity.destination.h = roundNumberSurface->h;

	TTF_CloseFont(roundNumberFont);
	SDL_FreeSurface(roundNumberSurface);

	TTF_Quit();
}

void drawPlayerHealth(Player &player, Renderer &window)
{
	if(TTF_Init() < 0)
		cout << "tff_init error: " << SDL_GetError() << endl;

	SDL_Color fontColor = {255, 0, 0};

	TTF_Font* playerHealthFont = TTF_OpenFont("resources/AovelSansRounded-rdDL.ttf", 100);
	char playerHealthBuffer[10];
	sprintf(playerHealthBuffer, "%d", player.health);
	SDL_Surface* playerHealthSurface = TTF_RenderText_Blended_Wrapped(playerHealthFont, playerHealthBuffer, fontColor, 0);
	player.healthEntity.texture = window.createTextureFromSurface(playerHealthSurface);
	player.healthEntity.destination.x = (2*SCREEN_WIDTH)/3 - playerHealthSurface->w/2;
	player.healthEntity.destination.y = (4*SCREEN_HEIGHT)/5 - playerHealthSurface->h/2;
	player.healthEntity.destination.w = playerHealthSurface->w;
	player.healthEntity.destination.h = playerHealthSurface->h;

	TTF_CloseFont(playerHealthFont);
	SDL_FreeSurface(playerHealthSurface);

	TTF_Quit();
}

void drawPlayerMana(Player &player, Renderer &window)
{
	if(TTF_Init() < 0)
		cout << "tff_init error: " << SDL_GetError() << endl;

	SDL_Color fontColor = {0, 0, 255};

	TTF_Font* playerManaFont = TTF_OpenFont("resources/AovelSansRounded-rdDL.ttf", 100);
	char playerManaBuffer[10];
	sprintf(playerManaBuffer, "%d", player.mana);
	SDL_Surface* playerManaSurface = TTF_RenderText_Blended_Wrapped(playerManaFont, playerManaBuffer, fontColor, 0);
	player.manaEntity.texture = window.createTextureFromSurface(playerManaSurface);
	player.manaEntity.destination.x = (2*SCREEN_WIDTH)/5 - playerManaSurface->w/2;
	player.manaEntity.destination.y = (4*SCREEN_HEIGHT)/5 - playerManaSurface->h/2;
	player.manaEntity.destination.w = playerManaSurface->w;
	player.manaEntity.destination.h = playerManaSurface->h;

	TTF_CloseFont(playerManaFont);
	SDL_FreeSurface(playerManaSurface);

	TTF_Quit();
}

void drawOpponentHealth(Player &opponent, Renderer &window)
{
	if(TTF_Init() < 0)
		cout << "tff_init error: " << SDL_GetError() << endl;

	SDL_Color fontColor = {255, 0, 0};

	TTF_Font* opponentHealthFont = TTF_OpenFont("resources/AovelSansRounded-rdDL.ttf", 100);
	char opponentHealthBuffer[10];
	sprintf(opponentHealthBuffer, "%d", opponent.health);
	SDL_Surface* opponentHealthSurface = TTF_RenderText_Blended_Wrapped(opponentHealthFont, opponentHealthBuffer, fontColor, 0);
	opponent.healthEntity.texture = window.createTextureFromSurface(opponentHealthSurface);
	opponent.healthEntity.destination.x = SCREEN_WIDTH/3 - opponentHealthSurface->w/2;
	opponent.healthEntity.destination.y = SCREEN_HEIGHT/5 - opponentHealthSurface->h/2;
	opponent.healthEntity.destination.w = opponentHealthSurface->w;
	opponent.healthEntity.destination.h = opponentHealthSurface->h;

	TTF_CloseFont(opponentHealthFont);
	SDL_FreeSurface(opponentHealthSurface);

	TTF_Quit();
}

void drawOpponentMana(Player &opponent, Renderer &window)
{
	if(TTF_Init() < 0)
		cout << "tff_init error: " << SDL_GetError() << endl;

	SDL_Color fontColor = {0, 0, 255};

	TTF_Font* opponentManaFont = TTF_OpenFont("resources/AovelSansRounded-rdDL.ttf", 100);
	char opponentManaBuffer[10];
	sprintf(opponentManaBuffer, "%d", opponent.mana);
	SDL_Surface* opponentManaSurface = TTF_RenderText_Blended_Wrapped(opponentManaFont, opponentManaBuffer, fontColor, 0);
	opponent.manaEntity.texture = window.createTextureFromSurface(opponentManaSurface);
	opponent.manaEntity.destination.x = (2*SCREEN_WIDTH/3) - opponentManaSurface->w/2;
	opponent.manaEntity.destination.y = SCREEN_HEIGHT/5 - opponentManaSurface->h/2;
	opponent.manaEntity.destination.w = opponentManaSurface->w;
	opponent.manaEntity.destination.h = opponentManaSurface->h;

	TTF_CloseFont(opponentManaFont);
	SDL_FreeSurface(opponentManaSurface);

	TTF_Quit();
}

void incrementHandController(int &handController)
{
	handController++;

	if(handController > 1)
		handController = 0;
}

void decrementHandController(int &handController)
{
	handController--;

	if(handController < 0)
		handController = 1;
}

void endRound(GameState &gameState, Player &player, Player &opponent, Renderer &window, vector<PlayerCard*> playerBoard)
{
	gameState.roundNumber++;
	drawRoundNumber(gameState.roundNumber, gameState.roundNumberEntity, window);

	gameState.playersTurn = (gameState.roundNumber % 2 != 0);

	player.mana = gameState.roundNumber;
	drawPlayerMana(player, window);

	opponent.mana = gameState.roundNumber;
	drawOpponentMana(opponent, window);

  //set all playere cards to not attacked
	for(PlayerCard* c : playerBoard)
	{
    c->state = onBoard;
	}
}

void endTurn(GameState &gameState)
{
	gameState.playersTurn = !gameState.playersTurn;

	if(gameState.playersTurn)
	{
		gameState.status = playersTurn;
		return;
	}

	gameState.status = opponentsTurn;
}

CardBase* createNewDummy(int position, Renderer &window)
{
	DummyCard* temp = new DummyCard(position, window.loadTexture("resources/dummy_card.jpg"));
	return temp;
}

OpponentCard* createOpponentCard(int position)
{
	OCard1* temp = new OCard1(position); 
	return temp;
}

void damageOpponent(PlayerCard* attacker, OpponentCard* target, Player &opponent)
{
	if(target == NULL)
	{
		opponent.health -= attacker->damage;
		return;
	}

	target->health -= attacker->damage;
	attacker->health -= target->damage;
}

void drawAfterDamage(vector<PlayerCard*> playerBoard, vector<OpponentCard*> opponentBoard, Player &player, Player &opponent, Renderer &window)
{
	for(PlayerCard* c : playerBoard)
	{
		window.drawCombatCard(*c);
	}

	for(OpponentCard* c : opponentBoard)
	{
		window.drawCombatCard(*c);
	}

	drawPlayerHealth(player, window);
	drawOpponentHealth(opponent, window);
}
