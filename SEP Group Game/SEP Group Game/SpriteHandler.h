#ifndef _SPRITEHANDLER_H_
#define _SPRITEHANDLER_H_

#include "SDLLib.h"

class SpriteHandler
{
protected:
	SDL_Rect rect; //Container for position and size values.
	SDL_Rect* loadSprites(const int quant, const int offset, const int width, const int height); //function to define the sprite animations to load. quant is amount of frames, offset is which animation to load, width and height are the size of each frame;
	SDL_Surface* spriteSheet; //Pointer to the sprite sheet.

	int speed; //Value for movement speed of sprite. This may have to move into public later.

public:
	SpriteHandler(void); //Constructor
	virtual ~SpriteHandler(void); //Virtual destructor. virtual because other classes will use it.

	static SDL_Surface* loadImage(char* dir); //Static function to load and optimize an image from file.
	static SDL_Surface* loadImage(char* dir, Uint8 r, Uint8 g, Uint8 b); //Overloaded static funtion to load and optimize an image from file, using a defined RGB value as an ignore colour.

	void setSpeed(int); //Function to set the speed value.
	int getSpeed(); //Function to retreive the speed value.

	void setX(int); //Function to change X position of sprite.
	void setY(int); //Function to change Y position of sprite.
	int getX(); //Function to retreive X position of sprite.
	int getY(); //Function to retreive Y position of sprite.
	//It was considered that these 2 sets of functions be merged but as the sprites will always be walking either vertically or horizontally it seems quicker to process if they are seperate.

	void setWidth(int); //Function to set the sprite frames width.
	void setHeight(int); //Function to set the sprite frames height.
	int getWidth();  //Function to retreive the sprite frames width.
	int getHeight(); //Function to retreive the sprite frames height.

	float getCenter(); //Function to define the center of each sprite frame. This will be a single function unless the height and width values are different.

	bool windowBorders(); //Function to check if a sprite is going out of the screen. This function is temporary as the map will extend outside the window.

	virtual void init(SDL_Surface* spriteSheet, SDL_Rect* position) = 0; //Virtual function to initialize sprite stuff. To be used by other classes.
	virtual void blit(SDL_Surface* window) = 0; //Virtual function to draw sprite to screen. To be used by other classes.
	virtual void update(float scalar) = 0; //Virtual function to update sprite stuff. To be used by other classes.
};

#endif