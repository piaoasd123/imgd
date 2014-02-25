#pragma once

#include "Creature.h"
#include "Pile.h"
#include "Map.h"

class Cell
{
public:
	Cell(void);
	~Cell(void);
	ColorChar getColorChar(); //returns the color and character of the occupant of the cell
private:
	Creature* occupant; //the creature in this cell
	Pile* junk; //the items in this cell
	int ground; //the color of the floor in this tile
};

