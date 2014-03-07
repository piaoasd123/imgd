// Gnome Engine.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#define GNOME

#ifdef GNOME

#include "StopWatch.h"
#include "LogManager.h"
#include "GraphicsManager.h"
#include "CycleManager.h"
#include "Game.h"
#include "CurrentGameInfo.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//Get manager instances
	LogManager* log = LogManager::getInstance();
	GraphicsManager* graph = GraphicsManager::getInstance();
	MapManager* map = MapManager::getInstance();
	CycleManager* cycle = CycleManager::getInstance();
	//Initialize managers
	log->startUp();
	graph->startUp();
	map->startUp();
	cycle->startUp();	
	//load and initialize game; this is the only line that changes when the game is switched out
	Game* thisGame = new GAMENAME();
	thisGame->initialize();
	cycle->runGame();
	//shut down gracefully
	cycle->shutDown();
	map->shutDown();
	graph->shutDown();
	log->shutDown();
	return 0;
}

#else

#include "stopWatch.h"
#include "LogManager.h"
#include "GraphicsManager.h"
#include "CycleManager.h"
#include "Game.h"
#include "CurrentGameInfo.h"
#include "Board.h"
#include "Minimax.h"

int _tmain(int argc, _TCHAR* argv[])
{

	//declare name:
	stopWatch *startTiming = new stopWatch(); //needed this to be accessible to the main method
	cout << "IF ConnectX Player" << endl;
	int height, width, length, turn, timeLimit;
	int column, isPop;
	cin >> height >> width >> length >> turn >> timeLimit;
	Board* toupdate = new Board(width, height, length); //also need this accessible
	Movetree* thoughts = new Movetree(toupdate->duplicate(), 0, turn == 1, width, startTiming, timeLimit);
	Move myMove;
	if(turn == 1)
	{
		//take first turn without provokation
		column = (width - 1) / 2; //this is an inelegant way to do that
		isPop = 1;
		
		//deleted references to move struct, only had the struct to make return statements easier


		toupdate->makeMove(column, true, isPop); //update our move tree
		cout << column << ' ' << isPop << endl;
	}
	while (true) //built in infinite loop = good design practice
	{
		cin >> column >> isPop;

		startTiming->startCounting(); //need this immediately
		if(column < 0)
			break;
		toupdate->makeMove(column, false, isPop == 0);
		thoughts->UpdateMovetree(toupdate->duplicate());
		myMove = *thoughts->Minimax();
		column = myMove.column;
		if(myMove.isPop > 0)
			isPop = 0;
		else
			isPop = 1;
		toupdate->makeMove(column, true, isPop);
		cout << column << ' ' << isPop << endl;
	}
}

#endif

