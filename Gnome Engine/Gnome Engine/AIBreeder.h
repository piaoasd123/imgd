#pragma once
#include "map.h"
#include "GeneticAI.h"

class AIBreeder :	public Map
{
public:
	AIBreeder(int _stockSize, StatBlock** _idStats, int _numBlocks);
	~AIBreeder(void);
	void resolveGeneration(); //have all existing ais fight and create new ones based on the results
private:
	int currentGeneration;
	int stockSize;
	int numBlocks;
	GeneticAI** breedingStock;
	int* runningScores;
	StatBlock** idStats
};

