#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <ctype.h>

#include "consoleColor.h"
#include "level.h"
#include "WeaponType.h"
#include "unitType.h"
#include "unitData.h"


int Key = 0;
const int maxUnitsCount = 40;

HANDLE consoleHandle = 0;
bool GameActive = true;
bool GlobalGameActive = true;

char levelData[rowsCount1][columsCount1];
bool fogOfWar[rowsCount1][columsCount1] ;

UnitData unitsData[maxUnitsCount];
int unitsCount = 0;
int HeroIndex = 0;
int BossIndex1 = 0;
int BossIndex2 = 0;
int BossIndex3 = 0;
int BossIndex4 = 0;

char tempBuffer[256];
char statusMessage[256];

//--------------------------------------------------------------------------------------------------------------------------------------------
//MENU
int iItem = 1;
int nLast = 5;
BOOL bRUN = TRUE;

void ShowMenu(int iItem)
{
	system("cls");
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_White);
	printf("\n\n\n\n\n\n\t\t***MENU***\n");
	printf("\t\t%s1 - START GAME OF STRESH\n", iItem == 1 ? ">" : " ");
	printf("\t\t%s2 - INFO ABOUT GAME\n", iItem == 2 ? ">" : " ");
	printf("\t\t%s3 - INFO ABOUT DEVELEPERS\n", iItem == 3 ? ">" : " ");
	printf("\t\t%s4 - GRATITUDE\n", iItem == 4 ? ">" : " ");
	printf("\t\t%s5 - HZ\n", iItem == 5 ? ">" : " ");
	printf("\t\t%s  - EXIT\n", "ESC");
}

void INFO()
{
	system("cls");
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_White);
	printf("\t\t***INFO ABOUT GAME***\n\n");
	printf("W - UP\n");
	printf("S - DOWN, kak Svito\n");
	printf("A - LEFT\n");
	printf("D - RIGHT\n");
	printf("You need to survive and find exit\n");
	printf("But be careful, there is very strong NPC\n");
	printf("GG WP =)\n");
	system("pause");
}

void HZ()
{
	system("cls");
	printf("#################@@####=#*#####+=@#%####===@#+####\n");
	printf("###################@#=@@@%%=%@#%@######@#@#@#%####\n");
	printf("##%########@%####%%%###@@@%%%%%%@#%%@-:+%=#####@#*\n");
	printf("###*###@#=###%%%==##@%%@@@@@%@%@@@@#@=*###@@######\n");
	printf("###%########@%%%@#@=+=@@%%@@@@@@@@@@@@#+##########\n");
	printf("##@########@%%%%@=:--*%%@@@@@@@@@@#@@@@####%###@##\n");
	printf("###########@@@@%%*---*+@@@@%@@##@@@##@@@=@########\n");
	printf("##########@@@@@@=:-..-:%@@@@%@########@@#=%#######\n");
	printf("#########@#####@*-....:*@#@##@##############@#####\n");
	printf("###############+:------:*@########################\n");
	printf("@=@############=+%#@%=+++=%################@==%###\n");
	printf("###############@+=%=@%+:*%########################\n");
	printf("############@=*::*++*::.-+==%==%@#################\n");
	printf("####%@######:----------.-:*:::::::+%##############\n");
	printf("#+%#########--....----...-::------:+##############\n");
	printf("#%##########:-----:-::----:::----::=##############\n");
	printf("############:----:--:+==%=*:::--::*###############\n");
	printf("##@@########+::::+*****:*+*+=+::::*###############\n");
	printf("#############+**::::-::-:*::**:***################\n");
	printf("#####@#######@=+*::::*+++**:**++=#################\n");
	printf("#=###@@######%+*+*:---:--::**+==%#################\n");
	printf("#%@@@########+****+++++**++=%=++%###########@#####\n");
	printf("#@@#####@##@%=*:::**+==%%==++**+@%###########%%###\n");
	printf("#@###%%@@%++====*::****++++***====%###############\n");
	printf("#@::**+++=++*=====+::*******===%===%##############\n");
	printf(":::**:*:::+***+==+=*::::***+++===++++++******@####\n");
	printf("::**:::::::****++*++*******===+++++++*****::::::+#\n");
	printf(":**:::::::::******=====**====+*++**+*:::::::::::::\n");
	printf(":::::::::::::********++**+**+==****+:::::*::::::::\n");
	printf("::::::::::::::*::*:***++++++=+**::**::::::::::::::\n");
	printf("::::::::::::****:::*:***++*=***::*+::::::::::*::::\n");
	system("pause");
}

void GemDev()
{
	system("cls");
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_DarkRed);
	printf("\n\n\n\n\n\n\t\t Developer : Alexander Stresh\n\n");
	printf("\t\t Curator : Mr.Kazak \n\n");
	printf("\t\t\t All rights reserved \n");
	printf("\t\t\t BSUIR 2016 \n");
	system("pause");
}

void tnx()
{
	system("cls");
	printf("Thank you me =)\n");
	system("pause");
}

void SetupSystem()
{
	statusMessage[0] = 0;

	srand(time(0));

	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	// Hide console cursor
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = 0;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void RevealFogOfWar(int row, int column)
{
	for (int r = row - 1; r <= row + 1; r++)
	{
		for (int c = column - 1; c <= column + 1; c++)
		{
			fogOfWar[r][c] = false;
		}
	}
}

/*------------------------------------------------------LEVEL 1---------------------------------------------------------------*/
void Initialize_1()
{
	unitsCount = 0;

	for (int r = 0; r < rowsCount1; r++)
	{
		for (int c = 0; c < columsCount1; c++)
		{
			fogOfWar[r][c] = true;

			char cellSymbol = levelData1[r][c];

			levelData[r][c] = cellSymbol;
			UnitType unitType = GetUnitTypeFromCell(cellSymbol);

			switch (cellSymbol)
			{
			case SymbolHero:
				HeroIndex = unitsCount;
				unitsData[unitsCount].type = unitType;
				unitsData[unitsCount].row = r;
				unitsData[unitsCount].column = c;
				unitsData[unitsCount].weapon = GetUnitDefaultWeapon(unitType);
				unitsData[unitsCount].health = GetUnitDefaultHealth(unitType);
				unitsCount++;
				break;

				//заполнение данных NPC and Hero
			case SymbolBoos1:
				BossIndex1 = unitsCount;
				unitsData[unitsCount].type = unitType;
				unitsData[unitsCount].row = r;
				unitsData[unitsCount].column = c;
				unitsData[unitsCount].weapon = GetUnitDefaultWeapon(unitType);
				unitsData[unitsCount].health = GetUnitDefaultHealth(unitType);
				unitsCount++;
				break;

			case SymbolBoos2:
				BossIndex2 = unitsCount;
				unitsData[unitsCount].type = unitType;
				unitsData[unitsCount].row = r;
				unitsData[unitsCount].column = c;
				unitsData[unitsCount].weapon = GetUnitDefaultWeapon(unitType);
				unitsData[unitsCount].health = GetUnitDefaultHealth(unitType);
				unitsCount++;
				break;

			case SymbolBoos3:
				BossIndex3 = unitsCount;
				unitsData[unitsCount].type = unitType;
				unitsData[unitsCount].row = r;
				unitsData[unitsCount].column = c;
				unitsData[unitsCount].weapon = GetUnitDefaultWeapon(unitType);
				unitsData[unitsCount].health = GetUnitDefaultHealth(unitType);
				unitsCount++;
				break;

			case SymbolBoos4:
				BossIndex4 = unitsCount;
				unitsData[unitsCount].type = unitType;
				unitsData[unitsCount].row = r;
				unitsData[unitsCount].column = c;
				unitsData[unitsCount].weapon = GetUnitDefaultWeapon(unitType);
				unitsData[unitsCount].health = GetUnitDefaultHealth(unitType);
				unitsCount++;
				break;

			case SymbolOrc:
			case SymbolSkeleton:
			case SymbolGlee:
			{
				unitsData[unitsCount].type = unitType;
				unitsData[unitsCount].row = r;
				unitsData[unitsCount].column = c;
				unitsData[unitsCount].weapon = GetUnitDefaultWeapon(unitType);
				unitsData[unitsCount].health = GetUnitDefaultHealth(unitType);
				unitsCount++;
				break;
			}
			}
		}
	}

	// открытие тумана войны
	RevealFogOfWar(unitsData[HeroIndex].row, unitsData[HeroIndex].column);
}

void Render_1()
{
	// курсор на 0 0
	COORD cursorCoord;
	cursorCoord.X = 0;
	cursorCoord.Y = 0;
	SetConsoleCursorPosition(consoleHandle, cursorCoord);


	// Вступление
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Green);
	printf("\n\tGAME OF STRESH");

	// Hero info
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Red);
	printf("\n\n\tHP: ");
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_White);
	printf("%i", unitsData[HeroIndex].health);

	// Hero Weapon
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Cyan);
	printf("     Weapon: ");
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_White);
	printf("%s", GetWeaponName(unitsData[HeroIndex].weapon));
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Gray);
	printf(" (Dmg: %i - %i)               ", GetWeaponDamage(unitsData[HeroIndex].weapon), GetWeaponDamage(unitsData[HeroIndex].weapon) + 7);

	// Boss 1 info
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Red);
	printf("\n\n\tHP: ");
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_White);
	printf("%i", unitsData[BossIndex1].health);

	// Boss 1 weapon
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Cyan);
	printf("     Weapon: ");
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_White);
	printf("%s", GetWeaponName(unitsData[BossIndex1].weapon));
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Gray);
	printf(" (Dmg: %i - %i)               ", GetWeaponDamage(unitsData[BossIndex1].weapon), GetWeaponDamage(unitsData[BossIndex1].weapon)+7);

	// рисование уровня
	printf("\n\n\t");
	for (int r = 0; r < rowsCount1; r++)
	{
		for (int c = 0; c < columsCount1; c++)
		{
			if (fogOfWar[r][c] == false)
			{
				char cellSymbol = levelData[r][c];

				char renderCellSymbol = GetRenderCellSymbol(cellSymbol);
				ConsoleColor cellColor = GetRenderCellSymbolColor(cellSymbol);

				SetConsoleTextAttribute(consoleHandle, cellColor);
				printf("%c", renderCellSymbol);
			}
			else
			{
				SetConsoleTextAttribute(consoleHandle, fogOfWarRenderColor);
				printf("%c", fogOfWarRenderSymbol);
			}
		}
		printf("\n\t");
	}
	//new
	// Fill status message with spaces
	while (strlen(statusMessage) < 255)
	{
		strcat_s(statusMessage, " ");
	}
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Green);
	printf("\n\n\t%s", statusMessage);

	// Clear status message
	statusMessage[0] = 0;
	//end new
}
/*-----------------------------------------------END OF LEVEL 1------------------------------------------------------------------*/

/*-------------------------------------------LEVEL 2 ----------------------------------------------------------------------------*/
void Initialize2()
{
	unitsCount = 0;

	for (int r = 0; r < rowsCount1; r++)
	{
		for (int c = 0; c < columsCount1; c++)
		{
			fogOfWar[r][c] = true;

			char cellSymbol = levelData3[r][c];

			levelData[r][c] = cellSymbol;
			UnitType unitType = GetUnitTypeFromCell(cellSymbol);

			switch (cellSymbol)
			{
			case SymbolHero:
				HeroIndex = unitsCount;
				unitsData[unitsCount].type = unitType;
				unitsData[unitsCount].row = r;
				unitsData[unitsCount].column = c;
				unitsData[unitsCount].weapon = GetUnitDefaultWeapon(unitType);
				unitsData[unitsCount].health = GetUnitDefaultHealth(unitType);
				unitsCount++;
				break;

				//заполнение данных NPC and Hero
			case SymbolBoos1:
				BossIndex1 = unitsCount;
				unitsData[unitsCount].type = unitType;
				unitsData[unitsCount].row = r;
				unitsData[unitsCount].column = c;
				unitsData[unitsCount].weapon = GetUnitDefaultWeapon(unitType);
				unitsData[unitsCount].health = GetUnitDefaultHealth(unitType);
				unitsCount++;
				break;

			case SymbolBoos2:
				BossIndex2 = unitsCount;
				unitsData[unitsCount].type = unitType;
				unitsData[unitsCount].row = r;
				unitsData[unitsCount].column = c;
				unitsData[unitsCount].weapon = GetUnitDefaultWeapon(unitType);
				unitsData[unitsCount].health = GetUnitDefaultHealth(unitType);
				unitsCount++;
				break;

			case SymbolBoos3:
				BossIndex3 = unitsCount;
				unitsData[unitsCount].type = unitType;
				unitsData[unitsCount].row = r;
				unitsData[unitsCount].column = c;
				unitsData[unitsCount].weapon = GetUnitDefaultWeapon(unitType);
				unitsData[unitsCount].health = GetUnitDefaultHealth(unitType);
				unitsCount++;
				break;

			case SymbolBoos4:
				BossIndex4 = unitsCount;
				unitsData[unitsCount].type = unitType;
				unitsData[unitsCount].row = r;
				unitsData[unitsCount].column = c;
				unitsData[unitsCount].weapon = GetUnitDefaultWeapon(unitType);
				unitsData[unitsCount].health = GetUnitDefaultHealth(unitType);
				unitsCount++;
				break;

			case SymbolOrc:
			case SymbolSkeleton:
			case SymbolGlee:
			{
				unitsData[unitsCount].type = unitType;
				unitsData[unitsCount].row = r;
				unitsData[unitsCount].column = c;
				unitsData[unitsCount].weapon = GetUnitDefaultWeapon(unitType);
				unitsData[unitsCount].health = GetUnitDefaultHealth(unitType);
				unitsCount++;
				break;
			}
			}
		}
	}

	// открытие тумана войны
	RevealFogOfWar(unitsData[HeroIndex].row, unitsData[HeroIndex].column);
}

void Render_2()
{
	// курсор на 0 0
	COORD cursorCoord;
	cursorCoord.X = 0;
	cursorCoord.Y = 0;
	SetConsoleCursorPosition(consoleHandle, cursorCoord);


	// Вступление
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Green);
	printf("\n\tGAME OF STRESH");

	// Hero info
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Red);
	printf("\n\n\tHP: ");
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_White);
	printf("%i", unitsData[HeroIndex].health);


	// Hero Weapon
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Cyan);
	printf("     Weapon: ");
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_White);
	printf("%s", GetWeaponName(unitsData[HeroIndex].weapon));
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Gray);
	printf(" (Dmg: %i - %i)               ", GetWeaponDamage(unitsData[HeroIndex].weapon), GetWeaponDamage(unitsData[HeroIndex].weapon) + 7);

	// Boss 2 info
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Red);
	printf("\n\n\tHP: ");
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_White);
	printf("%i", unitsData[BossIndex2].health);

	// Boss 2 weapon
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Cyan);
	printf("     Weapon: ");
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_White);
	printf("%s", GetWeaponName(unitsData[BossIndex2].weapon));
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Gray);
	printf("%i - %i", unitsData[BossIndex2].weapon, unitsData[BossIndex2].weapon + 7);

	// рисование уровня
	printf("\n\n\t");
	for (int r = 0; r < rowsCount1; r++)
	{
		for (int c = 0; c < columsCount1; c++)
		{
			if (fogOfWar[r][c] == false)
			{
				char cellSymbol = levelData[r][c];

				char renderCellSymbol = GetRenderCellSymbol(cellSymbol);
				ConsoleColor cellColor = GetRenderCellSymbolColor(cellSymbol);

				SetConsoleTextAttribute(consoleHandle, cellColor);
				printf("%c", renderCellSymbol);
			}
			else
			{
				SetConsoleTextAttribute(consoleHandle, fogOfWarRenderColor);
				printf("%c", fogOfWarRenderSymbol);
			}
		}
		printf("\n\t");
	}
	//new
	// Fill status message with spaces
	while (strlen(statusMessage) < 160)
	{
		strcat_s(statusMessage, " ");
	}
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Green);
	printf("\n\n\t%s", statusMessage);

	// Clear status message
	statusMessage[0] = 0;
	//end new
}
/*------------------------------END OF LEVEL 2------------------------------------------------------------------------------------*/

/*-------------------------------------------LEVEL 3------------------------------------------------------------------------------*/
void Initialize3()
{
	unitsCount = 0;

	for (int r = 0; r < rowsCount1; r++)
	{
		for (int c = 0; c < columsCount1; c++)
		{
			fogOfWar[r][c] = true;

			char cellSymbol = levelData4[r][c];

			levelData[r][c] = cellSymbol;
			UnitType unitType = GetUnitTypeFromCell(cellSymbol);

			switch (cellSymbol)
			{
			case SymbolHero:
				HeroIndex = unitsCount;
				unitsData[unitsCount].type = unitType;
				unitsData[unitsCount].row = r;
				unitsData[unitsCount].column = c;
				unitsData[unitsCount].weapon = GetUnitDefaultWeapon(unitType);
				unitsData[unitsCount].health = GetUnitDefaultHealth(unitType);
				unitsCount++;
				break;

				//заполнение данных NPC and Hero
			case SymbolBoos1:
				BossIndex1 = unitsCount;
				unitsData[unitsCount].type = unitType;
				unitsData[unitsCount].row = r;
				unitsData[unitsCount].column = c;
				unitsData[unitsCount].weapon = GetUnitDefaultWeapon(unitType);
				unitsData[unitsCount].health = GetUnitDefaultHealth(unitType);
				unitsCount++;
				break;

			case SymbolBoos2:
				BossIndex2 = unitsCount;
				unitsData[unitsCount].type = unitType;
				unitsData[unitsCount].row = r;
				unitsData[unitsCount].column = c;
				unitsData[unitsCount].weapon = GetUnitDefaultWeapon(unitType);
				unitsData[unitsCount].health = GetUnitDefaultHealth(unitType);
				unitsCount++;
				break;

			case SymbolBoos3:
				BossIndex3 = unitsCount;
				unitsData[unitsCount].type = unitType;
				unitsData[unitsCount].row = r;
				unitsData[unitsCount].column = c;
				unitsData[unitsCount].weapon = GetUnitDefaultWeapon(unitType);
				unitsData[unitsCount].health = GetUnitDefaultHealth(unitType);
				unitsCount++;
				break;
			case SymbolBoos4:
				BossIndex4 = unitsCount;
				unitsData[unitsCount].type = unitType;
				unitsData[unitsCount].row = r;
				unitsData[unitsCount].column = c;
				unitsData[unitsCount].weapon = GetUnitDefaultWeapon(unitType);
				unitsData[unitsCount].health = GetUnitDefaultHealth(unitType);
				unitsCount++;
				break;

			case SymbolOrc:
			case SymbolSkeleton:
			case SymbolGlee:
			{
				unitsData[unitsCount].type = unitType;
				unitsData[unitsCount].row = r;
				unitsData[unitsCount].column = c;
				unitsData[unitsCount].weapon = GetUnitDefaultWeapon(unitType);
				unitsData[unitsCount].health = GetUnitDefaultHealth(unitType);
				unitsCount++;
				break;
			}
			}
		}
	}

	// открытие тумана войны
	RevealFogOfWar(unitsData[HeroIndex].row, unitsData[HeroIndex].column);
}

void Render_3()
{
	// курсор на 0 0
	COORD cursorCoord;
	cursorCoord.X = 0;
	cursorCoord.Y = 0;
	SetConsoleCursorPosition(consoleHandle, cursorCoord);

	// Вступление
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Green);
	printf("\n\tGAME OF STRESH");

	// Hero info
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Red);
	printf("\n\n\tHP: ");
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_White);
	printf("%i", unitsData[HeroIndex].health);

	// Hero Weapon
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Cyan);
	printf("     Weapon: ");
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_White);
	printf("%s", GetWeaponName(unitsData[HeroIndex].weapon));
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Gray);
	printf(" (Dmg: %i - %i)               ", GetWeaponDamage(unitsData[HeroIndex].weapon), GetWeaponDamage(unitsData[HeroIndex].weapon) + 7);

	// Boss 3 info
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Red);
	printf("\n\n\tHP: ");
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_White);
	printf("%i", unitsData[BossIndex3].health);


	// Boss 3 weapon
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Cyan);
	printf("     Weapon: ");
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_White);
	printf("%s", GetWeaponName(unitsData[BossIndex3].weapon));
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Gray);
	printf("%i - %i", unitsData[BossIndex3].weapon, unitsData[BossIndex3].weapon + 7);

	// рисование уровня
	printf("\n\n\t");
	for (int r = 0; r < rowsCount1; r++)
	{
		for (int c = 0; c < columsCount1; c++)
		{
			if (fogOfWar[r][c] == false)
			{
				char cellSymbol = levelData[r][c];

				char renderCellSymbol = GetRenderCellSymbol(cellSymbol);
				ConsoleColor cellColor = GetRenderCellSymbolColor(cellSymbol);

				SetConsoleTextAttribute(consoleHandle, cellColor);
				printf("%c", renderCellSymbol);
			}
			else
			{
				SetConsoleTextAttribute(consoleHandle, fogOfWarRenderColor);
				printf("%c", fogOfWarRenderSymbol);
			}
		}
		printf("\n\t");
	}
	// Fill status message with spaces
	while (strlen(statusMessage) < 255)
	{
		strcat_s(statusMessage, " ");
	}
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Green);
	printf("\n\n\t%s", statusMessage);
	// Clear status message
	statusMessage[0] = 0;
	//end new
}
/*-------------------------------------END OF LEVEL 3------------------------------------------------------------------------------*/

void MoveUnitTo(UnitData* pointerToUnitData, int row, int column)
{
	// Пропуск мертвых
	if (pointerToUnitData->health <= 0)
	{
		return;
	}

	char unitSymbol = levelData[pointerToUnitData->row][pointerToUnitData->column];
	char _CellSymbol = levelData[row][column];
	bool canMoveToCell = false;

	// Добавление действий
	switch (_CellSymbol)
	{
		// Empty cell
	case SymbolEmpty:
	{
		canMoveToCell = true;
		break;
	}

	// NPC and Hero actions
	case SymbolHero:
	case SymbolOrc:
	case SymbolSkeleton:
	case SymbolGlee:
	case SymbolBoos1:
	case SymbolBoos2:
	case SymbolBoos3:
	case SymbolBoos4:
	{
		UnitType _UnitType = GetUnitTypeFromCell(_CellSymbol);

		// Если разыне типы монстров
		if (pointerToUnitData->type != _UnitType)
		{
			// Поиск типов в структуре
			for (int i = 0; i < unitsCount; i++)
			{
				// пропуск мертвых
				if (unitsData[i].health <= 0)
					continue;

				if (unitsData[i].row == row && unitsData[i].column == column)
				{
					// Вычисление Урона
					int damage = GetWeaponDamage(pointerToUnitData->weapon) + rand() % 7 ;
					unitsData[i].health = unitsData[i].health - damage;

					//----------------------------------------------------
					// Add to status message
					sprintf_s(tempBuffer, " %s dealt %i damage to %s.", GetUnitName(pointerToUnitData->type), damage, GetUnitName(_UnitType));
					strcat_s(statusMessage, tempBuffer);
					//-----------------------------------------------------
					
					// В случае смерти
					if (unitsData[i].health <= 0.0f)
					{
						levelData[row][column] = SymbolEmpty;
						switch (rand() % 6)
						{
						case 0: levelData[row][column] = SymbolHeart;
							break;
						case 1: levelData[row][column] = SymbolSaber;
							break;
						case 2: levelData[row][column] = SymbolClub;
							break;
						case 3: levelData[row][column] = SymbolEmpty;
							break;
						case 4: levelData[row][column] = SymbolFalx;
							break;
						case 5: levelData[row][column] = SymbolEmpty;
							break;
						}

						//----------------------------------------------------------
						// Add to status message
						sprintf_s(tempBuffer, " %s died.", GetUnitName(_UnitType), damage, GetUnitName(_UnitType));
						strcat_s(statusMessage, tempBuffer);
						//-------------------------------------------------------------
					}
					if (unitsData[BossIndex1].health < 0.0f)
					{		
						unitsData[BossIndex1].health = 0;
					}
					if (unitsData[BossIndex2].health < 0.0f)
					{					
						unitsData[BossIndex2].health = 0;
					}
					if (unitsData[BossIndex3].health < 0.0f)
					{						
						unitsData[BossIndex3].health = 0;
					}
					if (unitsData[BossIndex4].health < 0.0f)
					{
						unitsData[BossIndex4].health = 0;
					}
					break;
				}
			}
		}
		break;
	}
	}

	// Только действия hero
	if (pointerToUnitData->type == UnitHero)
	{
		switch (_CellSymbol)
		{
			// Weapon Cell
		case SymbolStick:
		case SymbolClub:
		case SymbolSpear:
		case SymbolSaber:

		case SymbolFalx:
		case SymbolMMA:
		case SymbolWorkBook:
		case SymbolCi:
		case SymbolS:
		case SymbolSword:
		case SymbolWhip:
		case SymbolMoustache:
		{
			canMoveToCell = true;

			WeaponType weaponType = GetWeaponTypeFromCell(_CellSymbol);
			if (unitsData[HeroIndex].weapon <= weaponType)
			{
				unitsData[HeroIndex].weapon = weaponType;
			}

			//-------------------------------------------------------------------------
			// Add to status message
			sprintf_s(tempBuffer, " %s found %s.", GetUnitName(pointerToUnitData->type), GetWeaponName(weaponType));
			strcat_s(statusMessage, tempBuffer);
			//-------------------------------------------------------------------------

			break;
		}

		// Heart
		case SymbolHeart:
		{
			canMoveToCell = true;
			unitsData[HeroIndex].health += heartHeal;
			break;
		}

		// Exit cell
		case SymbolExit:
		{
			GameActive = false;
			break;
		}
		}
	}

	if (canMoveToCell)
	{
		// Удаление игрока с прошлой клетки
		levelData[pointerToUnitData->row][pointerToUnitData->column] = SymbolEmpty;

		// Новая клетка
		pointerToUnitData->row = row;
		pointerToUnitData->column = column;
		levelData[pointerToUnitData->row][pointerToUnitData->column] = unitSymbol;


	    // открытие тума войны
		if (pointerToUnitData->type == UnitHero)
		{
		RevealFogOfWar(row, column);
		}
	}
}

void UpdateNPC()
{
	// Проходим через всех NPC
	for (int i = 0; i < unitsCount; i++)
	{
		// Ignore Hero
		if (i == HeroIndex)
			continue;

		// Пропуск мертвых
		if (unitsData[i].health <= 0)
			continue;

		// Расстояние до героя
		int distanceToHeroR = abs(unitsData[HeroIndex].row - unitsData[i].row);
		int distanceToHeroC = abs(unitsData[HeroIndex].column - unitsData[i].column);

		// В случае если он близко
		if ((distanceToHeroR + distanceToHeroC) == 1)
		{
			// Attack hero
			MoveUnitTo(&unitsData[i], unitsData[HeroIndex].row, unitsData[HeroIndex].column);
		}
		else
		{
			// Рандомный ход
			switch (rand() % 4)
			{
			case 0:
				MoveUnitTo(&unitsData[i], unitsData[i].row, unitsData[i].column + 1);
				break;

			case 1:
				MoveUnitTo(&unitsData[i], unitsData[i].row , unitsData[i].column - 1);
				break;

			case 2:
				MoveUnitTo(&unitsData[i], unitsData[i].row + 1, unitsData[i].column);
				break;

			case 3:
				MoveUnitTo(&unitsData[i], unitsData[i].row - 1, unitsData[i].column);
				break;
			}
		}
	}
}

void Update()
{
	char inputChar = _getch();
	inputChar = tolower(inputChar);

	switch (inputChar)
	{
	case 'w':
		MoveUnitTo(&unitsData[HeroIndex], unitsData[HeroIndex].row - 1, unitsData[HeroIndex].column);
		break;

	case 's':
		MoveUnitTo(&unitsData[HeroIndex], unitsData[HeroIndex].row + 1, unitsData[HeroIndex].column);
		break;

	case 'a':
		MoveUnitTo(&unitsData[HeroIndex], unitsData[HeroIndex].row, unitsData[HeroIndex].column - 1);
		break;

	case 'd':
		MoveUnitTo(&unitsData[HeroIndex], unitsData[HeroIndex].row, unitsData[HeroIndex].column + 1);
		break;

	}

	UpdateNPC();

	// Hero death
	if (unitsData[HeroIndex].health <= 0)
	{
		GameActive = false;
		GlobalGameActive = false;
	}
	else
	{
		// Регенерация
		if (unitsData[HeroIndex].health < 200)
		{
			unitsData[HeroIndex].health++;
		}
	}

}

void Shutdown_win()
{
	system("cls");
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Green);
	printf("\n\n\n\n\n\n\t\tYou Win...maybe...\n");
	system("pause");
	return;
}

void Shutdown_died()
{
	system("cls");
	SetConsoleTextAttribute(consoleHandle, ConsoleColor_Red);
	printf("\n\n\n\n\n\n\t\t...You DIED...\n");
	system("pause");
	system("cls");
}

void Level_1()
{
	GameActive = true;
	GlobalGameActive = true;
	SetupSystem();
	Initialize_1();
	do
	{
		Render_1();
		Update();
	} while (GameActive);
	system("cls");
	system("pause");
}

void Level_2()
{
	system("cls");
	GameActive = true;
	SetupSystem();
	Initialize2();
	do
	{
		Render_2();
		Update();
	} while (GameActive);
	system("cls");
	system("pause");
}

void Level_3()
{
	system("cls");
	GameActive = true;
	SetupSystem();
	Initialize3();
	do
	{
		Render_3();
		Update();
	} while (GameActive);
	system("cls");
	system("pause");
}

void menu()
{
	while (bRUN)
	{
		ShowMenu(iItem);
		if (GetAsyncKeyState(VK_UP))
			if (GetAsyncKeyState(VK_UP))
			{
				if (0 < iItem - 1)
					iItem = iItem - 1;
				else
					iItem = nLast;
				ShowMenu(iItem);
			}
		if (GetAsyncKeyState(VK_DOWN))
			if (GetAsyncKeyState(VK_DOWN))
			{
				if (iItem < nLast)
					iItem = iItem + 1;
				else
					iItem = 1;
				ShowMenu(iItem);
			}
		if (GetAsyncKeyState(VK_RETURN))
			if (GetAsyncKeyState(VK_RETURN))
			{
				ShowMenu(iItem);

				switch (iItem)
				{

				case 1:
					system("cls");
					Level_1();
					if (GlobalGameActive == false) Shutdown_died();
						
					/*--------------------------------------Level 2---------------------------------------------------------------------------------*/
					else {
						Level_2();
						if (GlobalGameActive == false) Shutdown_died();
						else {
							/*----------------------------------Level 3---------------------------------------------------------------------------------------*/
							Level_3();
							if (GlobalGameActive == false) Shutdown_died();
							else Shutdown_win();
						}
					}
					break;

				case 2:
					INFO();
					break;

				case 3:
					GemDev();
					break;

				case 4:
					tnx();
					break;

				case 5:
					HZ();
					break;
				}
			}
		if (GetAsyncKeyState(VK_ESCAPE))
			bRUN = FALSE;
		Sleep(100);
	}
}

/*---------------------------------MAIN----------------------------------------------------------------------------------------------*/
int main()
{
	menu();
	
	return 0;
}