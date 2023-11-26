#include "play_game.hpp"

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

	Player player;
	player.health = 30;
	player.mana = 1;
	drawPlayerHealth(player, window);
	drawPlayerMana(player, window);

	DummyCard test1(0, window.loadTexture("resources/dummy_card.jpg"));
	DummyCard test2(1, window.loadTexture("resources/dummy_card.jpg"));
	PlayerCard test3(2, "resources/card.jpg");
	window.drawCombatCard(test3);

	CardBase* playerDeck[] = {&test1, &test2, &test3};

	CardBase* movingCard = NULL;

	Player opponent;
	opponent.health = 50;
	opponent.mana = 1;
	drawOpponentHealth(opponent, window);
	drawOpponentMana(opponent, window);

	int roundNumber = 0;
	Entity roundNumberEntity;
	drawRoundNumber(roundNumber, roundNumberEntity, window);

	SDL_Event event;

	while(true)
	{
		mouse.update();
		mainMenuButton.update(mouse);
		testFunctionButton.update(mouse);
		scrollDeckup.update(mouse);
		scrollDeckDown.update(mouse);
		skip.update(mouse);

		for (int i = 0; i < 3; i++)
		{
			playerDeck[i]->update(mouse);
		}

		if (!(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON_LMASK))
		{
			if (movingCard != NULL)
				movingCard->resetCardPosition();
			movingCard = NULL;
		}

		if(movingCard != NULL)
			movingCard->moveCard(mouse);

		while(SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					window.cleanUp();
					return 0;
				case SDL_MOUSEBUTTONDOWN:
					for(int i = 0; i < 3; i++)
					{
						if(playerDeck[i]->getIsSelected()) 
						{
							movingCard = playerDeck[i];
							break;
						}
					}
				case SDL_MOUSEBUTTONUP:
					if(event.button.button == SDL_BUTTON_LEFT)
					{
						if (mainMenuButton.getIsSelected())
						{
							cout << "main menu clicked" << endl;
							window.cleanUp();
							return 1;
						}
					}
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
		window.renderFullSource(roundNumberEntity);

		for (int i = 0; i < 3; i++)
		{
			window.renderFullSource(playerDeck[i]->entity);
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
