#include "TestEnemy.h"


TestEnemy::TestEnemy() : SpriteHandler()
{
	currentAnimation = Stand; //Should this be here or in init?

	currentFrame = 0;

	upFrameAmount = 5; //I'll put these here for the test enemy but move them to init when i implement the real enemies.
	downFrameAmount = 5;
	leftFrameAmount = 5;
	rightFrameAmount = 5;

	upFrames = NULL;
	downFrames = NULL;
	leftFrames = NULL;
	rightFrames = NULL;
	standFrame = NULL;
}


TestEnemy::~TestEnemy(void)
{
	delete [] upFrames;
	delete [] downFrames;
	delete [] leftFrames;
	delete [] rightFrames;
	delete standFrame;

	upFrames = NULL;
	downFrames = NULL;
	leftFrames = NULL;
	rightFrames = NULL;
	standFrame = NULL;
}

void TestEnemy::init(SDL_Surface* spriteSheet, SDL_Rect* position)
{

	chooseEnemy(); //Run the function to determine the enemy types variables. Not yet finished, will pull an error as the class does not know what enemy type it is yet.

	this->rect = *position;

	rect.w = size;
	rect.h = size;

	upFrames = loadSprites(upFrameAmount, 1, rect.w, rect.h); //Sprite sheet standard: down, up, left, right.
	downFrames = loadSprites(downFrameAmount, 0, rect.w, rect.h); //If all the sprites have the same amount of frames I might set it to just a hard coded value.
	leftFrames = loadSprites(leftFrameAmount, 2, rect.w, rect.h);
	rightFrames = loadSprites(rightFrameAmount, 3, rect.w, rect.h);
	standFrame = loadSprites(1, currentDirection, rect.w, rect.h); //currentDirection is used as the value changes depending on what the last direction was.

	this->spriteSheet = spriteSheet; //this needs to be used because of the passed in value but also because when multiple enemies are spawned they each need to use this seperately. I'll use this-> on other things as I go along but for now just no.
}

void TestEnemy::blit(SDL_Surface* window)
{
	switch(currentAnimation) //A case statement is used as there are too many options to use if/else.
	{
	case Stand:
		SDL_BlitSurface(spriteSheet, standFrame, window, &rect);
	break;
	case Up:
		SDL_BlitSurface(spriteSheet, &(upFrames[currentFrame]), window, &rect);
	break;
	case Down:
		SDL_BlitSurface(spriteSheet, &(downFrames[currentFrame]), window, &rect);
	break;
	case Left:
		SDL_BlitSurface(spriteSheet, &(leftFrames[currentFrame]), window, &rect);
	break;
	case Right:
		SDL_BlitSurface(spriteSheet, &(rightFrames[currentFrame]), window, &rect);
	break;
	default:
		printf("Unable to blit an enemy."); //Error message in case something goes wrong. Used to identify problems during testing.
	}
}

void TestEnemy::chooseEnemy()
{
	switch(enemyType)
	{
	case Zombie:
		maxHealth = 10;
		damage = 3;
		speed = 5;
	break;
	case Skeleton:
		maxHealth = 5;
		damage = 5;
		speed = 3;
	break;
	case Spider:
		maxHealth = 1;
		damage = 3;
		speed = 10;
	break;
	default:
		printf("Error: Invalid enemy type?"); //Error message to help identify problems.
	}
}

void TestEnemy::update(float scalar)
{
	switch(currentAnimation) //Another case statement is used as tbhe animation length may differ. if they dont in the final we will only need one case, shortening the code completely.
	{
	case Up:
	if(currentFrame < upFrameAmount) //If the current frame is less than the final frame...
		currentFrame++; //switch to the next frame;
	else
		currentFrame = 0; //go back to the first frame, looping the animation.
	break;
	case Down:
	if(currentFrame < downFrameAmount) //If the current frame is less than the final frame...
		currentFrame++; //switch to the next frame;
	else
		currentFrame = 0; //go back to the first frame, looping the animation.
	break;
	case Left:
	if(currentFrame < leftFrameAmount) //If the current frame is less than the final frame...
		currentFrame++; //switch to the next frame;
	else
		currentFrame = 0; //go back to the first frame, looping the animation.
	break;
	case Right:
	if(currentFrame < rightFrameAmount) //If the current frame is less than the final frame...
		currentFrame++; //switch to the next frame;
	else
		currentFrame = 0; //go back to the first frame, looping the animation.
	break;
	default:
		printf("Error: Failed to update enemies animation.");
	}
}

void TestEnemy::reduceHealth(int reduction)
{
	health -= reduction;

	if(health > 0)
	{
		delete this; //If health is 0 delete this enemy instance.
	}
}

int TestEnemy::getHealth()
{
	return health;
}

void TestEnemy::moveUp()
{
	this->currentAnimation = Up;
	this->xSpeed = 0;
	this->ySpeed = -speed;
}

void TestEnemy::moveDown()
{
	this->currentAnimation = Down;
	this->xSpeed = 0;
	this->ySpeed = speed;
}

void TestEnemy::moveLeft()
{
	this->currentAnimation = Left;
	this->xSpeed = -speed;
	this->ySpeed = 0;
}

void TestEnemy::moveRight()
{
	this->currentAnimation = Right;
	this->xSpeed = speed;
	this->ySpeed = 0;
}

void TestEnemy::stand()
{
	this->currentAnimation = Stand;
	this->xSpeed = 0;
	this->ySpeed = 0;
}

void TestEnemy::doAttack()
{

}

void TestEnemy::avoidWalls()
{

}

void TestEnemy::track()
{

}