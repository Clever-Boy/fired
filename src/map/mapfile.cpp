#include "game.hpp"

//======================================================================


void mapLoad(fired::Map *map, const char* filename) {
	FILE *fp = fopen(filename, "r");
	if (!fp) return;

	mapLoadMeta(map, fp);
	mapLoadTiles(map, fp);
	mapLoadDecors(map, fp);
	mapLoadObjects(map, fp);

	fclose(fp);
}

//======================================================================


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

//======================================================================


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