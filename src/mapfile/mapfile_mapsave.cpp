/***********************************************************************
     * File       : mapfile_mapsave.cpp
     * Created    : Aug 27, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * mapSaveMeta

***********************************************************************/
void mapSaveMeta(fired::Map *map, FILE *fp) {
	fwrite( map->biome->name, sizeof(map->biome->name), 1, fp);
	fwrite(&map->startRect  , sizeof(map->startRect)  , 1, fp);
	fwrite(&map->sizeX      , sizeof(int)             , 1, fp);
	fwrite(&map->sizeY      , sizeof(int)             , 1, fp);
}



/***********************************************************************
     * mapSaveTiles

***********************************************************************/
void mapSaveTiles(fired::Map *map, FILE *fp) {
	fired::MapTile tile;

	for (int i = 0; i < map->sizeX; i++)
		for (int j = 0; j < map->sizeY; j++) {
			tile.tileset    = map->tiles[i][j].tileset;
			tile.isWall     = map->tiles[i][j].isWall;
			tile.isPlatform = map->tiles[i][j].isPlatform;
			fwrite(&tile, sizeof(tile), 1, fp);
		}
}



/***********************************************************************
     * mapSaveCollectorItems

***********************************************************************/
void mapSaveCollectorItems(fired::MapObjectCollector *obj, FILE *fp) {
	std::vector<fired::MapItem*> items;
	unsigned int itemCount;

	for (int i = 0; i < 10; i++) for (int j = 0; j < 5; j++) if (obj->items[i][j].base != NULL)
		items.push_back(new fired::MapItem(obj->items[i][j].count, obj->items[i][j].base->ID));

	itemCount = items.size();
	fwrite(&itemCount, sizeof(itemCount), 1, fp);

	for (unsigned int j = 0; j < itemCount; j++)
		fwrite(items[j], sizeof(fired::MapItem), 1, fp);
}



/***********************************************************************
     * mapSaveObject

***********************************************************************/
void mapSaveObject(fired::MapObject *obj, FILE *fp) {
	fired::BaseMapObject curObj(obj->decorId, obj->decor->pos, obj->type);
	fwrite(&curObj, sizeof(curObj), 1, fp);

	switch (curObj.type) {
		case fired::moCollector: {
			fired::MapObjectCollector *collObj = (fired::MapObjectCollector*)obj;
			mapSaveCollectorItems(collObj, fp);
			break;
		}

		case fired::moLightSource: {
			fired::MapObjectLightSource *lightObj = (fired::MapObjectLightSource*)obj;
			fwrite(&lightObj->id, sizeof(lightObj->id), 1, fp);
			break;
		}

		case fired::moNone:
			break;
	}
}



/***********************************************************************
     * mapSaveObjects

***********************************************************************/
void mapSaveObjects(fired::Map *map, FILE *fp) {
	unsigned int objCount = map->objects.size();
	fwrite(&objCount, sizeof(objCount), 1, fp);

	for (unsigned int i = 0; i < objCount; i++)
		mapSaveObject(map->objects[i], fp);
}



/***********************************************************************
     * mapSaveSpawns

***********************************************************************/
void mapSaveSpawns(fired::Map *map, FILE *fp) {
	unsigned int spawnsCount = map->spawns.size();
	fwrite(&spawnsCount, sizeof(spawnsCount), 1, fp);

	for (unsigned int i = 0; i < spawnsCount; i++)
		fwrite(&map->spawns[i], sizeof(sf::IntRect), 1, fp);
}
