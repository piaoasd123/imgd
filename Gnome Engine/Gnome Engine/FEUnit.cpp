/*#include "StdAfx.h"
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
}*/

#include "StdAfx.h"
#include "FEUnit.h"
#include <stdlib.h>

FEUnit::FEUnit(char _face, int _skin, int _team, StatBlock* _stats, int _range, WEAPON_TYPE _weapon_type, int _weapon_accuracy, int _weapon_crit, string _name) : Creature(_face, _skin)
{
	player = _team;
	stats = _stats;
	range = _range;
	weapon_type = _weapon_type;
	weapon_accuracy = _weapon_accuracy;
	weapon_crit = _weapon_crit;
	name = _name;
}


FEUnit::~FEUnit(void)
{
}

bool FEUnit::attack(FEUnit* enemy, bool counter)
{
	//assume range is checked elsewhere
	int enemy_dr = enemy->getDamageReduction(weapon_type);
	int enemy_avoid = enemy->getAvoid(weapon_type);
	int base_damage = getBaseDamage();
	int base_accuracy = getBaseAccuracy();
	bool enemy_killed = false;
	if(enemy_dr >= base_damage)
		return enemy_killed; //attack has no effect
	if(enemy_avoid >= base_accuracy)
		return enemy_killed; //never hit
	//roll to hit
	int toHitRoll =  ( (rand() % 100) + (rand() % 100) ) / 2; //using dynamic hit
	if(toHitRoll <= (base_accuracy - enemy_avoid))
	{
		//hit
		int total_damage = base_damage - enemy_dr;
		int crit_chance = getBaseCritChance() - enemy->getStats().luck;
		if( ( rand() % 100) <= crit_chance ) total_damage *= 2;
		enemy_killed = enemy->modifyHP(-total_damage);
		if(enemy_killed) delete enemy;
		else
		{
			bool killed_by_counter = false;
			if (!counter) killed_by_counter = enemy->attack(this, true);
			if(!killed_by_counter && stats->speed >= enemy->getStats().speed + 4) //double attack for high speed
			{
				toHitRoll = ( (rand() % 100) + (rand() % 100) ) / 2; //using dynamic hit
				if(toHitRoll <= (base_accuracy - enemy_avoid))
				{
					int total_damage = base_damage - enemy_dr;
					int crit_chance = getBaseCritChance() - enemy->getStats().luck;
					if( ( rand() % 100) <= crit_chance ) total_damage *= 2;
					bool enemy_killed = enemy->modifyHP(-total_damage);
					if(enemy_killed) delete enemy;
				}
			}
		}
	}
	return enemy_killed;
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

StatBlock FEUnit::getStats()
{
	return *stats;
}

int FEUnit::getRange()
{
	return range;
}

string FEUnit::getName()
{
	return name;
}

int FEUnit::getDamageReduction(WEAPON_TYPE against)
{
	int dr;
	switch(against)
	{
	case SWORD:
		dr = stats->defense;
		if(weapon_type == AXE) dr += 1;
		else if(weapon_type == LANCE) dr -= 1;
		break;
	case AXE:
		dr = stats->defense;
		if(weapon_type == LANCE) dr += 1;
		else if(weapon_type == SWORD) dr -= 1;
		break;
	case LANCE:
		dr = stats->defense;
		if(weapon_type == SWORD) dr += 1;
		else if(weapon_type == AXE) dr -= 1;
		break;
	case BOW:
		dr = stats->defense;
		break;
	case ANIMA:
		dr = stats->resist;
		if(weapon_type == LIGHT) dr += 1;
		else if(weapon_type == DARK) dr -= 1;
		break;
	case LIGHT:
		dr = stats->resist;
		if(weapon_type == DARK) dr += 1;
		else if(weapon_type == ANIMA) dr -= 1;
		break;
	case DARK:
		dr = stats->resist;
		if(weapon_type == ANIMA) dr += 1;
		else if(weapon_type == LIGHT) dr -= 1;
		break;
	case STAFF:
		dr = 0;
		break;
	}
	return dr;
}

int FEUnit::getAvoid(WEAPON_TYPE against)
{
	int avoid = stats->luck + ( 2 * stats->speed);
	switch(against)
	{
	case SWORD:
		if(weapon_type == AXE) avoid += 15;
		else if(weapon_type == LANCE) avoid -= 15;
		break;
	case AXE:
		if(weapon_type == LANCE) avoid += 15;
		else if(weapon_type == SWORD) avoid -= 15;
		break;
	case LANCE:
		if(weapon_type == SWORD) avoid += 15;
		else if(weapon_type == AXE) avoid -= 15;
		break;
	case BOW:
		break;
	case ANIMA:
		if(weapon_type == LIGHT) avoid += 15;
		else if(weapon_type == DARK) avoid -= 15;
		break;
	case LIGHT:
		if(weapon_type == DARK) avoid += 15;
		else if(weapon_type == ANIMA) avoid -= 15;
		break;
	case DARK:
		if(weapon_type == ANIMA) avoid += 15;
		else if(weapon_type == LIGHT) avoid -= 15;
		break;
	case STAFF:
		break;
	}
	return avoid;
}

int FEUnit::getBaseDamage()
{
	int base_damage;
	if(weapon_type == SWORD || weapon_type == LANCE || weapon_type == AXE || weapon_type == BOW) base_damage = stats->strength;
	else if(weapon_type == ANIMA || weapon_type == LIGHT || weapon_type == DARK || weapon_type == STAFF) base_damage = stats->magic;
	return base_damage;
}

int FEUnit::getBaseAccuracy()
{
	return stats->luck + (2 * stats->skill) + weapon_accuracy;
}

int FEUnit::getBaseCritChance()
{
	return stats->skill /2 + weapon_crit;
}

bool FEUnit::modifyHP(int change)
{
	stats->current_hp += change;
	if(stats->current_hp >= stats->max_hp) stats->current_hp = stats->max_hp;
	if(stats->current_hp <= 0) return true;
	else return false;
}

int FEUnit::getMove()
{
	return stats->move;
}