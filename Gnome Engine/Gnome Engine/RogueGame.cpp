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
	MapManager* map = MapManager::getInstance();
	GraphicsManager* graph = GraphicsManager::getInstance();
	FEStatViewer* sampleStatViewer = new FEStatViewer();
	FEBattleField* sampleBattleField = new FEBattleField(2, 6, 6, sampleStatViewer);
	sampleBattleField->setAI(new SampleFEAI(), 1);
	sampleBattleField->enter(new FEUnit('K', 4, 0, 6, 1, 6, 4, 100, 0, 8, "Lancelot"), 2, 2);
	sampleBattleField->enter(new FEUnit('A', 1, 1, 4, 2, 4, 0, 100, 0, 6, "Galehad "), 2, 4);
	sampleBattleField->enter(new FEUnit('K', 4, 0, 6, 1, 6, 4, 100, 0, 8, "Robin   "), 4, 2);
	sampleBattleField->enter(new FEUnit('A', 1, 1, 4, 2, 4, 0, 100, 0, 6, "William "), 4, 4);
	Camera* cam = new Camera(sampleBattleField, 0, 0, 0, 0, 6, 6);
	graph->insert(cam);
	Camera* cam2 = new Camera(sampleStatViewer, 6, 0, 0, 0, 11, 5);
	graph->insert(cam2);
	map->activateMap(sampleBattleField);
	map->registerForInput(sampleBattleField);
}