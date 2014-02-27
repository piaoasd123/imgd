#include "StdAfx.h"
#include "RogueGame.h"
#include "GraphicsManager.h"
#include "Camera.h"
#include "MapManager.h"
#include "Dungeon.h"
#include "NumWalker.h"
#include "RandomWalker.h"

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
	Dungeon* sampleBattleField = new Dungeon(6, 6);
	sampleBattleField->enter(new NumWalker(), 2, 2);
	sampleBattleField->enter(new RandomWalker(), 4, 4);
	Camera* cam = new Camera(sampleBattleField, 0, 0, 0, 0, 6, 6);
	graph->insert(cam);
	map->activateMap(sampleBattleField);
	map->registerForInput(sampleBattleField);
}