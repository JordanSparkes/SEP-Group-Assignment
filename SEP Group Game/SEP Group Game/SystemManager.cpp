#include "SystemManager.h"

SystemManager::SystemManager(SDL_Surface* x)
{
	//Pointer to the current game scene
	quit = false;
	screen = x;
	pCurrentScene = Splashscreen::instance();
	pCurrentScene->load(this);
	backgroundPos = 0;
}

void SystemManager::update(void)
{
	//Calls update on the current game scene
	pCurrentScene->update(this);
}

void SystemManager::changeScene(Scene* pNewScene)
{
	//Sets the pointer to the new scene
	pCurrentScene = pNewScene;
	//Calls load on the current scene
	pCurrentScene->load(this);
}

void SystemManager::redraw(float interpolation)
{
	//Calls draw on the current scene
	pCurrentScene->draw(this, interpolation);
	SDL_Flip(screen);
}

void SystemManager::applySurface(int x, int y, SDL_Surface* source)
{
	//Create a rect and store the coorinates in it
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;
	
	//draw the image to the screen surface at the desired coordinates
	SDL_BlitSurface(source, NULL, screen, &offset);
}

SDL_Surface* SystemManager::loadImage(char* filename)
{
	//load functions for images
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimisedImage = NULL;

	loadedImage = IMG_Load(filename);

	if(loadedImage != NULL)
	{
		optimisedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
	}

	return optimisedImage;
}

SDL_Surface* SystemManager::loadImageAlpha(char* filename)
{
	//function for loading an image with Alpha values
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimisedImage = NULL;

	loadedImage = IMG_Load(filename);

	if(loadedImage != NULL)
	{
		optimisedImage = SDL_DisplayFormatAlpha(loadedImage);
		SDL_FreeSurface(loadedImage);
	}

	return optimisedImage;
}

void SystemManager::setQuit()
{
	//Quit the game if this is ever set
	quit = true;
}

bool SystemManager::getQuit()
{
	return quit;
}

void SystemManager::setBackgroundPos(int bkPos)
{
	backgroundPos = bkPos;
}

int SystemManager::getBackgroundPos()
{
	return backgroundPos;
}