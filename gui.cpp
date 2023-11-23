#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "play_game.hpp"
#include "button.hpp"
#include "renderer.hpp"
#include "globals.hpp"
#include "entity.hpp"

using namespace std;

int mainMenu();

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

	short gameLoopValue = 2;

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
	Renderer window("Main Menu");

	SDL_Texture* backgroundTexture = window.loadTexture("resources/background.png");
	
	Button playButton(window.loadTexture("resources/buttons.png"), 50, 115, SCREEN_WIDTH/2 - 100, 500);
	Button exitButton(window.loadTexture("resources/buttons.png"), 50, 115, SCREEN_WIDTH/2 - 100, 600);

	Mouse mouse(window.loadTexture("resources/cursor.png"));

	vector<Entity> entities;
	entities.push_back(playButton.entity);
	entities.push_back(exitButton.entity);

	SDL_Event event;

	while(true)
	{
		mouse.update();
		playButton.update(mouse);
		exitButton.update(mouse);

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
						if (playButton.getIsSelected())
						{
							cout << "play clicked" << endl;
							window.cleanUp();
							return 2;
						}
						
						else if (exitButton.getIsSelected())
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

		window.renderBackground(backgroundTexture);

		window.render(exitButton.entity);
		window.render(playButton.entity);

		window.renderFullSource(mouse.entity);

		window.display();
	}
}
