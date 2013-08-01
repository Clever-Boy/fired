#include <stdio.h>
#include "game.hpp"

//======================================================================


void fired::MapGenerator::generate() {
	genClear(200, 100);
	genLandscape(0, sizeX, 40);
	genPlayer();

	save("data/maps/test.map");
	deinit();
}

//======================================================================


void fired::MapGenerator::deinit() {
	for (int i = 0; i < sizeX; i++)
		delete tiles[i];

	delete tiles;
}

//======================================================================


void fired::MapGenerator::save(const char* filename) {
	FILE *fp;


	if ((fp = fopen(filename, "w")) == NULL) return;
	fwrite(&startPos, sizeof(startPos), 1, fp);
	fwrite(&sizeX, sizeof(int), 1, fp);
	fwrite(&sizeY, sizeof(int), 1, fp);

	for (int i = 0; i < sizeX; i++)
		for (int j = 0; j < sizeY; j++) {
			fwrite(&tiles[i][j], sizeof(fired::MapTile), 1, fp);
		}

	fclose(fp);
}

//======================================================================


void fired::MapGenerator::genClear(int xSize, int ySize) {
	sizeX = xSize;
	sizeY = ySize;

	tiles = new fired::MapTile*[sizeX];
	for (int i = 0; i < sizeX; i++)
		tiles[i] = new fired::MapTile[sizeY];

	genFill(0, 0, sizeX, sizeY, 0, false);
}

//======================================================================


void fired::MapGenerator::genLandscape(int areaStart, int areaEnd, int horizon) {
	genFill(areaStart, horizon, areaEnd, sizeY, 1, true);
	genFill(areaStart, horizon - 2, areaEnd, horizon, 1, false);

	genFill(areaStart  , horizon - 2, areaStart + 4, horizon, 1, true);
	genFill(areaEnd - 4, horizon - 2, areaEnd      , horizon, 1, true);

	genFill(areaStart + 4, horizon - 1, areaStart + 8, horizon, 1, true);
	genFill(areaEnd - 8  , horizon - 1, areaEnd - 4  , horizon, 1, true);
}

//======================================================================


void fired::MapGenerator::genPlayer() {
	int y = 0;
	startPos.x = (sizeX / 2) * TILE_SIZE;

	while (!tiles[sizeX / 2][y].tileset) y++;
	startPos.y = (y - 3) * TILE_SIZE;
}

//======================================================================


void fired::MapGenerator::genBar(int x, int startHeight, int endHeight, int tileset, bool isWall) {
	for (int j = startHeight; j < endHeight; j++)
		tiles[x][j].tileset = tileset;
}

//======================================================================


void fired::MapGenerator::genFill(int x1, int y1, int x2, int y2, int tileset, bool isWall) {
	for (int i = x1; i < x2; i++) for (int j = y1; j < y2; j++) {
		tiles[i][j].tileset = tileset;
		tiles[i][j].isWall  = isWall;
	}
}
