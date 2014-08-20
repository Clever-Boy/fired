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
	addTileToPalette("grass");
	addTileToPalette("dirt");

	addTileToPalette("brick.snow");
	addTileToPalette("brick.brown");
	addTileToPalette("brick.gray");
	addTileToPalette("brick.red");
	addTileToPalette("brick.old");
	addTileToPalette("brick.stone");
	addTileToPalette("brick.cobble");
	addTileToPalette("brick.clay.gray");
	addTileToPalette("brick.clay.pink");
	addTileToPalette("brick.clay.silver");
	addTileToPalette("brick.clay.white");
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
}



/***********************************************************************
     * MapGenerator
     * genLocationCityPlayer

***********************************************************************/
void fired::MapGenerator::genLocationCityPlayer() {
	setStart(170, 35, 8, 5);
}



/***********************************************************************
     * MapGenerator
     * genLocationCitySetRandomBrush

***********************************************************************/
void fired::MapGenerator::genLocationCitySetRandomBrush() {
	switch (rand() % 11) {
		case  0: setBrush("brick.snow"       ); break;
		case  1: setBrush("brick.brown"      ); break;
		case  2: setBrush("brick.gray"       ); break;
		case  3: setBrush("brick.red"        ); break;
		case  4: setBrush("brick.old"        ); break;
		case  5: setBrush("brick.stone"      ); break;
		case  6: setBrush("brick.cobble"     ); break;
		case  7: setBrush("brick.clay.gray"  ); break;
		case  8: setBrush("brick.clay.pink"  ); break;
		case  9: setBrush("brick.clay.silver"); break;
		case 10: setBrush("brick.clay.white" ); break;
	}
}
