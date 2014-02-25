#pragma once
#include "map.h"
#include "Cell.h"
class Dungeon :	public Map
{
public:
	Dungeon(void);
	~Dungeon(void);
	void takeInput(char in);
	void step(void);
	ColorChar getColorChar(int x, int y);
private:
	//lets assume all dungeons are on orthogonal grids
	int height;
	int width;
	Cell* contents; //this is an array; assume a null value is impassible, but generally these should be avoided
};

