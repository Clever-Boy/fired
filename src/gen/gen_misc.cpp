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

	setEraser();
	genFill(0, 0, sizeX - 1, sizeY - 1, false);
	objects.clear();
}



/***********************************************************************
     * MapGenerator
     * genBar

***********************************************************************/
void fired::MapGenerator::genBar(int x, int startHeight, int endHeight, bool isWall) {
	genFill(x, startHeight, x, endHeight, isWall);
}



/***********************************************************************
     * MapGenerator
     * genFill

***********************************************************************/
void fired::MapGenerator::genFill(int x1, int y1, int x2, int y2, bool isWall) {
	for (int i = x1; i <= x2; i++) for (int j = y1; j <= y2; j++) {
		tiles[i][j].tileset    = brush;
		tiles[i][j].isWall     = isWall;
		tiles[i][j].isPlatform = false;
	}
}



/***********************************************************************
     * MapGenerator
     * addDecor

***********************************************************************/
void fired::MapGenerator::addDecor(float x, float y, const char *name) {
	objects.push_back(new fired::BaseMapObject(container->getDecor(name), sf::Vector2f(x, y), moNone));
}



/***********************************************************************
     * MapGenerator
     * addCollector

***********************************************************************/
void fired::MapGenerator::addCollector(float x, float y, const char *name) {
	objects.push_back(new fired::BaseMapObjectCollector(container->getDecor(name), sf::Vector2f(x, y)));
	((fired::BaseMapObjectCollector*)objects.back())->generateLoot();
}



/***********************************************************************
     * MapGenerator
     * addLightSource

***********************************************************************/
void fired::MapGenerator::addLightSource(float x, float y, const char *name) {
	objects.push_back(new fired::BaseMapObjectLightSource(container->getLight(name), sf::Vector2f(x, y)));
}



/***********************************************************************
     * MapGenerator
     * addPlatform

***********************************************************************/
void fired::MapGenerator::addPlatform(int x, int y, const char *name) {
	addDecor(x * TILE_SIZE, y * TILE_SIZE, name);
	tiles[x][y].isPlatform = true;
}



/***********************************************************************
     * MapGenerator
     * addTileToPalette

***********************************************************************/
void fired::MapGenerator::addTileToPalette(const char *name) {
	int index = container->getTileset(name);
	if (index != -1) palette.push_back(new fired::GenTileset(index, name));
}



/***********************************************************************
     * MapGenerator
     * setBrush

***********************************************************************/
void fired::MapGenerator::setBrush(const char *name) {
	for (unsigned int i = 0; i < palette.size(); i++)
		if (!strcmp(name, palette[i]->name)) {
			brush = palette[i]->ID;
			break;
		}
}



/***********************************************************************
     * MapGenerator
     * setEraser

***********************************************************************/
void fired::MapGenerator::setEraser() {
	brush = 0;
}



/***********************************************************************
     * MapGenerator
     * fillPalette

***********************************************************************/
void fired::MapGenerator::fillPalette() {
	if (!strcmp(biome->name, "City")) genCityPalette();
}
