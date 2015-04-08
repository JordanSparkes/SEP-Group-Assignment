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
	FILE* file = fopen("test.txt", "r");
	int defenceData[11];

	fscanf(file, "%d", &defenceData);
	while (!feof(file))
	{
		printf("%d\n", defenceData);
		fscanf(file, "%d", &defenceData);
	}
	fclose(file);
	int Sheild = defenceData[4];
	printf_s("Sheild defence stat = %d", &Sheild);
	return 0;
}

int lootModifiers()
{
	FILE *file = fopen("defenceData.txt", "r");
	int integers[100];

	int i = 0;
	int num;
	while (fscanf(file, "%d", &num) > 0) {
		integers[i] = num;
		i++;
	}
	fclose(file);
	for (i = 0; i < (sizeof(integers) / sizeof(integers[0])); i++)
	{
		printf("%lf\n", integers[i]);
	}
	return 0;
}