#pragma once
#include "map.h"
#include "FEUnit.h"

/*
Na:$$$$$$$$
Hp:$$______
Mi:$$Ac:$$$
De:$$Av:$$$
Mo:$$Ra:$$_
width: 11
Height: 5
*/

class FEStatViewer :	public Map
{
public:
	FEStatViewer(void);
	~FEStatViewer(void);
	virtual ColorChar getColorChar(int x, int y);
	void setUnit(FEUnit* newUnit);
private:
	char* screen;
};

