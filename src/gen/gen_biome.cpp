/***********************************************************************
     * File       : gen_biome.cpp
     * Created    : Apr 02, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * MapGenerator
     * genPalette

***********************************************************************/
void fired::MapGenerator::genPalette() {
	if (!strcmp(biome->name, "Building"))  genBuildingPalette();
	if (!strcmp(biome->name, "Mine"))      genMinePalette();
	if (!strcmp(biome->name, "Snow"))      genSnowPalette();
	if (!strcmp(biome->name, "Sewers"))    genSewersPalette();
	if (!strcmp(biome->name, "Castle"))    genCastlePalette();
	if (!strcmp(biome->name, "Cave"))      genCavePalette();
	if (!strcmp(biome->name, "Mountains")) genMountainsPalette();
	if (!strcmp(biome->name, "Graveyard")) genGraveyardPalette();
	if (!strcmp(biome->name, "Forest"))    genForestPalette();
}



/***********************************************************************
     * MapGenerator
     * genBiome

***********************************************************************/
void fired::MapGenerator::genBiome() {
	if (!strcmp(biome->name, "Building"))  genBuilding();
	if (!strcmp(biome->name, "Mine"))      genMine();
	if (!strcmp(biome->name, "Snow"))      genSnow();
	if (!strcmp(biome->name, "Sewers"))    genSewers();
	if (!strcmp(biome->name, "Castle"))    genCastle();
	if (!strcmp(biome->name, "Cave"))      genCave();
	if (!strcmp(biome->name, "Mountains")) genMountains();
	if (!strcmp(biome->name, "Graveyard")) genGraveyard();
	if (!strcmp(biome->name, "Forest"))    genForest();
}
