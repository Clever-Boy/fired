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
	genMineTunnels();
	genMinePlayer();
}



/***********************************************************************
     * MapGenerator
     * genMinePalette

***********************************************************************/
void fired::MapGenerator::genMinePalette() {
	addTileToPalette("clay");
	addTileToPalette("plank.dark");
}



/***********************************************************************
     * MapGenerator
     * genMineMeta

***********************************************************************/
void fired::MapGenerator::genMineMeta() {
	mine.landscape = random() % 20 + 40;
	mine.tunnels   = random() % 3 + 3;
	mine.width     = random() % 20 + 150;

	mine.tunOffset  = random() % 3 + 2;
	mine.landOffset = random() % 3 + 3;
	mine.midlayer   = random() % 5 + 5;

	mine.lanternDiff = random() % 5 + 20;
	mine.beamDiff    = random() % 5 + 15;

	for (int i = 0; i < mine.tunnels; i++) mine.tunHeight.push_back(random() % 10 + 7);


	sf::Vector2i size(0, 0);

	size.x = mine.width;

	size.y += mine.landscape + mine.landOffset;
	size.y += mine.midlayer;
	for (int i = 0; i < mine.tunnels; i++) size.y += mine.tunHeight[i] + mine.tunOffset * 2 + mine.midlayer;

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
     * genMineTunnels

***********************************************************************/
void fired::MapGenerator::genMineTunnels() {
	sf::IntRect tunRect(mine.tunOffset, mine.landscape + mine.landOffset + mine.midlayer, sizeX - 2 * mine.tunOffset - 1, 2 * mine.tunOffset + mine.tunHeight[0]);

	for (int i = 0; i < mine.tunnels; i++) {
		tunRect.height  = 2 * mine.tunOffset + mine.tunHeight[i];
		genMineTunnel(tunRect);
		tunRect.top    += tunRect.height + mine.midlayer;
	}
}



/***********************************************************************
     * MapGenerator
     * genMineTunnel

***********************************************************************/
void fired::MapGenerator::genMineTunnel(sf::IntRect tunRect) {
	int hi = tunRect.top + random() % (mine.tunOffset);
	int lo = tunRect.top - random() % (mine.tunOffset) + tunRect.height;

	int diff = (lo - hi) / 3;
	genBar(tunRect.left    , hi + diff    , lo - diff    , false);
	genBar(tunRect.left + 1, hi + diff / 2, lo - diff / 2, false);

	int hiLen = 0;
	int loLen = 0;

	int lantern = mine.lanternDiff / 2;
	int beam    = mine.beamDiff / 2;

	for (int x = tunRect.left + 2; x <= tunRect.left + tunRect.width - 2; x++) {
		if (!hiLen) {
			hiLen = random() % 3 + 3;
			if (random() % 2) hi--;
			else              hi++;

			if (hi > tunRect.top + mine.tunOffset)
				hi -= 2;

			if (hi < tunRect.top)
				hi += 2;
		}

		if (!loLen) {
			loLen = random() % 3 + 3;

			if (random() % 2) lo--;
			else              lo++;

			if (lo > tunRect.top + tunRect.height - 1)
				lo -= 2;

			if (lo < tunRect.top + tunRect.height - mine.tunOffset - 1)
				lo += 2;
		}

		hiLen--;
		loLen--;
		lantern++;
		beam++;

		if (lantern == mine.lanternDiff) {
			lantern = 0;
			if (tunRect.left + tunRect.width - x - 1 > mine.lanternDiff / 4)
				addLightSource(x * TILE_SIZE, hi * TILE_SIZE, "lantern");
		}

		if (beam == mine.beamDiff) {
			beam = 0;
			setBrush("plank.dark");
			genBar(x, hi, lo, false);
			setBrush("clay");
		} else
			genBar(x, hi, lo, false);
	}

	diff = (lo - hi) / 3;
	genBar(tunRect.left + tunRect.width - 1, hi + diff / 2, lo - diff / 2, false);
	genBar(tunRect.left + tunRect.width    , hi + diff    , lo - diff    , false);
}



/***********************************************************************
     * MapGenerator
     * genMinePlayer

***********************************************************************/
void fired::MapGenerator::genMinePlayer() {
	/** TEMPORARY LADDER **/
	setEraser();
	genBar(30, 0, sizeY - 1, false);
	genBar(31, 0, sizeY - 1, false);
	genBar(32, 0, sizeY - 1, false);

	int y = 0;
	startPos.x = 20 * TILE_SIZE;

	while (!tiles[20][y].tileset || !tiles[20][y].isWall) y++;
	startPos.y = (y - 4) * TILE_SIZE;
}
