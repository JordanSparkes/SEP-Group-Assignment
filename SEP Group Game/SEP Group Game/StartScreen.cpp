#include "StartScreen.h"
#include "SystemManager.h"

//Start Screen//////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
void StartScreen::load(SystemManager* pSM)
{
	//Here goes any images you need to load for this scene
	//You can use .png format, and use loadImageAlpha if you 
	//want to load a .png with transparency. 
	background = pSM->loadImage("images/mainmenu_background.png");

}

void StartScreen::update(SystemManager* pSM)
{
	//here goes any update code, as well as calling the function to
	//handle any events that happened.
	handleEvents(pSM);
}

void StartScreen::draw(SystemManager* pSM, float interpolation)
{
	//If you want to use the interpolation, simply add it to 
	//the position attibute of the item you wish to draw.
	//This should make it's movements appear smoother at
	//higher framerates. Then call applySurface, parameters are
	//the X position, the Y position, and what object you wish to draw.
	int viewPosition = backgroundPos + (interpolation);
	pSM->applySurface(viewPosition, 0, background);

}

void StartScreen::unload(SystemManager* pSM)
{
	//Here you want to free any memory you used in your scene.
	//This is called when you leave the scene.
	SDL_FreeSurface(background);
	SDL_FreeSurface(foreground);
	SDL_FreeSurface(blackbar);
}

StartScreen* StartScreen::instance()
{
	//This is for instantiating the scene in the first place.
	//Don't change this.
	static StartScreen instance;
	return &instance;
}

void StartScreen::handleEvents(SystemManager* pSM)
{
	//Do any event handling here.
	//I've left some example stuff in.
	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			pSM->setQuit();
		}
		if (event.type == SDL_MOUSEMOTION)
		{
			mouseX = event.motion.x;
			mouseY = event.motion.y;

		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
			}
		}
		if (event.type == SDL_MOUSEBUTTONUP)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				
			}
		}
	}
}