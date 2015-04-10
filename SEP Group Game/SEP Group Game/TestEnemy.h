#ifndef _TESTENEMY_H_
#define _TESTENEMY_H_

#include "SDLLib.h"
#include "SpriteHandler.h"

class TestEnemy : public SpriteHandler //Class of enemy, inherits from SpriteHandler.
{
private:
	int health; //Variable for amount of health.
	static const int maxHealth; //variable to define health limit. Necessary? Could just use hard-coded values.
	int damage; //Variable for amount of damage an attack will cause.
	bool attack; //True/false to determine whether enemy will attack or not. Might not be needed.

	Uint32 a; //Unsigned 32bit ints for timers. These will be used with SDL_GetTicks and updated to create a fire rate delay. Try find my original code for this.
	Uint32 b;
	Uint32 c;

	void move(); //Simple function to make the enemy move on it's own.

public:
	TestEnemy(void);
	~TestEnemy(void);

	void update(float scalar); //Update method to update enemy information when called.
	void init(SDL_Surface* spriteSheet); //Init method to initialize enemy information.
};

#endif