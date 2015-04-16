#include "Spawner.h"
#include "TestEnemy.h"


Spawner::Spawner(void)
{
	enemyAmount = 0; //Set the value to 0 for the constructor.
}


Spawner::~Spawner(void)
{
	for(int i = 0; i < enemyAmount; i++) //Loop through the array and delete each enemy for deconstructor.
	{
		delete enemies[i];
		enemies[i] = NULL; //Null the memory address for deconstructor.
	}
}

void Spawner::spawn(TestEnemy* addEnemy) //Query: Move timer stuff to somewhere else? Might make things quicker?
{
	static Uint32 spawnTime = 0; //Set the spawn time staticaly to 0.
	currentTime = SDL_GetTicks(); //As the function is in the update it will be called every tick. This variable tracks the current time in ticks usingthe SDL function.

	if(currentTime > spawnTime + 1000) //If current time is less than the spawn time + 1000 (where 1000 is our delay)...
	{
		if(enemyAmount < maxEnemies) //If there is space in the array...
		{
			enemies[enemyAmount] = addEnemy; //Create a new enemy at the first free array slot, tracked by enemyAmount.
			enemyAmount++; //Add to the amount value as  an enemy has been created. This will now select the next array slot when the next enemy spawns.
		}
		else
			printf("Spawn ignored, Maximum enemies reached.");

		spawnTime = currentTime; //Update spawnTime with currentTime so we can use it again with the next delay.
	}
}

void Spawner::blit(SDL_Surface* window)
{
	if(enemyAmount > 0) //This check is purely there to save on processing power so we don't need to try to draw if there's nothing to draw.
	{
		for(int i = 0; i < enemyAmount; i++) //loop through the spawner array...
		{
			enemies[i]->blit(window); //Redraw each enemy to the screen.
		}
	}
}

void Spawner::update(float scalar)
{
	if(enemyAmount > 0) //Again, a simple check so we don't have to bother processing an update if there is nothing to update.
	{
		for(int i = 0; i < enemyAmount; i++) //loop through the spawner array...
		{
			enemies[i]->update(scalar); //update each enemy;
		}
	}
}