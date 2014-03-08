#include "StdAfx.h"
#include "AIBreeder.h"


AIBreeder::AIBreeder(int _stockSize, StatBlock** _idStats, int _numBlocks)
{
	currentGeneration = 1;
	stockSize = _stockSize;
	numBlocks = _numBlocks;
	idStats = _idStats;
	breedingStock = new GeneticAI*[stockSize];
	runningScores = new int[stockSize];
	for(int counter = 0; counter < stockSize; counter++)
	{
		breedingStock[counter] = new GeneticAI(idStats, numBlocks);
		runningScores[counter] = 0;
	}
}


AIBreeder::~AIBreeder(void)
{
	//continue here
}
