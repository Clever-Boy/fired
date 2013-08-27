#include "game.hpp"

//======================================================================


void mapLoad(fired::Map *map, const char* filename) {
	FILE *fp;
	fired::MapTile tile;


	if ((fp = fopen(filename, "r")) == NULL) return;
	fread(&map->startPos, sizeof(map->startPos), 1, fp);
	fread(&map->sizeX, sizeof(int), 1, fp);
	fread(&map->sizeY, sizeof(int), 1, fp);
	map->mapSize = sf::Vector2i(map->sizeX * TILE_SIZE, map->sizeY * TILE_SIZE);

	map->tiles = new fired::Tile*[map->sizeX];
	for (int i = 0; i < map->sizeX; i++)
		map->tiles[i] = new fired::Tile[map->sizeY];

	for (int i = 0; i < map->sizeX; i++)
		for (int j = 0; j < map->sizeY; j++) {
			fread(&tile, sizeof(tile), 1, fp);
			map->tiles[i][j].set(tile.tileset, tile.isWall, i, j);
		}

	map->findTiles(0, 0, map->sizeX, map->sizeY);
	for (int i = 0; i < map->sizeX; i++) for (int j = 0; j < map->sizeY; j++)
		map->tiles[i][j].setTileset(map->tileset);


	unsigned int decorCount;
	fired::MapDecor decor;

	fread(&decorCount, sizeof(decorCount), 1, fp);
	for (unsigned int i = 0; i < decorCount; i++) {
		fread(&decor, sizeof(decor), 1, fp);
		map->decors.push_back(new fired::Decor(map->world->getDecor(decor.name), decor.pos));
	}

	unsigned int objCount;
	fired::BaseMapObject obj;

	fread(&objCount, sizeof(objCount), 1, fp);
	for (unsigned int i = 0; i < objCount; i++) {
		fread(&obj, sizeof(obj), 1, fp);

		if (obj.type == fired::moNone) map->objects.push_back(new fired::MapObject(new fired::Decor(map->world->getDecor(obj.decorName), obj.pos)));
		if (obj.type == fired::moCollector) {
			map->objects.push_back(new fired::MapObjectCollector(new fired::Decor(map->world->getDecor(obj.decorName), obj.pos)));

			unsigned int itemCount;
			fired::MapItem item;
			fired::MapObjectCollector *collObj = (fired::MapObjectCollector*)map->objects.back();

			fread(&itemCount, sizeof(itemCount), 1, fp);
			for (unsigned int j = 0; j < itemCount; j++) {
				fread(&item, sizeof(item), 1, fp);
				collObj->items[j%10][j/5] = new fired::InventoryItem(&item, map->world);
			}
		}
	}

	fclose(fp);
}

//======================================================================


void mapSave(fired::Map *map, const char* filename) {
	FILE *fp;
	struct stat buf;
	fired::MapTile tile;

	if (stat("data/maps", &buf) == -1) mkdir("data/maps", 0755);
	if ((fp = fopen(filename, "w")) == NULL) return;
	fwrite(&map->startPos, sizeof(map->startPos), 1, fp);
	fwrite(&map->sizeX, sizeof(int), 1, fp);
	fwrite(&map->sizeY, sizeof(int), 1, fp);

	for (int i = 0; i < map->sizeX; i++)
		for (int j = 0; j < map->sizeY; j++) {
			tile.tileset = map->tiles[i][j].getIndex();
			tile.isWall  = map->tiles[i][j].isSolid();
			fwrite(&tile, sizeof(tile), 1, fp);
		}


	unsigned int decorCount = map->decors.size();
	fwrite(&decorCount, sizeof(decorCount), 1, fp);

	for (unsigned int i = 0; i < decorCount; i++) {
		fired::MapDecor decor(map->decors[i]->name, map->decors[i]->pos);
		fwrite(&decor, sizeof(decor), 1, fp);
	}


	unsigned int objCount = map->objects.size();
	fwrite(&objCount, sizeof(objCount), 1, fp);

	for (unsigned int i = 0; i < objCount; i++) {
		fired::BaseMapObject obj(map->objects[i]->decor->name, map->objects[i]->decor->pos, map->objects[i]->type);
		fwrite(&obj, sizeof(obj), 1, fp);
	}

	fclose(fp);
}

//======================================================================


void genSave(fired::MapGenerator *gen, const char* filename) {
	FILE *fp;
	struct stat buf;

	if (stat("data/maps", &buf) == -1) mkdir("data/maps", 0755);
	if ((fp = fopen(filename, "w")) == NULL) return;

	fwrite(&gen->startPos, sizeof(gen->startPos), 1, fp);
	fwrite(&gen->sizeX, sizeof(int), 1, fp);
	fwrite(&gen->sizeY, sizeof(int), 1, fp);

	for (int i = 0; i < gen->sizeX; i++)
		for (int j = 0; j < gen->sizeY; j++) {
			fwrite(&gen->tiles[i][j], sizeof(fired::MapTile), 1, fp);
		}


	unsigned int decorCount = gen->decors.size();
	fwrite(&decorCount, sizeof(decorCount), 1, fp);
	for (unsigned int i = 0; i < decorCount; i++) fwrite(gen->decors[i], sizeof(fired::MapDecor), 1, fp);


	fired::BaseMapObject curObj;
	unsigned int objCount = gen->objects.size();
	fwrite(&objCount, sizeof(objCount), 1, fp);
	for (unsigned int i = 0; i < objCount; i++) {
		curObj = fired::BaseMapObject(gen->objects[i]->decorName, gen->objects[i]->pos, gen->objects[i]->type);
		fwrite(&curObj, sizeof(curObj), 1, fp);

		if (curObj.type == fired::moCollector) {
			fired::BaseMapObjectCollector *collObj = (fired::BaseMapObjectCollector*)gen->objects[i];
			unsigned int itemCount = collObj->items.size();

			fwrite(&itemCount, sizeof(itemCount), 1, fp);
			for (unsigned int j = 0; j < itemCount; j++)
				fwrite(collObj->items[j], sizeof(fired::MapItem), 1, fp);
		}
	}

	fclose(fp);
}

