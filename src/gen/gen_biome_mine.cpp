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
	genMineLadders();
	genMinePlayer();
	genMineClean();
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
	mine.landscape = rand() % 20 + 40;
	mine.tunCount  = rand() % 3 + 3;
	mine.width     = rand() % 200 + 150;
	mine.tunMinLen = rand() % 30 + 45;

	mine.tunOffset  = rand() % 3 + 2;
	mine.tunSpace   = rand() % 10 + 5;
	mine.landOffset = rand() % 3 + 3;
	mine.midlayer   = rand() % 5 + 5;

	mine.lanternDiff = rand() % 5 + 20;
	mine.beamDiff    = rand() % 5 + 15;


	int height = mine.landscape + mine.landOffset + mine.midlayer;
	mineTunLayer *layer;
	for (int i = 0; i < mine.tunCount; i++) {
		layer = new mineTunLayer;
		genMineMetaLayer(layer, height);
		mine.layers.push_back(layer);

		height += 2 * mine.tunOffset + mine.midlayer + layer->tunHeight;
	}


	genClear(mine.width, height);
}



/***********************************************************************
     * MapGenerator
     * genMineMetaLayer

***********************************************************************/
void fired::MapGenerator::genMineMetaLayer(mineTunLayer *layer, int height) {
	mineTunnel* tun;

	layer->tunHeight = rand() % 10 + 7;

	int startX, tunW, tunH, tunC, freeW;
	tunC   = rand() % ((mine.width - 2 * mine.tunSpace) / (mine.tunMinLen + mine.tunSpace)) + 1;
	tunW   = mine.width / tunC;
	startX = mine.tunSpace;

	for (int i = 0; i < tunC; i++) {
		tunH = rand() % 10 + 7;
		if (tunH > layer->tunHeight) tunH = layer->tunHeight;

		tun = new mineTunnel;
		tun->connected = false;
		tun->tunRect = sf::IntRect(startX, height, mine.tunMinLen, layer->tunHeight + 2 * mine.tunOffset);
		layer->tunnels.push_back(tun);

		startX += mine.tunMinLen + mine.tunSpace;
	}

	freeW = mine.width - startX - 1;

	for (int i = 0; i < tunC; i++) {
		tunW = rand() % freeW;
		freeW -= tunW;

		layer->tunnels[i]->tunRect.width += tunW;

		for (int j = i + 1; j < tunC; j++)
			layer->tunnels[j]->tunRect.left += tunW;
	}

	for (int i = 0; i < tunC; i++) {
		tunW = rand() % freeW;
		freeW -= tunW;

		layer->tunnels[i]->tunRect.left += tunW;

		for (int j = i + 1; j < tunC; j++)
			layer->tunnels[j]->tunRect.left += tunW;
	}
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
			planeWidth = rand() % 10 + 10;

			if (rand() % 2) planeHeight--;
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
	for (int i = 0; i < mine.tunCount; i++)
		for (unsigned int j = 0; j < mine.layers[i]->tunnels.size(); j++)
			genMineTunnel(mine.layers[i]->tunnels[j]);
}



/***********************************************************************
     * MapGenerator
     * genMineTunnel

***********************************************************************/
void fired::MapGenerator::genMineTunnel(mineTunnel *tun) {
	int hi = tun->tunRect.top + rand() % (mine.tunOffset);
	int lo = tun->tunRect.top - rand() % (mine.tunOffset) + tun->tunRect.height;

	int diff = (lo - hi) / 3;
	genBar(tun->tunRect.left    , hi + diff    , lo - diff    , false);
	genBar(tun->tunRect.left + 1, hi + diff / 2, lo - diff / 2, false);

	int hiLen = 0;
	int loLen = 0;

	int lantern = mine.lanternDiff / 2;
	int beam    = mine.beamDiff / 2;

	for (int x = tun->tunRect.left + 2; x <= tun->tunRect.left + tun->tunRect.width - 2; x++) {
		if (!hiLen) {
			hiLen = rand() % 3 + 3;
			if (rand() % 2) hi--;
			else            hi++;

			if (hi > tun->tunRect.top + mine.tunOffset)
				hi -= 2;

			if (hi < tun->tunRect.top)
				hi += 2;
		}

		if (!loLen) {
			loLen = rand() % 3 + 3;

			if (rand() % 2) lo--;
			else            lo++;

			if (lo > tun->tunRect.top + tun->tunRect.height - 1)
				lo -= 2;

			if (lo < tun->tunRect.top + tun->tunRect.height - mine.tunOffset - 1)
				lo += 2;
		}

		hiLen--;
		loLen--;
		lantern++;
		beam++;

		if (lantern == mine.lanternDiff) {
			lantern = 0;

			if (tun->tunRect.left + tun->tunRect.width - x - 1 > mine.lanternDiff / 8) {
				tun->usedUp.push_back(x);
				addLightSource(x * TILE_SIZE, hi * TILE_SIZE, "lantern");
			}
		}

		if (beam == mine.beamDiff) {
			beam = 0;
			tun->usedUp.push_back(x);
			tun->usedDown.push_back(x);

			setBrush("plank.dark");
			genBar(x, hi, lo, false);
			setBrush("clay");
		} else
			genBar(x, hi, lo, false);
	}

	diff = (lo - hi) / 3;
	genBar(tun->tunRect.left + tun->tunRect.width - 1, hi + diff / 2, lo - diff / 2, false);
	genBar(tun->tunRect.left + tun->tunRect.width    , hi + diff    , lo - diff    , false);
}



/***********************************************************************
     * MapGenerator
     * genMineLadders

***********************************************************************/
void fired::MapGenerator::genMineLadders() {
	for (int i = 0; i < mine.tunCount; i++)
		for (unsigned int j = 0; j < mine.layers[i]->tunnels.size(); j++)
			genFill(mine.layers[i]->tunnels[j]->tunRect.left+2, 0, mine.layers[i]->tunnels[j]->tunRect.left+4, mine.layers[i]->tunnels[j]->tunRect.top + 5,false);
}



/***********************************************************************
     * MapGenerator
     * genMinePlayer

***********************************************************************/
void fired::MapGenerator::genMinePlayer() {
	int y = 0;
	startPos.x = 20 * TILE_SIZE;

	while (!tiles[20][y].tileset || !tiles[20][y].isWall) y++;
	startPos.y = (y - 4) * TILE_SIZE;
}



/***********************************************************************
     * MapGenerator
     * genMineClean

***********************************************************************/
void fired::MapGenerator::genMineClean() {
	for (unsigned int i = 0; i < mine.layers.size(); i++)
		deleteList(mine.layers[i]->tunnels);

	deleteList(mine.layers);
}
