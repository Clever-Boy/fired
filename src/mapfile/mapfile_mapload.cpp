/***********************************************************************
     * File       : mapfile_mapload.cpp
     * Created    : Aug 27, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * mapLoadMeta

***********************************************************************/
void mapLoadMeta(fired::Map *map, FILE *fp) {
	char biomeName[64];

	fread( biomeName        , sizeof(biomeName)             , 1, fp);
	fread(&map->startRect   , sizeof(map->startRect)        , 1, fp);
	fread(&map->sizeX       , sizeof(int)                   , 1, fp);
	fread(&map->sizeY       , sizeof(int)                   , 1, fp);
	fread(&map->worldProps  , sizeof(fired::WorldProperties), 1, fp);

	map->biome = container->getBiome(biomeName);
}



/***********************************************************************
     * mapLoadTiles

***********************************************************************/
void mapLoadTiles(fired::Map *map, FILE *fp) {
	fired::MapTile tile;

	map->tiles = new fired::Tile*[map->sizeX];
	for (int i = 0; i < map->sizeX; i++)
		map->tiles[i] = new fired::Tile[map->sizeY];

	for (int i = 0; i < map->sizeX; i++)
		for (int j = 0; j < map->sizeY; j++) {
			fread(&tile, sizeof(tile), 1, fp);
			map->tiles[i][j].set(tile.tileset, tile.isWall, tile.isPlatform, i, j);
		}

	map->findTiles(0, 0, map->sizeX, map->sizeY);
	for (int i = 0; i < map->sizeX; i++) for (int j = 0; j < map->sizeY; j++)
		map->tiles[i][j].setTileset();
}



/***********************************************************************
     * mapLoadCollectorItems

***********************************************************************/
void mapLoadCollectorItems(fired::MapObjectCollector *obj, FILE *fp) {
	unsigned int itemCount;
	fired::MapItem item;

	fread(&itemCount, sizeof(itemCount), 1, fp);
	for (unsigned int j = 0; j < itemCount; j++) {
		fread(&item, sizeof(item), 1, fp);
		obj->items[j%10][j/10].base = container->items[item.id];
		obj->items[j%10][j/10].count = item.count;
	}
}



/***********************************************************************
     * mapLoadObject

***********************************************************************/
void mapLoadObject(fired::Map *map, fired::BaseMapObject obj, FILE *fp) {
	switch (obj.type) {
		case fired::moNone: {
			fired::MapObject *newObj = new fired::MapObject(obj.decorId, obj.pos);
			map->objects.push_back(newObj);
			break;
		}

		case fired::moCollector: {
			fired::MapObjectCollector *collObj = new fired::MapObjectCollector(obj.decorId, obj.pos);
			mapLoadCollectorItems(collObj, fp);
			map->objects.push_back(collObj);
			break;
		}

		case fired::moLightSource: {
			fired::BaseMapObjectLightSource lightObj;
			fread(&lightObj.id, sizeof(lightObj.id), 1, fp);
			map->objects.push_back(new fired::MapObjectLightSource(lightObj.id, obj.pos));
			break;
		}
	}
}



/***********************************************************************
     * mapLoadObjects

***********************************************************************/
void mapLoadObjects(fired::Map *map, FILE *fp) {
	unsigned int objCount;
	fired::BaseMapObject obj;

	fread(&objCount, sizeof(objCount), 1, fp);
	for (unsigned int i = 0; i < objCount; i++) {
		fread(&obj, sizeof(obj), 1, fp);
		mapLoadObject(map, obj, fp);
	}
}



/***********************************************************************
     * mapLoadSpawns

***********************************************************************/
void mapLoadSpawns(fired::Map *map, FILE *fp) {
	unsigned int spawnsCount;
	fired::MapSpawn spawn;

	fread(&spawnsCount, sizeof(spawnsCount), 1, fp);
	for (unsigned int i = 0; i < spawnsCount; i++) {
		fread(&spawn, sizeof(spawn), 1, fp);
		map->spawns.push_back(new fired::MapSpawn(spawn.spawn, spawn.type));
	}
}
