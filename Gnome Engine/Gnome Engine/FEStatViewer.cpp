#include "StdAfx.h"
#include "FEStatViewer.h"

#define HEIGHT 5
#define WIDTH 11

FEStatViewer::FEStatViewer(void)
{
	screen = new char[55];
	//there must be a more compressed way to do this
	screen[0] = 'N'; screen[1] = 'a';
	screen[11] = 'H'; screen[12] = 'p';
	screen[22] = 'M'; screen[23] = 'i';
	screen[27] = 'A'; screen[28] = 'c';
	screen[33] = 'D'; screen[34] = 'e';
	screen[38] = 'A'; screen[39] = 'v';
	screen[44] = 'M'; screen[45] = 'o';
	screen[49] = 'R'; screen[50] = 'a';
	for(int counter = 0; counter < 5; counter++)
	{
		screen[2 + WIDTH * counter] = ':';
	}
	for(int counter = 2; counter < 5; counter++)
	{
		screen[7 + WIDTH * counter] = ':';
	}
	for(int counter = 0; counter < 2; counter++)
	{
		for(int counte = 3; counte < WIDTH; counte++)
		{
			screen[counte + counter * WIDTH] = ' ';
		}
	}
	for(int counter = 2; counter < HEIGHT; counter++)
	{
		for(int counte = 3; counte < 5; counte++)
		{
			screen[counte + counter * WIDTH] = ' ';
		}
	}
	for(int counter = 2; counter < HEIGHT; counter++)
	{
		for(int counte = 8; counte < WIDTH; counte++)
		{
			screen[counte + counter * WIDTH] = ' ';
		}
	}
	screen[16] = '/';
}


FEStatViewer::~FEStatViewer(void)
{
	delete screen;
}

ColorChar FEStatViewer::getColorChar(int x, int y)
{
	ColorChar retVal = ColorChar();
	retVal.color = 7; //white on black
	retVal.glyph = screen[x + y * WIDTH];
	return retVal;
}

void FEStatViewer::setUnit(FEUnit* newUnit)
{
	string tempString = newUnit->getName();
	for(int counter = 0; counter < 8; counter++)
	{
		screen[3+counter] = tempString[counter];
	}
	int temp = newUnit->getHp();
	screen[14]=(temp/10) + 48;
	screen[15]=(temp%10) + 48;
	temp = newUnit->getMaxHp();
	screen[17]=(temp/10) + 48;
	screen[18]=(temp%10) + 48;
	temp = newUnit->getMight();
	screen[25]=(temp/10) + 48;
	screen[26]=(temp%10) + 48;
	temp = newUnit->getAccuracy();
	screen[30]=(temp/100) + 48;
	screen[31]=((temp/10) % 10) + 48;
	screen[32]=(temp%10) + 48;
	temp = newUnit->getDefense();
	screen[36]=(temp/10) + 48;
	screen[37]=(temp%10) + 48;
	temp = newUnit->getAvoid();
	screen[41]=(temp/100) + 48;
	screen[42]=((temp/10) % 10) + 48;
	screen[43]=(temp%10) + 48;
	temp = newUnit->getMove();
	screen[47]=(temp/10) + 48;
	screen[48]=(temp%10) + 48;
	temp = newUnit->getRange();
	screen[52]=(temp/10) + 48;
	screen[53]=(temp%10) + 48;
}