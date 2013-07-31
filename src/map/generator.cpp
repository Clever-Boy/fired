#include <stdio.h>
#include "game.hpp"

//======================================================================


void fired::MapGenerator::generate() {
	genClear();
	genLandscape(0, sizeX, 30, 37, 23);
	genHills(0, sizeX, 30);
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


void fired::MapGenerator::genClear() {
	sizeX = 500;
	sizeY = 100;

	tiles = new fired::MapTile*[sizeX];
	for (int i = 0; i < sizeX; i++)
		tiles[i] = new fired::MapTile[sizeY];

	genFill(0, 0, sizeX, sizeY, 0);
}

//======================================================================


void fired::MapGenerator::genLandscape(int areaStart, int areaEnd, int horizon, int max, int min) {
	int height = horizon;
	int width  = 0;
	int i = areaStart;

	while (i < areaEnd) {
		if (!width) {
			width = 5 + random() % 20;

			if      (height == min) height += random() % 4;
			else if (height == max) height -= random() % 4;
			else     height += random() % 7 - 3;

			if (height < min) height = min;
			if (height > max) height = max;
		}

		genBar(i, sizeY - height, sizeY, 2);
		tiles[i][sizeY - height].tileset = 1;

		width--;
		i++;
	}
}

//======================================================================


void fired::MapGenerator::genPlayer() {
	int y = 0;
	startPos.x = (sizeX / 2) * TILE_SIZE;

	while (!tiles[sizeX / 2][y].tileset) y++;
	startPos.y = (y - 3) * TILE_SIZE;
}

//======================================================================


void fired::MapGenerator::genHills(int areaStart, int areaEnd, int horizon) {
	int count = (areaEnd - areaStart) / 250 + (random() % 3 - 1);
	int area = (areaEnd - areaStart) / count;

	for (int i = 0; i < count; i++)
		genHill(areaStart + i * area, area, 20, horizon);
}

//======================================================================


void fired::MapGenerator::genHill(int areaStart, int areaWidth, int height, int horizon) {
	int curHeight = height + random() % 7 - 3;
	int width = 45 + random() % 11 - 5;
	int start = areaStart + random() % (areaWidth - width - 5);
	int leftSide = width / 4 + random() % 9 - 4;
	int rightSide = width / 4 + random() % 9 - 4;
	int topWidth = (width - leftSide - rightSide) / 2 + random() % 5 - 2;
	int topStart = random() % (width - leftSide - rightSide - topWidth - 1) + 1;
	int lastH = -1;

	for (int i = start; i < start + leftSide; i++) {
		int h = horizon + (i - start) * curHeight / leftSide + random() % 3 - 1;
		if (h < lastH) h = lastH;
		else lastH = h;

		if (tiles[i][sizeY - h + 1].tileset) continue;
		genBar(i, sizeY - h, sizeY, 2);
		tiles[i][sizeY - h].tileset = 1;
	}

	genFill(start + leftSide, sizeY - (horizon + curHeight), start + width - rightSide, sizeY, 2);
	genFill(start + leftSide, sizeY - (horizon + curHeight), start + width - rightSide, sizeY - (horizon + curHeight) + 1, 1);

	genFill(start + leftSide + topStart, sizeY - (horizon + curHeight) - 1, start + leftSide + topStart + topWidth, sizeY - (horizon + curHeight), 1);

	for (int i = start + width - rightSide; i < start + width; i++) {
		int h = horizon + (start + width - i) * curHeight / rightSide + random() % 3 - 1;
		if (h > lastH) h = lastH;
		else lastH = h;

		if (tiles[i][sizeY - h + 1].tileset) continue;
		genBar(i, sizeY - h, sizeY, 2);
		tiles[i][sizeY - h].tileset = 1;
	}
}

//======================================================================


void fired::MapGenerator::genBar(int x, int startHeight, int endHeight, int tileset) {
	for (int j = startHeight; j < endHeight; j++)
		tiles[x][j].tileset = tileset;
}

//======================================================================


void fired::MapGenerator::genFill(int x1, int y1, int x2, int y2, int tileset) {
	for (int i = x1; i < x2; i++) for (int j = y1; j < y2; j++)
		tiles[i][j].tileset = tileset;
}
