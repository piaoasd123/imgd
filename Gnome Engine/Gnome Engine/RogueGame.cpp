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
	FEBattleField* sampleBattleField = new FEBattleField(2, 20, 10, sampleStatViewer);
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
	//sampleBattleField->setAI(new SampleFEAI(), 2);

	StatBlock* lancelot_stats = new StatBlock(20, 15, 0, 8, 5, 7, 5, 5, 4, Proficiency());
	StatBlock* galahad_stats = new StatBlock(20, 15, 0, 8, 5, 7, 5, 5, 4, Proficiency());
	StatBlock* william_stats = new StatBlock(15, 13, 0, 5, 6, 8, 9, 5, 5, Proficiency());
	StatBlock* robin_stats = new StatBlock(15, 13, 0, 5, 6, 8, 9, 5, 5, Proficiency());

	FEUnit* lancelot = new FEUnit('K', 4, 1, lancelot_stats, 1, SWORD, 90, 5, "Lancelot");
	FEUnit* william = new FEUnit('A', 4, 1, william_stats, 2, BOW, 80, 5, "William");

	FEUnit* galahad = new FEUnit('K', 1, 2, galahad_stats, 1, SWORD, 90, 5, "Galahad");
	FEUnit* robin = new FEUnit('A', 1, 2, robin_stats, 2, BOW, 80, 5, "Robin");

	sampleBattleField->enter(lancelot, 2, 2);
	sampleBattleField->enter(william, 2, 4);
	sampleBattleField->enter(galahad, 4, 2);
	sampleBattleField->enter(robin, 4, 4);

	sampleBattleField->InitTerrain(map, 10, 20);
	//sampleBattleField->enter(new FEUnit('K', 4, 0, 6, 1, 6, 4, 100, 0, 8, "Lancelot"), 2, 2);
	//sampleBattleField->enter(new FEUnit('A', 1, 1, 4, 2, 4, 0, 100, 0, 6, "Galehad "), 2, 4);
	//sampleBattleField->enter(new FEUnit('K', 4, 0, 6, 1, 6, 4, 100, 0, 8, "Robin   "), 4, 2);
	//sampleBattleField->enter(new FEUnit('A', 1, 1, 4, 2, 4, 0, 100, 0, 6, "William "), 4, 4);
	//sampleBattleField->getCell(2, 2)->tryToMoveToCell(sampleBattleField->getCell(4, 3), FALSE);
	Camera* cam = new Camera(sampleBattleField, 0, 0, -1, -1, 12, 22);
	graph->insert(cam);
	Camera* cam2 = new Camera(sampleStatViewer, 12, 0, 0, 0, 12, 8);
	graph->insert(cam2);
	mapmgr->activateMap(sampleBattleField);
	mapmgr->registerForInput(sampleBattleField);
}
