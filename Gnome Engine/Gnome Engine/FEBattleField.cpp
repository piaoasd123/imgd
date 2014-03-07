#include "StdAfx.h"
#include "FEBattleField.h"
#include <algorithm> 

using namespace std;

FEBattleField::FEBattleField(int numberOfPlayers, int height, int width, FEStatViewer* statViewer) : Dungeon(height, width)
{
	activeUnit = nullptr;
	cursorX = 0;
	cursorY = 0;
	moveCounter = 0;
	flashCounter = 0;
	currentTurn = 0;
	numPlayers = numberOfPlayers;
	unitsOnField = 0;
	unitCounts = new LinkedList<FEUnit>*[numberOfPlayers];
	factionAIs = new FEAIInterface*[numberOfPlayers];
	for(int counter = 0; counter < numberOfPlayers; counter++)
	{
		unitCounts[counter] = new LinkedList<FEUnit>();
		factionAIs[counter] = nullptr;
	}
	attackMode = false;
	statWindow = statViewer;
	unitsToMove = new LinkedList<FEUnit>();
	terrainObjects = new int*[width];
	for (int i = 0; i < width; i++)
		terrainObjects[i] = new int[height];
}


FEBattleField::~FEBattleField(void)
{
	for(int counter = 0; counter < numPlayers; counter++)
	{
		delete unitCounts[counter];
		delete factionAIs;
	}
	delete unitCounts;
}

ColorChar FEBattleField::getColorChar(int x, int y)
{
	ColorChar retVal = contents[x + y * width]->getColorChar();
	if(x == cursorX && y == cursorY && flashCounter > 10)
	{
		retVal.color = 56; //black on white
	}
	else if(activeUnit != nullptr)
	{
		if(attackMode)
		{
			if(getDistance(activeUnit->getMyX(), activeUnit->getMyY(), x, y) <= activeUnit->getRange() &&
				(!contents[x + y * width]->hasOccupant() || static_cast<FEUnit*>(contents[x + y * width]->getOccupant())->getTeam() != activeUnit->getTeam()))
			{
				retVal.color = (retVal.color % 8) + 40; //angry background
			}
		}
		else
		{
			//blue field can be moved to
			if(!contents[y * width + x]->hasOccupant() && getDistance(activeUnit->getMyX(), activeUnit->getMyY(), x, y) <= activeUnit->getMove())
			{
				retVal.color = (retVal.color % 8) + 24; //cyan background
			}
			else if(getDistance(activeUnit->getMyX(), activeUnit->getMyY(), x, y) <= activeUnit->getMove() + activeUnit->getRange() &&
				(!contents[x + y * width]->hasOccupant() || static_cast<FEUnit*>(contents[x + y * width]->getOccupant())->getTeam() != activeUnit->getTeam()))
			{
				retVal.color = (retVal.color % 8) + 40; //angry background
			}
		}
	}
	return retVal;
}

bool FEBattleField::enter(Creature* newCreature, int x, int y)
{
	//TODO: check that newCreature is an FE creature, somehow
/*	if(typeid (newCreature) != typeid(FEUnit*)) //extensions should be allowed; I'll have to rewrite this check
	{
		return false;
	}*/
	bool attempt = Dungeon::enter(newCreature, x, y);
	if(!attempt)
	{
		return false;
	}
	unitsOnField++;
	unitCounts[(static_cast <FEUnit*>(newCreature))->getTeam()]->insert(static_cast <FEUnit*>(newCreature));
	if((static_cast <FEUnit*>(newCreature))->getTeam() == currentTurn)
	{
		unitsToMove->insert(static_cast <FEUnit*>(newCreature));
	}
	return true;
}

void FEBattleField::exit(int x, int y)
{
	if(contents[x + y * width]->getOccupant() != nullptr)
	{
		if(contents[x + y * width]->getOccupant() == activeUnit)
		{
			finishMoving();
		}
		totalUnits--;
		unitCounts[static_cast<FEUnit*>(contents[x + y * width]->getOccupant())->getTeam()]->remove(static_cast<FEUnit*>(contents[x + y * width]->getOccupant()));
		unitsToMove->remove(static_cast<FEUnit*>(contents[x + y * width]->getOccupant()));
	}
	Dungeon::exit(x, y);
}

void FEBattleField::takeInput(char in) //finish this function
{
	if(moveCounter > 8 && factionAIs[currentTurn] == nullptr)
	{
		moveCounter = 0;
		//if there's a num key, move the cursor
		if(in >= '1' && in <= '9')
		{
			if(in % 3 == 1)
			{
				cursorX--;
				cursorX = max(cursorX, 0);
			}
			else if(in % 3 == 0)
			{
				cursorX++;
				cursorX = min(cursorX, width - 1);
			}
			if(in < '4')
			{
				cursorY++;
				cursorY = min(cursorY, height - 1);
			}
			else if(in > '6')
			{
				cursorY--;
				cursorY = max(cursorY, 0);
			}
			//if we moused over a unit, display it
			if(contents[width * cursorY + cursorX]->hasOccupant())
			{
				statWindow->setUnit(static_cast<FEUnit*>(contents[width * cursorY + cursorX]->getOccupant()));
			}
		}
		else if(in == 'a') //select
		{
			//if no unit is selected, select the unit in the current cell
			if(activeUnit == nullptr)
			{
				if(contents[cursorX + cursorY * width]->hasOccupant())
				{
					activeUnit = static_cast<FEUnit*> (contents[cursorX + cursorY * width]->getOccupant());
					if(!activeUnit->getIsActive() || activeUnit->getTeam() != currentTurn)
					{
						activeUnit = nullptr; //can't select inactive units
					}
				}
			}
			else if(attackMode)
			{
				//try to attack the unit at the indicated location
				if(canAttack(activeUnit, cursorX, cursorY))
				{
					activeUnit->attack(static_cast<FEUnit*>(contents[cursorX + cursorY * width]->getOccupant()));
					finishMoving();
				}
			}
			else //a unit is selected, so try to move to the indicated location
			{
				//first check if there is enough range
				if(canMove(activeUnit, cursorX, cursorY))
				{
					if(activeUnit->getMyLocation()->tryToMoveToCell(contents[cursorX + cursorY * width], false))
					{
						attackMode = true;
					}
				}
			}
		}
		else if(in == 'b') //cancel
		{
			if(attackMode)
			{
				finishMoving();
			}
		}
	}
}

void FEBattleField::step()
{
	flashCounter = (flashCounter + 1) % 15;
	moveCounter++;
	if(moveCounter >= 24 && factionAIs[currentTurn] != nullptr)
	{
		FEMoveOrder thisOrder = factionAIs[currentTurn]->getNextMove(this, unitsToMove);
		//execute the order
		activeUnit = thisOrder.unitToMove;
		if(canMove(activeUnit, thisOrder.endX, thisOrder.endY))
		{
			activeUnit->getMyLocation()->tryToMoveToCell(contents[thisOrder.endX + thisOrder.endY * width], false);
		}
		if(thisOrder.attackTarget != nullptr && canAttack(activeUnit, thisOrder.attackTarget->getMyX(), thisOrder.attackTarget->getMyY()))
		{
			activeUnit->attack(thisOrder.attackTarget);
		}
		finishMoving();
	}
}

inline int FEBattleField::getDistance(int xStart, int yStart, int xEnd, int yEnd)
{
	return abs(xStart - xEnd) + abs(yStart - yEnd);
}

void FEBattleField::finishMoving()
{
	if(activeUnit != nullptr)
	{
		activeUnit->deactivate();
		unitsToMove->remove(activeUnit);
	}
	attackMode = false;
	activeUnit = nullptr;
	//check if there are any activeUnits left of the current team
	bool anyUnitsLeft = false;
	forEach(FEUnit, counter, unitCounts[currentTurn]->getFirst())
	{
		if(counter->first->getIsActive())
		{
			anyUnitsLeft = true;
			break;
		}
	}
	if(!anyUnitsLeft) //no units left to move so advance the turn
	{
		//make all inactive units active
		forEach(FEUnit, counter, unitCounts[currentTurn]->getFirst())
		{
			counter->first->activate();
		}
		do
		{
			currentTurn = (currentTurn + 1) % numPlayers;
		}
		while(unitCounts[currentTurn]->getFirst() == nullptr); //skip the turns of anyone with no units
		delete unitsToMove;
		unitsToMove = unitCounts[currentTurn]->copyList();
	}
}

inline bool FEBattleField::canMove(FEUnit* movingUnit, int x, int y)
{
	return getDistance(movingUnit->getMyX(), movingUnit->getMyY(), x, y) <= movingUnit->getMove();
}

inline bool FEBattleField::canAttack(FEUnit* attackingUnit, int x, int y)
{
	return getDistance(attackingUnit->getMyX(), attackingUnit->getMyY(), x, y) <= attackingUnit->getRange() &&
	contents[x + y * width]->hasOccupant() &&
	static_cast<FEUnit*>(contents[x + y * width]->getOccupant())->getTeam() != attackingUnit->getTeam();
}

void FEBattleField::setAI(FEAIInterface* newAI, int faction)
{
	factionAIs[faction] = newAI;
}

LinkedList<FEUnit>* FEBattleField::getPlayerUnits()
{
	return unitCounts[0];
}

LinkedList<FEUnit>* FEBattleField::getAIUnits()
{
	return unitCounts[1];
}

int FEBattleField::InitTerrain(int map[], int x, int y)
{
	if (x != width || y != height)
		return -1;
	else {
		for (int i = 0; i < x; i++)
		for (int j = 0; j < y; j++) {
			if (map[i*y+j] == 1) {
				terrainObjects[i][j] = map[i*y+j];
				this->enter(new FEUnit('X', 4, 1, 0, 0, 0, 0, 0, 0, 0, "Rock   "), i, j);
			}
		}
	}
	return 0;
}