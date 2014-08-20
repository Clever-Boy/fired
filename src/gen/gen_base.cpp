/***********************************************************************
     * File       : gen_base.cpp
     * Created    : Jul 31, 2013
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * MapGenerator
     * constructor

***********************************************************************/
fired::MapGenerator::MapGenerator(fired::Biome *_biome, fired::WorldProperties _worldProps) {
	biome = _biome;
	memcpy(&worldProps, &_worldProps, sizeof(fired::WorldProperties));

	if (!strcmp(biome->name, "Building"))  genBuilding();
	if (!strcmp(biome->name, "Mine"))      genMine();
	if (!strcmp(biome->name, "Snow"))      genSnow();
	if (!strcmp(biome->name, "Sewers"))    genSewers();
	if (!strcmp(biome->name, "Castle"))    genCastle();
	if (!strcmp(biome->name, "Cave"))      genCave();
	if (!strcmp(biome->name, "City"))      genCity();
	if (!strcmp(biome->name, "Mountains")) genMountains();
	if (!strcmp(biome->name, "Graveyard")) genGraveyard();
	if (!strcmp(biome->name, "Forest"))    genForest();

	genSave(this, "data/maps/test.map");
}



/***********************************************************************
     * MapGenerator
     * constructor

***********************************************************************/
fired::MapGenerator::MapGenerator(const char *location) {
	char filename[128];
/*
	if (!strcmp(location, "City"))  genLocationCity();
	if (!strcmp(location, "Home"))  genLocationHome();
*/
	snprintf(filename, sizeof(filename), "data/maps/%s.map", location);
	genSave(this, filename);
}



/***********************************************************************
     * MapGenerator
     * destructor

***********************************************************************/
fired::MapGenerator::~MapGenerator() {
	for (int i = 0; i < sizeX; i++)
		delete tiles[i];

	delete tiles;

	deleteList(objects);
	deleteList(palette);
	deleteList(spawns);
}
