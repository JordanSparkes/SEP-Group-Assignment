#include "Splashscreen.h"
#include "SystemManager.h"

//Splashscreen Scene //////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void Splashscreen::load(SystemManager* pSM)
{
	background = pSM->loadImage("images/splashscreen_background.png");
	blackbar = pSM->loadImage("images/splashscreen_blackbar.png");
}

void Splashscreen::update(SystemManager* pSM)
{
	//Scrolls the blackbar up, then goes to Main Menu
	if(scroller >= 1)
	{
		ypos--;
		scroller = 0;
		if(ypos <= 10)
		{
			unload(pSM);
			pSM->changeScene(StartScreen::instance());
		}
	}
	else
	{
		scroller++;
	}
	
	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			unload(pSM);
			pSM->setQuit();
		}
	}
}

void Splashscreen::draw(SystemManager* pSM, float interpolation)
{
	//Draws to the screen
	pSM->applySurface(-1, 0, background);
	pSM->applySurface(0, ypos, blackbar);
}

void Splashscreen::unload(SystemManager* pSM)
{
	//Deallocates the surfaces when leaving the scene
	SDL_FreeSurface(background);
	SDL_FreeSurface(blackbar);
}

Splashscreen* Splashscreen::instance()
{
	//returns as instance of Splashscreen scene
	static Splashscreen instance;
	return &instance;
}
