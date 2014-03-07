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
	FEBattleField* sampleBattleField = new FEBattleField(2, 7, 7, sampleStatViewer);
	int map[49] = {
		0, 0, 0, 0, 0, 0, 0,
		0, 1, 0, 1, 0, 1, 0,
		0, 0, 0, 0, 0, 0, 0,
		0, 1, 0, 1, 0, 1, 0,
		0, 0, 0, 0, 0, 0, 0,
		0, 1, 0, 1, 0, 1, 0,
		0, 0, 0, 0, 0, 0, 0};
	sampleBattleField->InitTerrain(map, 7, 7);
	sampleBattleField->setAI(new SampleFEAI(), 2);
	sampleBattleField->enter(new FEUnit('K', 4, 1, 6, 1, 6, 4, 100, 0, 8, "Lancelot"), 2, 2);
	sampleBattleField->enter(new FEUnit('A', 1, 2, 4, 2, 4, 0, 100, 0, 6, "Galehad "), 2, 4);
	sampleBattleField->enter(new FEUnit('K', 4, 1, 6, 1, 6, 4, 100, 0, 8, "Robin   "), 4, 2);
	sampleBattleField->enter(new FEUnit('A', 1, 2, 4, 2, 4, 0, 100, 0, 6, "William "), 4, 4);
	//sampleBattleField->getCell(2, 2)->tryToMoveToCell(sampleBattleField->getCell(4, 3), FALSE);
	Camera* cam = new Camera(sampleBattleField, 0, 0, -1, -1, 9, 9);
	graph->insert(cam);
	Camera* cam2 = new Camera(sampleStatViewer, 9, 0, 0, 0, 11, 5);
	graph->insert(cam2);
	mapmgr->activateMap(sampleBattleField);
	mapmgr->registerForInput(sampleBattleField);
}