#include <stdio.h>
#include "game.hpp"

//======================================================================


void fired::MapGenerator::generate() {
	genClear();
	genLandscape();
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


	for (int i = 0; i < sizeX; i++) for (int j = 0; j < sizeY; j++)
		tiles[i][j].tileset = 0;
}

//======================================================================


void fired::MapGenerator::genLandscape() {
	int height = 30;
	int width  = 0;
	int i = 0;

	while (i < sizeX) {
		if (!width) {
			width = 10 + random() % 30;
			height += random() % 7 - 3;
			if (height < 1) height = 1;
		}

		for (int j = sizeY - 1; j > sizeY - height; j--)
			tiles[i][j].tileset = 2;
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
