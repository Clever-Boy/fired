/***********************************************************************
     * File       : gen_biome_forest.hpp
     * Created    : Apr 02, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#ifndef __GEN_BIOME_FOREST
#define __GEN_BIOME_FOREST


struct {
	std::vector<fired::LootItem*> loot;
} forest;


void genForest();
void genForestMeta();
void genForestPalette();
void genForestCreateLoot();
void genForestClearLoot();
void genForestLandscape();
void genForestPlayer();
void genForestSpawns();
void genForestDecors();
void genForestCollectors();

#endif
