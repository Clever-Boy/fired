/***********************************************************************
     * File       : gen_location_city.cpp
     * Created    : Aug 20, 2014
     * Copyright  : (C) 2014 Achpile
     * Author     : Fedosov Alexander
     * Email      : achpile@gmail.com

***********************************************************************/
#include "game.hpp"



/***********************************************************************
     * MapGenerator
     * genLocationCity

***********************************************************************/
void fired::MapGenerator::genLocationCity() {
	genLocationCityMeta();
	genLocationCityPalette();
	genLocationCityLandscape();
	genLocationCityPlayer();
}



/***********************************************************************
     * MapGenerator
     * genLocationCityPalette

***********************************************************************/
void fired::MapGenerator::genLocationCityPalette() {
	addTileToPalette("dirt");
}



/***********************************************************************
     * MapGenerator
     * genLocationCityMeta

***********************************************************************/
void fired::MapGenerator::genLocationCityMeta() {
	genClear(200, 100);
}



/***********************************************************************
     * MapGenerator
     * genLocationCityLandscape

***********************************************************************/
void fired::MapGenerator::genLocationCityLandscape() {
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
     * genLocationCityPlayer

***********************************************************************/
void fired::MapGenerator::genLocationCityPlayer() {
	setStart(170, 35, 8, 5);
}
