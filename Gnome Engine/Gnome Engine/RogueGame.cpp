#include "StdAfx.h"
#include "RogueGame.h"
#include "GraphicsManager.h"
#include "Camera.h"
#include "MapManager.h"
#include "FEBattleField.h"
#include "NumWalker.h"
#include "RandomWalker.h"
#include "SampleFEAI.h"

RogueGame::RogueGame(void)
{
}


RogueGame::~RogueGame(void)
{
}

void RogueGame::initialize(void)
{
	MapManager* mapmgr = MapManager::getInstance();
	GraphicsManager* graph = GraphicsManager::getInstance();
	FEStatViewer* sampleStatViewer = new FEStatViewer();
	FEConsole* sampleConsole = new FEConsole(30, 10);
	FEBattleField* sampleBattleField = new FEBattleField(2, 20, 10, sampleStatViewer, sampleConsole);
	int map[200] = {0, 0, 1, 1, 1, 1, 1, 1, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
					0, 0, 1, 0, 0, 0, 0, 1, 0, 0,
					1, 0, 1, 0, 0, 0, 0, 1, 0, 1,
					1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
					1, 0, 1, 0, 0, 0, 0, 1, 0, 1,
					0, 0, 1, 0, 0, 0, 0, 1, 0, 0,
					0, 1, 1, 0, 0, 0, 0, 1, 1, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
					1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
					1, 0, 0, 1, 1, 1, 1, 0, 0, 1,
					1, 0, 0, 1, 1, 1, 1, 0, 0, 1,
					1, 0, 1, 0, 0, 0, 0, 1, 0, 1,
					1, 0, 1, 0, 0, 0, 0, 1, 0, 1,
					1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
					1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
					1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
					1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
					1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	sampleBattleField->setAI(new SampleFEAI(), 2);

	StatBlock* knight_stats = new StatBlock(20, 15, 0, 8, 5, 7, 5, 5, 4, Proficiency());
	StatBlock* archer_stats = new StatBlock(15, 13, 0, 5, 6, 8, 9, 5, 5, Proficiency());

	FEUnit* lancelot = new FEUnit('K', 4, 1, knight_stats, 1, 1, SWORD, 90, 5, "Lancelot");
	FEUnit* william = new FEUnit('A', 4, 1, archer_stats, 2, 2, BOW, 80, 5, "William");

	FEUnit* galahad = new FEUnit('K', 1, 2, knight_stats, 1, 1, SWORD, 90, 5, "Galahad");
	FEUnit* robin = new FEUnit('A', 1, 2, archer_stats, 2, 2, BOW, 80, 5, "Robin");

	sampleBattleField->enter(lancelot, 2, 2);
	sampleBattleField->enter(william, 2, 4);
	sampleBattleField->enter(galahad, 4, 2);
	sampleBattleField->enter(robin, 4, 4);

	sampleBattleField->InitTerrain(map, 10, 20);

	Camera* cam = new Camera(sampleBattleField, 0, 0, -1, -1, 12, 22);
	graph->insert(cam);
	Camera* cam2 = new Camera(sampleStatViewer, 12, 0, 0, 0, 12, 8);
	graph->insert(cam2);
	Camera* cam3 = new Camera(sampleConsole, 12, 8, 0, 0, 30, 10);
	graph->insert(cam3);
	mapmgr->activateMap(sampleBattleField);
	mapmgr->registerForInput(sampleBattleField);
}
