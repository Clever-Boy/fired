/***********************************************************************
     * File       : mapfile_gensave.cpp
     * Created    : Aug 27, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * genSaveMeta

***********************************************************************/
void genSaveMeta(fired::MapGenerator *gen, FILE *fp) {
	fwrite( gen->biome->name, sizeof(gen->biome->name), 1, fp);
	fwrite(&gen->startRect  , sizeof(gen->startRect)  , 1, fp);
	fwrite(&gen->sizeX      , sizeof(int)             , 1, fp);
	fwrite(&gen->sizeY      , sizeof(int)             , 1, fp);
}



/***********************************************************************
     * genSaveTiles

***********************************************************************/
void genSaveTiles(fired::MapGenerator *gen, FILE *fp) {
	for (int i = 0; i < gen->sizeX; i++)
		for (int j = 0; j < gen->sizeY; j++)
			fwrite(&gen->tiles[i][j], sizeof(fired::MapTile), 1, fp);
}



/***********************************************************************
     * genSaveCollectorItems

***********************************************************************/
void genSaveCollectorItems(fired::BaseMapObjectCollector *obj, FILE *fp) {
	unsigned int itemCount = obj->items.size();
	fwrite(&itemCount, sizeof(itemCount), 1, fp);

	for (unsigned int j = 0; j < itemCount; j++)
		fwrite(obj->items[j], sizeof(fired::MapItem), 1, fp);
}



/***********************************************************************
     * genSaveObject

***********************************************************************/
void genSaveObject(fired::BaseMapObject *obj, FILE *fp) {
	fired::BaseMapObject curObj(obj->decorId, obj->pos, obj->type);
	fwrite(&curObj, sizeof(curObj), 1, fp);

	switch (curObj.type) {
		case fired::moCollector: {
			fired::BaseMapObjectCollector *collObj = (fired::BaseMapObjectCollector*)obj;
			genSaveCollectorItems(collObj, fp);
			break;
		}

		case fired::moLightSource: {
			fired::BaseMapObjectLightSource *lightObj = (fired::BaseMapObjectLightSource*)obj;
			fwrite(&lightObj->id, sizeof(lightObj->id), 1, fp);
			break;
		}

		case fired::moNone:
			break;
	}
}



/***********************************************************************
     * genSaveObjects

***********************************************************************/
void genSaveObjects(fired::MapGenerator *gen, FILE *fp) {
	unsigned int objCount = gen->objects.size();
	fwrite(&objCount, sizeof(objCount), 1, fp);

	for (unsigned int i = 0; i < objCount; i++)
		genSaveObject(gen->objects[i], fp);
}



/***********************************************************************
     * genSaveSpawns

***********************************************************************/
void genSaveSpawns(fired::MapGenerator *gen, FILE *fp) {
	unsigned int spawnsCount = gen->spawns.size();
	fwrite(&spawnsCount, sizeof(spawnsCount), 1, fp);

	for (unsigned int i = 0; i < spawnsCount; i++)
		fwrite(gen->spawns[i], sizeof(fired::MapSpawn), 1, fp);
}
