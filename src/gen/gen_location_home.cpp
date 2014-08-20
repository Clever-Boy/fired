/***********************************************************************
     * File       : gen_location_home.cpp
     * Created    : Aug 20, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * MapGenerator
     * genLocationHome

***********************************************************************/
void fired::MapGenerator::genLocationHome() {
	genLocationHomeMeta();
	genLocationHomePalette();
	genLocationHomeLandscape();
	genLocationHomePlayer();
}



/***********************************************************************
     * MapGenerator
     * genLocationHomePalette

***********************************************************************/
void fired::MapGenerator::genLocationHomePalette() {
	addTileToPalette("dirt");
}



/***********************************************************************
     * MapGenerator
     * genLocationHomeMeta

***********************************************************************/
void fired::MapGenerator::genLocationHomeMeta() {
	genClear(200, 100);
}



/***********************************************************************
     * MapGenerator
     * genLocationHomeLandscape

***********************************************************************/
void fired::MapGenerator::genLocationHomeLandscape() {
	setBrush("dirt");
	genFill(0, 40, 199, 99, true);
	genFill(0, 38, 199, 39, false);

	genFill(0  , 38, 3  , 39, true);
	genFill(195, 38, 199, 39, true);

	genFill(4  , 39, 7  , 39, true);
	genFill(191, 39, 194, 39, true);
}



/***********************************************************************
     * MapGenerator
     * genLocationHomePlayer

***********************************************************************/
void fired::MapGenerator::genLocationHomePlayer() {
	setStart(170, 35, 8, 5);
}
