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
fired::MapGenerator::MapGenerator(fired::Biome *_biome) {
	biome = _biome;

	genClear(200, 100);
	fillPalette();

	if (!strcmp(biome->name, "City")) genCity();

	genSave(this, "data/maps/test.map");
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
}
