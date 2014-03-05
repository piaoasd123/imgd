#pragma once
#include "dungeon.h"
#include "FEUnit.h"
#include "FEStatViewer.h"
#include "FEAIInterface.h"

class FEAIInterface;

class FEBattleField :	public Dungeon
{
public:
	FEBattleField(int numberOfPlayers, int height, int width, FEStatViewer* statWindow);
	~FEBattleField(void);
	void step();
	void takeInput(char in);
	ColorChar getColorChar(int x, int y);
	bool enter(Creature* newCreature, int x, int y);
	void exit(int x, int y);
	void setAI(FEAIInterface* newAI, int faction);
private:
	FEUnit* activeUnit; //this unit is selected
	int cursorX;
	int cursorY;
	int moveCounter;
	int flashCounter;
	int currentTurn; //whose turn it is
	int numPlayers;
	int unitsOnField;
	int totalUnits;
	LinkedList<FEUnit>** unitCounts; //for determining when the game is over
	int getDistance(int startX, int startY, int endX, int endY);
	bool attackMode; //true when done moving but about to attack
	void finishMoving(); //to be called when a unit becomes inactive
	FEStatViewer* statWindow;
	FEAIInterface** factionAIs;
	LinkedList<FEUnit>* unitsToMove;
	bool canMove(FEUnit* movingUnit, int x, int y);
	bool canAttack(FEUnit* attackingUnit, int x, int y);
};

