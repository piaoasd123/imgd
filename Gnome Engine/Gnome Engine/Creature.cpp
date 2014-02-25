#include "StdAfx.h"
#include "Creature.h"


Creature::Creature(void)
{
	inventory = new Pile();
}


Creature::~Creature(void)
{
	delete inventory;
}

ColorChar Creature::getColorChar(void)
{
	ColorChar retVal = ColorChar();
	retVal.color = skin;
	retVal.glyph = face;
	return retVal;
}