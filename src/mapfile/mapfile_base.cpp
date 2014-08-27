/***********************************************************************
     * File       : mapfile_base.cpp
     * Created    : Aug 27, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * mapLoad

***********************************************************************/
void mapLoad(fired::Map *map, const char* filename) {
	FILE *fp = fopen(filename, "rb");
	if (!fp) return;

	mapLoadMeta(map, fp);
	mapLoadTiles(map, fp);
	mapLoadObjects(map, fp);
	mapLoadSpawns(map, fp);

	fclose(fp);
}



/***********************************************************************
     * mapSave

***********************************************************************/
void mapSave(fired::Map *map, const char* filename) {
	FILE *fp;
	struct stat buf;

	if (stat("data/maps", &buf) == -1) MKDIR("data/maps");
	if ((fp = fopen(filename, "wb")) == NULL) return;

	mapSaveMeta(map, fp);
	mapSaveTiles(map, fp);
	mapSaveObjects(map, fp);
	mapSaveSpawns(map, fp);

	fclose(fp);
}



/***********************************************************************
     * genLoad

***********************************************************************/
void genLoad(fired::MapGenerator *gen, const char* filename) {
	FILE *fp = fopen(filename, "rb");
	if (!fp) return;

	genLoadMeta(gen, fp);
	genLoadTiles(gen, fp);
	genLoadObjects(gen, fp);
	genLoadSpawns(gen, fp);

	fclose(fp);
}



/***********************************************************************
     * genSave

***********************************************************************/
void genSave(fired::MapGenerator *gen, const char* filename) {
	FILE *fp;
	struct stat buf;

	if (stat("data/maps", &buf) == -1) MKDIR("data/maps");
	if ((fp = fopen(filename, "wb")) == NULL) return;

	genSaveMeta(gen, fp);
	genSaveTiles(gen, fp);
	genSaveObjects(gen, fp);
	genSaveSpawns(gen, fp);

	fclose(fp);
}
