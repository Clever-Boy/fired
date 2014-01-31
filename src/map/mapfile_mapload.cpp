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

	fread(biomeName, sizeof(biomeName), 1, fp);
	fread(&map->startPos, sizeof(map->startPos), 1, fp);
	fread(&map->sizeX, sizeof(int), 1, fp);
	fread(&map->sizeY, sizeof(int), 1, fp);

	map->biome = container->getBiome(biomeName);
}



/***********************************************************************
     * mapLoadTiles

***********************************************************************/
void mapLoadTiles(fired::Map *map, FILE *fp) {
	fired::MapTile tile;
	map->mapSize = sf::Vector2i(map->sizeX * TILE_SIZE, map->sizeY * TILE_SIZE);

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
     * mapLoadDecors

***********************************************************************/
void mapLoadDecors(fired::Map *map, FILE *fp) {
	unsigned int decorCount;
	fired::MapDecor decor;

	fread(&decorCount, sizeof(decorCount), 1, fp);
	for (unsigned int i = 0; i < decorCount; i++) {
		fread(&decor, sizeof(decor), 1, fp);
		map->decors.push_back(new fired::Decor(container->getDecor(decor.name), decor.pos));
	}
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
		obj->items[j%10][j/10].base = container->getItem(item.name);
		obj->items[j%10][j/10].count = item.count;
	}
}



/***********************************************************************
     * mapLoadObject

***********************************************************************/
void mapLoadObject(fired::Map *map, fired::BaseMapObject obj, FILE *fp) {
	switch (obj.type) {
		case fired::moNone: {
			fired::MapObject *newObj = new fired::MapObject(new fired::Decor(container->getDecor(obj.decorName), obj.pos));
			map->objects.push_back(newObj);
			break;
		}

		case fired::moCollector: {
			fired::MapObjectCollector *collObj = new fired::MapObjectCollector(new fired::Decor(container->getDecor(obj.decorName), obj.pos));
			mapLoadCollectorItems(collObj, fp);
			map->objects.push_back(collObj);
			break;
		}

		case fired::moLightSource: {
			fired::BaseMapObjectLightSource lightObj;
			fread(lightObj.name, sizeof(lightObj.name), 1, fp);
			map->objects.push_back(new fired::MapObjectLightSource(container->getLight(lightObj.name), obj.pos));
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


