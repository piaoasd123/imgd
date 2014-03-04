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

