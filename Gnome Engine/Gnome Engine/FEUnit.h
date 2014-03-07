/*
#pragma once
#include "creature.h"
#include <string>

using namespace std;

class FEUnit :	public Creature
{
public:
	FEUnit(char face, int skin, int team, int speed, int range, int might, int defense, int accuracy, int avoid, int hp, string name);
	~FEUnit(void);
	void attack(FEUnit* enemy);
	virtual ColorChar getColorChar();
	int getTeam();
	bool getIsActive();
	void activate(); //make active
	void deactivate(); //make inactive
	int getMove();
	int getRange();
	string getName();
	int getHp();
	int getMight();
	int getDefense();
	int getAccuracy();
	int getAvoid();
	int getMaxHp();
private:
	int move;
	int range; //should be 1 to 6 or so
	int might; //or magic; same stat
	int defense; //or resist
	int accuracy; //skill and luck are unimportant, only speed
	int avoid; //same with speed and luck
	int currentHp; //maybe redundant with defense
	int maxHp;
	bool isActive; //if this unit has moved yet this turn; true means it can still move
	int player; //the number of the player who owns this unit
	string name; //like "Sir Fred" or whatever this individual guy is called
	
//friend class FEBattleField;
};
*/
#pragma once
#include "creature.h"
#include <string>
#include <vector>

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
	int current_hp;
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
		current_hp = _hp;
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
	FEUnit(char _face, int _skin, int _team, StatBlock* _stats, int _range, WEAPON_TYPE _weapon_type, int _weapon_accuracy, int _weapon_crit, string _name);
	~FEUnit(void);
	bool attack(FEUnit* enemy, bool counter);
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
	int getMove();
private:
	StatBlock* stats;
	int range; //should be 1 to 6 or so //should come from first item in inventory
	WEAPON_TYPE weapon_type; //should come from first item in inventory
	int weapon_accuracy; //should come from first item in inventory
	int weapon_crit; //should come from first item in inventory
	bool isActive; //if this unit has moved yet this turn; true means it can still move
	int player; //the number of the player who owns this unit
	string name; //like "Sir Fred" or whatever this individual guy is called
	
//friend class FEBattleField;
};