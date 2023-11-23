#include "play_game.hpp"

int playGame()
{
	Renderer window("Playing Game");

	Button mainMenuButton(window.loadTexture("resources/buttons.png"), 50, 115, 960 - 100, 50);
	Button testFunctionButton(window.loadTexture("resources/buttons.png"), 50, 115, 960 - 100, 150);
	Button scrollDeckup(window.loadTexture("resources/buttons.png"), 50, 115, 1500, 850);
	Button scrollDeckDown(window.loadTexture("resources/buttons.png"), 50, 115, 1500, 950);
	Button skip(window.loadTexture("resources/buttons.png"), 50, 115, 1800, SCREEN_HEIGHT/2);	

	Mouse mouse(window.loadTexture("resources/cursor.png"));

	SDL_Texture* backgroundImage = window.loadTexture("resources/game_background.png");

	SDL_Event event;

	while(true)
	{
		mouse.update();
		mainMenuButton.update(mouse);
		testFunctionButton.update(mouse);
		scrollDeckup.update(mouse);
		scrollDeckDown.update(mouse);
		skip.update(mouse);

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

		window.renderFullSource(mouse.entity);

		window.display();
	}
}
