/***********************************************************************
     * File       : gen_biome_mine.hpp
     * Created    : Apr 02, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __GEN_BIOME_MINE
#define __GEN_BIOME_MINE


struct mineTunLayer {
	int tunHeight;
	std::vector<sf::IntRect> tunnels;
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
void genMineLandscape();
void genMineTunnels();
void genMineTunnel(sf::IntRect tunRect);
void genMinePlayer();
void genMineClean();

#endif
