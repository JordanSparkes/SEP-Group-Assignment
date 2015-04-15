#ifndef _SPAWNER_H_
#define _SPAWNER_H_

#include "SDLLib.h"

class TestEnemy; //include enemy class so we can use enemies in the spawners functions.

class Spawner
{
private:
	static const int maxEnemies = 32; //Value for maximum enemies to be on the map at any one time.
	TestEnemy* enemies[maxEnemies]; //Array to store and limit the enemies.
	int enemyAmount; //Value to count the current amount of enemies alive. Used for looping through the arrays (Quicker than using while loops).

	Uint32 a; //Unsigned 32bit ints for timers. These will be used with SDL_GetTicks and updated to create a spawn delay. Try find my original code for this.
	Uint32 b;
	Uint32 c;

public:
	Spawner(void);
	~Spawner(void);

	void spawn(TestEnemy* enemy);
	void blit(SDL_Surface* screen);
	void update(float scalar);
};
#endif