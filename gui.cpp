#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "play_game.hpp"

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
	RenderWindow window("Main Menu");
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
