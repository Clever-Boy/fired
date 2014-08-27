/***********************************************************************
     * File       : mapfile_genload.cpp
     * Created    : Aug 27, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * genLoadMeta

***********************************************************************/
void genLoadMeta(fired::MapGenerator *gen, FILE *fp) {
	char biomeName[64];

	fread( biomeName       , sizeof(biomeName)             , 1, fp);
	fread(&gen->startRect  , sizeof(gen->startRect)        , 1, fp);
	fread(&gen->sizeX      , sizeof(int)                   , 1, fp);
	fread(&gen->sizeY      , sizeof(int)                   , 1, fp);
	fread(&gen->worldProps , sizeof(fired::WorldProperties), 1, fp);

	gen->biome = container->getBiome(biomeName);
}



/***********************************************************************
     * genLoadTiles

***********************************************************************/
void genLoadTiles(fired::MapGenerator *gen, FILE *fp) {
	gen->tiles = new fired::MapTile*[gen->sizeX];
	for (int i = 0; i < gen->sizeX; i++)
		gen->tiles[i] = new fired::MapTile[gen->sizeY];

	for (int i = 0; i < gen->sizeX; i++)
		for (int j = 0; j < gen->sizeY; j++)
			fread(&gen->tiles[i][j], sizeof(fired::MapTile), 1, fp);
}



/***********************************************************************
     * genLoadCollectorItems

***********************************************************************/
void genLoadCollectorItems(fired::BaseMapObjectCollector *obj, FILE *fp) {
	unsigned int itemCount;
	fired::MapItem item;

	fread(&itemCount, sizeof(itemCount), 1, fp);
	for (unsigned int j = 0; j < itemCount; j++) {
		fread(&item, sizeof(fired::MapItem), 1, fp);
		obj->items.push_back(new fired::MapItem(item.count, item.id));
	}
}



/***********************************************************************
     * genLoadObject

***********************************************************************/
void genLoadObject(fired::MapGenerator *gen, fired::BaseMapObject obj, FILE *fp) {
	switch (obj.type) {
		case fired::moNone: {
			fired::BaseMapObject *newObj = new fired::BaseMapObject(obj.decorId, obj.pos, obj.type);
			gen->objects.push_back(newObj);
			break;
		}

		case fired::moCollector: {
			fired::BaseMapObjectCollector *collObj = new fired::BaseMapObjectCollector(obj.decorId, obj.pos);
			genLoadCollectorItems(collObj, fp);
			gen->objects.push_back(collObj);
			break;
		}

		case fired::moLightSource: {
			fired::BaseMapObjectLightSource lightObj;
			fread(&lightObj.id, sizeof(lightObj.id), 1, fp);
			gen->objects.push_back(new fired::BaseMapObjectLightSource(lightObj.id, obj.pos));
			break;
		}
	}
}



/***********************************************************************
     * genLoadObjects

***********************************************************************/
void genLoadObjects(fired::MapGenerator *gen, FILE *fp) {
	unsigned int objCount;
	fired::BaseMapObject obj;

	fread(&objCount, sizeof(objCount), 1, fp);
	for (unsigned int i = 0; i < objCount; i++) {
		fread(&obj, sizeof(obj), 1, fp);
		genLoadObject(gen, obj, fp);
	}
}



/***********************************************************************
     * genLoadSpawns

***********************************************************************/
void genLoadSpawns(fired::MapGenerator *gen, FILE *fp) {
	unsigned int spawnsCount;
	fired::MapSpawn spawn;

	fread(&spawnsCount, sizeof(spawnsCount), 1, fp);
	for (unsigned int i = 0; i < spawnsCount; i++) {
		fread(&spawn, sizeof(spawn), 1, fp);
		gen->spawns.push_back(new fired::MapSpawn(spawn.spawn, spawn.type));
	}
}
