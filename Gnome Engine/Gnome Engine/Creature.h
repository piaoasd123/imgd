#pragma once

#include "Pile.h"
#include "Map.h"

class Creature
{
public:
	Creature(void);
	~Creature(void);
	ColorChar getColorChar();
private:
	Pile* inventory;
	char face; //the glyph used to represent this creature
	int skin; //the color of that glyph
};

