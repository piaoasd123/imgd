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

void Creature::step()
{
	//this will be extended by children
}

void Creature::takeInput(char input)
{
	//this will be extended by children
}

int Creature::getMyX()
{
	return here->myX;
}

int Creature::getMyY()
{
	return here->myY;
}