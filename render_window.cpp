#include <iostream>

#include "render_window.hpp"
#include "entity.hpp"
#include "globals.hpp"

using namespace std;

RenderWindow::RenderWindow(const char* p_title)//, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN); // && SDL_WINDOW_BORDERLESS

	if (window == NULL)
		cout << "Window failed to init: " << SDL_GetError() << endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(renderer, 1920, 1080);
}

SDL_Texture* RenderWindow::loadTexture(const char* filePath)
{
	SDL_Texture * texture = IMG_LoadTexture(renderer, filePath);

	if (texture == NULL)
		cout << "Failed to load texture: " << SDL_GetError() << endl;

	return texture;
}

SDL_Texture* RenderWindow::createTextureFromSurface(SDL_Surface* surface)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == NULL)
		cout << "Failed to create texture from surface: " << SDL_GetError() << endl;

	return texture;
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity)
{
	SDL_Rect source;
	source.x = p_entity.getCurrentFrame().x;
	source.y = p_entity.getCurrentFrame().y;
	source.w = p_entity.getCurrentFrame().w;
	source.h = p_entity.getCurrentFrame().h;

	SDL_Rect destination;
	destination.x = p_entity.getX() * 1;
	destination.y = p_entity.getY() * 1;
	destination.w = p_entity.getCurrentFrame().w * .25; 
	destination.h = p_entity.getCurrentFrame().h * .25;

	SDL_RenderCopy(renderer, p_entity.getTexture(), &source, &destination);
}

void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}

void RenderWindow::renderMouse(Mouse &mouse)
{
	SDL_RenderCopy(renderer, mouse.getTexture(), NULL, &mouse.imageRect);
}

void RenderWindow::renderButton(Button &button)
{
	SDL_RenderCopy(renderer, button.getTexture(), &button.source, &button.destination);
}

void RenderWindow::renderBackground(SDL_Texture* p_backgroundImage)
{
	SDL_RenderCopy(renderer, p_backgroundImage, NULL, NULL);
}

void RenderWindow::renderStat(SDL_Texture* texture, SDL_Rect &destination)
{
	SDL_RenderCopy(renderer, texture, NULL, &destination);
}

void RenderWindow::initializeCardTextures(Card &card)
{
	card.targetTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, BACKGROUND_ORIGIN_WIDTH, BACKGROUND_ORIGIN_HEIGHT);
	card.noNumbers = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, BACKGROUND_ORIGIN_WIDTH, BACKGROUND_ORIGIN_HEIGHT);

	if(card.targetTexture == NULL)
		cout << "Card render target not created: " << SDL_GetError() << endl;
	
	if(card.noNumbers == NULL)
		cout << "Card noNumbers not created: " << SDL_GetError() << endl;

	if(SDL_SetRenderTarget(renderer, card.noNumbers) < 0)
		cout << "Changing render target to noNumbers failed: " << SDL_GetError() << endl;

	SDL_Texture* cardBackground = IMG_LoadTexture(renderer, "resources/card.jpg");
	SDL_Rect backgroundSource;
	backgroundSource.x = 0;
	backgroundSource.y = 0;
	backgroundSource.w = BACKGROUND_ORIGIN_WIDTH;
	backgroundSource.h = BACKGROUND_ORIGIN_HEIGHT;
	SDL_RenderCopy(renderer, cardBackground, &backgroundSource, NULL);
	SDL_DestroyTexture(cardBackground);

	if(TTF_Init() < 0)
		cout << "tff_init error: " << SDL_GetError() << endl;

	SDL_Color fontColor = { 255, 255, 255 };

	TTF_Font* cardDescriptionFont = TTF_OpenFont("resources/AovelSansRounded-rdDL.ttf", 100);
	SDL_Surface* cardDescriptionSurface = TTF_RenderText_Blended_Wrapped(cardDescriptionFont, "Welcome to\nGigi Labs", fontColor, 0);
	SDL_Texture* cardDescriptionTexture = SDL_CreateTextureFromSurface(renderer, cardDescriptionSurface);
	SDL_Rect descriptionTextDest;
	descriptionTextDest.x = BACKGROUND_ORIGIN_WIDTH/2 - cardDescriptionSurface->w/2;
	descriptionTextDest.y = BACKGROUND_ORIGIN_HEIGHT/2;
	descriptionTextDest.w = cardDescriptionSurface->w;
	descriptionTextDest.h = cardDescriptionSurface->h;
	SDL_RenderCopy(renderer, cardDescriptionTexture, NULL, &descriptionTextDest);
	TTF_CloseFont(cardDescriptionFont);
	SDL_FreeSurface(cardDescriptionSurface);
	SDL_DestroyTexture(cardDescriptionTexture);

	TTF_Quit();

	drawCardDynamicStats(card);
}

void RenderWindow::drawCardDynamicStats(Card &card)
{
	if(SDL_SetRenderTarget(renderer, card.targetTexture) < 0)
		cout << "Changing render target to targetTexture failed: " << SDL_GetError() << endl;

	SDL_RenderCopy(renderer, card.noNumbers, NULL, NULL);

	if(TTF_Init() < 0)
		cout << "tff_init error: " << SDL_GetError() << endl;

	TTF_Font* cardStatsFont = TTF_OpenFont("resources/AovelSansRounded-rdDL.ttf", 200);

	char statTextBuffer[50];

	SDL_Color fontColor = { 255, 0, 0 };

	sprintf(statTextBuffer, "%d", card.getHealth());
	SDL_Surface* healthSurface = TTF_RenderText_Blended_Wrapped(cardStatsFont, statTextBuffer, fontColor, 0);
	SDL_Texture* healthTexture = SDL_CreateTextureFromSurface(renderer, healthSurface);
	SDL_Rect healthTextDest;
	healthTextDest.x = BACKGROUND_ORIGIN_WIDTH - 200;
	healthTextDest.y = BACKGROUND_ORIGIN_HEIGHT - 300;
	healthTextDest.w = healthSurface->w;
	healthTextDest.h = healthSurface->h;
	SDL_RenderCopy(renderer, healthTexture, NULL, &healthTextDest);
	SDL_FreeSurface(healthSurface);
	
	fontColor = { 255, 255, 255 };

	sprintf(statTextBuffer, "%d", card.getDamage());
	SDL_Surface* damageSurface = TTF_RenderText_Blended_Wrapped(cardStatsFont, statTextBuffer, fontColor, 0);
	SDL_Texture* damageTexture = SDL_CreateTextureFromSurface(renderer, damageSurface);
	SDL_Rect damageTextDest;
	damageTextDest.x = 100;
	damageTextDest.y = BACKGROUND_ORIGIN_HEIGHT - 300;
	damageTextDest.w = damageSurface->w;
	damageTextDest.h = damageSurface->h;
	SDL_RenderCopy(renderer, damageTexture, NULL, &damageTextDest);
	SDL_FreeSurface(damageSurface);
	
	sprintf(statTextBuffer, "%d", card.getCost());
	SDL_Surface* costSurface = TTF_RenderText_Blended_Wrapped(cardStatsFont, statTextBuffer, fontColor, 0);
	SDL_Texture* costTexture = SDL_CreateTextureFromSurface(renderer, costSurface);
	SDL_Rect costTextDest;
	costTextDest.x = BACKGROUND_ORIGIN_WIDTH/2 - costSurface->w/2;
	costTextDest.y = 0;
	costTextDest.w = costSurface->w;
	costTextDest.h = costSurface->h;
	SDL_RenderCopy(renderer, costTexture, NULL, &costTextDest);
	SDL_FreeSurface(costSurface);

	TTF_CloseFont(cardStatsFont);
	TTF_Quit();

	if(SDL_SetRenderTarget(renderer, NULL) < 0)
		cout << "Changing render target to default failed: " << SDL_GetError() << endl;
}

void RenderWindow::renderCard(Card &card)
{
	SDL_RenderCopy(renderer, card.targetTexture, NULL, &card.targetDest);
}

void RenderWindow::initializeDummyCardTextures(DummyCard &dummyCard)
{
	dummyCard.targetTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, BACKGROUND_ORIGIN_WIDTH, BACKGROUND_ORIGIN_HEIGHT);

	if(dummyCard.targetTexture == NULL)
		cout << "render target not created: " << SDL_GetError() << endl;

	if(SDL_SetRenderTarget(renderer, dummyCard.targetTexture) < 0)
		cout << "Changing render target to targetTexture failed: " << SDL_GetError() << endl;

	SDL_Texture* cardBackground = IMG_LoadTexture(renderer, "resources/dummy_card.jpg");
	SDL_Rect backgroundSource;
	backgroundSource.x = 0;
	backgroundSource.y = 0;
	backgroundSource.w = BACKGROUND_ORIGIN_WIDTH;
	backgroundSource.h = BACKGROUND_ORIGIN_HEIGHT;
	SDL_RenderCopy(renderer, cardBackground, &backgroundSource, NULL);
	SDL_DestroyTexture(cardBackground);

	if(TTF_Init() < 0)
		cout << "tff_init error: " << SDL_GetError() << endl;

	SDL_Color fontColor = { 255, 255, 255 };

	TTF_Font* cardDescriptionFont = TTF_OpenFont("resources/AovelSansRounded-rdDL.ttf", 100);
	SDL_Surface* cardDescriptionSurface = TTF_RenderText_Blended_Wrapped(cardDescriptionFont, "This is a\ndummy card", fontColor, 0);
	SDL_Texture* cardDescriptionTexture = SDL_CreateTextureFromSurface(renderer, cardDescriptionSurface);
	SDL_Rect descriptionTextDest;
	descriptionTextDest.x = BACKGROUND_ORIGIN_WIDTH/2 - cardDescriptionSurface->w/2;
	descriptionTextDest.y = BACKGROUND_ORIGIN_HEIGHT/2;
	descriptionTextDest.w = cardDescriptionSurface->w;
	descriptionTextDest.h = cardDescriptionSurface->h;
	SDL_RenderCopy(renderer, cardDescriptionTexture, NULL, &descriptionTextDest);
	TTF_CloseFont(cardDescriptionFont);
	SDL_FreeSurface(cardDescriptionSurface);
	SDL_DestroyTexture(cardDescriptionTexture);


	TTF_Font* cardStatsFont = TTF_OpenFont("resources/AovelSansRounded-rdDL.ttf", 200);
	char healthBuffer[16];
	short health = 5;
	sprintf(healthBuffer, "%d", health);
	SDL_Surface* healthSurface = TTF_RenderText_Blended_Wrapped(cardStatsFont, healthBuffer, fontColor, 0);
	SDL_Texture* healthTexture = SDL_CreateTextureFromSurface(renderer, healthSurface);
	SDL_Rect healthTextDest;
	healthTextDest.x = BACKGROUND_ORIGIN_WIDTH - 200;
	healthTextDest.y = BACKGROUND_ORIGIN_HEIGHT - 300;
	healthTextDest.w = healthSurface->w;
	healthTextDest.h = healthSurface->h;
	SDL_RenderCopy(renderer, healthTexture, NULL, &healthTextDest);
	TTF_CloseFont(cardStatsFont);
	SDL_FreeSurface(healthSurface);
	SDL_DestroyTexture(healthTexture);

	TTF_Quit();

	if(SDL_SetRenderTarget(renderer, NULL) < 0)
		cout << "Changing render target to default failed: " << SDL_GetError() << endl;
}

void RenderWindow::renderDummyCard(DummyCard &dummyCard)
{
	SDL_RenderCopy(renderer, dummyCard.targetTexture, NULL, &dummyCard.targetDest);
}

void RenderWindow::initializeOpponentCardTextures(OpponentCard &opponentCard)
{
	opponentCard.targetTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, BACKGROUND_ORIGIN_WIDTH, BACKGROUND_ORIGIN_HEIGHT);
	opponentCard.noNumbers = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, BACKGROUND_ORIGIN_WIDTH, BACKGROUND_ORIGIN_HEIGHT);
	
	if(opponentCard.targetTexture == NULL)
		cout << "render target not created: " << SDL_GetError() << endl;

	if(SDL_SetRenderTarget(renderer, opponentCard.noNumbers) < 0)
		cout << "Changing render target to noNumbers failed: " << SDL_GetError() << endl;

	SDL_Texture* cardBackground = IMG_LoadTexture(renderer, "resources/card.jpg");
	SDL_Rect backgroundSource;
	backgroundSource.x = 0;
	backgroundSource.y = 0;
	backgroundSource.w = BACKGROUND_ORIGIN_WIDTH;
	backgroundSource.h = BACKGROUND_ORIGIN_HEIGHT;
	SDL_RenderCopy(renderer, cardBackground, &backgroundSource, NULL);
	SDL_DestroyTexture(cardBackground);

	if(TTF_Init() < 0)
		cout << "tff_init error: " << SDL_GetError() << endl;

	SDL_Color fontColor = { 255, 255, 255 };

	TTF_Font* cardDescriptionFont = TTF_OpenFont("resources/AovelSansRounded-rdDL.ttf", 100);
	SDL_Surface* cardDescriptionSurface = TTF_RenderText_Blended_Wrapped(cardDescriptionFont, "Welcome to\nGigi Labs", fontColor, 0);
	SDL_Texture* cardDescriptionTexture = SDL_CreateTextureFromSurface(renderer, cardDescriptionSurface);
	SDL_Rect descriptionTextDest;
	descriptionTextDest.x = BACKGROUND_ORIGIN_WIDTH/2 - cardDescriptionSurface->w/2;
	descriptionTextDest.y = BACKGROUND_ORIGIN_HEIGHT/2;
	descriptionTextDest.w = cardDescriptionSurface->w;
	descriptionTextDest.h = cardDescriptionSurface->h;
	SDL_RenderCopy(renderer, cardDescriptionTexture, NULL, &descriptionTextDest);
	TTF_CloseFont(cardDescriptionFont);
	SDL_FreeSurface(cardDescriptionSurface);
	SDL_DestroyTexture(cardDescriptionTexture);

	TTF_Quit();

	drawOpponentCardDynamicStats(opponentCard);
}

void RenderWindow::drawOpponentCardDynamicStats(OpponentCard &card)
{
	if(SDL_SetRenderTarget(renderer, card.targetTexture) < 0)
		cout << "Changing render target to targetTexture failed: " << SDL_GetError() << endl;

	SDL_RenderCopy(renderer, card.noNumbers, NULL, NULL);

	if(TTF_Init() < 0)
		cout << "tff_init error: " << SDL_GetError() << endl;

	char statTextBuffer[50];

	SDL_Color fontColor = { 255, 0, 0 };

	TTF_Font* cardStatsFont = TTF_OpenFont("resources/AovelSansRounded-rdDL.ttf", 200);
	sprintf(statTextBuffer, "%d", card.getHealth());
	SDL_Surface* healthSurface = TTF_RenderText_Blended_Wrapped(cardStatsFont, statTextBuffer, fontColor, 0);
	SDL_Texture* healthTexture = SDL_CreateTextureFromSurface(renderer, healthSurface);
	SDL_Rect healthTextDest;
	healthTextDest.x = BACKGROUND_ORIGIN_WIDTH - 200;
	healthTextDest.y = BACKGROUND_ORIGIN_HEIGHT - 300;
	healthTextDest.w = healthSurface->w;
	healthTextDest.h = healthSurface->h;
	SDL_RenderCopy(renderer, healthTexture, NULL, &healthTextDest);
	SDL_FreeSurface(healthSurface);
	SDL_DestroyTexture(healthTexture);
	
	fontColor = { 255, 255, 255 };
	sprintf(statTextBuffer, "%d", card.getDamage());
	SDL_Surface* damageSurface = TTF_RenderText_Blended_Wrapped(cardStatsFont, statTextBuffer, fontColor, 0);
	SDL_Texture* damageTexture = SDL_CreateTextureFromSurface(renderer, damageSurface);
	SDL_Rect damageTextDest;
	damageTextDest.x = 100;
	damageTextDest.y = BACKGROUND_ORIGIN_HEIGHT - 300;
	damageTextDest.w = damageSurface->w;
	damageTextDest.h = damageSurface->h;
	SDL_RenderCopy(renderer, damageTexture, NULL, &damageTextDest);
	TTF_CloseFont(cardStatsFont);
	SDL_FreeSurface(damageSurface);
	/* SDL_DestroyTexture(damageTexture); */

	TTF_Quit();

	if(SDL_SetRenderTarget(renderer, NULL) < 0)
		cout << "Changing render target to default failed: " << SDL_GetError() << endl;
}

void RenderWindow::renderOpponentCard(OpponentCard &card)
{
	SDL_RenderCopy(renderer, card.targetTexture, NULL, &card.targetDest);
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}
