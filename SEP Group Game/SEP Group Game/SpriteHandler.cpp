#include "SpriteHandler.h"

SpriteHandler::SpriteHandler(void)
{
	xSpeed = 0; //Set the speed to 0 for the constructor.
	ySpeed = 0;

	spriteSheet = NULL; //set the pointers to null for the constructor.
}

SpriteHandler::~SpriteHandler(void)
{
	SDL_FreeSurface(spriteSheet); //use SDL to remove the SDL_Surface from memory upon deconstruction.

	spriteSheet = NULL; //Set pointers to null after use.
}

SDL_Surface* SpriteHandler::loadImage(char* dir)
{
	SDL_Surface* original; //Pointer to original, raw image. Should this be Predefined for constructor/destructor?
	SDL_Surface* optimized; //Pointer to SDl optimized image. Should this be Predefined for constructor/destructor?

	original = SDL_LoadBMP(dir); //Images have to be BMP for SDL as it is the raw, uncompressed format.

	if(original !=NULL) //If the image is not null (most likely case comes first).
	{
		optimized = SDL_DisplayFormat(original); //Optimize the image for SDL to use. I don't know what the difference between this and SDL_ConvertSurface is but apparantly DisplayFormat is better or does more.
		
		SDL_FreeSurface(original); //Remove the original unoptimized image from memory.
	}
	else //If the image is null.
	{
		printf("Error: The sprite you are trying to load does not exist."); //Error message as image has not been allocated. this is purely here for testing.
		exit(1);
	}
	return optimized; //Return the optimized version of the image.
}

SDL_Surface* SpriteHandler::loadImage(char* dir, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Surface* original;
	SDL_Surface* optimized;

	original = SDL_LoadBMP(dir);

	if(original != NULL)
	{
		optimized = SDL_DisplayFormat(original);

		Uint32 ignoreColour = SDL_MapRGB(optimized->format,r,g,b); //Create a unsigned 32bit int to define the colour of the bitmap to ignore.

		SDL_SetColorKey(optimized,SDL_SRCCOLORKEY,ignoreColour); //SDL sets any pixel that has the RGB value of the colour key to transparent.
		SDL_FreeSurface(original);
	}
	else
	{
		printf("Error: The sprite you are trying to load does not exist."); //Error message as image has not been allocated. this is purely here for testing.
		exit(1);
	}
	return optimized;
}

void SpriteHandler::setSpeed(int value)
{
	xSpeed = value; //Sets the speed to the value that has been passed in.
	ySpeed = value;
}

int SpriteHandler::getXSpeed()
{
	return xSpeed; //Gets the current speed value.
}

int SpriteHandler::getYSpeed()
{
	return ySpeed; //Gets the current speed value.
}

void SpriteHandler::setX(int X)
{
	rect.x = X; //Sets the X position of the sprite to the value that has been passed in.
}

void SpriteHandler::setY(int Y)
{
	rect.y = Y; //Sets the Y position of the sprite to the value that has been passed in.
}

int SpriteHandler::getX()
{
	return rect.x; //Gets the current X position value.
}

int SpriteHandler::getY()
{
	return rect.y; //Gets the current Y position value.
}

void SpriteHandler::setWidth(int W)
{
	rect.w = W; //Sets the Width of the sprites frame.
}

void SpriteHandler::setHeight(int H)
{
	rect.h = H; //Sets the height of the sprites frame.
}

int SpriteHandler::getWidth()
{
	return rect.w; //Gets the Width of the sprites frame.
}

int SpriteHandler::getHeight()
{
	return rect.h; //Gets the height of the sprites frame.
}

float SpriteHandler::getCenter() //The contents of this function are very temporary.
{
	return /*centerX;*/rect.x+(rect.w/2.0f); //Move these into the sprites creation code to save processing power.
	return /*centerY;*/rect.y+(rect.h/2.0f);
}

SDL_Rect* SpriteHandler::loadSprites(const int quant, const int offset, const int width, const int height)
{
	SDL_Rect* animations = new SDL_Rect[quant]; //Create an array containing the number of animations the sprite sheet contains.

	for(int i = 0; i < quant; i++) //Simple loop through the array.
	{
		animations[i].x = offset*width; //For the current animation set, the X value = the offset times the width.
		animations[i].y = i*height; //For the current animation set, the Y value = the current array number times the height.
		animations[i].w = width; //For the current animation set, the width = the predefined width value.
		animations[i].h = height; //For the current animation set, the height = the predefined height value.
	}
	return animations;
}