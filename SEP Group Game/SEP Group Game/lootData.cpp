#include "lootData.h"

int damageDataIO()
{
	int x;
	char damageData[50];
	ifstream damageFile;
	cin.getline(damageData, 50);
	damageFile.open(damageData);

	if (!damageFile.is_open())
	{
		cout << "File Open Failed" << endl;
		return 0;
	}

	while (damageFile >> x)
	{
		cout << x << endl;
	}
}

int defenceDataIO()
{
	return 0;
}

int lootModifiers()
{
	return 0;
}