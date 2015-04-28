#include "SDLLib.h"
#include "SystemManager.h"
#include "lootData.h"

//Screen Attributes
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int SCREEN_BPP = 32;

//Framerate regulating stuff
const int UPDATES_PER_SECOND = 60;
const int SKIP_TICKS = 1000 / UPDATES_PER_SECOND;
const int MAX_FRAMESKIP = 5;

int main(int argc, char* args[])
{
	damageDataIO();
	defenceDataIO();
	itemData();
	lootModifiers();
	//Start SDL
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	//Variables
	bool quit = false;
	int loops;
	float interpolation;
	Uint32 nextGameTick = SDL_GetTicks();

	SDL_Surface* screen = NULL;

	//SDL_WM_SetIcon(); Use this to set the little icon later
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	SDL_WM_SetCaption("SEP Game!", NULL);

	//Instantiate game objects
	SystemManager myManager(screen);

	//Main Game Loop
	while (myManager.getQuit() == false)
	{
		loops = 0;
		
		while( SDL_GetTicks() > nextGameTick && loops < MAX_FRAMESKIP && myManager.getQuit() == false)
		{
			myManager.update();
			
			nextGameTick += SKIP_TICKS;
			loops++;
		}
		
		if(myManager.getQuit() == false)
		{
			interpolation = float((SDL_GetTicks() + SKIP_TICKS - nextGameTick) / float(SKIP_TICKS));
			myManager.redraw(interpolation);
		}
	}

	TTF_Quit();
	SDL_Quit();
	return 0;
}
