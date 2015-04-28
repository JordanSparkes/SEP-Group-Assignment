#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "Scene.h"
#include "SDL.h"
#include "SDL_image.h"

class SystemManager;		//Forward declaration of Scene Manager

class Splashscreen : public Scene
{
private:
	SDL_Surface* background;		//background image
	SDL_Surface* blackbar;			//black bar at the bottom of the screen
	SDL_Event event;			//SDL Event Handler
	int ypos;					//yPos of the blackbar, used for scrolling
	bool stopScrolling;			//used to tell the bar to stop scrolling
	int scroller;				//used to track the distance the bar has scrolled

public:
	Splashscreen()				//constructor
	{
		background = NULL; 
		blackbar = NULL;
		ypos = 150;
		stopScrolling = false;
		scroller = 0;
	};
	static Splashscreen* instance();		//pass an instance of the Splashscreen to the GameManager
	virtual void update(SystemManager*);		//Update the logic of this scene
	virtual void draw(SystemManager*, float);	//Draw the objects of this scene to the screen surface
	virtual void load(SystemManager*);		//load the assets required for this scene
	virtual void unload(SystemManager*);		//deallocate any memory used by this scene
};

#endif