#include "game.hpp"

//======================================================================


void genSaveMeta(fired::MapGenerator *gen, FILE *fp) {
	fwrite(&gen->startPos, sizeof(gen->startPos), 1, fp);
	fwrite(&gen->sizeX, sizeof(int), 1, fp);
	fwrite(&gen->sizeY, sizeof(int), 1, fp);
}

//======================================================================


void genSaveTiles(fired::MapGenerator *gen, FILE *fp) {
	for (int i = 0; i < gen->sizeX; i++)
		for (int j = 0; j < gen->sizeY; j++)
			fwrite(&gen->tiles[i][j], sizeof(fired::MapTile), 1, fp);
}

//======================================================================


void genSaveDecors(fired::MapGenerator *gen, FILE *fp) {
	unsigned int decorCount = gen->decors.size();
	fwrite(&decorCount, sizeof(decorCount), 1, fp);
	for (unsigned int i = 0; i < decorCount; i++) fwrite(gen->decors[i], sizeof(fired::MapDecor), 1, fp);
}

//======================================================================


void genSaveCollectorItems(fired::BaseMapObjectCollector *obj, FILE *fp) {
	unsigned int itemCount = obj->items.size();
	fwrite(&itemCount, sizeof(itemCount), 1, fp);

	for (unsigned int j = 0; j < itemCount; j++)
		fwrite(obj->items[j], sizeof(fired::MapItem), 1, fp);
}

//======================================================================


void genSaveObject(fired::BaseMapObject *obj, FILE *fp) {
	fired::BaseMapObject curObj(obj->decorName, obj->pos, obj->type);
	fwrite(&curObj, sizeof(curObj), 1, fp);

	switch (curObj.type) {
		case fired::moCollector: {
			fired::BaseMapObjectCollector *collObj = (fired::BaseMapObjectCollector*)obj;
			genSaveCollectorItems(collObj, fp);
			break;
		}

		case fired::moNone:
			break;
	}
}

//======================================================================


void genSaveObjects(fired::MapGenerator *gen, FILE *fp) {
	unsigned int objCount = gen->objects.size();
	fwrite(&objCount, sizeof(objCount), 1, fp);

	for (unsigned int i = 0; i < objCount; i++)
		genSaveObject(gen->objects[i], fp);
}

