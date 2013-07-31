#include <stdio.h>
#include "game.hpp"

//======================================================================


void fired::MapGenerator::generate() {
	sizeX = 200;
	sizeY = 200;

	tiles = new fired::MapTile*[sizeX];
	for (int i = 0; i < sizeX; i++)
		tiles[i] = new fired::MapTile[sizeY];


	for (int i = 0; i < sizeX; i++) for (int j = 0; j < sizeY; j++)
		tiles[i][j].tileset = 0;


	// Test map generation
	for (int i = 0; i < 19; i++) 
		for (int j = 0; j < 200; j++)
			tiles[j][199-i].tileset = 2;

		for (int j = 0; j < 200; j++)
			tiles[j][180].tileset = 1;

	for (int i = 65; i < 200; i++) tiles[i][180].tileset = 1;
	for (int i = 75; i < 200; i++) tiles[i][179].tileset = 1;
	
	for (int i = 100; i < 200; i++) tiles[i][178].tileset = 1;
	for (int i = 100; i < 200; i++) tiles[i][177].tileset = 1;

	for (int i = 125; i < 200; i++) tiles[i][176].tileset = 1;
	for (int i = 125; i < 200; i++) tiles[i][175].tileset = 1;
	for (int i = 125; i < 200; i++) tiles[i][174].tileset = 1;
	
	for (int i = 150; i < 200; i++) tiles[i][173].tileset = 1;
	for (int i = 150; i < 200; i++) tiles[i][172].tileset = 1;
	for (int i = 150; i < 200; i++) tiles[i][171].tileset = 1;
	for (int i = 150; i < 200; i++) tiles[i][170].tileset = 1;
	
	for (int i = 175; i < 200; i++) tiles[i][169].tileset = 1;
	for (int i = 175; i < 200; i++) tiles[i][168].tileset = 1;
	for (int i = 175; i < 200; i++) tiles[i][167].tileset = 1;
	for (int i = 175; i < 200; i++) tiles[i][166].tileset = 1;
	for (int i = 175; i < 200; i++) tiles[i][165].tileset = 1;

	for (int i = 185; i < 200; i++) tiles[i][164].tileset = 1;
	for (int i = 185; i < 200; i++) tiles[i][163].tileset = 1;
	for (int i = 185; i < 200; i++) tiles[i][162].tileset = 1;
	for (int i = 185; i < 200; i++) tiles[i][161].tileset = 1;
	for (int i = 185; i < 200; i++) tiles[i][160].tileset = 1;
	for (int i = 185; i < 200; i++) tiles[i][159].tileset = 1;

	for (int i = 195; i < 200; i++) tiles[i][158].tileset = 1;
	for (int i = 195; i < 200; i++) tiles[i][157].tileset = 1;
	for (int i = 195; i < 200; i++) tiles[i][156].tileset = 1;
	for (int i = 195; i < 200; i++) tiles[i][155].tileset = 1;
	for (int i = 195; i < 200; i++) tiles[i][154].tileset = 1;
	for (int i = 195; i < 200; i++) tiles[i][153].tileset = 1;
	for (int i = 195; i < 200; i++) tiles[i][152].tileset = 1;

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
	fwrite(&sizeX, sizeof(int), 1, fp);
	fwrite(&sizeY, sizeof(int), 1, fp);

	for (int i = 0; i < sizeX; i++)
		for (int j = 0; j < sizeY; j++) {
			fwrite(&tiles[i][j], sizeof(fired::MapTile), 1, fp);
		}

	fclose(fp);
}
