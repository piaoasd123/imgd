#include "StdAfx.h"
#include "SampleFEAI.h"


SampleFEAI::SampleFEAI(void)
{
}


SampleFEAI::~SampleFEAI(void)
{
}

FEMoveOrder SampleFEAI::getNextMove(FEBattleField* currentBattleField, LinkedList<FEUnit>* unitsToMove)
{
	FEMoveOrder retVal;
	LinkedList<FEUnit>* PlayerUnits = currentBattleField->getPlayerUnits();
	retVal.unitToMove = unitsToMove->getFirst()->first;
	retVal.endX = retVal.unitToMove->getMyX();
	retVal.endY = retVal.unitToMove->getMyY();
	retVal.attackTarget = nullptr;
	return retVal;
}