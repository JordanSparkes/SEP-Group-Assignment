#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

//Includes
#include "SDL.h"
#include "SDL_image.h"
#include "Splashscreen.h"
#include "MainMenu.h"
#include "HighScore.h"
#include "StartScreen.h"

class Scene;						//Forward Declaration of Scene

class SystemManager	
{
private:
	Scene* pCurrentScene;			//Pointer to the current state
	SDL_Surface* screen;
	bool quit;
	int backgroundPos;

public:
	SystemManager();					//Constructor
	SystemManager(SDL_Surface*);		//Overloaded Constructor
	~SystemManager(){    }			//Deconstructor
	void update();					//Calls update on the scene
	void redraw(float);				//Calls draw on the scnee
	void applySurface(int, int, SDL_Surface*); //Draws to the screen
	SDL_Surface* loadImage(char*);	//Loads an image 
	SDL_Surface* loadImageAlpha(char* filename); //Load alpha image
	void setQuit();					//Set quit to true
	bool getQuit();					//Check the value of quit.
	void setBackgroundPos(int);		//make sure the background stays consistent
	int getBackgroundPos();			//Same as above
	void changeScene(Scene* pNewScene);	//Unloads current scene and loads the new scene
									//sets current scene to new scene.
};									

#endif
