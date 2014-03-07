#include "StdAfx.h"
#include "Dungeon.h"

Dungeon::Dungeon()
{
	Dungeon(side, side);
}

Dungeon::Dungeon(int height, int width)
{
	this->height = height;
	this->width = width;
	size = height * width;
	contents = new Cell*[size];
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			contents[i * width + j] = new Cell(this, j, i);
		}
	}
	
	//link up all the new cells
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			for(int k = -1; k <= 1; k++)
			{
				for(int l = -1; l <= 1; l++)
				{
					if((i + k >= 0) && (i + k < height) &&
						(j + l >= 0) && (j + l < width))
					{
						contents[i * width + j]->
							makeCellAdjecent(contents[(i + k) * width + j + l]);
					}
				}
			}
		}
	}
}


Dungeon::~Dungeon(void)
{
}

void Dungeon::takeInput(char in)
{
	//tell each cell to step
	for(int counter = 0; counter < size; counter++)
	{
		contents[counter]->takeInput(in);
	}
}

void Dungeon::step(void)
{
	//tell each cell to step
	for(int counter = 0; counter < size; counter++)
	{
		contents[counter]->step();
	}
}

ColorChar Dungeon::getColorChar(int x, int y)
{
	if(y * width + x < size)
	{
		return contents[y * width + x]->getColorChar();
	}
	else
	{
		ColorChar retVal;
		retVal.color = 0;
		retVal.glyph = ' ';
		return retVal;
	}
}

LinkedList<Cell>* Dungeon::getAdjecentCells(int x, int y)
{
	return contents[x * y * width]->getAdjecentCells();
}

bool Dungeon::enter(Creature* newCreature, int x, int y)
{
	if(!(contents[y * width + x]->hasOccupant()))
	{
		contents[y * width + x]->spawn(newCreature);
		return true;
	}
	else
	{
		return false;
	}
}

void Dungeon::exit(int x, int y)
{
	contents[x + y * width]->despawn();
}

Cell* Dungeon::getCell(int x, int y)
{
	return contents[x + y * width];
}