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

char levelData[rowsCount1][columsCount1];
bool fogOfWar[rowsCount1][columsCount1] ;


UnitData unitsData[maxUnitsCount];
int unitsCount = 0;
int HeroIndex = 0;
int BossIndex1 = 0;
int BossIndex2 = 0;
int BossIndex3 = 0;
int BossIndex4 = 0;

//Update 1.1.3
char tempBuffer[256];
char statusMessage[256];

//--------------------------------------------------------------------------------------------------------------------------
//MENU

//--------------------------------------------------------------------------------------------------------------------------


void SetupSystem()
{
	//new
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

void Initialize()
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

				//���������� ������ NPC and Hero
			case SymbolOrc:
			case SymbolSkeleton:
			case SymbolGlee:
			{
				UnitType unitType = GetUnitTypeFromCell(cellSymbol);
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

	// �������� ������ �����
	RevealFogOfWar(unitsData[HeroIndex].row, unitsData[HeroIndex].column);
}

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

				//���������� ������ NPC and Hero
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

	// �������� ������ �����
	RevealFogOfWar(unitsData[HeroIndex].row, unitsData[HeroIndex].column);
}

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

				//���������� ������ NPC and Hero
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

	// �������� ������ �����
	RevealFogOfWar(unitsData[HeroIndex].row, unitsData[HeroIndex].column);
}

void Render()
{
	// ������ �� 0 0
	COORD cursorCoord;
	cursorCoord.X = 0;
	cursorCoord.Y = 0;
	SetConsoleCursorPosition(consoleHandle, cursorCoord);


	// ����������
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
	printf(" (Dmg: %i)               ", GetWeaponDamage(unitsData[HeroIndex].weapon));




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
	printf(" (Dmg: %i)               ", GetWeaponDamage(unitsData[BossIndex1].weapon));



	// ��������� ������
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

void MoveUnitTo(UnitData* pointerToUnitData, int row, int column)
{
	// ������� �������
	if (pointerToUnitData->health <= 0)
	{
		return;
	}

	char unitSymbol = levelData[pointerToUnitData->row][pointerToUnitData->column];
	char _CellSymbol = levelData[row][column];
	bool canMoveToCell = false;

	// ���������� ��������
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

		// ���� ������ ���� ��������
		if (pointerToUnitData->type != _UnitType)
		{
			// ����� ����� � ���������
			for (int i = 0; i < unitsCount; i++)
			{
				// ������� �������
				if (unitsData[i].health <= 0)
					continue;

				if (unitsData[i].row == row && unitsData[i].column == column)
				{
					// ���������� �����
					int damage = GetWeaponDamage(pointerToUnitData->weapon);
					unitsData[i].health = unitsData[i].health - damage;


					//----------------------------------------------------
					// Add to status message
					sprintf_s(tempBuffer, " %s dealt %i damage to %s.", GetUnitName(pointerToUnitData->type), damage, GetUnitName(_UnitType));
					strcat_s(statusMessage, tempBuffer);
					//-----------------------------------------------------
					

					// � ������ ������
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
						levelData[row][column] = SymbolMMA;
						unitsData[BossIndex1].health = 0;
					}
					if (unitsData[BossIndex2].health < 0.0f)
					{
						levelData[row][column] = SymbolWorkBook;
						unitsData[BossIndex2].health = 0;
					}
					if (unitsData[BossIndex3].health < 0.0f)
					{
						levelData[row][column] = SymbolCi;
						unitsData[BossIndex3].health = 0;
					}
					if (unitsData[BossIndex4].health < 0.0f)
					{
						levelData[row][column] = SymbolS;
						unitsData[BossIndex4].health = 0;
					}
					break;
				}
			}
		}
		break;
	}
	}

	// ������ �������� hero
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
		// �������� ������ � ������� ������
		levelData[pointerToUnitData->row][pointerToUnitData->column] = SymbolEmpty;

		// ����� ������
		pointerToUnitData->row = row;
		pointerToUnitData->column = column;
		levelData[pointerToUnitData->row][pointerToUnitData->column] = unitSymbol;


	    // �������� ���� �����
		if (pointerToUnitData->type == UnitHero)
		{
		RevealFogOfWar(row, column);
		}
	}
}

void UpdateNPC()
{
	// �������� ����� ���� NPC
	for (int i = 0; i < unitsCount; i++)
	{
		// Ignore Hero
		if (i == HeroIndex)
			continue;

		// ������� �������
		if (unitsData[i].health <= 0)
			continue;

		// ���������� �� �����
		int distanceToHeroR = abs(unitsData[HeroIndex].row - unitsData[i].row);
		int distanceToHeroC = abs(unitsData[HeroIndex].column - unitsData[i].column);

		// � ������ ���� �� ������
		if ((distanceToHeroR + distanceToHeroC) == 1)
		{
			// Attack hero
			MoveUnitTo(&unitsData[i], unitsData[HeroIndex].row, unitsData[HeroIndex].column);
		}
		else
		{
			// ��������� ���
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

		// Restart level
	case 'r':
		Initialize();
		break;
	}

	UpdateNPC();

	// Hero death
	if (unitsData[HeroIndex].health <= 0)
	{
		GameActive = false;
	}
	else
	{
		// �����������
		if (unitsData[HeroIndex].health < 200)
		{
			unitsData[HeroIndex].health++;
		}
	}

}

void Shutdown()
{
	system("cls");
	printf("\n\tGame over...");
	_getch();
}

void Level_1()
{
	SetupSystem();
	Initialize();
	do
	{
		Render();
		Update();
	} while (GameActive);
	Shutdown();
}

void Level_2()
{
	GameActive = true;
	SetupSystem();
	Initialize2();
	do
	{
		Render();
		Update();
	} while (GameActive);
	Shutdown();
}

void Level_3()
{
	GameActive = true;
	SetupSystem();
	Initialize3();
	do
	{
		Render();
		Update();
	} while (GameActive);
	Shutdown();
}

/*---------------------------------MAIN----------------------------------------------------------------------------------*/
int main()
{
	Level_1();

/*--------------------------------------Level 2-------------------------------------------------------------------------*/
	
	Level_2();

/*--------------------Level 3---------------------------------------------------------------------------------------*/

	Level_3();

	return 0;
}