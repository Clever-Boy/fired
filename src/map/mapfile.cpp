/***********************************************************************
     * File       : mapfile.cpp
     * Created    : Aug 27, 2013
     * Copyright  : (C) 2013 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * mapLoad

***********************************************************************/
void mapLoad(fired::Map *map, const char* filename) {
	FILE *fp = fopen(filename, "r");
	if (!fp) return;

	mapLoadMeta(map, fp);
	mapLoadTiles(map, fp);
	mapLoadDecors(map, fp);
	mapLoadObjects(map, fp);

	fclose(fp);
}



/***********************************************************************
     * mapSave

***********************************************************************/
void mapSave(fired::Map *map, const char* filename) {
	FILE *fp;
	struct stat buf;

	if (stat("data/maps", &buf) == -1) mkdir("data/maps", 0755);
	if ((fp = fopen(filename, "w")) == NULL) return;

	mapSaveMeta(map, fp);
	mapSaveTiles(map, fp);
	mapSaveDecors(map, fp);
	mapSaveObjects(map, fp);

	fclose(fp);
}



/***********************************************************************
     * genSave

***********************************************************************/
void genSave(fired::MapGenerator *gen, const char* filename) {
	FILE *fp;
	struct stat buf;

	if (stat("data/maps", &buf) == -1) mkdir("data/maps", 0755);
	if ((fp = fopen(filename, "w")) == NULL) return;

	genSaveMeta(gen, fp);
	genSaveTiles(gen, fp);
	genSaveDecors(gen, fp);
	genSaveObjects(gen, fp);

	fclose(fp);
}
