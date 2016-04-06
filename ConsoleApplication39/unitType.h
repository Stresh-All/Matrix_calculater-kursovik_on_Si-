#pragma once

#include "level.h"
#include "weaponType.h"

enum UnitType
{
	UnitNone,
	UnitHero,
	UnitOrc,
	UnitSkeleton,
	//Update
	UnitGlee,
	UnitT,
	UnitB,
	UnitK,
	UnitS
};

const char* UnitName_None = "None";
const char* UnitName_Hero = "Stresh";
const char* UnitName_Orc = "Orc";
const char* UnitName_Skeleton = "Skeleton";
//update
const char* UnitName_Glee = "Slabka";
const char* UnitName_T = "Tesla";
const char* UnitName_B = "WoRoNa";
const char* UnitName_K = "K";
const char* UnitName_S = "Svitko MC";

const char* GetUnitName(UnitType unitType)
{
	switch (unitType)
	{
	case UnitHero:     return UnitName_Hero;
	case UnitOrc:      return UnitName_Orc;
	case UnitSkeleton: return UnitName_Skeleton;
		//Update
	case UnitGlee:     return UnitName_Glee;
	case UnitT:        return UnitName_T;
	case UnitB:        return UnitName_B;
	case UnitK:        return UnitName_K;
	case UnitS:        return UnitName_S;
	}

	return UnitName_None;
}

WeaponType GetUnitDefaultWeapon(UnitType unitType)
{
	switch (unitType)
	{
	case UnitHero:             return WeaponFist;
	case UnitOrc:              return WeaponClub;
	case UnitSkeleton:         return WeaponSaber;
		//Update
	case UnitGlee:             return WeaponFalx;
	case UnitT:                return WeaponMMA;
	case UnitB:                return WeaponWorkBook;
	case UnitK:                return WeaponCi;
	case UnitS:                return WeaponSvito;
	}

	return WeaponNo;
}

int GetUnitDefaultHealth(UnitType unitType)
{
	switch (unitType)
	{
	case UnitHero:         return 500;
	case UnitOrc:          return 60;
	case UnitSkeleton:     return 80;
		//Update
	case UnitGlee:         return 100;
	case UnitT:            return 300;
	case UnitB:            return 400;
	case UnitK:            return 500;
	case UnitS:            return 600;
	}

	return 0;
}

UnitType GetUnitTypeFromCell(unsigned char cellSymbol)
{
	switch (cellSymbol)
	{
	case SymbolHero:               return UnitHero;
	case SymbolOrc:                return UnitOrc;
	case SymbolSkeleton:           return UnitSkeleton;
		//update
	case SymbolGlee:               return UnitGlee;
	case SymbolBoos1:              return UnitT;
	case SymbolBoos2:              return UnitB;
	case SymbolBoos3:              return UnitK;
	case SymbolBoos4:              return UnitS;
	}

	return UnitNone;
}