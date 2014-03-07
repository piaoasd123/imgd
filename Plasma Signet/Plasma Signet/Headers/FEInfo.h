#pragma once
//parameters of the connectX game
#include "FE.h"

#define GAMENAME FE

//initiallize all the pairs
/*
        COLOR_BLACK   0
        COLOR_RED     1
        COLOR_GREEN   2
        COLOR_YELLOW  3
        COLOR_BLUE    4
        COLOR_MAGENTA 5
        COLOR_CYAN    6
        COLOR_WHITE   7
*/
#define COLORMAP \
	for(int i = 0; i < 8; i++) \
	{ \
		for(int j = 0; j < 8; j++) \
		{ \
			init_pair(i * 8 + j, j, i); \
		} \
	}