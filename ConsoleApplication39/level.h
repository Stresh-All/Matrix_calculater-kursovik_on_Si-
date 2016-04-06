#pragma once
#include "consoleColor.h"

const int rowsCount1 = 15;
const int columsCount1 = 35;

const  int rowsCount2 = 24;
const  int columsCount2 = 27;

const int heartHeal = 150;

const char fogOfWarRenderSymbol = 176;
ConsoleColor fogOfWarRenderColor = ConsoleColor_DarkGray;

const char SymbolEmpty = ' ';
const char SymbolWall = '#';
const char SymbolHero = 'h';
const char SymbolExit = 'e';
const char SymbolOrc = 'o';
const char SymbolSkeleton = 's';
const char SymbolStick = '1';
const char SymbolClub = '2';
const char SymbolSpear = '3';
const char SymbolSaber = '4';
const char SymbolHeart = '+';

//планируется
const char SymbolSword = '5';
const char SymbolWhip = '6';
const char SymbolMoustache = '7';
const char SymbolBoos1 = 'T';
const char SymbolBoos2 = 'B';
const char SymbolBoos3 = 'K';
const char SymbolBoos4 = 'S';
const char SymbolFalx = '8';
const char SymbolGlee = '*';

//Wepon for Boss
//..
const char SymbolMMA = 131;
const char SymbolWorkBook = 8;
const char SymbolCi = 123;
const char SymbolS = 138;



const char levelData1[rowsCount1][columsCount1 + 1] = {
	"###################################",
	"#   #+##      o           s       #",
	"# # o  #o############## ######### #",
	"# ###### #   #+#3  s  # ##s##   # #",
	"#  s       # # ###### # #s4   #s# #",
	"###### # ### #      # # ##s##   # #",
	"##  o# # # # #### # #   ##### # # #",
	"#+ #   # # o    # ##+######+#   # #",
	"######## # ####         #  s# # #s#",
	"#  2#    #      ####### # # #   # #",
	"# ### #### ######   o   # #   #   #",
	"#  o       #      ####### #########",
	"############ ######   #1# #   #   #",
	"#h                                #",
	"#################################e#",
};

const char levelData2 [rowsCount2][columsCount2 + 1] = {
	"#e##################",
	"# #  # #   ####    #",
	"# ## # # #    # ## #",
	"#      # #### #  # #",
	"###### # #  # ## # #",
	"#  #     ##      # #",
	"# ## #####  # #### #",
	"#        #### #    #",
	"###### ###    # ####",
	"##   #  ## ####    #",
	"#  #     #    #### #",
	"############# #    #",
	"#             # ####",
	"# ## ##########    #",
	"# #   #   #     ## #",
	"# ## ## # ### #    #",
	"# #   # #   ########",
	"# # # # # #        #",
	"# # # # # ######## #",
	"# # # # #          #",
	"# # #   # ###### # #",
	"# # #####   # #  # #",
	"#h#     ###   # ## #",
	"####################",
};

const char levelData3[rowsCount1][columsCount1 + 1] = {
	"#################e#################",
	"#   #    # ##   # #        #      #",
	"# # ####   s  ### # ######## #### #",
	"# #     ##### # # #   s #     #   #",
	"# #####      s# # #### ## ####### #",
	"#      ######## # # #  #      # # #",
	"######          # #     ##### # #Y#",
	"#      ########## #####     # # ###",
	"# ######   #  # # #      ###      #",
	"# #    # # #    # # ####   # ######",
	"# # #### # #### # #    r#### ##   #",
	"# #      #      # #        #    # #",
	"# ###### ########3######## ###### #",
	"# o              h 6  *         o #",
	"###################################",
};

const char levelData4[rowsCount1][columsCount1 + 1] = {
	"#e#################################",
	"#              S                  #",
	"################################# #",
	"#                              +# #",
	"#7                          K     #",
	"# #################################",
	"# #   B          6             +  #",
	"# # ############################  #",
	"# # #           +#                #",
	"# # #            #                #",
	"#   # ############                #",
	"#####            #     T          #",
	"#                #                #",
	"#h             765                #",
	"###################################",
};

unsigned char GetRenderCellSymbol(unsigned char cellSymbol)
{
	switch (cellSymbol)
	{
	case SymbolEmpty:          return ' ';
	case SymbolWall:           return 177;
	case SymbolHero:           return 2;
	case SymbolOrc:            return 2;
	case SymbolSkeleton:       return 2;
	case SymbolStick:          return 47;
	case SymbolClub:           return 33;
	case SymbolSpear:          return 24;
	case SymbolSaber:          return 108;
	case SymbolExit:           return 178;
	case SymbolHeart:          return 3;

	//Обновление
	case SymbolSword:          return 134;
	case SymbolWhip:           return 244;
	case SymbolMoustache:      return 236;
	case SymbolFalx:           return 135;
	case SymbolBoos1:          return 84;
	case SymbolBoos2:          return 66;
	case SymbolBoos3:          return 75;
	case SymbolBoos4:          return 83;
	case SymbolGlee:           return 176;//моб
	}

	return '0';
}

ConsoleColor GetRenderCellSymbolColor(unsigned char cellSymbol)
{
	switch (cellSymbol)
	{
	case SymbolEmpty:          return ConsoleColor_Black;
	case SymbolWall:           return ConsoleColor_White;
	case SymbolHero:           return ConsoleColor_Yellow;
	case SymbolOrc:            return ConsoleColor_Green;
	case SymbolSkeleton:       return ConsoleColor_White;
	case SymbolStick:          return ConsoleColor_DarkYellow;
	case SymbolClub:           return ConsoleColor_DarkRed;
	case SymbolSpear:          return ConsoleColor_DarkCyan;
	case SymbolSaber:          return ConsoleColor_Cyan;
	case SymbolExit:           return ConsoleColor_DarkRed;
	case SymbolHeart:          return ConsoleColor_Red;

		//Обновление 
	case SymbolSword:          return ConsoleColor_DarkRed;
	case SymbolWhip:           return ConsoleColor_Blue;
	case SymbolMoustache:      return ConsoleColor_Black;
	case SymbolFalx:           return ConsoleColor_Green;
	case SymbolBoos1:          return ConsoleColor_White;
	case SymbolBoos2:          return ConsoleColor_DarkCyan;
	case SymbolBoos3:          return ConsoleColor_DarkGreen;
	case SymbolBoos4:          return ConsoleColor_Red;
	case SymbolGlee:           return ConsoleColor_DarkGreen;//моб
	case SymbolMMA:            return ConsoleColor_DarkGreen;
	case SymbolCi:             return ConsoleColor_DarkYellow;
	case SymbolWorkBook:       return ConsoleColor_Blue;
	case SymbolS:              return ConsoleColor_Red;
	}

	return ConsoleColor_Gray;
}