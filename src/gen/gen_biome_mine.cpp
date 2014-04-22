/***********************************************************************
     * File       : gen_biome_mine.cpp
     * Created    : Apr 02, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * MapGenerator
     * genMine

***********************************************************************/
void fired::MapGenerator::genMine() {
	genMineMeta();
	genMinePalette();
	genMineLandscape();
	genMinePlayer();
}



/***********************************************************************
     * MapGenerator
     * genMinePalette

***********************************************************************/
void fired::MapGenerator::genMinePalette() {
	addTileToPalette("clay");
	addTileToPalette("sand");
	addTileToPalette("dirt.orange");
	addTileToPalette("stone.cobble");
}



/***********************************************************************
     * MapGenerator
     * genMineMeta

***********************************************************************/
void fired::MapGenerator::genMineMeta() {
	mine.landscape = random() % 20 + 40;
	mine.tunnels   = random() % 3 + 3;
	mine.tunHeight = random() % 5 + 10;
	mine.width     = random() % 20 + 150;

	mine.tunOffset  = random() % 3 + 3;
	mine.landOffset = random() % 3 + 3;
	mine.midlayer   = random() % 5 + 5;

	sf::Vector2i size(0, 0);

	size.x = mine.width;

	size.y += mine.landscape + mine.landOffset;
	size.y += mine.midlayer;
	size.y += mine.tunnels * (mine.tunHeight + mine.tunOffset * 2 + mine.midlayer);

	genClear(size.x, size.y);
}



/***********************************************************************
     * MapGenerator
     * genMineLandscape

***********************************************************************/
void fired::MapGenerator::genMineLandscape() {
	setBrush("clay");

	int planeWidth  = 0;
	int planeHeight = mine.landscape;

	for (int x = 0; x < sizeX; x++) {
		if (!planeWidth) {
			planeWidth = random() % 10 + 10;

			if (random() % 2) planeHeight--;
			else              planeHeight++;

			if (planeHeight > mine.landscape + mine.landOffset)
				planeHeight -= 2;

			if (planeHeight < mine.landscape - mine.landOffset)
				planeHeight += 2;
		}

		planeWidth--;
		genBar(x, planeHeight, sizeY - 1, true);
	}
}



/***********************************************************************
     * MapGenerator
     * genMinePlayer

***********************************************************************/
void fired::MapGenerator::genMinePlayer() {
	int y = 0;
	startPos.x = 20 * TILE_SIZE;

	while (!tiles[sizeX / 2][y].tileset || !tiles[sizeX / 2][y].isWall) y++;
	startPos.y = (y - 3) * TILE_SIZE;
}
