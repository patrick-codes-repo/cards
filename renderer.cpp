#include <iostream>

#include "renderer.hpp"

using namespace std;

Renderer::Renderer(const char* p_title)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN); // && SDL_WINDOW_BORDERLESS

	if (window == NULL)
		cout << "Window failed to init: " << SDL_GetError() << endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(renderer, 1920, 1080);
}

SDL_Texture* Renderer::loadTexture(const char* filePath)
{
	SDL_Texture * texture = IMG_LoadTexture(renderer, filePath);

	if (texture == NULL)
		cout << "Failed to load texture: " << SDL_GetError() << endl;

	return texture;
}

SDL_Texture* Renderer::createTextureFromSurface(SDL_Surface* surface)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == NULL)
		cout << "Failed to create texture from surface: " << SDL_GetError() << endl;

	return texture;
}

void Renderer::clear()
{
	SDL_RenderClear(renderer);
}

void Renderer::render(Entity& p_entity)
{
	SDL_RenderCopy(renderer, p_entity.texture, &p_entity.source, &p_entity.destination);
}

void Renderer::renderFullSource(Entity& p_entity)
{
	SDL_RenderCopy(renderer, p_entity.texture, NULL, &p_entity.destination);
}

void Renderer::renderBackground(SDL_Texture* p_backgroundImage)
{
	SDL_RenderCopy(renderer, p_backgroundImage, NULL, NULL);
}

void Renderer::drawCombatCard(CombatCard &card)
{
	card.entity.texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, BACKGROUND_ORIGIN_WIDTH, BACKGROUND_ORIGIN_HEIGHT);
	card.noStats = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, BACKGROUND_ORIGIN_WIDTH, BACKGROUND_ORIGIN_HEIGHT);

	if(card.entity.texture == NULL)
		cout << "target texture not created: " << SDL_GetError() << endl;

	if(card.noStats == NULL)
		cout << "noStats not created: " << SDL_GetError() << endl;

	if(SDL_SetRenderTarget(renderer, card.noStats) < 0)
		cout << "Changing render target to noStats failed: " << SDL_GetError() << endl;

	SDL_Texture* cardBackground = IMG_LoadTexture(renderer, card.backgroundImagePath);
	SDL_Rect backgroundSource;
	backgroundSource.x = 0;
	backgroundSource.y = 0;
	backgroundSource.w = BACKGROUND_ORIGIN_WIDTH;
	backgroundSource.h = BACKGROUND_ORIGIN_HEIGHT;
	SDL_RenderCopy(renderer, cardBackground, &backgroundSource, NULL);
	SDL_DestroyTexture(cardBackground);

	if(TTF_Init() < 0)
		cout << "tff_init error: " << SDL_GetError() << endl;

	SDL_Color fontColor = {255, 255, 255};

	TTF_Font* cardDescriptionFont = TTF_OpenFont("resources/AovelSansRounded-rdDL.ttf", 100);

	SDL_Surface* cardDescriptionSurface = TTF_RenderText_Blended_Wrapped(cardDescriptionFont, card.description, fontColor, 0);

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

	if(SDL_SetRenderTarget(renderer, NULL) < 0)
		cout << "Changing render target to default failed: " << SDL_GetError() << endl;

	drawCombatCardStats(card);
}

void Renderer::drawCombatCardStats(CombatCard &card)
{
	if(SDL_SetRenderTarget(renderer, card.entity.texture) < 0)
		cout << "Changing render target to targetTexture failed: " << SDL_GetError() << endl;

	SDL_RenderCopy(renderer, card.noStats, NULL, NULL);

	if(TTF_Init() < 0)
		cout << "tff_init error: " << SDL_GetError() << endl;

	SDL_Color fontColor = {255, 0, 0};

	TTF_Font* cardStatsFont = TTF_OpenFont("resources/AovelSansRounded-rdDL.ttf", 200);

	char cardHealthBuffer[10];
	sprintf(cardHealthBuffer, "%d", card.health);
	SDL_Surface* healthSurface = TTF_RenderText_Blended_Wrapped(cardStatsFont, cardHealthBuffer, fontColor, 0);

	SDL_Texture* healthTexture = SDL_CreateTextureFromSurface(renderer, healthSurface);

	SDL_Rect healthTextDest;
	healthTextDest.x = BACKGROUND_ORIGIN_WIDTH - 200;
	healthTextDest.y = BACKGROUND_ORIGIN_HEIGHT - 300;
	healthTextDest.w = healthSurface->w;
	healthTextDest.h = healthSurface->h;

	SDL_RenderCopy(renderer, healthTexture, NULL, &healthTextDest);

	SDL_FreeSurface(healthSurface);
	SDL_DestroyTexture(healthTexture);
	
	fontColor = {255, 255, 255};

	char cardDamageBuffer[10];
	sprintf(cardDamageBuffer, "%d", card.damage);
	SDL_Surface* damageSurface = TTF_RenderText_Blended_Wrapped(cardStatsFont, cardDamageBuffer, fontColor, 0);

	SDL_Texture* damageTexture = SDL_CreateTextureFromSurface(renderer, damageSurface);

	SDL_Rect damageTextDest;
	damageTextDest.x = 100;
	damageTextDest.y = BACKGROUND_ORIGIN_HEIGHT - 300;
	damageTextDest.w = damageSurface->w;
	damageTextDest.h = damageSurface->h;

	SDL_RenderCopy(renderer, damageTexture, NULL, &damageTextDest);

	SDL_FreeSurface(damageSurface);
	SDL_DestroyTexture(damageTexture); 

	char cardCostBuffer[10];
	sprintf(cardCostBuffer, "%d", card.cost);
	SDL_Surface* costSurface = TTF_RenderText_Blended_Wrapped(cardStatsFont, cardCostBuffer, fontColor, 0);

	SDL_Texture* costTexture = SDL_CreateTextureFromSurface(renderer, costSurface);

	SDL_Rect costTextDest;
	costTextDest.x = BACKGROUND_ORIGIN_WIDTH/2 - costSurface->w/2;
	costTextDest.y = 0;
	costTextDest.w = costSurface->w;
	costTextDest.h = costSurface->h;

	SDL_RenderCopy(renderer, costTexture, NULL, &costTextDest);

	SDL_FreeSurface(costSurface);
	SDL_DestroyTexture(costTexture);

	TTF_CloseFont(cardStatsFont);
	TTF_Quit();

	if(SDL_SetRenderTarget(renderer, NULL) < 0)
		cout << "Changing render target to default failed: " << SDL_GetError() << endl;
}

void Renderer::display()
{
	SDL_RenderPresent(renderer);
}

void Renderer::cleanUp()
{
	SDL_DestroyWindow(window);
}
