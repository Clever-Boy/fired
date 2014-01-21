#include "game.hpp"

//======================================================================


fired::MapGenerator::MapGenerator() {
	generate();
}

//======================================================================


fired::MapGenerator::~MapGenerator() {
	for (int i = 0; i < sizeX; i++)
		delete tiles[i];

	delete tiles;

	deleteList(decors);
	deleteList(objects);
}

//======================================================================


void fired::MapGenerator::generate() {
	genClear(200, 100);
	genLandscape(0, sizeX, 40);
	genDecors();
	genPlatforms();
	genCollectors();
	genPlayer();

	genSave(this, "data/maps/test.map");
}

//======================================================================


void fired::MapGenerator::genClear(int xSize, int ySize) {
	sizeX = xSize;
	sizeY = ySize;

	tiles = new fired::MapTile*[sizeX];
	for (int i = 0; i < sizeX; i++)
		tiles[i] = new fired::MapTile[sizeY];

	genFill(0, 0, sizeX, sizeY, 0, false);
	decors.clear();
}

//======================================================================


void fired::MapGenerator::genLandscape(int areaStart, int areaEnd, int horizon) {
	genFill(areaStart, horizon, areaEnd, sizeY, 1, true);
	genFill(areaStart, horizon - 2, areaEnd, horizon, 1, false);

	genFill(areaStart  , horizon - 2, areaStart + 4, horizon, 1, true);
	genFill(areaEnd - 4, horizon - 2, areaEnd      , horizon, 1, true);

	genFill(areaStart + 4, horizon - 1, areaStart + 8, horizon, 1, true);
	genFill(areaEnd - 8  , horizon - 1, areaEnd - 4  , horizon, 1, true);

	//Generating testing planes
	genBar(41, horizon - 6, horizon, 2, false);
	genBar(47, horizon - 6, horizon, 2, false);
	genFill(41, horizon - 2, 48, horizon, 2, false);
	genFill(40, horizon - 5, 49, horizon - 4, 4, true);

	genBar(81, horizon - 6, horizon, 2, false);
	genBar(87, horizon - 6, horizon, 2, false);
	genFill(81, horizon - 2, 88, horizon, 2, false);
	genFill(80, horizon - 5, 89, horizon - 4, 4, true);

	//Generating testing house
	genFill(140, horizon - 10, 160, horizon, 3, false);
	genFill(140, horizon, 160, horizon + 1, 3, true);
	genFill(140, horizon - 10, 160, horizon - 9, 3, true);
	genBar(140, horizon - 10, horizon - 5, 3, true);
	genBar(159, horizon - 10, horizon - 5, 3, true);

	genFill(142, horizon - 11, 158, horizon - 10, 3, true);
	genFill(144, horizon - 12, 156, horizon - 11, 3, true);
	genFill(146, horizon - 13, 154, horizon - 12, 3, true);
	genFill(148, horizon - 14, 152, horizon - 13, 3, true);
}

//======================================================================


void fired::MapGenerator::genDecors() {
	decors.push_back(new fired::MapDecor("box", sf::Vector2f(1900, 608)));
	decors.push_back(new fired::MapDecor("box", sf::Vector2f(1932, 608)));
	decors.push_back(new fired::MapDecor("box", sf::Vector2f(1916, 576)));

	decors.push_back(new fired::MapDecor("barrel", sf::Vector2f(2288, 608)));
	decors.push_back(new fired::MapDecor("barrel", sf::Vector2f(2368, 608)));
	decors.push_back(new fired::MapDecor("barrel", sf::Vector2f(2400, 608)));
}

//======================================================================


void fired::MapGenerator::genPlatforms() {
	int x, y = 35;
	for (x = 49; x < 80; x++) {
		decors.push_back(new fired::MapDecor("bridge.metal", sf::Vector2f(x*TILE_SIZE, y*TILE_SIZE)));
		tiles[x][y].isPlatform = true;
	}
}

//======================================================================


void fired::MapGenerator::genCollectors() {
	objects.push_back(new fired::BaseMapObjectCollector("chest", sf::Vector2f(44*TILE_SIZE, 33*TILE_SIZE)));
	((fired::BaseMapObjectCollector*)objects.back())->generateLoot();

	objects.push_back(new fired::BaseMapObjectCollector("chest", sf::Vector2f(84*TILE_SIZE, 33*TILE_SIZE)));
	((fired::BaseMapObjectCollector*)objects.back())->generateLoot();
}

//======================================================================


void fired::MapGenerator::genPlayer() {
	int y = 0;
	startPos.x = (sizeX / 2) * TILE_SIZE;

	while (!tiles[sizeX / 2][y].tileset || !tiles[sizeX / 2][y].isWall) y++;
	startPos.y = (y - 3) * TILE_SIZE;
}

//======================================================================


void fired::MapGenerator::genBar(int x, int startHeight, int endHeight, int tileset, bool isWall) {
	for (int j = startHeight; j < endHeight; j++) {
		tiles[x][j].tileset    = tileset;
		tiles[x][j].isWall     = isWall;
		tiles[x][j].isPlatform = false;
	}
}

//======================================================================


void fired::MapGenerator::genFill(int x1, int y1, int x2, int y2, int tileset, bool isWall) {
	for (int i = x1; i < x2; i++) for (int j = y1; j < y2; j++) {
		tiles[i][j].tileset    = tileset;
		tiles[i][j].isWall     = isWall;
		tiles[i][j].isPlatform = false;
	}
}
