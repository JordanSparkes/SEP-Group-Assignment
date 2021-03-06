#ifndef _TESTENEMY_H_
#define _TESTENEMY_H_

#include "SDLLib.h"
#include "SpriteHandler.h"

class TestEnemy : public SpriteHandler //Class of enemy, inherits from SpriteHandler.
{
private:
	int health; //Variable for amount of health.
	int maxHealth; //variable to define health limit. Necessary? Could just use hard-coded values.
	int damage; //Variable for amount of damage an attack will cause.
	int speed; //Variable to judge enemies speed.
	int currentDirection; //Variable to adjust enemy standing direction.
	bool attack; //True/false to determine whether enemy will attack or not. Might not be needed.

	Uint32 currentTime; //Unsigned 32bit ints for timers. These will be used with SDL_GetTicks and updated to create a fire rate delay.
	static Uint32 lastTime;
	static Uint32 attackTime;

	void move(); //Simple function to make the enemy move on it's own.

protected:
	int currentFrame;
	int currentAnimation;
	int enemyType;

	SDL_Rect* upFrames; //4 direction movement animation arrays.
	SDL_Rect* downFrames;
	SDL_Rect* leftFrames;
	SDL_Rect* rightFrames;
	SDL_Rect* standFrame;

	int upFrameAmount;
	int downFrameAmount;
	int leftFrameAmount;
	int rightFrameAmount;

public:
	TestEnemy(void);
	~TestEnemy(void); //Destructor not virtual as we do not want SpriteHandler to be destroyed when an enemy is destroyed. Is this right? Consult group.

	static const int size = 100; //Width and height of each frame. They're square for now so only one value is needed and is static constant because it will never change.

	enum enemyTypes {Zombie, Skeleton, Spider}; //This enum will be used later. It will be used so that all enemy types can derive from a single class using an if statement to determine the sprite sheet to use, health, damage, attack type speed etc. values. Debatable: Unused attack functions if one enemy type is selected, more efficient than seperating classes into each enemy type? Testing required.
	enum direction {Up, Down, Left, Right, Stand}; //Enum to handle directional movement.

	void moveUp(); //Functions to handle movement. May merge these into one movement function but that may not be optimal. testing required.
	void moveDown();
	void moveLeft();
	void moveRight();
	void stand();

	void avoidWalls(); //Function to do AI. Unused in the test enemy. Does this need to be in private?
	void track(); //Function to follow player. Unused in the test enemy. Does this need to be in private?
	void doAttack(); //Function to handle attacks. Unused in the test enemy. Does this need to be in private?

	int getDirection();

	int getHealth();
	void reduceHealth(int);

	void update(float scalar); //Update method to update enemy information when called.
	void init(SDL_Surface* spriteSheet, SDL_Rect* position); //Init method to initialize enemy information.
	void blit(SDL_Surface* window); //Draw method to handle drawing the enemy to the screen.
	void chooseEnemy();
};

#endif