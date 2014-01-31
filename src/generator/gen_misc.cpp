/***********************************************************************
     * File       : gen_misc.cpp
     * Created    : Jan 22, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * MapGenerator
     * genClear

***********************************************************************/
void fired::MapGenerator::genClear(int xSize, int ySize) {
	sizeX = xSize;
	sizeY = ySize;

	tiles = new fired::MapTile*[sizeX];
	for (int i = 0; i < sizeX; i++)
		tiles[i] = new fired::MapTile[sizeY];

	genFill(0, 0, sizeX - 1, sizeY - 1, 0, false);
	decors.clear();
}



/***********************************************************************
     * MapGenerator
     * genBar

***********************************************************************/
void fired::MapGenerator::genBar(int x, int startHeight, int endHeight, int tileset, bool isWall) {
	genFill(x, startHeight, x, endHeight, tileset, isWall);
}



/***********************************************************************
     * MapGenerator
     * genFill

***********************************************************************/
void fired::MapGenerator::genFill(int x1, int y1, int x2, int y2, int tileset, bool isWall) {
	for (int i = x1; i <= x2; i++) for (int j = y1; j <= y2; j++) {
		tiles[i][j].tileset    = tileset;
		tiles[i][j].isWall     = isWall;
		tiles[i][j].isPlatform = false;
	}
}



/***********************************************************************
     * MapGenerator
     * addDecor

***********************************************************************/
void fired::MapGenerator::addDecor(float x, float y, const char *name) {
	decors.push_back(new fired::MapDecor(name, sf::Vector2f(x, y)));
}



/***********************************************************************
     * MapGenerator
     * addCollector

***********************************************************************/
void fired::MapGenerator::addCollector(float x, float y, const char *name) {
	objects.push_back(new fired::BaseMapObjectCollector(name, sf::Vector2f(x, y)));
	((fired::BaseMapObjectCollector*)objects.back())->generateLoot();
}



/***********************************************************************
     * MapGenerator
     * addLightSource

***********************************************************************/
void fired::MapGenerator::addLightSource(float x, float y, const char *name) {
	objects.push_back(new fired::BaseMapObjectLightSource(name, sf::Vector2f(x, y)));
}



/***********************************************************************
     * MapGenerator
     * addPlatform

***********************************************************************/
void fired::MapGenerator::addPlatform(int x, int y, const char *name) {
	addDecor(x * TILE_SIZE, y * TILE_SIZE, name);
	tiles[x][y].isPlatform = true;
}
