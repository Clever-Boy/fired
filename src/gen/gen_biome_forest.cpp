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
	addCollector( 2, 40, "chest", &forest.loot);
	addCollector(96, 40, "chest", &forest.loot);
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
	addSpawn( 6, 46, 10,  4, mstCritter);
	addSpawn(16, 46, 10,  4, mstCritter);
	addSpawn(26, 46, 10,  4, mstCritter);
	addSpawn(36, 46, 10,  4, mstCritter);
	addSpawn(46, 46, 10,  4, mstCritter);
	addSpawn(56, 46, 10,  4, mstCritter);
	addSpawn(66, 46, 10,  4, mstCritter);
	addSpawn(76, 46, 10,  4, mstCritter);
	addSpawn(86, 46, 10,  4, mstCritter);
}



/***********************************************************************
     * MapGenerator
     * genForestCreateLoot

***********************************************************************/
void fired::MapGenerator::genForestCreateLoot() {
	forest.loot.push_back(new fired::MapLootItem("weapon.minigun", 1, 1, 1.0f));
	forest.loot.push_back(new fired::MapLootItem("ammo.bullet", 200, 200, 1.0f));
	forest.loot.push_back(new fired::MapLootItem("ammo.bullet", 200, 200, 1.0f));
	forest.loot.push_back(new fired::MapLootItem("ammo.bullet", 200, 200, 1.0f));
	forest.loot.push_back(new fired::MapLootItem("ammo.bullet", 200, 200, 1.0f));
	forest.loot.push_back(new fired::MapLootItem("ammo.bullet", 200, 200, 1.0f));
	forest.loot.push_back(new fired::MapLootItem("ammo.bullet", 200, 200, 1.0f));

	forest.loot.push_back(new fired::MapLootItem("weapon.launcher", 1, 1, 1.0f));
	forest.loot.push_back(new fired::MapLootItem("ammo.rocket", 50, 50, 1.0f));
	forest.loot.push_back(new fired::MapLootItem("ammo.rocket", 50, 50, 1.0f));
	forest.loot.push_back(new fired::MapLootItem("ammo.rocket", 50, 50, 1.0f));
	forest.loot.push_back(new fired::MapLootItem("ammo.rocket", 50, 50, 1.0f));
	forest.loot.push_back(new fired::MapLootItem("ammo.rocket", 50, 50, 1.0f));
	forest.loot.push_back(new fired::MapLootItem("ammo.rocket", 50, 50, 1.0f));
}



/***********************************************************************
     * MapGenerator
     * genForestClearLoot

***********************************************************************/
void fired::MapGenerator::genForestClearLoot() {
	deleteList(forest.loot);
}
