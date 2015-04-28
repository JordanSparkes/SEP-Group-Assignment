#ifndef MBUTTON_H
#define MBUTTON_H

#include "SDL.h"
#include "SDL_ttf.h"

class SystemManager;		//Forward declaration of Scene Manager

class MButton
{
private:
	int x;				//Button x position
	int y;				//button y position
	int downPos;		//the position the button moves to when the mouse is clicked on it
	int upPos;			//the default position of the button
	int height;			//the height of the button, for checking if the mouse is over it
	int width;			//the width of the button
	bool mouseOver;		//track whether the mouse is over the button
	bool mouseD;		//track whether the mouse is down over the button
	int textXPos;		//x position of the text
	int textYPos;		//y position of the text
	
	TTF_Font* font;			//font used for the button text
	SDL_Color textColour;	//colour of the font
	SDL_Surface* text;		//surface to hold the text for the object
	SDL_Surface* otherText;	//used if the text requires two layers
	SDL_Surface* textDown;	//change text colour if button is down
	SDL_Surface* otherTextDown;	//change bottom layer text colour if button is down
	SDL_Surface* buttonOn;		//draw this if button is hovered over by the mouse
	SDL_Surface* buttonOff;		//draw this if mouse is outside the button
	SDL_Surface* toDraw;	//tracks which button image to draw

public:
	MButton(int xPos, int yPos, char* buttonText, char* otherButtonText, SystemManager* pSM);	//constructor
	~MButton();	//desctructor
	void loadImages(SystemManager* pSM);	//used to load any assets required by this button
	void draw(SystemManager* pSM);		//used to draw the button to the screen surface
	void mouseEvent(int mouseX, int mouseY);		//used to handle mouse events
	void mouseDown();		//check if mouse is down over the button
	bool mouseUp();			//check if mouse is up over the button
};

#endif