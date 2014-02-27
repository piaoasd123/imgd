#pragma once

#include "Pile.h"
#include "Dungeon.h"
#include "Cell.h"

class Cell;

class Creature
{
public:
	Creature(void);
	Creature(char face, int skin);
	~Creature(void);
	ColorChar getColorChar();
	virtual void step(); //advances one game tic
	virtual void takeInput(char in);
protected:
	Pile* inventory;
	char face; //the glyph used to represent this creature
	int skin; //the color of that glyph
	Cell* here; //the cell that this creature is in
	int getMyX(); //returns the x value of the current Cell
	int getMyY(); //returns the x value of the current Cell

friend class Cell;
friend class Dungeon;
};

