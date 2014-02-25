#include "StdAfx.h"
#include "RogueGame.h"


RogueGame::RogueGame(void)
{
}


RogueGame::~RogueGame(void)
{
}

/*
void RogueGame::initialize(void)
{
	MapManager* map = MapManager::getInstance();
	GraphicsManager* graph = GraphicsManager::getInstance();
	Map* cXMap = new ConnectXBoard(WIDTH, HEIGHT, LENGTH);
	Camera* cam = new Camera(cXMap, 0, 0, -1, 0, WIDTH + 3, HEIGHT + 3);
	graph->insert(cam);
	map->activateMap(cXMap);
	map->registerForInput(cXMap);
}*/