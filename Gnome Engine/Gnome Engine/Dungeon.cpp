#include "StdAfx.h"
#include "Dungeon.h"


Dungeon::Dungeon(void)
{
}


Dungeon::~Dungeon(void)
{
}

void Dungeon::takeInput(char in)
{
}

void Dungeon::step(void)
{
}

ColorChar Dungeon::getColorChar(int x, int y)
{
	return contents[y * width + x].getColorChar();
}