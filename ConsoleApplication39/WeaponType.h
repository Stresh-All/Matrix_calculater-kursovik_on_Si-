#pragma once
#include "level.h"


enum WeaponType
{
	WeaponNo,
	WeaponFist,
	WeapoòStick,
	WeaponClub,
	WeaponSpear,
	WeaponSaber,
	//Update
	WeaponSword,
	WeaponWhip,
	WeaponMoustache,
	WeaponFalx,
	//weapon for Boss
	WeaponMMA,
	WeaponWorkBook,
	WeaponCi,
	WeaponSvito
};


const char* WeaponName_None = "BERESHNOV";
const char* WeaponName_Fist = "Fist of Semich";
const char* WeaponName_Stick = "Stick of Truth";
const char* WeaponName_Club = "MICHOLAPOV's mom";
const char* WeaponName_Spear = "Pika of Vlados-Dydos";
const char* WeaponName_Saber = "Saber of usless Toxa";

const char* WeaponName_Sword = "Seva's Sword";
const char* WeaponName_Whip = "Castelvania";
const char* WeaponName_Moustache = "Legendary Moustache";
const char* WeaponName_Falx = "Falx of stupid Artur";
const char* WeaponName_MMA = "Sbornik Kysnecova dla TR";
const char* WeaponName_WorkBook = "Churnal Starosti";
const char* WeaponName_Ci = "Bag in Labs";
const char* WeaponName_Svito = "Chrenovie STUTOCHKI";

const char* GetWeaponName(WeaponType weaponType)
{
	switch (weaponType)
	{
	case WeaponFist:           return WeaponName_Fist;
	case WeapoòStick:          return WeaponName_Stick;
	case WeaponClub:           return WeaponName_Club;
	case WeaponSpear:          return WeaponName_Spear;
	case WeaponSaber:          return WeaponName_Saber;
		//Update
	case WeaponSword:         return WeaponName_Sword;
	case WeaponWhip:          return WeaponName_Whip;
	case WeaponMoustache:     return WeaponName_Moustache;
	case WeaponFalx:          return WeaponName_Falx;

	case WeaponCi: return WeaponName_Ci;
	case WeaponMMA: return WeaponName_MMA;
	case WeaponWorkBook: return WeaponName_WorkBook;
	case WeaponSvito: return WeaponName_Svito;
	}

	return WeaponName_None;
}

int GetWeaponDamage(WeaponType weaponType)
{
	switch (weaponType)
	{
	case WeaponFist:           return 6;
	case WeapoòStick:          return 16;
	case WeaponClub:           return 24;
	case WeaponSpear:          return 32;
	case WeaponSaber:          return 40;
		//Update
	case WeaponSword:         return 60;
	case WeaponWhip:          return 45;
	case WeaponMoustache:     return 500;
	case WeaponFalx:          return 30;

	case WeaponMMA:           return 50;
	case WeaponCi:            return 60;
	case WeaponSvito:         return 60;
	case WeaponWorkBook:      return 45;
	}

	return 0;
}

WeaponType GetWeaponTypeFromCell(unsigned char cellSymbol)
{
	switch (cellSymbol)
	{
	case SymbolStick:          return WeapoòStick;
	case SymbolClub:           return WeaponClub;
	case SymbolSpear:          return WeaponSpear;
	case SymbolSaber:          return WeaponSaber;

		//Update
	case SymbolSword:          return WeaponSword;
	case SymbolWhip:           return WeaponWhip;
	case SymbolMoustache:      return WeaponMoustache;
	case SymbolFalx:           return WeaponFalx;

	//Weapon of Boss
	//..
	case SymbolMMA:            return WeaponMMA;
	case SymbolWorkBook:       return WeaponWorkBook;
	case SymbolCi:             return WeaponCi;
	case SymbolS:              return WeaponSvito;

	}

	return WeaponNo;
}