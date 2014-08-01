/***********************************************************************
     * File       : gen_biome_mine.hpp
     * Created    : Apr 02, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __GEN_BIOME_MINE
#define __GEN_BIOME_MINE


struct mineTunnel {
	bool connected;
	std::vector<int> usedUp;
	std::vector<int> usedDown;
	sf::IntRect tunRect;
};


struct mineTunLayer {
	int tunHeight;
	std::vector<mineTunnel*> tunnels;
};


struct {
	int landscape;
	int tunCount;
	int tunMinLen;
	int tunSpace;
	int width;
	int tunOffset;
	int landOffset;
	int midlayer;
	int lanternDiff;
	int beamDiff;

	std::vector<mineTunLayer*> layers;
} mine;


void genMine();
void genMineMeta();
void genMineMetaLayer(mineTunLayer *layer, int height);
void genMinePalette();
void genMineCreateLoot();
void genMineClearLoot();
void genMineLandscape();
void genMineTunnels();
void genMineTunnel(mineTunnel *tun);
void genMineLadders();
void genMinePlayer();
void genMineSpawns();
void genMineClean();

#endif
