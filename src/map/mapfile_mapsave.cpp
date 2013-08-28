#include "game.hpp"

//======================================================================


void mapSaveMeta(fired::Map *map, FILE *fp) {
	fwrite(&map->startPos, sizeof(map->startPos), 1, fp);
	fwrite(&map->sizeX, sizeof(int), 1, fp);
	fwrite(&map->sizeY, sizeof(int), 1, fp);
}

//======================================================================


void mapSaveTiles(fired::Map *map, FILE *fp) {
	fired::MapTile tile;

	for (int i = 0; i < map->sizeX; i++)
		for (int j = 0; j < map->sizeY; j++) {
			tile.tileset = map->tiles[i][j].getIndex();
			tile.isWall  = map->tiles[i][j].isSolid();
			fwrite(&tile, sizeof(tile), 1, fp);
		}
}

//======================================================================


void mapSaveDecors(fired::Map *map, FILE *fp) {
	unsigned int decorCount = map->decors.size();
	fwrite(&decorCount, sizeof(decorCount), 1, fp);

	for (unsigned int i = 0; i < decorCount; i++) {
		fired::MapDecor decor(map->decors[i]->name, map->decors[i]->pos);
		fwrite(&decor, sizeof(decor), 1, fp);
	}
}

//======================================================================


void mapSaveCollectorItems(fired::MapObjectCollector *obj, FILE *fp) {
	std::vector<fired::MapItem*> items;
	unsigned int itemCount;

	for (int i = 0; i < 10; i++) for (int j = 0; j < 5; j++) if (obj->items[i][j] != NULL)
		items.push_back(new fired::MapItem(obj->items[i][j]->type, obj->items[i][j]->count, obj->items[i][j]->name));

	itemCount = items.size();
	fwrite(&itemCount, sizeof(itemCount), 1, fp);

	for (unsigned int j = 0; j < itemCount; j++)
		fwrite(items[j], sizeof(fired::MapItem), 1, fp);
}

//======================================================================


void mapSaveObject(fired::MapObject *obj, FILE *fp) {
	fired::BaseMapObject curObj(obj->decor->name, obj->decor->pos, obj->type);
	fwrite(&curObj, sizeof(curObj), 1, fp);

	switch (curObj.type) {
		case fired::moCollector: {
			fired::MapObjectCollector *collObj = (fired::MapObjectCollector*)obj;
			mapSaveCollectorItems(collObj, fp);
			break;
		}

		case fired::moNone:
			break;
	}
}

//======================================================================


void mapSaveObjects(fired::Map *map, FILE *fp) {
	unsigned int objCount = map->objects.size();
	fwrite(&objCount, sizeof(objCount), 1, fp);

	for (unsigned int i = 0; i < objCount; i++)
		mapSaveObject(map->objects[i], fp);
}
