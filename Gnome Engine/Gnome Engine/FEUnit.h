#pragma once
#include "creature.h"
#include <string>
#include <vector>
#include "FEConsole.h"

using namespace std;

enum WEAPON_TYPE {SWORD, AXE, LANCE, BOW, ANIMA, LIGHT, DARK, STAFF, ITEM};

struct Proficiency
{
	int sword;
	int axe;
	int lance;
	int anima;
	int light;
	int dark;
	int staff;

	Proficiency(){}
	Proficiency(int _sword, int _axe, int _lance, int _anima, int _light, int _dark, int _staff)
	{
		sword = _sword;
		axe = _axe;
		lance = _lance;
		anima = _anima;
		light = _light;
		dark = _dark;
		staff = _staff;
	}
};

struct StatBlock
{
	int max_hp;
	int strength;
	int magic;
	int defense;
	int resist;
	int skill;
	int speed;
	int luck;
	int move;
	Proficiency proficiencies;

	StatBlock(){}
	StatBlock( int _hp, int _strength, int _magic, int _defense, int _resist, int _skill, int _speed, int _luck, int _move, Proficiency _proficiencies)
	{
		max_hp = _hp;
		strength = _strength;
		magic = _magic;
		defense = _defense;
		resist = _resist;
		skill = _skill;
		speed = _speed;
		luck = _luck;
		move = _move;
		proficiencies = _proficiencies;
	}
};

using namespace std;

class FEUnit :	public Creature
{
public:
	FEUnit(char _face, int _skin, int _team, StatBlock* _stats, int _range, int _minRange, WEAPON_TYPE _weapon_type, int _weapon_accuracy, int _weapon_crit, string _name);
	~FEUnit(void);
	bool attack(FEUnit* enemy, bool counter, FEConsole* log);
	virtual ColorChar getColorChar();
	int getTeam();
	bool getIsActive();
	void activate(); //make active
	void deactivate(); //make inactive
	string getName();
	//stat getters
	StatBlock getStats();
	int getDamageReduction(WEAPON_TYPE);
	int getAvoid(WEAPON_TYPE);
	int getBaseDamage(); //given weapon type, strength or magic
	int getBaseAccuracy(); //given skill, luck, and weapon accuracy
	int getBaseCritChance(); //given skill
	
	bool modifyHP(int change); //returns true if unit is destroyed, otherwise false
	int getRange();
	int getMinRange();
	bool inRange(int distance);
	int getMove();
	int getCurrentHP();
	FEUnit* clone();
private:
	StatBlock* stats;
	int range; //should be 1 to 6 or so //should come from first item in inventory
	int minRange;
	WEAPON_TYPE weapon_type; //should come from first item in inventory
	int weapon_accuracy; //should come from first item in inventory
	int weapon_crit; //should come from first item in inventory
	bool isActive; //if this unit has moved yet this turn; true means it can still move
	int player; //the number of the player who owns this unit
	string name; //like "Sir Fred" or whatever this individual guy is called
	int currentHP;
	
//friend class FEBattleField;
};