#include "TestEnemy.h"


TestEnemy::TestEnemy() : SpriteHandler()
{
	currentDirection = 0; //Sets the default/initial offset to 0. This means the initial stand direction is facing downwards. We do this as this does not have a value at first.
	currentAnimation = Stand; //Sets the default/initial animation set when the enemy spawns. We want him standing initially.
	currentFrame = 0; //We start at the first frame of the animation.

	upFrameAmount = 5; //If we do have all values as the same for each animation set then our code wil be significantly shorter.
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
	//currentDirection = find offset. //Will have to do a getOffset and return the current directions offset so we can pass the value here.

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