/***********************************************************************
     * File       : gen_biome_forest.cpp
     * Created    : Apr 02, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * MapGenerator
     * genForest

***********************************************************************/
void fired::MapGenerator::genForest() {
	genForestMeta();
	genForestPalette();
	genForestCreateLoot();
	genForestLandscape();
	genForestDecors();
	genForestCollectors();
	genForestPlayer();
	genForestSpawns();
	genForestClearLoot();
}



/***********************************************************************
     * MapGenerator
     * genForestPalette

***********************************************************************/
void fired::MapGenerator::genForestPalette() {
	addTileToPalette("stone");
	addTileToPalette("grass");
}



/***********************************************************************
     * MapGenerator
     * genForestMeta

***********************************************************************/
void fired::MapGenerator::genForestMeta() {
	genClear(100, 90);
}



/***********************************************************************
     * MapGenerator
     * genForestLandscape

***********************************************************************/
void fired::MapGenerator::genForestLandscape() {
	setBrush("grass");
	genFill( 0, 50, 99, 89, true);

	setBrush("stone");
	genFill( 0, 42,  5, 49, true);
	genFill(95, 42, 99, 49, true);
}



/***********************************************************************
     * MapGenerator
     * genForestDecors

***********************************************************************/
void fired::MapGenerator::genForestDecors() {
	addDecor( 7, 41, "tree4");
	addDecor(10, 41, "tree1");
	addDecor(14, 41, "tree4");
	addDecor(18, 42, "tree3");
	addDecor(24, 44, "tree2");
	addDecor(26, 41, "tree1");
	addDecor(32, 45, "tree5");
	addDecor(38, 44, "tree2");
	addDecor(41, 42, "tree3");
	addDecor(44, 41, "tree1");
	addDecor(50, 41, "tree4");
	addDecor(54, 45, "tree5");
	addDecor(57, 44, "tree2");
	addDecor(62, 41, "tree4");
	addDecor(63, 42, "tree3");
	addDecor(68, 45, "tree5");
	addDecor(72, 41, "tree1");
	addDecor(76, 41, "tree4");
	addDecor(79, 41, "tree1");
	addDecor(82, 42, "tree3");
	addDecor(86, 45, "tree5");
	addDecor(90, 44, "tree2");
}



/***********************************************************************
     * MapGenerator
     * genForestCollectors

***********************************************************************/
void fired::MapGenerator::genForestCollectors() {
	addCollector( 2, 40, "chest");
	addCollector(96, 40, "chest");
}



/***********************************************************************
     * MapGenerator
     * genForestPlayer

***********************************************************************/
void fired::MapGenerator::genForestPlayer() {
	setStart(0, 37, 5, 5);
}



/***********************************************************************
     * MapGenerator
     * genForestSpawns

***********************************************************************/
void fired::MapGenerator::genForestSpawns() {
	return;
}



/***********************************************************************
     * MapGenerator
     * genForestCreateLoot

***********************************************************************/
void fired::MapGenerator::genForestCreateLoot() {
	return;
}



/***********************************************************************
     * MapGenerator
     * genForestClearLoot

***********************************************************************/
void fired::MapGenerator::genForestClearLoot() {
	deleteList(forest.loot);
}
