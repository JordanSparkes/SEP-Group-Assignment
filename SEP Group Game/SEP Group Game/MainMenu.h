#ifndef MAINMENU_H
#define MAINMENU_H
 
#include "Scene.h"
#include "SDL.h"
#include "SDL_image.h"
#include "MButton.h"

class SystemManager;		//Forward declaration of Scene Manager

class MainMenu : public Scene
{
private:
	SDL_Surface* background;	//Background image
	SDL_Surface* blackbar;		//Blackbar at the bottom of the sreen
	MButton* levelSelect;		//Button to navigate to the LevelSelect screen
	MButton* highscore;			//Button to navigate to the Highscore screen
	MButton* quitgame;			//Button to quit the game
	SDL_Event event;			//SDL event handler
	int backgroundPos;			//track the background position
	bool movingLeft;			//set which direction the background scrolls in
	int counter;				//gate the speed at which the background scrolls
	int mouseX;					//track the mouse X position
	int mouseY;					//track the mouse Y position

public:
	MainMenu()			//Constructor
	{
		background = NULL;
		blackbar = NULL;
		backgroundPos = 0;
		movingLeft = true;
		counter = 0;
	};									//functions derived from Scene superclass
	static MainMenu* instance();			//pass an instance of this class to the Scene Manager
	virtual void update(SystemManager*);		//update the logic of the MainMenu objects
	virtual void draw(SystemManager*, float);	//Draw the objects of this scene to the screen surface
	virtual void load(SystemManager*);		//load the assets required for this scene
	virtual void unload(SystemManager*);		//deallocate any memory used by this scene
	void handleEvents(SystemManager*);		//Poll the SDL event structure for events and handle them
};

#endif