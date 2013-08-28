#include "game.hpp"

//======================================================================


void mapLoadMeta(fired::Map *map, FILE *fp) {
	fread(&map->startPos, sizeof(map->startPos), 1, fp);
	fread(&map->sizeX, sizeof(int), 1, fp);
	fread(&map->sizeY, sizeof(int), 1, fp);
}

//======================================================================


void mapLoadTiles(fired::Map *map, FILE *fp) {
	fired::MapTile tile;
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
}

//======================================================================


void mapLoadDecors(fired::Map *map, FILE *fp) {
	unsigned int decorCount;
	fired::MapDecor decor;

	fread(&decorCount, sizeof(decorCount), 1, fp);
	for (unsigned int i = 0; i < decorCount; i++) {
		fread(&decor, sizeof(decor), 1, fp);
		map->decors.push_back(new fired::Decor(map->world->getDecor(decor.name), decor.pos));
	}
}

//======================================================================


void mapLoadCollectorItems(fired::Map *map, fired::MapObjectCollector *obj, FILE *fp) {
	unsigned int itemCount;
	fired::MapItem item;

	fread(&itemCount, sizeof(itemCount), 1, fp);
	for (unsigned int j = 0; j < itemCount; j++) {
		fread(&item, sizeof(item), 1, fp);
		obj->items[j%10][j/5] = new fired::InventoryItem(&item, map->world);
	}
}

//======================================================================


void mapLoadObject(fired::Map *map, fired::BaseMapObject obj, FILE *fp) {
	switch (obj.type) {
		case fired::moNone: {
			fired::MapObject *newObj = new fired::MapObject(new fired::Decor(map->world->getDecor(obj.decorName), obj.pos));
			map->objects.push_back(newObj);
			break;
		}

		case fired::moCollector: {
			fired::MapObjectCollector *collObj = new fired::MapObjectCollector(new fired::Decor(map->world->getDecor(obj.decorName), obj.pos));
			mapLoadCollectorItems(map, collObj, fp);
			map->objects.push_back(collObj);
			break;
		}
	}
}

//======================================================================


void mapLoadObjects(fired::Map *map, FILE *fp) {
	unsigned int objCount;
	fired::BaseMapObject obj;

	fread(&objCount, sizeof(objCount), 1, fp);
	for (unsigned int i = 0; i < objCount; i++) {
		fread(&obj, sizeof(obj), 1, fp);
		mapLoadObject(map, obj, fp);
	}
}

