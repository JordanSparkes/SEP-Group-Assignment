#include "SpriteHandler.h"

SpriteHandler::SpriteHandler(void)
{
	speed = 0; //Set the speed to 0 for the constructor.

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
		optimized = SDL_DisplayFormat(original); //Optimize the image for SDL to use)
		
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
	speed = value; //Sets the speed to the value that has been passed in.
}

int SpriteHandler::getSpeed()
{
	return speed; //Gets the current speed value.
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
	return rect.x+(rect.w/2.0f); //Move these into the sprites creation code to save processing power.
	return rect.y+(rect.h/2.0f);
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

/*bool SpriteHandler::windowBorders()
{
	if(rect.y > 0 && (rect.y + rect.h) < game::Height && rect.x > 0 && (rect.x + rect.w) < game::Width) //If the sprite is within all 4 borders, do nothing. This if statement comes first to save on processing power. Currently broken: Needs framework code - Might make a rough temporary copy.
		return false;
	else //Else, check if corners are being breached. If so, "move the screen" to reveal more of the map and stuff.
	{
		//Do this later. As we are checking all 4 sides in one function (may be unoptimized, do some testing later), turn the if statements into a case statement to save space and neaten code.
	}
}*/