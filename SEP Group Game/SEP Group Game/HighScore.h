#ifndef HIGHSCORE_H
#define HIGHSCORE_H

//includes
#include "Scene.h"
#include "SDL.h"
#include "SDL_image.h"
#include "MButton.h"

class SystemManager;		//Forward declaration of Scene Manager

class HighScore : public Scene
{
private:
	SDL_Surface* background;	//Background  image
	SDL_Surface* foreground;	//foreground image
	SDL_Surface* blackbar;		//Bar at the bottom of the screen
	SDL_Event event;			//Event tracker
	MButton* backButton;		//Back button, return to main menu
	int backgroundPos;			//keep track of the scrolling background position
	int counter;				//used to gate the speed at which the background scrolls
	bool movingLeft;			//sets the direction that the background scrolls
	int mouseX;					//store the mouse x pos
	int mouseY;					//store the mouse y pos
public:
	HighScore()					//constructor
	{
		background = NULL;
		foreground = NULL;
		backgroundPos = 0;
		movingLeft = true;
		counter = 0;
	};										//functions derived from Scene superclass
	static HighScore* instance();			//returns an instance of Highscore, used by the game manager
	virtual void update(SystemManager*);		//update the logic of the Highscore scene
	virtual void draw(SystemManager*, float);	//draw the content of the Highscore scene to the screen
	virtual void load(SystemManager*);		//load the assets requried for this scene
	virtual void unload(SystemManager*);		//deallocate any memory when you leave the scene
	void handleEvents(SystemManager*);		//Poll the SDL event structure for events
};

#endif