#include "lootData.h"

void damageDataIO()
{
	ifstream file("damageData.txt");
	if (file.is_open())
	{
		int damageArray[25];

		for (int i = 0; i < 25; ++i)
		{
			file >> damageArray[i];
			printf("%d\n", damageArray[i]);
		}
	}
}

void defenceDataIO()
{
	ifstream file("defenceData.txt");
	if (file.is_open())
	{
		int defenceArray[25];

		for (int i = 0; i < 25; ++i)
		{
			file >> defenceArray[i];
			printf("%d\n", defenceArray[i]);
		}
	}
}

void itemData()
{
	ifstream file("itemData.txt");
	if (file.is_open())
	{
		char itemName[25];

		for (int i = 0; i < 25; ++i)
		{
			file >> itemName[i];
			printf("%s\n", itemName[i]); //not sure why this returns some squiggly lines, searched it up and %s should be correct
		}
	}
}

void lootModifiers()
{
	//This will be used to judge what level the player is currently at, and the algorithm then should choose an item drop sutible for that level
	int level = 1; //This should be done by Jordan/Irish (im assuming level is between 1 and 10
	int Difficulty[3]; //A possible feature that could be change the modifiers
	if (level <= 3)
	{
		itemData();
		printf("%d", itemName[i]);
	}
	else if (level > 3 <= 5)
	{

	}
	else if (level > 5 <= 7)
	{
	
	}
	else
	{

	}
}