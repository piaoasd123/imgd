#include "StdAfx.h"
#include "FEUnit.h"
#include <stdlib.h>


FEUnit::FEUnit(char face, int skin, int team, int speed, int range, int might, int defense, int accuracy, int avoid, int hp, string name) : Creature(face, skin)
{
	player = team;
	move = speed;
	this->range = range;
	this->might = might;
	this->defense = defense;
	this->accuracy = accuracy;
	this->avoid = avoid;
	maxHp = hp;
	currentHp = hp;
	this->name = name;
}


FEUnit::~FEUnit(void)
{
}

void FEUnit::attack(FEUnit* enemy)
{
	//assume range is checked elsewhere
	if(enemy->defense >= might)
		return; //attack has no effect
	if(enemy->avoid >= accuracy)
		return; //never hit
	//roll to hit
	int toHitRoll = (rand() % 100) + (rand() % 100); //using dynamic hit
	if(toHitRoll <= (accuracy - enemy->avoid) * 2)
	{
		//hit
		enemy->currentHp -= (might - enemy->defense);
		if(enemy->currentHp <= 0)
		{
			//kill the enemy
			delete enemy;
		}
	}
}

int FEUnit::getTeam()
{
	return player;
}

bool FEUnit::getIsActive()
{
	return isActive;
}

ColorChar FEUnit::getColorChar()
{
	ColorChar retVal = Creature::getColorChar();
	if(!isActive)
	{
		retVal.color = 0; //black when inactive
	}
	return retVal;
}

void FEUnit::activate()
{
	isActive = true;
}

void FEUnit::deactivate()
{
	isActive = false;
}

int FEUnit::getMove()
{
	return move;
}

int FEUnit::getRange()
{
	return range;
}

string FEUnit::getName()
{
	return name;
}

int FEUnit::getHp()
{
	return currentHp;
}

int FEUnit::getMight()
{
	return might;
}

int FEUnit::getDefense()
{
	return defense;
}

int FEUnit::getAccuracy()
{
	return accuracy;
}

int FEUnit::getAvoid()
{
	return avoid;
}

int FEUnit::getMaxHp()
{
	return maxHp;
}